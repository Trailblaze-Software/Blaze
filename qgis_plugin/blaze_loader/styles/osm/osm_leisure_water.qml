<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="1" maxScale="0" minScale="1e+08" readOnly="0" styleCategories="LayerConfiguration|Symbology|Labeling|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{lw-root}">
      <rule filter="&quot;leisure&quot; = 'swimming_pool' OR &quot;leisure&quot; = 'swimming_area'" key="{lw-pool}" label="Swimming pool" symbol="0"></rule>
      <rule filter="ELSE" key="{lw-other}" label="Marina / slipway / other" symbol="1"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="fill">
        <layer class="SimpleFill" enabled="1" id="{lw-pool-fill}" locked="0" pass="0">
          <Option type="Map">
            <Option name="color" type="QString" value="0,158,224,255"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.3"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="fill">
        <layer class="SimpleFill" enabled="1" id="{lw-other-fill}" locked="0" pass="0">
          <Option type="Map">
            <Option name="color" type="QString" value="0,158,224,200"></Option>
            <Option name="outline_color" type="QString" value="0,110,170,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.2"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
    </symbols>
  </renderer-v2>
  <labeling type="simple">
    <settings calloutType="simple">
      <text-style allowHtml="0" capitalization="1004" fieldName="name" fontFamily="Arial" fontItalic="1" fontSize="8" fontSizeUnit="Point" fontWeight="50" textColor="0,75,140,255" textOpacity="1">
        <text-buffer bufferColor="255,255,255,255" bufferDraw="1" bufferNoFill="0" bufferOpacity="0.7" bufferSize="0.35" bufferSizeUnits="MM"></text-buffer>
      </text-style>
      <placement overlapHandling="PreventOverlap" placement="4" priority="4"></placement>
      <rendering drawLabels="1" obstacle="1" scaleMax="60000" scaleMin="0" scaleVisibility="1"></rendering>
    </settings>
  </labeling>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
</qgis>