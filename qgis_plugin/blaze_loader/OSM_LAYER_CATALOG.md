# OSM layer catalog (Blaze QGIS loader)

This document lists **candidate OpenStreetMap feature classes** that could be downloaded via Overpass into separate GeoPackage layers. It mirrors the [Map features](https://wiki.openstreetmap.org/wiki/Map_Features) taxonomy. Not everything here should be enabled by default—some tags are extremely dense (every shop), some need relation-only handling, and some overlap (merge vs split is a design choice).

**Legend**

| Status | Meaning |
|--------|---------|
| **Done** | Implemented in `create_qgis_project.py` → `OSM_LAYER_DEFS` |
| **Next** | Good value for orienteering / topo maps; straightforward Overpass |
| **Later** | Useful but heavier, relation-heavy, or needs special rules |
| **Skip** | Usually too noisy, indoor-only, or out of scope |

Geometry column: **W** = way, **N** = node, **R** = relation (often `type=multipolygon` or route).

---

## 1. Highways & access (linear, mostly `highway=*`)

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Motor roads | `highway=motorway/trunk/primary/...` | W | **Done** | `osm_roads` |
| Paths & tracks | `highway=track/path/footway/...` | W | **Done** | `osm_tracks` |
| Link roads | `*_link` variants | W | **Done** | In `osm_roads` |
| Bus / guideway | `highway=bus_guideway`, `busway=*` | W | **Done** | `osm_bus_guideways` |
| Steps / escalator | `highway=steps`, `highway=elevator` | W | **Done** (steps) | Escalator rare outdoors |
| Via ferrata | `highway=via_ferrata` | W | **Done** | `osm_via_ferrata` |
| Proposed / construction | `highway=proposed`, `construction=*` | W | **Later** | Dashed styling |
| Raceway | `highway=raceway` | W | **Later** | Niche |
| Escape / emergency | `highway=escape` | W | **Later** | Rare |
| Rest area / services | `highway=rest_area`, `highway=services` | W/N | **Done** | `osm_rest_areas_pts`, `osm_rest_areas_ways` |
| Turning circle / loop | `highway=turning_circle`, `turning_loop` | N | **Later** | Minor |
| Passing place | `highway=passing_place` | N | **Later** | Rural roads |
| Junction ref | `highway=motorway_junction` | N | **Later** | Label nodes |
| Give way / mini roundabout | `highway=give_way`, `mini_roundabout` | N | **Later** | Very dense in cities |
| Traffic signals / crossings | `highway=traffic_signals`, `crossing=*` | N | **Later** | Dense |
| Street lamps | `highway=street_lamp` | N | **Skip** | Extremely dense |
| Sidewalk as separate way | `highway=footway` + `footway=sidewalk` | W | **Done** | Covered by paths |
| Private / access | `access=private` on ways | attr | **Later** | Filter or label from `tags` |

---

## 2. Railways & guided transport (`railway=*`, `public_transport=*`)

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| All rail ways | `railway=rail/light_rail/subway/tram/...` | W | **Done** | `osm_railways` excludes abandoned/disused/razed |
| Abandoned / disused / razed | `railway=abandoned/disused/razed` | W | **Done** | `osm_rail_abandoned` |
| Narrow gauge / preserved | `railway=narrow_gauge`, `preserved` | W | **Done** | In generic `railway` |
| Station / halt / tram_stop | `railway=station`, `halt`, `tram_stop` | N/W | **Done** | `osm_station_pts`, `osm_station_ways` |
| Subway entrance | `railway=subway_entrance` | N | **Later** | Urban |
| Level crossing | `railway=level_crossing` | N | **Later** | |
| Public transport stop | `public_transport=stop_position`, `platform` | N/W | **Later** | GTFS-like; busy |

---

## 3. Water — linear (`waterway=*`, `natural=coastline`)

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Rivers, streams, drains | `waterway=river/stream/...` | W | **Done** | `osm_waterways` |
| Canal / ditch / drain | `waterway=canal/ditch/drain/...` | W | **Done** | |
| Dam / weir / waterfall | `waterway=dam/weir/waterfall` | W | **Done** | Linear features in `osm_waterways` |
| Fish pass | `waterway=fish_pass` | W | **Later** | |
| Boatyard / fuel | `waterway=boatyard`, `fuel` | N/W | **Later** | |
| Coastline | `natural=coastline` | W | **Done** | `osm_coastlines`; clipped |
| Riverbank (line) | `waterway=riverbank` | W | **Later** | Legacy; some areas still use it |

---

## 4. Water — polygons & relations

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Natural water areas | `natural=water`, `bay`, `wetland`, `pond` | W | **Done** | `osm_water` |
| `water=*` lakes/ponds | `water=lake/pond/reservoir/...` | W | **Done** | |
| Reservoir / basin | `landuse=reservoir/basin/water` | W | **Done** | |
| Multipolygon water | `type=multipolygon` + water tags | R | **Done** | Merged into `osm_water` |
| Swimming / marina / dock | `leisure=swimming_area`, `natural=beach` + harbour | W/R | **Done** | `osm_leisure_water`; beaches also `osm_natural_surface` |
| Wastewater / basin | `man_made=wastewater_basin` | W/R | **Later** | |
| Salt pond | `salt_pond=yes` / landuse | W/R | **Later** | |

---

## 5. Natural / landcover (non-wood)

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Wood / scrub / heath | `natural=wood/scrub/heath` | W | **Done** | `osm_wood` |
| Grassland / sand / beach / rock | `natural=grassland/sand/beach/rock/shingle` | W | **Done** | `osm_natural_surface` (relations may be missing in Overpass mode) |
| Cliff / ridge / arete | `natural=cliff/ridge/arete/fell` | W | **Done** | `osm_landform_lines` (`cliff`/`ridge`/`arete`), `osm_landform_poly` (`fell`) |
| Peak / volcano / saddle | `natural=peak/volcano/saddle` | N | **Done** | `osm_peaks` |
| Cave entrance | `natural=cave_entrance` | N | **Done** | `osm_cave_entrances` |
| Sinkhole / doline | `natural=sinkhole` | N/W | **Later** | |
| Tree row / tree | `natural=tree_row`, `natural=tree` | W/N | **Later** | Trees very dense |
| Glacier | `natural=glacier` | W/R | **Later** | |

---

## 6. Landuse & landform

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Common landuse | `landuse=forest/farmland/...` | W | **Done** | `osm_landuse` |
| Additional values | `landuse=quarry/landfill/military/brownfield/greenfield/allotments` | W | **Done** | In `osm_landuse` |
| Meadow vs farmland | `landuse=meadow/pasture` | W | **Done** | |
| Salt evaporation | `landuse=salt_pond` | W/R | **Later** | |
| Humanitarian | `landuse=depot`, `burial` | W | **Skip** | Niche |

---

## 7. Leisure, sport, tourism

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Parks, reserves, golf, pitch | `leisure=*` (subset) | W | **Done** | `osm_leisure` |
| Track (running) | `leisure=track` | W | **Done** | `osm_leisure` |
| Swimming pool | `leisure=swimming_pool` | W | **Later** | |
| Slipway / marina (leisure) | `leisure=slipway`, overlaps water | W | **Done** | `osm_leisure_water` |
| Tourism | `tourism=viewpoint/information/alpine_hut/wilderness_hut/camp_site` | N/W | **Done** | `osm_tourism_pts`, `osm_tourism_poly` (`picnic_site` included) |
| Picnic site | `tourism=picnic_site` | N/W | **Done** | Same layers |
| Artwork | `tourism=artwork` | N | **Later** | |

---

## 8. Buildings & addresses

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Building footprint | `building=*` | W | **Done** | `osm_buildings` |
| Building:part | `building:part=*` | W | **Later** | 3D; often cluttered |
| Address / entrance | `entrance=*`, `addr:*` | N | **Later** | Dense in urban |

---

## 9. Barriers (`barrier=*`)

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Barrier lines (incl. line fences) | `barrier=*` on ways (open + closed) | W | **Done** | `osm_barriers` (geom: line) + skip list |
| Fenced enclosures (polygons) | `barrier=fence` closed ways + multipolygon relations | W/R | **Done** | `osm_fences` (geom: polygon) |
| All barrier nodes | `barrier=*` on nodes | N | **Done** | `osm_barrier_points` |
| Retaining wall / ditch | `barrier=retaining_wall`, `ditch` | W | **Done** | In `osm_barriers` |
| Trench | `barrier=trench` | W | **Done** | In `osm_barriers` |

---

## 10. Power, pipelines, telecom

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Power lines | `power=line/minor_line` | W | **Done** | `osm_power_lines` |
| Power towers / poles | `power=tower/pole` | N | **Done** | `osm_power_towers_pts` |
| Substation / plant | `power=substation/plant/generator` | W/R | **Partial** | `osm_power_areas` (polygon/line closed ways only; multipolygon relations omitted) |
| Pipeline | `man_made=pipeline` | W | **Done** | `osm_pipeline` |
| Cable / telecom | `man_made=cable`, `telecom=*` | W | **Later** | |

---

## 11. Man-made (selected)

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Bridge / pier | `man_made=bridge`, `pier` | W/R | **Later** | Often implicit in highways |
| Tower / mast / chimney | `man_made=tower/mast/chimney` | N/W | **Done** | `osm_mast_pts` (nodes); ways not modeled separately |
| Survey point / trig | `man_made=survey_point`, `benchmark` | N | **Done** | `osm_survey_points` (incl. `historic=benchmark`) |
| Pipeline station | `man_made=pipeline_marker` | N | **Later** | |
| Silo / storage tank | `man_made=silo/storage_tank` | N/W | **Later** | |
| Cutline / embankment | `man_made=cutline`, `embankment` | W | **Done** | `osm_embankment` |
| Water tower / windmill | `man_made=water_tower/windmill` | N/W | **Later** | |
| Lighthouse | `man_made=lighthouse` | N/W | **Later** | Coastal |

---

## 12. Aeroway

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Runway / taxiway | `aeroway=runway/taxiway/apron` | W | **Later** | |
| Helipad / aerodrome | `aeroway=helipad`, `aerodrome` | N/W | **Later** | |
| Hangar / terminal | `aeroway=hangar/terminal_gate` | W | **Skip** | |

---

## 13. Boundaries & protected areas

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Admin boundary | `boundary=administrative` | W/R | **Later** | Often huge relations |
| Protected area | `boundary=protected_area`, `leisure=nature_reserve` | W/R | **Partial** | `osm_boundary_protected` multipolygon relations; way-mapped reserves often in `osm_leisure` |
| National park / forest border | `boundary=national_park`, `protected_area=*` | W/R | **Partial** | Same layer for `national_park` / `protected_area` relations |
| Maritime | `boundary=maritime` | W/R | **Later** | |

---

## 14. Places & labels (`place=*`, `name=*`)

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Settlements | `place=city/town/village/...` | N | **Done** | `osm_places` |
| Regions | `place=region`, `island`, `islet` | N | **Done** | `osm_place_regions` |
| Locality only | `place=locality` | N | **Done** | |
| Named peaks (without natural=peak) | `name=*` on nodes | — | **Skip** | Need tagging rules |

---

## 15. Route relations (`type=route`)

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Walking / hiking | `route=hiking/foot/walking` | R → W | **Later** | Assemble from member ways |
| Bicycle / MTB | `route=bicycle/mtb` | R → W | **Later** | |
| Horse / ski / climbing | `route=horse/ski/climbing` | R → W | **Later** | |
| Fitness / running | `route=fitness_trail` | R → W | **Later** | |

Requires **merging member ways** into LineString/MultiLineString (no simple `out geom` on relation alone).

---

## 16. Amenities & POIs (dense)

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Parking | `amenity=parking` | W/N | **Later** | Polygons common |
| Shelter / bench / toilet | `amenity=shelter/toilets` | N/W | **Partial** | `osm_remote_amenities` (shelter, toilets nodes; benches **Later**) |
| Drinking water / fountain | `amenity=drinking_water/fountain` | N | **Done** | `osm_remote_amenities` |
| Post box / recycling | `amenity=post_box/recycling` | N | **Skip** | Urban noise |
| All shops | `shop=*` | N | **Skip** | Too dense for topo |

---

## 17. Historic & military

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Archaeological / ruins | `historic=archaeological_site/ruins` | N/W | **Later** | |
| Wayside cross / shrine | `historic=wayside_cross` | N | **Later** | |
| Military land | `military=*`, `landuse=military` | W/R | **Later** | Restricted areas |

---

## 18. Emergency & healthcare

| Topic | Typical tags | Geom | Status | Notes |
|-------|----------------|------|--------|-------|
| Mountain rescue / defibrillator | `emergency=mountain_rescue/defibrillator` | N | **Later** | |
| Hospital / pharmacy | `amenity=hospital/pharmacy` | N/W | **Skip** | Unless requested |

---

## Implemented today (summary)

| Layer id | What it covers |
|----------|----------------|
| `osm_roads` | Motorised `highway` classes |
| `osm_tracks` | Track, path, footway, cycleway, steps, pedestrian |
| `osm_bus_guideways` | `highway=bus_guideway`, `busway=*` |
| `osm_via_ferrata` | `highway=via_ferrata` |
| `osm_rest_areas_pts` | `highway=rest_area`, `services` (nodes) |
| `osm_rest_areas_ways` | `highway=rest_area`, `services` (ways; line or closed polygon) |
| `osm_railways` | `railway=*` ways except `abandoned` / `disused` / `razed` |
| `osm_rail_abandoned` | `railway=abandoned`, `disused`, `razed` |
| `osm_station_pts` | `railway=station`, `halt`, `tram_stop` (nodes) |
| `osm_station_ways` | Same tags on ways (footprint / platform outline) |
| `osm_power_lines` | `power=line`, `minor_line` |
| `osm_power_towers_pts` | `power=tower`, `pole` |
| `osm_pipeline` | `man_made=pipeline` |
| `osm_power_areas` | `power=substation`, `plant`, `generator` (closed ways / outlines) |
| `osm_waterways` | All `waterway=*` ways |
| `osm_coastlines` | `natural=coastline` |
| `osm_water` | Area water (many tag combinations, ways) |
| `osm_water` | Area water (ways + multipolygon relations) |
| `osm_leisure_water` | `leisure=swimming_area`, `slipway`, `marina` |
| `osm_landform_lines` | `natural=cliff`, `ridge`, `arete` |
| `osm_landform_poly` | `natural=fell` |
| `osm_natural_surface` | `natural=grassland`, `sand`, `beach`, `rock`, `shingle` |
| `osm_natural_surface` | Natural surface polygons (ways; relations may be missing in Overpass mode) |
| `osm_boundary_protected` | `boundary=national_park`, `protected_area`; `leisure=nature_reserve` relations |
| `osm_buildings` | `building=*` |
| `osm_wood` | `natural=wood/scrub/heath` |
| `osm_landuse` | Selected `landuse=*` (incl. brownfield, greenfield, allotments) |
| `osm_leisure` | Parks, reserves, golf, playground, pitch, sports_centre, `leisure=track` |
| `osm_barriers` | All `barrier=*` ways as lines (with skip list); includes line fences |
| `osm_fences` | `barrier=fence` polygons (closed ways + multipolygon relations) |
| `osm_barrier_points` | All `barrier=*` nodes (with skip list) |
| `osm_survey_points` | `man_made=survey_point`, `benchmark`; `historic=benchmark` |
| `osm_mast_pts` | `man_made=tower`, `mast`, `chimney` |
| `osm_embankment` | `man_made=cutline`, `embankment` |
| `osm_tourism_pts` | `tourism` viewpoints, huts, camps, picnic, information (nodes) |
| `osm_tourism_poly` | Same subset on area ways |
| `osm_remote_amenities` | `amenity=shelter`, `toilets`, `drinking_water`, `fountain` |
| `osm_cave_entrances` | `natural=cave_entrance` |
| `osm_place_regions` | `place=region`, `island`, `islet` |
| `osm_peaks` | `natural=peak`, `volcano`, `saddle` |
| `osm_places` | Major settlement `place=*` values |

---

## Regional extract (Geofabrik, worldwide)

In the loader dialog, **OSM data source** can be set to **Geofabrik regional extract** instead of the Overpass API. The plugin downloads [Geofabrik’s `index-v1.json`](https://download.geofabrik.de/index-v1.json) (cached under `~/.cache/blaze_loader/`), picks one or more `.osm.pbf` extracts whose polygons intersect the map extent (worldwide), caches PBFS under `~/.cache/blaze_loader/geofabrik_pbf/`, and fills the same GPKG layers via the GDAL OSM driver (`osm_regional_extract.py`). Headless / CI: set `BLAZE_OSM_SOURCE=geofabrik`. Tag matching mirrors Overpass `filters` where possible; very complex multipolygon relations may differ slightly from Overpass `out geom`.

## How to extend the plugin

1. Add a dict entry to **`OSM_LAYER_DEFS`** in `create_qgis_project.py` (`name`, `element`, `filters`, `tag`, `geom`, `visible`, optional `timeout`). Use **`query_batches`** (list of `{element, filters}`) instead of `element` when one logical layer needs multiple Overpass element types (e.g. only nodes). Use **`geom`: `line_or_polygon`** for ways that may be open lines or closed areas (stored in a single GPKG layer with mixed geometry type). The same definitions are used for **Geofabrik** mode in `osm_regional_extract.py`.
2. Add the layer name to **`OSM_RENDER_ORDER`** (in the same file, just above `OSM_LAYER_DEFS`) at the slot you want it to occupy in the OSM group: top of the list = renders on top of the map. The list goes points → lines → polygons by convention, with `osm_trees_pts` deliberately placed under all line layers. Layers missing from the list still get sorted by geometry tier so they render somewhere sensible.
3. Add matching **`styles/osm/<name>.qml`** (optional—fallback symbology still applies).
4. For **new geometry kinds** (e.g. route relations), add a code path in `add_osm_layers` similar to `relation` + `_osm_relation_polygon_geometry`.
5. Prefer **one Overpass round-trip per layer** with multiple `way[...](bbox);` lines in one query; use **higher `timeout`** for heavy layers.

This catalog should be updated whenever new layers are merged so it stays the single checklist for “what OSM can do” in Blaze.
