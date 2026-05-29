# -*- coding: utf-8 -*-
"""Worldwide OpenStreetMap regional extracts via Geofabrik (PBF) + GDAL OSM driver.

Selects the smallest set of Geofabrik leaf extracts that cover the project extent,
downloads them to a cache, reads ``.osm.pbf`` with OGR, and writes the same per-layer
GeoPackage schema as :func:`create_qgis_project.add_osm_layers`.

Does not import ``create_qgis_project`` (avoid circular imports). The caller passes
``layer_defs`` and ``attach_fn`` for map styling.
"""

from __future__ import annotations

import json
import re
import time
import urllib.error
import urllib.request
from collections import defaultdict
from pathlib import Path

from osgeo import ogr

_OSM_BARRIER_SKIP = frozenset({"entrance", "kerb", "border_control", "yes", "no", "height_restrictor"})

GEOFABRIK_INDEX_URL = "https://download.geofabrik.de/index-v1.json"
INDEX_MAX_AGE_SEC = 86400 * 3  # refresh every 3 days
MAX_LEAF_EXTRACTS = 6
OGR_SCAN_LAYERS = (
    "points",
    "lines",
    "multilinestrings",
    "multipolygons",
    "other_relations",
)


def _plugin_cache_dir() -> Path:
    base = Path.home() / ".cache" / "blaze_loader"
    base.mkdir(parents=True, exist_ok=True)
    return base


def _load_geofabrik_index(log_fn):
    cache = _plugin_cache_dir() / "geofabrik_index_v1.json"
    need_fetch = True
    if cache.exists():
        age = time.time() - cache.stat().st_mtime
        if age < INDEX_MAX_AGE_SEC:
            need_fetch = False
    if need_fetch:
        log_fn(f"Downloading Geofabrik index ({GEOFABRIK_INDEX_URL})...")
        req = urllib.request.Request(
            GEOFABRIK_INDEX_URL,
            headers={"User-Agent": "BlazeLoader-QGIS-Plugin/0.1"},
        )
        with urllib.request.urlopen(req, timeout=120) as resp:
            data = resp.read()
        cache.write_bytes(data)
        log_fn(f"Geofabrik index cached: {cache}")
    return json.loads(cache.read_text(encoding="utf-8"))


def _internal_parent_ids(features: list) -> set:
    children = defaultdict(list)
    for f in features:
        par = f["properties"].get("parent")
        if par:
            children[par].append(f["properties"]["id"])
    return {k for k, v in children.items() if v}


def _qgs_geometry_from_geojson(geom: dict):
    """Build QgsGeometry from a GeoJSON geometry dict (WGS84).

    Uses GDAL ``CreateGeometryFromJson`` so it works on QGIS builds where
    ``QgsGeometry.fromJson`` is not available.
    """
    from qgis.core import QgsGeometry

    if not geom or geom.get("type") is None:
        return QgsGeometry()
    try:
        ogr_g = ogr.CreateGeometryFromJson(json.dumps(geom))
        if ogr_g is None:
            return QgsGeometry()
        wkt = ogr_g.ExportToWkt()
        if not wkt:
            return QgsGeometry()
        q = QgsGeometry.fromWkt(wkt)
        return q if q is not None else QgsGeometry()
    except Exception:
        return QgsGeometry()


def select_geofabrik_extracts(wgs84_bbox, log_fn) -> list[dict]:
    """Return list of {id, name, url, area} for PBF extracts to download.

    ``wgs84_bbox`` is a QgsRectangle in EPSG:4326.
    """
    from qgis.core import QgsGeometry

    data = _load_geofabrik_index(log_fn)
    features = data.get("features") or []
    internal = _internal_parent_ids(features)
    leaf_feats = [f for f in features if f["properties"]["id"] not in internal]

    rect_poly = QgsGeometry.fromRect(wgs84_bbox)
    hits = []
    for f in leaf_feats:
        geom = _qgs_geometry_from_geojson(f.get("geometry") or {})
        if geom.isEmpty() or not geom.intersects(rect_poly):
            continue
        props = f["properties"]
        urls = props.get("urls") or {}
        pbf = urls.get("pbf")
        if not pbf:
            continue
        hits.append(
            {
                "id": props["id"],
                "name": props.get("name", props["id"]),
                "url": pbf,
                "geom": geom,
            }
        )

    if not hits:
        log_fn("Geofabrik: no leaf extract intersects project extent.")
        return []

    if len(hits) <= MAX_LEAF_EXTRACTS:
        log_fn(f"Geofabrik: using {len(hits)} extract(s): {[h['id'] for h in hits]}")
        return hits

    # Too many leaves (e.g. large map spanning Europe): pick one smallest polygon that contains bbox.
    log_fn(
        f"Geofabrik: {len(hits)} leaf extracts intersect extent (cap {MAX_LEAF_EXTRACTS}); "
        "searching for a single enclosing extract..."
    )
    containing = []
    for f in features:
        props = f["properties"]
        urls = props.get("urls") or {}
        pbf = urls.get("pbf")
        if not pbf:
            continue
        geom = _qgs_geometry_from_geojson(f.get("geometry") or {})
        if geom.isEmpty() or not geom.contains(rect_poly):
            continue
        containing.append(
            {
                "id": props["id"],
                "name": props.get("name", props["id"]),
                "url": pbf,
                "geom": geom,
            }
        )
    if containing:
        containing.sort(key=lambda x: x["geom"].area())
        pick = containing[0]
        log_fn(f"Geofabrik: using single enclosing extract {pick['id']} ({pick['name']})")
        return [pick]

    # Fallback: take the MAX_LEAF_EXTRACTS smallest-area intersecting leaves by extract size
    hits.sort(key=lambda x: x["geom"].area())
    picked = hits[:MAX_LEAF_EXTRACTS]
    log_fn("Geofabrik: using first " f"{len(picked)} smallest intersecting extracts: {[h['id'] for h in picked]}")
    return picked


def _download_pbf(url: str, dest: Path, log_fn) -> bool:
    dest.parent.mkdir(parents=True, exist_ok=True)
    log_fn(f"Downloading {dest.name} ...")
    req = urllib.request.Request(url, headers={"User-Agent": "BlazeLoader-QGIS-Plugin/0.1"})
    try:
        with urllib.request.urlopen(req, timeout=600) as resp, open(dest, "wb") as out:
            while True:
                chunk = resp.read(8 * 1024 * 1024)
                if not chunk:
                    break
                out.write(chunk)
        log_fn(f"Saved {dest} ({dest.stat().st_size // (1024 * 1024)} MiB)")
        return True
    except (urllib.error.URLError, urllib.error.HTTPError, OSError) as e:
        log_fn(f"ERROR: download failed {url}: {e}")
        return False


def _bracket_inners(filter_expr: str) -> list[str]:
    return re.findall(r"\[([^\]]+)\]", filter_expr)


def _inner_satisfies(tags: dict, inner: str) -> bool:
    inner = inner.strip()
    m = re.match(r'"([^"]+)"="([^"]*)"', inner)
    if m:
        return str(tags.get(m.group(1))) == m.group(2)
    m = re.match(r'"([^"]+)"~"([^"]*)"', inner)
    if m:
        v = tags.get(m.group(1))
        if v is None:
            return False
        try:
            return re.search(m.group(2), str(v)) is not None
        except re.error:
            return False
    m = re.match(r'"([^"]+)"!~"([^"]*)"', inner)
    if m:
        v = tags.get(m.group(1))
        if v is None:
            return True
        try:
            return re.search(m.group(2), str(v)) is None
        except re.error:
            return True
    m = re.match(r'"([^"]+)"', inner)
    if m:
        return m.group(1) in tags and tags[m.group(1)] not in (None, "")
    return False


def _filter_expr_matches(tags: dict, expr: str) -> bool:
    for inner in _bracket_inners(expr):
        if not _inner_satisfies(tags, inner):
            return False
    return bool(_bracket_inners(expr))


def _spec_or_filter_list(spec: dict) -> list[str]:
    if spec.get("query_batches"):
        out = []
        for b in spec["query_batches"]:
            out.extend(b.get("filters") or [])
        return out
    return list(spec.get("filters") or [])


def tags_match_spec_filters(tags: dict, spec: dict) -> bool:
    flist = _spec_or_filter_list(spec)
    if not flist:
        return False
    return any(_filter_expr_matches(tags, f) for f in flist)


def _allowed_elements(spec: dict) -> frozenset:
    if spec.get("allowed_elements"):
        return frozenset(spec["allowed_elements"])
    if spec.get("query_batches"):
        elems = []
        for b in spec["query_batches"]:
            e = b["element"]
            if e == "rel":
                e = "relation"
            elems.append(e)
        return frozenset(elems)
    e = spec["element"]
    if e == "rel":
        e = "relation"
    return frozenset([e])


def _infer_osm_element(tags: dict, src_lyr: str) -> str:
    if src_lyr == "points":
        return "node"
    if src_lyr == "other_relations":
        return "relation"
    if src_lyr == "multipolygons" and str(tags.get("type")) == "multipolygon":
        return "relation"
    return "way"


def _ogr_layer_matches_spec(src_lyr: str, spec: dict) -> bool:
    geom_kind = spec["geom"]
    allowed = _allowed_elements(spec)
    if "node" in allowed and src_lyr == "points":
        return True
    if "relation" in allowed:
        if src_lyr == "other_relations":
            return True
        if src_lyr == "multipolygons" and geom_kind == "polygon":
            return True
    if "way" in allowed:
        if geom_kind == "line":
            return src_lyr in ("lines", "multilinestrings")
        if geom_kind == "polygon":
            return src_lyr == "multipolygons"
        if geom_kind == "line_or_polygon":
            return src_lyr in ("lines", "multilinestrings", "multipolygons")
    return False


def _tags_from_ogr_feature(feat, lyr_defn) -> dict:
    tags = {}
    for i in range(feat.GetFieldCount()):
        fd = lyr_defn.GetFieldDefn(i)
        name = fd.GetName()
        if name in ("other_tags", "all_tags"):
            continue
        if not feat.IsFieldSet(i):
            continue
        if fd.GetType() in (ogr.OFTString,):
            v = feat.GetFieldAsString(i)
        elif fd.GetType() in (ogr.OFTInteger, ogr.OFTInteger64):
            v = feat.GetFieldAsInteger64(i)
        else:
            v = feat.GetFieldAsString(i)
        if v is None or v == "":
            continue
        tags[name] = v
    ot = feat.GetFieldAsString("other_tags") if feat.GetFieldIndex("other_tags") >= 0 else ""
    if ot:
        for part in re.findall(r'"([^"]+)"=>"([^"]*)"', ot):
            tags[part[0]] = part[1]
        for part in re.findall(r'"([^"]+)"=>([^,]+)', ot):
            if part[0] not in tags:
                tags[part[0]] = part[1].strip('"')
    return tags


def _ogr_osm_id(feat) -> int:
    for name in ("osm_id", "OSM_ID"):
        idx = feat.GetFieldIndex(name)
        if idx >= 0 and feat.IsFieldSet(idx):
            return int(feat.GetFieldAsInteger64(idx))
    for name in ("osm_way_id", "OSM_WAY_ID"):
        idx = feat.GetFieldIndex(name)
        if idx >= 0 and feat.IsFieldSet(idx):
            return int(feat.GetFieldAsInteger64(idx))
    return 0


def _feat_to_qgs_geometry(feat, transform_from_wgs84):
    from qgis.core import QgsGeometry

    ogr_g = feat.GetGeometryRef()
    if ogr_g is None:
        return None
    wkt = ogr_g.ExportToWkt()
    if not wkt:
        return None
    q = QgsGeometry.fromWkt(wkt)
    if q.isEmpty():
        return None
    try:
        q.transform(transform_from_wgs84)
    except Exception:
        return None
    return q


def _geom_compatible(qgs_geom, geom_kind: str) -> bool:
    from qgis.core import QgsWkbTypes

    t = qgs_geom.type()
    if geom_kind == "point":
        return t == QgsWkbTypes.PointGeometry
    if geom_kind == "line":
        return t == QgsWkbTypes.LineGeometry
    if geom_kind == "polygon":
        return t == QgsWkbTypes.PolygonGeometry
    if geom_kind == "line_or_polygon":
        return t in (QgsWkbTypes.LineGeometry, QgsWkbTypes.PolygonGeometry)
    return False


def _set_primary_fields(name, primary_tag, tags, ogr_feat):
    import json as _json

    if "name" in tags:
        ogr_feat.SetField("name", str(tags["name"])[:254])
    if primary_tag == "natural" and name in (
        "osm_water",
        "osm_water_multipolygon",
        "osm_natural_surface",
        "osm_natural_surface_mp",
    ):
        pv = tags.get("natural") or tags.get("water") or tags.get("landuse")
        if pv is not None:
            ogr_feat.SetField(primary_tag, str(pv)[:254])
    elif name == "osm_survey_points":
        sv = tags.get("man_made") or tags.get("historic") or ""
        if sv:
            ogr_feat.SetField(primary_tag, str(sv)[:254])
    elif name == "osm_landform_poly":
        lf = tags.get("natural") or ""
        if lf:
            ogr_feat.SetField(primary_tag, str(lf)[:254])
    elif name == "osm_boundary_protected":
        bv = tags.get("boundary") or tags.get("leisure") or ""
        if bv:
            ogr_feat.SetField(primary_tag, str(bv)[:254])
    elif primary_tag in tags and tags[primary_tag] is not None:
        ogr_feat.SetField(primary_tag, str(tags[primary_tag])[:254])
    try:
        tag_json = _json.dumps(tags, ensure_ascii=False)
        if len(tag_json) > 4096:
            tag_json = tag_json[:4093] + "..."
        ogr_feat.SetField("tags", tag_json)
    except Exception:
        pass


def add_osm_layers_from_regional_extract(
    group,
    extent,
    crs,
    output_dir,
    layer_defs: list,
    attach_fn,
    progress_callback=None,
    log_func=None,
    gpkg_output_path=None,
    parent_window=None,
):
    """Build OSM GPKG from Geofabrik extracts covering ``extent`` and attach to project.

    Args:
        layer_defs: Same structure as ``OSM_LAYER_DEFS`` in ``create_qgis_project``.
        attach_fn: ``attach_osm_gpkg_to_project`` from the caller module.
    """
    from osgeo import osr
    from qgis.core import (
        QgsCoordinateReferenceSystem,
        QgsCoordinateTransform,
        QgsGeometry,
        QgsProject,
        QgsRectangle,
    )

    def local_log(msg):
        if log_func:
            log_func(msg)
        else:
            print(msg)

    def report_progress(msg, pct=None):
        local_log(msg)
        if progress_callback:
            progress_callback(msg, pct)

    wgs84 = QgsCoordinateReferenceSystem("EPSG:4326")
    transform_to_wgs84 = QgsCoordinateTransform(crs, wgs84, QgsProject.instance())
    transform_from_wgs84 = QgsCoordinateTransform(wgs84, crs, QgsProject.instance())

    extent_with_margin = QgsRectangle(extent)
    extent_with_margin.grow(500)
    wgs84_extent = transform_to_wgs84.transformBoundingBox(extent_with_margin)

    buffer_meters = 10000
    buffered_extent = QgsRectangle(extent)
    buffered_extent.grow(buffer_meters)
    clip_rect = QgsGeometry.fromRect(buffered_extent)

    west, south = wgs84_extent.xMinimum(), wgs84_extent.yMinimum()
    east, north = wgs84_extent.xMaximum(), wgs84_extent.yMaximum()
    wgs_rect = QgsRectangle(west, south, east, north)

    if gpkg_output_path:
        gpkg_path = Path(gpkg_output_path)
    else:
        gpkg_path = Path(output_dir) / "osm.gpkg"

    osm_results = {
        "with_data": [],
        "empty": [],
        "failed": [],
        "network_errors": [],
        "total_dupes_skipped": 0,
        "dedup_active": True,
        "geofabrik_extracts": [],
    }

    extracts = select_geofabrik_extracts(wgs_rect, local_log)
    if not extracts:
        local_log("Regional OSM: no Geofabrik extract available for this extent.")
        return osm_results

    cache_dir = _plugin_cache_dir() / "geofabrik_pbf"
    pbf_paths = []
    for ex in extracts:
        safe = re.sub(r"[^a-zA-Z0-9_.-]+", "_", ex["id"])
        dest = cache_dir / f"{safe}-latest.osm.pbf"
        osm_results["geofabrik_extracts"].append({"id": ex["id"], "path": str(dest)})
        if not dest.exists() or dest.stat().st_size < 1024:
            if not _download_pbf(ex["url"], dest, local_log):
                osm_results["network_errors"].append((ex["id"], ex["url"]))
                return osm_results
        pbf_paths.append(dest)

    driver = ogr.GetDriverByName("GPKG")
    if driver is None:
        local_log("ERROR: GPKG driver not available for OSM layers")
        return osm_results

    if gpkg_path.exists():
        try:
            for suffix in ("", "-wal", "-shm"):
                p = Path(str(gpkg_path) + suffix)
                if p.exists():
                    p.unlink()
        except OSError as e:
            local_log(f"WARNING: Could not delete existing {gpkg_path.name}: {e}")

    ds_out = driver.CreateDataSource(str(gpkg_path))
    if ds_out is None:
        local_log(f"ERROR: Could not create OSM GPKG at {gpkg_path}")
        return osm_results

    srs = osr.SpatialReference()
    srs.ImportFromWkt(crs.toWkt())

    qgis_geom_to_ogr = {
        "line": ogr.wkbLineString,
        "polygon": ogr.wkbPolygon,
        "point": ogr.wkbPoint,
    }

    out_layers = {}
    for spec in layer_defs:
        name = spec["name"]
        geom_kind = spec["geom"]
        if geom_kind == "line_or_polygon":
            ogr_geom_type = ogr.wkbUnknown
        else:
            ogr_geom_type = qgis_geom_to_ogr.get(geom_kind)
            if ogr_geom_type is None:
                continue
        allowed = _allowed_elements(spec)
        if allowed <= frozenset({"relation"}) and geom_kind == "polygon":
            ogr_geom_type = ogr.wkbMultiPolygon
        lyr = ds_out.CreateLayer(name, srs, ogr_geom_type)
        if lyr is None:
            continue
        primary_tag = spec["tag"]
        for col_name, col_type, col_width in [
            ("osm_id", ogr.OFTInteger64, None),
            ("osm_type", ogr.OFTString, 16),
            ("name", ogr.OFTString, 254),
            (primary_tag, ogr.OFTString, 254),
            ("tags", ogr.OFTString, None),
        ]:
            fld = ogr.FieldDefn(col_name, col_type)
            if col_width is not None:
                fld.SetWidth(col_width)
            elif col_name == "tags":
                fld.SetWidth(4096)
            lyr.CreateField(fld)
        out_layers[name] = (lyr, spec, ogr_geom_type)

    counts = {name: 0 for name in out_layers}
    seen = set()
    dupes = 0

    def _normalize_mp(qgs_geom, ogr_geom_type):
        if ogr_geom_type != ogr.wkbMultiPolygon:
            return qgs_geom
        from qgis.core import QgsGeometry, QgsWkbTypes

        if qgs_geom.type() == QgsWkbTypes.PolygonGeometry and not qgs_geom.isMultipart():
            return QgsGeometry.fromMultiPolygonXY([qgs_geom.asPolygon()])
        return qgs_geom

    total_pbfs = len(pbf_paths)
    for pi, pbf_path in enumerate(pbf_paths):
        report_progress(f"Reading OSM PBF ({pi + 1}/{total_pbfs}): {pbf_path.name}...", 52)
        # OGR's OSM/PBF reader can otherwise buffer huge numbers of features in-memory
        # (especially from big extracts like NSW), triggering:
        # "Too many features have accumulated in lines layer..."
        # Interleaved reading streams features without that accumulation.
        try:
            from osgeo import gdal

            gdal.SetConfigOption("OGR_INTERLEAVED_READING", "YES")
        except Exception:
            pass

        try:
            ds_in = ogr.OpenEx(str(pbf_path), open_options=["INTERLEAVED_READING=YES"])
        except Exception:
            ds_in = ogr.Open(str(pbf_path))
        if ds_in is None:
            local_log(f"ERROR: OGR could not open {pbf_path}")
            continue
        for src_name in OGR_SCAN_LAYERS:
            lyr_in = ds_in.GetLayerByName(src_name)
            if lyr_in is None:
                continue
            lyr_in.SetSpatialFilterRect(west, south, east, north)
            lyr_in.ResetReading()
            while True:
                feat = lyr_in.GetNextFeature()
                if feat is None:
                    break
                try:
                    tags = _tags_from_ogr_feature(feat, lyr_in.GetLayerDefn())
                    el_type = _infer_osm_element(tags, src_name)
                    osm_id = _ogr_osm_id(feat)
                    qgs_geom = _feat_to_qgs_geometry(feat, transform_from_wgs84)
                    if qgs_geom is None or qgs_geom.isEmpty():
                        continue
                    for out_name, (ogr_lyr, spec, ogr_geom_type) in out_layers.items():
                        if not _ogr_layer_matches_spec(src_name, spec):
                            continue
                        allowed = _allowed_elements(spec)
                        if el_type not in allowed:
                            continue
                        geom_kind = spec["geom"]
                        if not _geom_compatible(qgs_geom, geom_kind):
                            continue
                        if not tags_match_spec_filters(tags, spec):
                            continue
                        if out_name in ("osm_barriers", "osm_barrier_points"):
                            if tags.get("barrier", "") in _OSM_BARRIER_SKIP:
                                continue
                        dedupe_key = (out_name, el_type, osm_id)
                        if dedupe_key in seen:
                            dupes += 1
                            continue
                        if not qgs_geom.intersects(clip_rect):
                            continue
                        gbox = qgs_geom.boundingBox()
                        needs_clip = (
                            gbox.xMinimum() < buffered_extent.xMinimum()
                            or gbox.xMaximum() > buffered_extent.xMaximum()
                            or gbox.yMinimum() < buffered_extent.yMinimum()
                            or gbox.yMaximum() > buffered_extent.yMaximum()
                        )
                        q_write = qgs_geom
                        if needs_clip:
                            clipped = qgs_geom.intersection(clip_rect)
                            if clipped is None or clipped.isEmpty():
                                continue
                            q_write = clipped
                        q_write = _normalize_mp(q_write, ogr_geom_type)
                        ogr_g = ogr.CreateGeometryFromWkt(q_write.asWkt())
                        if ogr_g is None:
                            continue
                        ogr_feat = ogr.Feature(ogr_lyr.GetLayerDefn())
                        ogr_feat.SetGeometry(ogr_g)
                        ogr_feat.SetField("osm_id", int(osm_id) if osm_id else 0)
                        ogr_feat.SetField("osm_type", el_type)
                        _set_primary_fields(out_name, spec["tag"], tags, ogr_feat)
                        if ogr_lyr.CreateFeature(ogr_feat) == ogr.OGRERR_NONE:
                            counts[out_name] += 1
                            seen.add(dedupe_key)
                finally:
                    feat.Destroy()

    ds_out = None

    osm_results["total_dupes_skipped"] = dupes
    for name in out_layers:
        c = counts.get(name, 0)
        local_log(f"Regional OSM {name}: wrote {c} features")
        if c == 0:
            osm_results["empty"].append(name)
        else:
            osm_results["with_data"].append((name, c, 0))

    local_log(
        f"Regional OSM summary: {len(osm_results['with_data'])}/{len(out_layers)} layers with data; "
        f"deduped {dupes} duplicate features"
    )
    local_log(f"OSM GPKG saved to: {gpkg_path}")

    if not osm_results["with_data"]:
        local_log("WARNING: No OSM data from regional extract.")
        return osm_results

    attach_fn(
        group,
        gpkg_path,
        progress_callback=progress_callback,
        log_func=log_func,
    )
    return osm_results
