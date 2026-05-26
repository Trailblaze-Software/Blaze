<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="1" labelsEnabled="0" maxScale="0" minScale="100000" readOnly="0" simplifyAlgorithm="0" simplifyDrawingHints="1" simplifyDrawingTol="1" simplifyLocal="1" simplifyMaxScale="1" styleCategories="LayerConfiguration|Symbology|Labeling|Fields|Rendering" symbologyReferenceScale="-1" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{pwr-root}">
      <rule filter="&quot;power&quot; = 'line'" key="{pwr-line}" label="High-voltage line" symbol="0"></rule>
      <rule filter="ELSE" key="{pwr-minor}" label="Minor power line" scalemaxdenom="30000" scalemindenom="1000" symbol="1"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="line">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleLine" enabled="1" id="{pwr-line-base}" locked="0" pass="0">
          <Option type="Map">
            <Option name="align_dash_pattern" type="QString" value="0"></Option>
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="customdash" type="QString" value="5;2"></Option>
            <Option name="customdash_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="dash_pattern_offset" type="QString" value="0"></Option>
            <Option name="dash_pattern_offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="dash_pattern_offset_unit" type="QString" value="MM"></Option>
            <Option name="draw_inside_polygon" type="QString" value="0"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="0,0,0,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.3"></Option>
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
        <layer class="MarkerLine" enabled="1" id="{pwr-line-pylons}" locked="0" pass="0">
          <Option type="Map">
            <Option name="average_angle_length" type="QString" value="4"></Option>
            <Option name="average_angle_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="average_angle_unit" type="QString" value="MM"></Option>
            <Option name="interval" type="QString" value="3"></Option>
            <Option name="interval_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="interval_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="offset_along_line" type="QString" value="0"></Option>
            <Option name="offset_along_line_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_along_line_unit" type="QString" value="MM"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="place_on_every_part" type="bool" value="true"></Option>
            <Option name="placements" type="QString" value="LastVertex|FirstVertex|InnerVertices"></Option>
            <Option name="ring_filter" type="QString" value="0"></Option>
            <Option name="rotate" type="QString" value="1"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
          <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="@0@1" type="marker">
            <data_defined_properties>
              <Option type="Map">
                <Option name="name" type="QString" value=""></Option>
                <Option name="properties"></Option>
                <Option name="type" type="QString" value="collection"></Option>
              </Option>
            </data_defined_properties>
            <layer class="SimpleMarker" enabled="1" id="{pwr-line-pylon-marker}" locked="0" pass="0">
              <Option type="Map">
                <Option name="angle" type="QString" value="0"></Option>
                <Option name="cap_style" type="QString" value="square"></Option>
                <Option name="color" type="QString" value="0,0,0,255"></Option>
                <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
                <Option name="joinstyle" type="QString" value="bevel"></Option>
                <Option name="name" type="QString" value="line"></Option>
                <Option name="offset" type="QString" value="0,0"></Option>
                <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
                <Option name="offset_unit" type="QString" value="MM"></Option>
                <Option name="outline_color" type="QString" value="0,0,0,255"></Option>
                <Option name="outline_style" type="QString" value="solid"></Option>
                <Option name="outline_width" type="QString" value="0.35"></Option>
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
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="line">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleLine" enabled="1" id="{pwr-minor-base}" locked="0" pass="0">
          <Option type="Map">
            <Option name="align_dash_pattern" type="QString" value="0"></Option>
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="customdash" type="QString" value="5;2"></Option>
            <Option name="customdash_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="dash_pattern_offset" type="QString" value="0"></Option>
            <Option name="dash_pattern_offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="dash_pattern_offset_unit" type="QString" value="MM"></Option>
            <Option name="draw_inside_polygon" type="QString" value="0"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="0,0,0,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.22"></Option>
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
        <layer class="MarkerLine" enabled="1" id="{pwr-minor-pylons}" locked="0" pass="0">
          <Option type="Map">
            <Option name="average_angle_length" type="QString" value="4"></Option>
            <Option name="average_angle_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="average_angle_unit" type="QString" value="MM"></Option>
            <Option name="interval" type="QString" value="3"></Option>
            <Option name="interval_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="interval_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="offset_along_line" type="QString" value="0"></Option>
            <Option name="offset_along_line_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_along_line_unit" type="QString" value="MM"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="place_on_every_part" type="bool" value="true"></Option>
            <Option name="placements" type="QString" value="LastVertex|FirstVertex|InnerVertices"></Option>
            <Option name="ring_filter" type="QString" value="0"></Option>
            <Option name="rotate" type="QString" value="1"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
          <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="@1@1" type="marker">
            <data_defined_properties>
              <Option type="Map">
                <Option name="name" type="QString" value=""></Option>
                <Option name="properties"></Option>
                <Option name="type" type="QString" value="collection"></Option>
              </Option>
            </data_defined_properties>
            <layer class="SimpleMarker" enabled="1" id="{pwr-minor-pylon-marker}" locked="0" pass="0">
              <Option type="Map">
                <Option name="angle" type="QString" value="0"></Option>
                <Option name="cap_style" type="QString" value="square"></Option>
                <Option name="color" type="QString" value="0,0,0,255"></Option>
                <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
                <Option name="joinstyle" type="QString" value="bevel"></Option>
                <Option name="name" type="QString" value="line"></Option>
                <Option name="offset" type="QString" value="0,0"></Option>
                <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
                <Option name="offset_unit" type="QString" value="MM"></Option>
                <Option name="outline_color" type="QString" value="0,0,0,255"></Option>
                <Option name="outline_style" type="QString" value="solid"></Option>
                <Option name="outline_width" type="QString" value="0.25"></Option>
                <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
                <Option name="outline_width_unit" type="QString" value="MM"></Option>
                <Option name="scale_method" type="QString" value="diameter"></Option>
                <Option name="size" type="QString" value="1.4"></Option>
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
        </layer>
      </symbol>
    </symbols>
  </renderer-v2>
  <selection mode="Default">
    <selectionColor invalid="1"></selectionColor>
    <selectionSymbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="" type="line">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleLine" enabled="1" id="{dad3942a-d7d0-4a19-851c-7cb828fc8513}" locked="0" pass="0">
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
            <Option name="line_color" type="QString" value="35,35,35,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.26"></Option>
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
    <field configurationFlags="NoFlag" name="power"></field>
    <field configurationFlags="NoFlag" name="tags"></field>
  </fieldConfiguration>
  <aliases>
    <alias field="fid" index="0" name=""></alias>
    <alias field="osm_id" index="1" name=""></alias>
    <alias field="osm_type" index="2" name=""></alias>
    <alias field="name" index="3" name=""></alias>
    <alias field="power" index="4" name=""></alias>
    <alias field="tags" index="5" name=""></alias>
  </aliases>
  <splitPolicies>
    <policy field="fid" policy="Duplicate"></policy>
    <policy field="osm_id" policy="Duplicate"></policy>
    <policy field="osm_type" policy="Duplicate"></policy>
    <policy field="name" policy="Duplicate"></policy>
    <policy field="power" policy="Duplicate"></policy>
    <policy field="tags" policy="Duplicate"></policy>
  </splitPolicies>
  <defaults>
    <default applyOnUpdate="0" expression="" field="fid"></default>
    <default applyOnUpdate="0" expression="" field="osm_id"></default>
    <default applyOnUpdate="0" expression="" field="osm_type"></default>
    <default applyOnUpdate="0" expression="" field="name"></default>
    <default applyOnUpdate="0" expression="" field="power"></default>
    <default applyOnUpdate="0" expression="" field="tags"></default>
  </defaults>
  <constraints>
    <constraint constraints="3" exp_strength="0" field="fid" notnull_strength="1" unique_strength="1"></constraint>
    <constraint constraints="0" exp_strength="0" field="osm_id" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="osm_type" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="name" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="power" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="tags" notnull_strength="0" unique_strength="0"></constraint>
  </constraints>
  <constraintExpressions>
    <constraint desc="" exp="" field="fid"></constraint>
    <constraint desc="" exp="" field="osm_id"></constraint>
    <constraint desc="" exp="" field="osm_type"></constraint>
    <constraint desc="" exp="" field="name"></constraint>
    <constraint desc="" exp="" field="power"></constraint>
    <constraint desc="" exp="" field="tags"></constraint>
  </constraintExpressions>
  <expressionfields></expressionfields>
  <previewExpression>"name"</previewExpression>
  <layerGeometryType>1</layerGeometryType>
</qgis>