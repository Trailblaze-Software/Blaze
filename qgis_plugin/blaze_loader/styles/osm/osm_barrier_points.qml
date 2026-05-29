<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="1" labelsEnabled="0" maxScale="0" minScale="60000" readOnly="0" simplifyAlgorithm="0" simplifyDrawingHints="0" simplifyDrawingTol="1" simplifyLocal="1" simplifyMaxScale="1" styleCategories="LayerConfiguration|Symbology|Labeling|Fields|Rendering" symbologyReferenceScale="-1" version="3.34.3-Prizren">
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
      <rule checkstate="0" filter="&quot;barrier&quot; = 'bollard'" key="{bp-boll}" label="Bollard" symbol="2"></rule>
      <rule checkstate="0" filter="ELSE" key="{bp-oth}" label="Other barrier" symbol="3"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="FontMarker" enabled="1" id="{c72d7d85-b278-4c40-8109-0ccf47cc28af}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="chr" type="QString" value="⋈"></Option>
            <Option name="color" type="QString" value="35,35,35,255"></Option>
            <Option name="font" type="QString" value="Arial"></Option>
            <Option name="font_style" type="QString" value="Regular"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="joinstyle" type="QString" value="miter"></Option>
            <Option name="offset" type="QString" value="0,-0.40000000000000002"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="35,35,35,255"></Option>
            <Option name="outline_width" type="QString" value="0.1"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="size" type="QString" value="4"></Option>
            <Option name="size_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="size_unit" type="QString" value="MM"></Option>
            <Option name="vertical_anchor_point" type="QString" value="1"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties" type="Map">
                <Option name="angle" type="Map">
                  <Option name="active" type="bool" value="true"></Option>
                  <Option name="expression" type="QString" value="90 - symbolrotation"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SvgMarker" enabled="1" id="{8a802196-dea7-453c-8db5-88d1d8c50dd9}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="color" type="QString" value="35,35,35,255"></Option>
            <Option name="fixedAspectRatio" type="QString" value="1.78571"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="name" type="QString" value="IB stuff/grid.svg"></Option>
            <Option name="offset" type="QString" value="0,1.66666666666666186"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="Point"></Option>
            <Option name="outline_color" type="QString" value="35,35,35,255"></Option>
            <Option name="outline_width" type="QString" value="0.2"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="parameters"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="5"></Option>
            <Option name="size_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="size_unit" type="QString" value="Point"></Option>
            <Option name="vertical_anchor_point" type="QString" value="1"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties" type="Map">
                <Option name="angle" type="Map">
                  <Option name="active" type="bool" value="true"></Option>
                  <Option name="field" type="QString" value="symbolrotation"></Option>
                  <Option name="type" type="int" value="2"></Option>
                </Option>
              </Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="2" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleMarker" enabled="1" id="{bp-boll}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="cap_style" type="QString" value="square"></Option>
            <Option name="color" type="QString" value="0,0,0,255"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="name" type="QString" value="circle"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.15"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="0.8"></Option>
            <Option name="size_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="size_unit" type="QString" value="MM"></Option>
            <Option name="vertical_anchor_point" type="QString" value="1"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="3" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleMarker" enabled="1" id="{bp-oth}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="cap_style" type="QString" value="square"></Option>
            <Option name="color" type="QString" value="0,0,0,255"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="name" type="QString" value="circle"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.15"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="0.7"></Option>
            <Option name="size_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="size_unit" type="QString" value="MM"></Option>
            <Option name="vertical_anchor_point" type="QString" value="1"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
    </symbols>
  </renderer-v2>
  <selection mode="Default">
    <selectionColor invalid="1"></selectionColor>
    <selectionSymbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleMarker" enabled="1" id="{73f3c690-38d7-4b24-89a1-d92cac4e54d2}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="cap_style" type="QString" value="square"></Option>
            <Option name="color" type="QString" value="255,0,0,255"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="name" type="QString" value="circle"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="35,35,35,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="2"></Option>
            <Option name="size_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="size_unit" type="QString" value="MM"></Option>
            <Option name="vertical_anchor_point" type="QString" value="1"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
    </selectionSymbol>
  </selection>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
  <layerOpacity>1</layerOpacity>
  <fieldConfiguration>
    <field configurationFlags="NoFlag" name="fid"></field>
    <field configurationFlags="NoFlag" name="osm_id"></field>
    <field configurationFlags="NoFlag" name="osm_type"></field>
    <field configurationFlags="NoFlag" name="name"></field>
    <field configurationFlags="NoFlag" name="barrier"></field>
    <field configurationFlags="NoFlag" name="tags"></field>
  </fieldConfiguration>
  <aliases>
    <alias field="fid" index="0" name=""></alias>
    <alias field="osm_id" index="1" name=""></alias>
    <alias field="osm_type" index="2" name=""></alias>
    <alias field="name" index="3" name=""></alias>
    <alias field="barrier" index="4" name=""></alias>
    <alias field="tags" index="5" name=""></alias>
  </aliases>
  <splitPolicies>
    <policy field="fid" policy="Duplicate"></policy>
    <policy field="osm_id" policy="Duplicate"></policy>
    <policy field="osm_type" policy="Duplicate"></policy>
    <policy field="name" policy="Duplicate"></policy>
    <policy field="barrier" policy="Duplicate"></policy>
    <policy field="tags" policy="Duplicate"></policy>
  </splitPolicies>
  <defaults>
    <default applyOnUpdate="0" expression="" field="fid"></default>
    <default applyOnUpdate="0" expression="" field="osm_id"></default>
    <default applyOnUpdate="0" expression="" field="osm_type"></default>
    <default applyOnUpdate="0" expression="" field="name"></default>
    <default applyOnUpdate="0" expression="" field="barrier"></default>
    <default applyOnUpdate="0" expression="" field="tags"></default>
  </defaults>
  <constraints>
    <constraint constraints="3" exp_strength="0" field="fid" notnull_strength="1" unique_strength="1"></constraint>
    <constraint constraints="0" exp_strength="0" field="osm_id" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="osm_type" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="name" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="barrier" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="tags" notnull_strength="0" unique_strength="0"></constraint>
  </constraints>
  <constraintExpressions>
    <constraint desc="" exp="" field="fid"></constraint>
    <constraint desc="" exp="" field="osm_id"></constraint>
    <constraint desc="" exp="" field="osm_type"></constraint>
    <constraint desc="" exp="" field="name"></constraint>
    <constraint desc="" exp="" field="barrier"></constraint>
    <constraint desc="" exp="" field="tags"></constraint>
  </constraintExpressions>
  <expressionfields></expressionfields>
  <previewExpression>"name"</previewExpression>
  <layerGeometryType>0</layerGeometryType>
</qgis>