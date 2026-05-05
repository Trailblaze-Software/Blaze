<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="1" maxScale="0" minScale="1e+08" readOnly="0" styleCategories="LayerConfiguration|Symbology|Labeling|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="singleSymbol">
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="marker">
        <layer class="SimpleMarker" enabled="1" id="{osm-station-pt}" locked="0" pass="0">
          <Option type="Map">
            <Option name="name" type="QString" value="circle"></Option>
            <Option name="size" type="QString" value="2.2"></Option>
            <Option name="size_unit" type="QString" value="MM"></Option>
            <Option name="color" type="QString" value="255,255,255,255"></Option>
            <Option name="outline_color" type="QString" value="40,40,40,255"></Option>
            <Option name="outline_width" type="QString" value="0.3"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
          </Option>
        </layer>
      </symbol>
    </symbols>
  </renderer-v2>
  <labeling type="simple">
    <settings calloutType="simple">
      <text-style allowHtml="0" capitalization="1004" fieldName="name" fontFamily="Arial" fontSize="8" fontSizeUnit="Point" fontWeight="50" textColor="40,40,40,255" textOpacity="1">
        <text-buffer bufferColor="250,250,250,255" bufferDraw="1" bufferNoFill="1" bufferOpacity="1" bufferSize="0.35" bufferSizeUnits="MM"></text-buffer>
      </text-style>
      <placement dist="2" distUnits="MM" overlapHandling="PreventOverlap" placement="6" preserveRotation="1" priority="6" quadOffset="2"></placement>
      <rendering drawLabels="1" obstacle="1" scaleMax="60000" scaleMin="0" scaleVisibility="1"></rendering>
    </settings>
  </labeling>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
</qgis>