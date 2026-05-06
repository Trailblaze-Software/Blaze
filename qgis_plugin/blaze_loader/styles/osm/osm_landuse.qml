<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="0" maxScale="0" minScale="100000000" readOnly="0" simplifyAlgorithm="0" simplifyDrawingHints="1" simplifyDrawingTol="1" simplifyLocal="1" simplifyMaxScale="1" styleCategories="LayerConfiguration|Symbology|Labeling|Fields|Rendering" symbologyReferenceScale="-1" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{lu-root}">
      <rule checkstate="0" filter="&quot;landuse&quot; = 'forest'" key="{lu-f}" label="Forest" symbol="0"></rule>
      <rule checkstate="0" filter="&quot;landuse&quot; IN ('grass','meadow','pasture','recreation_ground','village_green')" key="{lu-g}" label="Open / Grass" symbol="1"></rule>
      <rule checkstate="0" filter="&quot;landuse&quot; IN ('farmland','orchard','vineyard','allotments')" key="{lu-fa}" label="Cultivated" symbol="2"></rule>
      <rule filter="&quot;landuse&quot; IN ('residential','industrial','commercial','retail')" key="{lu-r}" label="Built-up" symbol="3"></rule>
      <rule filter="&quot;landuse&quot; IN ('quarry','landfill','brownfield')" key="{lu-q}" label="Bare / disturbed" symbol="4"></rule>
      <rule filter="&quot;landuse&quot; = 'military'" key="{lu-mil}" label="Military" symbol="5"></rule>
      <rule checkstate="0" filter="ELSE" key="{lu-o}" label="Other" symbol="6"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{lu-forest}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="133,199,159,180"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{lu-grass}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="255,243,170,220"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="2" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{lu-farm}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="247,217,167,200"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="3" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{lu-built}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="186,184,108,255"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
        <layer class="SimpleLine" enabled="1" id="{c830f16a-5e75-4069-a5da-71d43dcdb67d}" locked="0" pass="0">
          <Option type="Map">
            <Option name="align_dash_pattern" type="QString" value="0"></Option>
            <Option name="capstyle" type="QString" value="square"></Option>
            <Option name="customdash" type="QString" value="5;2"></Option>
            <Option name="customdash_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="dash_pattern_offset" type="QString" value="0"></Option>
            <Option name="dash_pattern_offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="dash_pattern_offset_unit" type="QString" value="MM"></Option>
            <Option name="draw_inside_polygon" type="QString" value="0"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="line_color" type="QString" value="0,0,0,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.14"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="ring_filter" type="QString" value="0"></Option>
            <Option name="trim_distance_end" type="QString" value="0"></Option>
            <Option name="trim_distance_end_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="trim_distance_end_unit" type="QString" value="MM"></Option>
            <Option name="trim_distance_start" type="QString" value="0"></Option>
            <Option name="trim_distance_start_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="trim_distance_start_unit" type="QString" value="MM"></Option>
            <Option name="tweak_dash_pattern_on_corners" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="0"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="4" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{lu-quarry}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="200,200,200,200"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="5" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{lu-mil}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="220,150,150,150"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="180,60,60,200"></Option>
            <Option name="outline_style" type="QString" value="dash"></Option>
            <Option name="outline_width" type="QString" value="0.2"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="6" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{lu-other}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="225,238,200,160"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,0"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{28584e80-43ae-4e78-97d8-865c64a49106}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="0,0,255,255"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="35,35,35,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.26"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="solid"></Option>
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
    <field configurationFlags="NoFlag" name="landuse"></field>
    <field configurationFlags="NoFlag" name="tags"></field>
  </fieldConfiguration>
  <aliases>
    <alias field="fid" index="0" name=""></alias>
    <alias field="osm_id" index="1" name=""></alias>
    <alias field="osm_type" index="2" name=""></alias>
    <alias field="name" index="3" name=""></alias>
    <alias field="landuse" index="4" name=""></alias>
    <alias field="tags" index="5" name=""></alias>
  </aliases>
  <splitPolicies>
    <policy field="fid" policy="Duplicate"></policy>
    <policy field="osm_id" policy="Duplicate"></policy>
    <policy field="osm_type" policy="Duplicate"></policy>
    <policy field="name" policy="Duplicate"></policy>
    <policy field="landuse" policy="Duplicate"></policy>
    <policy field="tags" policy="Duplicate"></policy>
  </splitPolicies>
  <defaults>
    <default applyOnUpdate="0" expression="" field="fid"></default>
    <default applyOnUpdate="0" expression="" field="osm_id"></default>
    <default applyOnUpdate="0" expression="" field="osm_type"></default>
    <default applyOnUpdate="0" expression="" field="name"></default>
    <default applyOnUpdate="0" expression="" field="landuse"></default>
    <default applyOnUpdate="0" expression="" field="tags"></default>
  </defaults>
  <constraints>
    <constraint constraints="3" exp_strength="0" field="fid" notnull_strength="1" unique_strength="1"></constraint>
    <constraint constraints="0" exp_strength="0" field="osm_id" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="osm_type" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="name" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="landuse" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="tags" notnull_strength="0" unique_strength="0"></constraint>
  </constraints>
  <constraintExpressions>
    <constraint desc="" exp="" field="fid"></constraint>
    <constraint desc="" exp="" field="osm_id"></constraint>
    <constraint desc="" exp="" field="osm_type"></constraint>
    <constraint desc="" exp="" field="name"></constraint>
    <constraint desc="" exp="" field="landuse"></constraint>
    <constraint desc="" exp="" field="tags"></constraint>
  </constraintExpressions>
  <expressionfields></expressionfields>
  <previewExpression>"name"</previewExpression>
  <layerGeometryType>2</layerGeometryType>
</qgis>