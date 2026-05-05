<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="1" maxScale="0" minScale="1e+08" readOnly="0" styleCategories="LayerConfiguration|Symbology|Labeling|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{osm-nat-surface-mp}">
      <rule filter="&quot;natural&quot; IN ('sand','beach')" label="Sand / beach" symbol="0"></rule>
      <rule filter="&quot;natural&quot; IN ('rock','shingle','bare_rock')" label="Rock" symbol="1"></rule>
      <rule filter="&quot;natural&quot; = 'grassland'" label="Grassland" symbol="2"></rule>
      <rule filter="&quot;natural&quot; = 'fell'" label="Fell" symbol="3"></rule>
      <rule filter="ELSE" label="Other open" symbol="4"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="fill">
        <layer class="SimpleFill" enabled="1" id="{osm-sand-mp}" locked="0" pass="0">
          <Option type="Map">
            <Option name="color" type="QString" value="255,235,130,220"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="fill">
        <layer class="SimpleFill" enabled="1" id="{osm-rock-mp}" locked="0" pass="0">
          <Option type="Map">
            <Option name="color" type="QString" value="200,200,200,200"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="2" type="fill">
        <layer class="SimpleFill" enabled="1" id="{osm-grassland-mp}" locked="0" pass="0">
          <Option type="Map">
            <Option name="color" type="QString" value="255,243,170,220"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="3" type="fill">
        <layer class="SimpleFill" enabled="1" id="{osm-fell-mp}" locked="0" pass="0">
          <Option type="Map">
            <Option name="color" type="QString" value="255,235,130,200"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="4" type="fill">
        <layer class="SimpleFill" enabled="1" id="{osm-surface-other-mp}" locked="0" pass="0">
          <Option type="Map">
            <Option name="color" type="QString" value="225,238,200,200"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
    </symbols>
  </renderer-v2>
  <labeling type="simple">
    <settings calloutType="simple">
      <text-style allowHtml="0" capitalization="1004" fieldName="name" fontFamily="Arial" fontItalic="1" fontSize="8" fontSizeUnit="Point" fontWeight="50" textColor="80,80,80,255" textOpacity="1">
        <text-buffer bufferColor="250,250,250,255" bufferDraw="1" bufferNoFill="1" bufferOpacity="1" bufferSize="0.35" bufferSizeUnits="MM"></text-buffer>
      </text-style>
      <placement overlapHandling="PreventOverlap" placement="4" priority="2"></placement>
      <rendering drawLabels="1" obstacle="1" scaleMax="60000" scaleMin="0" scaleVisibility="1"></rendering>
    </settings>
  </labeling>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
</qgis>