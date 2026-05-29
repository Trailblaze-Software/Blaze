<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="1" maxScale="0" minScale="1e+08" readOnly="0" styleCategories="LayerConfiguration|Symbology|Labeling|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{osm-admin}">
      <rule filter="&quot;boundary&quot;='administrative' AND &quot;admin_level&quot; IN ('2','3','4')" label="National/State" symbol="0"></rule>
      <rule filter="&quot;boundary&quot;='administrative' AND &quot;admin_level&quot; IN ('5','6')" label="Regional" symbol="1"></rule>
      <rule filter="ELSE" label="Local" symbol="2"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="line">
        <layer class="SimpleLine" enabled="1" id="{osm-admin-0}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="60,60,60,255"></Option>
            <Option name="line_style" type="QString" value="dash"></Option>
            <Option name="line_width" type="QString" value="0.6"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="line">
        <layer class="SimpleLine" enabled="1" id="{osm-admin-1}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="80,80,80,255"></Option>
            <Option name="line_style" type="QString" value="dash"></Option>
            <Option name="line_width" type="QString" value="0.45"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="2" type="line">
        <layer class="SimpleLine" enabled="1" id="{osm-admin-2}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="100,100,100,255"></Option>
            <Option name="line_style" type="QString" value="dash"></Option>
            <Option name="line_width" type="QString" value="0.3"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
          </Option>
        </layer>
      </symbol>
    </symbols>
  </renderer-v2>
  <labeling type="simple">
    <settings calloutType="simple">
      <text-style allowHtml="0" capitalization="1004" fieldName="name" fontFamily="Arial" fontItalic="1" fontSize="9" fontSizeUnit="Point" fontWeight="50" textColor="70,70,70,255" textOpacity="0.9">
        <text-buffer bufferColor="255,255,255,255" bufferDraw="1" bufferNoFill="0" bufferOpacity="0.6" bufferSize="0.35" bufferSizeUnits="MM"></text-buffer>
      </text-style>
      <placement maxCurvedCharAngleIn="40" maxCurvedCharAngleOut="-40" overlapHandling="PreventOverlap" placement="3" placementFlags="10" preserveRotation="1" priority="1" repeatDistance="500" repeatDistanceUnit="MM"></placement>
      <rendering drawLabels="1" obstacle="0" scaleMax="1000000" scaleMin="0" scaleVisibility="1"></rendering>
    </settings>
  </labeling>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
</qgis>