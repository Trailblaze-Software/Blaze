<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="0" maxScale="0" minScale="1e+08" readOnly="0" styleCategories="LayerConfiguration|Symbology|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{pwt-root}">
      <rule filter="&quot;power&quot; = 'tower'" key="{pwt-tower}" label="High-voltage pylon" symbol="0"></rule>
      <rule filter="ELSE" key="{pwt-pole}" label="Pole" symbol="1"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="marker">
        <layer class="SimpleMarker" enabled="1" id="{pwt-tower-marker}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="color" type="QString" value="0,0,0,255"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="name" type="QString" value="square"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.2"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="size" type="QString" value="1.2"></Option>
            <Option name="size_unit" type="QString" value="MM"></Option>
            <Option name="vertical_anchor_point" type="QString" value="1"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="marker">
        <layer class="SimpleMarker" enabled="1" id="{pwt-pole-marker}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="color" type="QString" value="0,0,0,255"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="name" type="QString" value="circle"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.15"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="size" type="QString" value="0.8"></Option>
            <Option name="size_unit" type="QString" value="MM"></Option>
            <Option name="vertical_anchor_point" type="QString" value="1"></Option>
          </Option>
        </layer>
      </symbol>
    </symbols>
  </renderer-v2>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
</qgis>