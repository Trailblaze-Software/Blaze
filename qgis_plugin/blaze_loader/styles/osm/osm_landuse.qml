<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="0" maxScale="0" minScale="1e+08" readOnly="0" styleCategories="LayerConfiguration|Symbology|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{lu-root}">
      <rule filter="&quot;landuse&quot; = 'forest'" key="{lu-f}" label="Forest" symbol="0"></rule>
      <rule filter="&quot;landuse&quot; IN ('grass','meadow','pasture','recreation_ground','village_green')" key="{lu-g}" label="Open / Grass" symbol="1"></rule>
      <rule filter="&quot;landuse&quot; IN ('farmland','orchard','vineyard','allotments')" key="{lu-fa}" label="Cultivated" symbol="2"></rule>
      <rule filter="&quot;landuse&quot; IN ('residential','industrial','commercial','retail')" key="{lu-r}" label="Built-up" symbol="3"></rule>
      <rule filter="&quot;landuse&quot; IN ('quarry','landfill','brownfield')" key="{lu-q}" label="Bare / disturbed" symbol="4"></rule>
      <rule filter="&quot;landuse&quot; = 'military'" key="{lu-mil}" label="Military" symbol="5"></rule>
      <rule filter="ELSE" key="{lu-o}" label="Other" symbol="6"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="fill">
        <layer class="SimpleFill" enabled="1" id="{lu-forest}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="133,199,159,180"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="fill">
        <layer class="SimpleFill" enabled="1" id="{lu-grass}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="255,243,170,220"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="2" type="fill">
        <layer class="SimpleFill" enabled="1" id="{lu-farm}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="247,217,167,200"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="3" type="fill">
        <layer class="SimpleFill" enabled="1" id="{lu-built}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="217,200,159,200"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="4" type="fill">
        <layer class="SimpleFill" enabled="1" id="{lu-quarry}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="200,200,200,200"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="5" type="fill">
        <layer class="SimpleFill" enabled="1" id="{lu-mil}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="220,150,150,150"></Option>
            <Option name="outline_color" type="QString" value="180,60,60,200"></Option>
            <Option name="outline_style" type="QString" value="dash"></Option>
            <Option name="outline_width" type="QString" value="0.2"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="6" type="fill">
        <layer class="SimpleFill" enabled="1" id="{lu-other}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="225,238,200,160"></Option>
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
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
</qgis>