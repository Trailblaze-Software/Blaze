# Test data

Small LAS/LAZ fixtures used by the unit tests and CI. Keep files here tiny
(tens of KB): they are checked into git.

- `geokeys_only_gda94_mga55.laz` — first 1000 points of
  `Araluen201804-LID2-C3-AHD_7686048_55_0002_0002.laz` (ELVIS / NSW Spatial
  Services, CC BY 4.0), rewritten as LAS 1.2 point format 3. Its CRS
  (GDA94 / MGA zone 55, EPSG:28355) is stored **only** as GeoTIFF GeoKeys
  (VLRs 34735/34737), with no WKT VLR, matching NSW Spatial Services
  downloads. Turning those keys into a CRS needs PROJ's `proj.db`, which
  makes this file a regression fixture for issue #36. Recreate with:

  ```sh
  pdal translate in.laz geokeys_only_gda94_mga55.laz head \
    --filters.head.count=1000 --writers.las.minor_version=2 \
    --writers.las.dataformat_id=3 --writers.las.compression=laszip \
    --writers.las.forward=scale,offset
  ```
