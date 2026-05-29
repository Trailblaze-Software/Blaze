<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="0" maxScale="0" minScale="1e+08" readOnly="0" styleCategories="LayerConfiguration|Symbology|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{wd-root}">
      <rule filter="&quot;natural&quot; = 'wood'" key="{wd-w}" label="Wood (forest)" symbol="0"></rule>
      <rule filter="&quot;natural&quot; = 'scrub'" key="{wd-s}" label="Scrub" symbol="1"></rule>
      <rule filter="ELSE" key="{wd-o}" label="Heath / other" symbol="2"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="fill">
        <layer class="SimpleFill" enabled="1" id="{wd-wood}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="133,199,159,200"></Option>
            <Option name="outline_color" type="QString" value="0,156,89,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="fill">
        <layer class="SimpleFill" enabled="1" id="{wd-scrub}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="195,227,198,200"></Option>
            <Option name="outline_color" type="QString" value="0,156,89,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="2" type="fill">
        <layer class="SimpleFill" enabled="1" id="{wd-heath}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="225,238,200,200"></Option>
            <Option name="outline_color" type="QString" value="0,156,89,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
    </symbols>
  </renderer-v2>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
</qgis>