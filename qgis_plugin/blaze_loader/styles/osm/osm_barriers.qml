<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="0" maxScale="0" minScale="1e+08" readOnly="0" styleCategories="LayerConfiguration|Symbology|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{br-root}">
      <rule filter="&quot;barrier&quot; IN ('wall','city_wall','retaining_wall')" key="{br-wall}" label="Wall" symbol="0"></rule>
      <rule filter="&quot;barrier&quot; IN ('hedge')" key="{br-hedge}" label="Hedge" symbol="1"></rule>
      <rule filter="&quot;barrier&quot; IN ('ditch','trench')" key="{br-ditch}" label="Ditch / trench" symbol="2"></rule>
      <rule filter="ELSE" key="{br-fence}" label="Fence / other" symbol="3"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="line">
        <layer class="SimpleLine" enabled="1" id="{br-wall-base}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="square"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="line_color" type="QString" value="0,0,0,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.35"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="0"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="line">
        <layer class="SimpleLine" enabled="1" id="{br-hedge-base}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="60,120,55,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.5"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="0"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="2" type="line">
        <layer class="SimpleLine" enabled="1" id="{br-ditch-base}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="customdash" type="QString" value="2;1.2"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="187,100,25,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.3"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="1"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="3" type="line">
        <layer class="SimpleLine" enabled="1" id="{br-fence-base}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="square"></Option>
            <Option name="customdash" type="QString" value="1.4;0.7"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="line_color" type="QString" value="0,0,0,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.2"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="1"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
    </symbols>
  </renderer-v2>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
</qgis>