# Test data

Tiny fixtures checked into git.

- `geokeys_only_gda94_mga55.laz`: the first 1000 points of an NSW Spatial
  Services (ELVIS, CC BY 4.0) tile, as LAS 1.2. Its CRS (EPSG:28355) is stored
  only as GeoTIFF GeoKeys, so reading it needs PROJ's `proj.db` (issue #36).
  Made with `pdal translate in.laz out.laz head --filters.head.count=1000
  --writers.las.minor_version=2 --writers.las.compression=laszip`.
- `Araluen201804-LID2-C3-AHD_7686048_55_0002_0002.laz`: the same points with
  no CRS at all, named like the ELVIS tile they came from, to test inferring
  the CRS from the file name.
