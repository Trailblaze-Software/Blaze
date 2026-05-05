<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="0" maxScale="0" minScale="1e+08" readOnly="0" styleCategories="LayerConfiguration|Symbology|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{bp-root}">
      <rule filter="&quot;barrier&quot; IN ('gate','lift_gate','swing_gate','sliding_gate','kissing_gate')" key="{bp-gate}" label="Gate" symbol="0"></rule>
      <rule filter="&quot;barrier&quot; = 'stile'" key="{bp-stile}" label="Stile" symbol="1"></rule>
      <rule filter="&quot;barrier&quot; = 'bollard'" key="{bp-boll}" label="Bollard" symbol="2"></rule>
      <rule filter="ELSE" key="{bp-oth}" label="Other barrier" symbol="3"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="marker">
        <layer class="SimpleMarker" enabled="1" id="{bp-gate}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="color" type="QString" value="255,255,255,255"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="name" type="QString" value="circle"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.3"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="size" type="QString" value="1.4"></Option>
            <Option name="size_unit" type="QString" value="MM"></Option>
            <Option name="vertical_anchor_point" type="QString" value="1"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="marker">
        <layer class="SimpleMarker" enabled="1" id="{bp-stile}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="color" type="QString" value="0,0,0,255"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="name" type="QString" value="square"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.2"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="size" type="QString" value="1.0"></Option>
            <Option name="size_unit" type="QString" value="MM"></Option>
            <Option name="vertical_anchor_point" type="QString" value="1"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="2" type="marker">
        <layer class="SimpleMarker" enabled="1" id="{bp-boll}" locked="0" pass="0">
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="3" type="marker">
        <layer class="SimpleMarker" enabled="1" id="{bp-oth}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="color" type="QString" value="0,0,0,255"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="name" type="QString" value="circle"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.15"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="size" type="QString" value="0.7"></Option>
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