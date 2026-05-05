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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="line">
        <layer class="SimpleLine" enabled="1" id="{osm-via-ferrata}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="90,0,0,255"></Option>
            <Option name="line_style" type="QString" value="dot"></Option>
            <Option name="line_width" type="QString" value="0.35"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="use_custom_dash" type="QString" value="0"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
    </symbols>
  </renderer-v2>
  <labeling type="simple">
    <settings calloutType="simple">
      <text-style allowHtml="0" capitalization="1004" fieldName="name" fontFamily="Arial" fontItalic="0" fontSize="8" fontSizeUnit="Point" fontWeight="50" textColor="70,0,0,255" textOpacity="1">
        <text-buffer bufferColor="250,250,250,255" bufferDraw="1" bufferNoFill="1" bufferOpacity="1" bufferSize="0.3" bufferSizeUnits="MM"></text-buffer>
      </text-style>
      <placement allowDegraded="0" maxCurvedCharAngleIn="40" maxCurvedCharAngleOut="-40" overlapHandling="PreventOverlap" placement="3" placementFlags="10" preserveRotation="1" priority="6" repeatDistance="250" repeatDistanceUnit="MM"></placement>
      <rendering drawLabels="1" obstacle="1" scaleMax="30000" scaleMin="0" scaleVisibility="1"></rendering>
    </settings>
  </labeling>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
</qgis>