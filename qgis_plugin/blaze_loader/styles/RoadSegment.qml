<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="0" maxScale="0" minScale="100000000" readOnly="0" simplifyAlgorithm="0" simplifyDrawingHints="1" simplifyDrawingTol="1" simplifyLocal="1" simplifyMaxScale="1" styleCategories="LayerConfiguration|Symbology|Symbology3D|Labeling|Fields|Forms|Actions|MapTips|Diagrams|AttributeTable|Rendering" symbologyReferenceScale="-1" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="1" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{90a5cbaa-c1d8-49da-820e-fd9b053d63e8}">
      <rule filter="roadontype in (4,7)" key="{855240d1-685f-48e1-b9da-fc329ea593e5}" label="Ford/Floodway" symbol="0"></rule>
      <rule description="Bridge width set by 'Data defined override', layer variable @road_width" filter="roadontype in (2,5,6)" key="{6bf31a68-44aa-4dc1-a641-4511ccc5c2d5}" label="Bridge" symbol="1"></rule>
      <rule description="Road width set by 'Data defined override', layer variable @road_width" filter="surface in (0, 1) and (functionhierarchy &lt; 8 or functionhierarchy = 10)" key="{f6d75ae4-08e2-48c3-8753-895dc1a193cf}" label="Sealed" symbol="2"></rule>
      <rule description="Road width set by 'Data defined override', layer variable @road_width" filter="surface = 2 and (functionhierarchy &lt; 9 ) and not classsubtype = 5" key="{43bec151-7591-4f3c-a021-99fafda9dac1}" label="Unsealed" symbol="3"></rule>
      <rule filter="surface = 2  and functionhierarchy &lt; 9 and classsubtype = 5" key="{ca095e73-3de9-426e-9ac5-8a8ae8b3b196}" label="2wd - dry weather" symbol="4"></rule>
      <rule filter="surface in (3, 4) and functionhierarchy = 8" key="{b3d3b67f-b93f-452f-b527-5eda2138dfcd}" label="4wd" symbol="5"></rule>
      <rule filter="functionhierarchy = 9" key="{db68cda4-6d6e-498b-879f-bc4510eaa904}" label="Path" symbol="6"></rule>
      <rule filter="functionhierarchy = 98" key="{ab0284d8-24a9-488c-ada1-540683173abe}" label="Overgrown" symbol="7"></rule>
      <rule checkstate="0" filter="functionhierarchy = 99" key="{33d3ba80-0bef-4110-8661-0471d10ae14b}" label="Delete" symbol="8"></rule>
      <rule filter="relevance = 100" key="{6219d35d-4246-4c07-bf90-e7011bc6c6ea}" label="Safety patrol" symbol="9"></rule>
      <rule filter="ELSE" key="{5c0dfca1-a5ab-4b68-9e2c-a8ce46eacb60}" label="Unkown" symbol="10"></rule>
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
        <layer class="SimpleLine" enabled="1" id="{e7d9f626-ce94-4003-b033-f6fa1a7cb96e}" locked="0" pass="0">
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
            <Option name="line_color" type="QString" value="1,115,255,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="1.2"></Option>
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
              <Option name="properties" type="Map">
                <Option name="outlineWidth" type="Map">
                  <Option name="active" type="bool" value="true"></Option>
                  <Option name="expression" type="QString" value="array_get(string_to_array(@road_width), functionhierarchy) + 0.6"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
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
        <layer class="SimpleLine" enabled="1" id="{5e280985-06e3-4541-835a-7380f2a045c8}" locked="0" pass="0">
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
            <Option name="line_width" type="QString" value="1.2"></Option>
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
              <Option name="properties" type="Map">
                <Option name="outlineWidth" type="Map">
                  <Option name="active" type="bool" value="true"></Option>
                  <Option name="expression" type="QString" value="array_get(string_to_array(@road_width), functionhierarchy) + 0.6"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="10" type="line">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleLine" enabled="1" id="{3200153a-4c20-4989-9c15-8b8d53a34ce5}" locked="0" pass="0">
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
            <Option name="line_color" type="QString" value="0,255,0,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="3"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="2" type="line">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleLine" enabled="1" id="{c5286670-a2d8-4b22-9f8f-f45fdaf3b7c0}" locked="0" pass="10">
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
            <Option name="line_color" type="QString" value="255,0,0,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.4"></Option>
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
              <Option name="properties" type="Map">
                <Option name="outlineWidth" type="Map">
                  <Option name="active" type="bool" value="true"></Option>
                  <Option name="expression" type="QString" value="array_get(string_to_array(@road_width), functionhierarchy)"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="3" type="line">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleLine" enabled="1" id="{68d87203-2384-4dfc-81b2-6d374743821a}" locked="0" pass="9">
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
            <Option name="line_width" type="QString" value="0.4"></Option>
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
              <Option name="properties" type="Map">
                <Option name="outlineWidth" type="Map">
                  <Option name="active" type="bool" value="true"></Option>
                  <Option name="expression" type="QString" value="array_get(string_to_array(@road_width), functionhierarchy)"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="4" type="line">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleLine" enabled="1" id="{bdb9283e-2b02-40c5-98a7-7e87d1b1f3f2}" locked="0" pass="8">
          <Option type="Map">
            <Option name="align_dash_pattern" type="QString" value="0"></Option>
            <Option name="capstyle" type="QString" value="square"></Option>
            <Option name="customdash" type="QString" value="4;1.4"></Option>
            <Option name="customdash_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="dash_pattern_offset" type="QString" value="0"></Option>
            <Option name="dash_pattern_offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="dash_pattern_offset_unit" type="QString" value="MM"></Option>
            <Option name="draw_inside_polygon" type="QString" value="0"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="line_color" type="QString" value="0,0,0,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.35"></Option>
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
            <Option name="use_custom_dash" type="QString" value="1"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="5" type="line">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleLine" enabled="1" id="{2326a95b-323c-4d99-8a2b-f41efa47494c}" locked="0" pass="7">
          <Option type="Map">
            <Option name="align_dash_pattern" type="QString" value="0"></Option>
            <Option name="capstyle" type="QString" value="square"></Option>
            <Option name="customdash" type="QString" value="2;0.7"></Option>
            <Option name="customdash_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="dash_pattern_offset" type="QString" value="0"></Option>
            <Option name="dash_pattern_offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="dash_pattern_offset_unit" type="QString" value="MM"></Option>
            <Option name="draw_inside_polygon" type="QString" value="0"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
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
            <Option name="use_custom_dash" type="QString" value="1"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="6" type="line">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleLine" enabled="1" id="{d253d42d-f5d0-42c7-a7df-af6d92c9e4fd}" locked="0" pass="6">
          <Option type="Map">
            <Option name="align_dash_pattern" type="QString" value="0"></Option>
            <Option name="capstyle" type="QString" value="square"></Option>
            <Option name="customdash" type="QString" value="1.5;0.5"></Option>
            <Option name="customdash_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="dash_pattern_offset" type="QString" value="0"></Option>
            <Option name="dash_pattern_offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="dash_pattern_offset_unit" type="QString" value="MM"></Option>
            <Option name="draw_inside_polygon" type="QString" value="0"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="line_color" type="QString" value="0,0,0,255"></Option>
            <Option name="line_style" type="QString" value="dot"></Option>
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
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="7" type="line">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleLine" enabled="1" id="{1d34bb36-2774-4200-812e-095f8a2b5b19}" locked="0" pass="5">
          <Option type="Map">
            <Option name="align_dash_pattern" type="QString" value="0"></Option>
            <Option name="capstyle" type="QString" value="square"></Option>
            <Option name="customdash" type="QString" value="2;2"></Option>
            <Option name="customdash_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="dash_pattern_offset" type="QString" value="0"></Option>
            <Option name="dash_pattern_offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="dash_pattern_offset_unit" type="QString" value="MM"></Option>
            <Option name="draw_inside_polygon" type="QString" value="0"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="line_color" type="QString" value="4,5,4,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.25"></Option>
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
            <Option name="use_custom_dash" type="QString" value="1"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="8" type="line">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="HashLine" enabled="1" id="{689fc948-09b2-4ff0-8324-17da7df8007a}" locked="0" pass="0">
          <Option type="Map">
            <Option name="average_angle_length" type="QString" value="4"></Option>
            <Option name="average_angle_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="average_angle_unit" type="QString" value="MM"></Option>
            <Option name="hash_angle" type="QString" value="0"></Option>
            <Option name="hash_length" type="QString" value="1"></Option>
            <Option name="hash_length_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="hash_length_unit" type="QString" value="MM"></Option>
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
            <Option name="placements" type="QString" value="Interval"></Option>
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
          <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="@8@0" type="line">
            <data_defined_properties>
              <Option type="Map">
                <Option name="name" type="QString" value=""></Option>
                <Option name="properties"></Option>
                <Option name="type" type="QString" value="collection"></Option>
              </Option>
            </data_defined_properties>
            <layer class="SimpleLine" enabled="1" id="{b6e84f08-f24a-4b2b-8faa-6db58c1df7fb}" locked="0" pass="0">
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
                <Option name="line_color" type="QString" value="255,0,0,255"></Option>
                <Option name="line_style" type="QString" value="solid"></Option>
                <Option name="line_width" type="QString" value="0.5"></Option>
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
        </layer>
      </symbol>
      <symbol alpha="0.3" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="9" type="line">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleLine" enabled="1" id="{3eff52f4-6bd0-43e3-bb45-1d996eb70735}" locked="0" pass="0">
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
            <Option name="line_color" type="QString" value="255,255,0,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="3.5"></Option>
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
        <layer class="SimpleLine" enabled="1" id="{045dbd13-7732-4d98-8c20-32abcc3fb36b}" locked="0" pass="0">
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
  <SingleCategoryDiagramRenderer attributeLegend="1" diagramType="Histogram">
    <DiagramCategory backgroundAlpha="255" backgroundColor="#ffffff" barWidth="5" diagramOrientation="Up" direction="0" enabled="0" height="15" labelPlacementMethod="XHeight" lineSizeScale="3x:0,0,0,0,0,0" lineSizeType="MM" maxScaleDenominator="1e+08" minScaleDenominator="0" minimumSize="0" opacity="1" penAlpha="255" penColor="#000000" penWidth="0" rotationOffset="270" scaleBasedVisibility="0" scaleDependency="Area" showAxis="1" sizeScale="3x:0,0,0,0,0,0" sizeType="MM" spacing="5" spacingUnit="MM" spacingUnitScale="3x:0,0,0,0,0,0" width="15">
      <fontProperties bold="0" description="MS Shell Dlg 2,8.25,-1,5,50,0,0,0,0,0" italic="0" strikethrough="0" style="" underline="0"></fontProperties>
      <attribute color="#000000" colorOpacity="1" field="" label=""></attribute>
      <axisSymbol>
        <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="" type="line">
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
          <layer class="SimpleLine" enabled="1" id="{03860f5a-f41d-4aea-8226-063aecbf4220}" locked="0" pass="0">
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
      </axisSymbol>
    </DiagramCategory>
  </SingleCategoryDiagramRenderer>
  <DiagramLayerSettings dist="0" linePlacementFlags="18" obstacle="0" placement="2" priority="0" showAll="1" zIndex="0">
    <properties>
      <Option type="Map">
        <Option name="name" type="QString" value=""></Option>
        <Option name="properties"></Option>
        <Option name="type" type="QString" value="collection"></Option>
      </Option>
    </properties>
  </DiagramLayerSettings>
  <fieldConfiguration>
    <field configurationFlags="NoFlag" name="fid">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="objectid">
      <editWidget type="Range">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="topoid">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="createdate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="objectmoddate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="featuremoddate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="classsubtype">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="featurereliabilitydate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="attributereliabilitydate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="capturesourcecode">
      <editWidget type="Range">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="capturemethodcode">
      <editWidget type="Range">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="planimetricaccuracy">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="verticalaccuracy">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="operationalstatus">
      <editWidget type="Range">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="roadnameoid">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="roadnamebase">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="roadnametype">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="roadnamesuffix">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="functionhierarchy">
      <editWidget type="Range">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="roadontype">
      <editWidget type="Range">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="surface">
      <editWidget type="Range">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="lanecount">
      <editWidget type="Range">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="roadnameextentoid">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="relevance">
      <editWidget type="Range">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="startdate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="enddate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="lastupdate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="msoid">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="centroidid">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="shapeuuid">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="changetype">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="processstate">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="urbanity">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="shape_Length">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
  </fieldConfiguration>
  <aliases>
    <alias field="fid" index="0" name=""></alias>
    <alias field="objectid" index="1" name=""></alias>
    <alias field="topoid" index="2" name=""></alias>
    <alias field="createdate" index="3" name=""></alias>
    <alias field="objectmoddate" index="4" name=""></alias>
    <alias field="featuremoddate" index="5" name=""></alias>
    <alias field="classsubtype" index="6" name=""></alias>
    <alias field="featurereliabilitydate" index="7" name=""></alias>
    <alias field="attributereliabilitydate" index="8" name=""></alias>
    <alias field="capturesourcecode" index="9" name=""></alias>
    <alias field="capturemethodcode" index="10" name=""></alias>
    <alias field="planimetricaccuracy" index="11" name=""></alias>
    <alias field="verticalaccuracy" index="12" name=""></alias>
    <alias field="operationalstatus" index="13" name=""></alias>
    <alias field="roadnameoid" index="14" name=""></alias>
    <alias field="roadnamebase" index="15" name=""></alias>
    <alias field="roadnametype" index="16" name=""></alias>
    <alias field="roadnamesuffix" index="17" name=""></alias>
    <alias field="functionhierarchy" index="18" name=""></alias>
    <alias field="roadontype" index="19" name=""></alias>
    <alias field="surface" index="20" name=""></alias>
    <alias field="lanecount" index="21" name=""></alias>
    <alias field="roadnameextentoid" index="22" name=""></alias>
    <alias field="relevance" index="23" name=""></alias>
    <alias field="startdate" index="24" name=""></alias>
    <alias field="enddate" index="25" name=""></alias>
    <alias field="lastupdate" index="26" name=""></alias>
    <alias field="msoid" index="27" name=""></alias>
    <alias field="centroidid" index="28" name=""></alias>
    <alias field="shapeuuid" index="29" name=""></alias>
    <alias field="changetype" index="30" name=""></alias>
    <alias field="processstate" index="31" name=""></alias>
    <alias field="urbanity" index="32" name=""></alias>
    <alias field="shape_Length" index="33" name=""></alias>
  </aliases>
  <splitPolicies>
    <policy field="fid" policy="Duplicate"></policy>
    <policy field="objectid" policy="Duplicate"></policy>
    <policy field="topoid" policy="Duplicate"></policy>
    <policy field="createdate" policy="Duplicate"></policy>
    <policy field="objectmoddate" policy="Duplicate"></policy>
    <policy field="featuremoddate" policy="Duplicate"></policy>
    <policy field="classsubtype" policy="Duplicate"></policy>
    <policy field="featurereliabilitydate" policy="Duplicate"></policy>
    <policy field="attributereliabilitydate" policy="Duplicate"></policy>
    <policy field="capturesourcecode" policy="Duplicate"></policy>
    <policy field="capturemethodcode" policy="Duplicate"></policy>
    <policy field="planimetricaccuracy" policy="Duplicate"></policy>
    <policy field="verticalaccuracy" policy="Duplicate"></policy>
    <policy field="operationalstatus" policy="Duplicate"></policy>
    <policy field="roadnameoid" policy="Duplicate"></policy>
    <policy field="roadnamebase" policy="Duplicate"></policy>
    <policy field="roadnametype" policy="Duplicate"></policy>
    <policy field="roadnamesuffix" policy="Duplicate"></policy>
    <policy field="functionhierarchy" policy="Duplicate"></policy>
    <policy field="roadontype" policy="Duplicate"></policy>
    <policy field="surface" policy="Duplicate"></policy>
    <policy field="lanecount" policy="Duplicate"></policy>
    <policy field="roadnameextentoid" policy="Duplicate"></policy>
    <policy field="relevance" policy="Duplicate"></policy>
    <policy field="startdate" policy="Duplicate"></policy>
    <policy field="enddate" policy="Duplicate"></policy>
    <policy field="lastupdate" policy="Duplicate"></policy>
    <policy field="msoid" policy="Duplicate"></policy>
    <policy field="centroidid" policy="Duplicate"></policy>
    <policy field="shapeuuid" policy="Duplicate"></policy>
    <policy field="changetype" policy="Duplicate"></policy>
    <policy field="processstate" policy="Duplicate"></policy>
    <policy field="urbanity" policy="Duplicate"></policy>
    <policy field="shape_Length" policy="Duplicate"></policy>
  </splitPolicies>
  <defaults>
    <default applyOnUpdate="0" expression="" field="fid"></default>
    <default applyOnUpdate="0" expression="" field="objectid"></default>
    <default applyOnUpdate="0" expression="" field="topoid"></default>
    <default applyOnUpdate="0" expression="" field="createdate"></default>
    <default applyOnUpdate="0" expression="" field="objectmoddate"></default>
    <default applyOnUpdate="0" expression="" field="featuremoddate"></default>
    <default applyOnUpdate="0" expression="" field="classsubtype"></default>
    <default applyOnUpdate="0" expression="" field="featurereliabilitydate"></default>
    <default applyOnUpdate="0" expression="" field="attributereliabilitydate"></default>
    <default applyOnUpdate="0" expression="" field="capturesourcecode"></default>
    <default applyOnUpdate="0" expression="" field="capturemethodcode"></default>
    <default applyOnUpdate="0" expression="" field="planimetricaccuracy"></default>
    <default applyOnUpdate="0" expression="" field="verticalaccuracy"></default>
    <default applyOnUpdate="0" expression="" field="operationalstatus"></default>
    <default applyOnUpdate="0" expression="" field="roadnameoid"></default>
    <default applyOnUpdate="0" expression="" field="roadnamebase"></default>
    <default applyOnUpdate="0" expression="" field="roadnametype"></default>
    <default applyOnUpdate="0" expression="" field="roadnamesuffix"></default>
    <default applyOnUpdate="0" expression="" field="functionhierarchy"></default>
    <default applyOnUpdate="0" expression="" field="roadontype"></default>
    <default applyOnUpdate="0" expression="" field="surface"></default>
    <default applyOnUpdate="0" expression="" field="lanecount"></default>
    <default applyOnUpdate="0" expression="" field="roadnameextentoid"></default>
    <default applyOnUpdate="0" expression="" field="relevance"></default>
    <default applyOnUpdate="0" expression="" field="startdate"></default>
    <default applyOnUpdate="0" expression="" field="enddate"></default>
    <default applyOnUpdate="0" expression="" field="lastupdate"></default>
    <default applyOnUpdate="0" expression="" field="msoid"></default>
    <default applyOnUpdate="0" expression="" field="centroidid"></default>
    <default applyOnUpdate="0" expression="" field="shapeuuid"></default>
    <default applyOnUpdate="0" expression="" field="changetype"></default>
    <default applyOnUpdate="0" expression="" field="processstate"></default>
    <default applyOnUpdate="0" expression="" field="urbanity"></default>
    <default applyOnUpdate="0" expression="" field="shape_Length"></default>
  </defaults>
  <constraints>
    <constraint constraints="3" exp_strength="0" field="fid" notnull_strength="1" unique_strength="1"></constraint>
    <constraint constraints="0" exp_strength="0" field="objectid" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="topoid" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="createdate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="objectmoddate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="featuremoddate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="classsubtype" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="featurereliabilitydate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="attributereliabilitydate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="capturesourcecode" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="capturemethodcode" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="planimetricaccuracy" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="verticalaccuracy" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="operationalstatus" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="roadnameoid" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="roadnamebase" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="roadnametype" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="roadnamesuffix" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="functionhierarchy" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="roadontype" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="surface" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="lanecount" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="roadnameextentoid" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="relevance" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="startdate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="enddate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="lastupdate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="msoid" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="centroidid" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="shapeuuid" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="changetype" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="processstate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="urbanity" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="shape_Length" notnull_strength="0" unique_strength="0"></constraint>
  </constraints>
  <constraintExpressions>
    <constraint desc="" exp="" field="fid"></constraint>
    <constraint desc="" exp="" field="objectid"></constraint>
    <constraint desc="" exp="" field="topoid"></constraint>
    <constraint desc="" exp="" field="createdate"></constraint>
    <constraint desc="" exp="" field="objectmoddate"></constraint>
    <constraint desc="" exp="" field="featuremoddate"></constraint>
    <constraint desc="" exp="" field="classsubtype"></constraint>
    <constraint desc="" exp="" field="featurereliabilitydate"></constraint>
    <constraint desc="" exp="" field="attributereliabilitydate"></constraint>
    <constraint desc="" exp="" field="capturesourcecode"></constraint>
    <constraint desc="" exp="" field="capturemethodcode"></constraint>
    <constraint desc="" exp="" field="planimetricaccuracy"></constraint>
    <constraint desc="" exp="" field="verticalaccuracy"></constraint>
    <constraint desc="" exp="" field="operationalstatus"></constraint>
    <constraint desc="" exp="" field="roadnameoid"></constraint>
    <constraint desc="" exp="" field="roadnamebase"></constraint>
    <constraint desc="" exp="" field="roadnametype"></constraint>
    <constraint desc="" exp="" field="roadnamesuffix"></constraint>
    <constraint desc="" exp="" field="functionhierarchy"></constraint>
    <constraint desc="" exp="" field="roadontype"></constraint>
    <constraint desc="" exp="" field="surface"></constraint>
    <constraint desc="" exp="" field="lanecount"></constraint>
    <constraint desc="" exp="" field="roadnameextentoid"></constraint>
    <constraint desc="" exp="" field="relevance"></constraint>
    <constraint desc="" exp="" field="startdate"></constraint>
    <constraint desc="" exp="" field="enddate"></constraint>
    <constraint desc="" exp="" field="lastupdate"></constraint>
    <constraint desc="" exp="" field="msoid"></constraint>
    <constraint desc="" exp="" field="centroidid"></constraint>
    <constraint desc="" exp="" field="shapeuuid"></constraint>
    <constraint desc="" exp="" field="changetype"></constraint>
    <constraint desc="" exp="" field="processstate"></constraint>
    <constraint desc="" exp="" field="urbanity"></constraint>
    <constraint desc="" exp="" field="shape_Length"></constraint>
  </constraintExpressions>
  <expressionfields></expressionfields>
  <attributeactions>
    <defaultAction key="Canvas" value="{00000000-0000-0000-0000-000000000000}"></defaultAction>
  </attributeactions>
  <attributetableconfig actionWidgetStyle="dropDown" sortExpression="" sortOrder="0">
    <columns>
      <column hidden="0" name="fid" type="field" width="-1"></column>
      <column hidden="0" name="topoid" type="field" width="-1"></column>
      <column hidden="0" name="createdate" type="field" width="-1"></column>
      <column hidden="0" name="objectmoddate" type="field" width="-1"></column>
      <column hidden="0" name="featuremoddate" type="field" width="-1"></column>
      <column hidden="0" name="classsubtype" type="field" width="-1"></column>
      <column hidden="0" name="featurereliabilitydate" type="field" width="-1"></column>
      <column hidden="0" name="attributereliabilitydate" type="field" width="-1"></column>
      <column hidden="0" name="capturesourcecode" type="field" width="-1"></column>
      <column hidden="0" name="capturemethodcode" type="field" width="-1"></column>
      <column hidden="0" name="planimetricaccuracy" type="field" width="-1"></column>
      <column hidden="0" name="verticalaccuracy" type="field" width="-1"></column>
      <column hidden="0" name="operationalstatus" type="field" width="-1"></column>
      <column hidden="0" name="roadnameoid" type="field" width="-1"></column>
      <column hidden="0" name="roadnamebase" type="field" width="-1"></column>
      <column hidden="0" name="roadnametype" type="field" width="-1"></column>
      <column hidden="0" name="roadnamesuffix" type="field" width="-1"></column>
      <column hidden="0" name="functionhierarchy" type="field" width="-1"></column>
      <column hidden="0" name="roadontype" type="field" width="-1"></column>
      <column hidden="0" name="surface" type="field" width="-1"></column>
      <column hidden="0" name="lanecount" type="field" width="-1"></column>
      <column hidden="0" name="roadnameextentoid" type="field" width="-1"></column>
      <column hidden="0" name="relevance" type="field" width="-1"></column>
      <column hidden="0" name="startdate" type="field" width="-1"></column>
      <column hidden="0" name="enddate" type="field" width="-1"></column>
      <column hidden="0" name="lastupdate" type="field" width="-1"></column>
      <column hidden="0" name="msoid" type="field" width="-1"></column>
      <column hidden="0" name="centroidid" type="field" width="-1"></column>
      <column hidden="0" name="shapeuuid" type="field" width="-1"></column>
      <column hidden="0" name="changetype" type="field" width="-1"></column>
      <column hidden="0" name="processstate" type="field" width="-1"></column>
      <column hidden="0" name="urbanity" type="field" width="-1"></column>
      <column hidden="0" name="objectid" type="field" width="-1"></column>
      <column hidden="0" name="shape_Length" type="field" width="-1"></column>
      <column hidden="1" type="actions" width="-1"></column>
    </columns>
  </attributetableconfig>
  <conditionalstyles>
    <rowstyles></rowstyles>
    <fieldstyles></fieldstyles>
  </conditionalstyles>
  <storedexpressions></storedexpressions>
  <editform tolerant="1"></editform>
  <editforminit></editforminit>
  <editforminitcodesource>0</editforminitcodesource>
  <editforminitfilepath></editforminitfilepath>
  <editforminitcode><![CDATA[# -*- coding: utf-8 -*-
"""
QGIS forms can have a Python function that is called when the form is
opened.

Use this function to add extra logic to your forms.

Enter the name of the function in the "Python Init function"
field.
An example follows:
"""
from qgis.PyQt.QtWidgets import QWidget

def my_form_open(dialog, layer, feature):
    geom = feature.geometry()
    control = dialog.findChild(QWidget, "MyLineEdit")
]]></editforminitcode>
  <featformsuppress>0</featformsuppress>
  <editorlayout>generatedlayout</editorlayout>
  <editable>
    <field editable="1" name="OBJECTID"></field>
    <field editable="1" name="Shape__Length"></field>
    <field editable="1" name="attributereliabilitydate"></field>
    <field editable="1" name="capturemethodcode"></field>
    <field editable="1" name="capturesourcecode"></field>
    <field editable="1" name="centroidid"></field>
    <field editable="1" name="changetype"></field>
    <field editable="1" name="classsubtype"></field>
    <field editable="1" name="createdate"></field>
    <field editable="1" name="enddate"></field>
    <field editable="1" name="featuremoddate"></field>
    <field editable="1" name="featurereliabilitydate"></field>
    <field editable="1" name="fid"></field>
    <field editable="1" name="functionhierarchy"></field>
    <field editable="1" name="lanecount"></field>
    <field editable="1" name="lastupdate"></field>
    <field editable="1" name="msoid"></field>
    <field editable="1" name="objectid"></field>
    <field editable="1" name="objectmoddate"></field>
    <field editable="1" name="operationalstatus"></field>
    <field editable="1" name="planimetricaccuracy"></field>
    <field editable="1" name="processstate"></field>
    <field editable="1" name="relevance"></field>
    <field editable="1" name="roadnamebase"></field>
    <field editable="1" name="roadnameextentoid"></field>
    <field editable="1" name="roadnameoid"></field>
    <field editable="1" name="roadnamesuffix"></field>
    <field editable="1" name="roadnametype"></field>
    <field editable="1" name="roadontype"></field>
    <field editable="1" name="shape_Length"></field>
    <field editable="1" name="shapeuuid"></field>
    <field editable="1" name="startdate"></field>
    <field editable="1" name="surface"></field>
    <field editable="1" name="topoid"></field>
    <field editable="1" name="urbanity"></field>
    <field editable="1" name="verticalaccuracy"></field>
  </editable>
  <labelOnTop>
    <field labelOnTop="0" name="OBJECTID"></field>
    <field labelOnTop="0" name="Shape__Length"></field>
    <field labelOnTop="0" name="attributereliabilitydate"></field>
    <field labelOnTop="0" name="capturemethodcode"></field>
    <field labelOnTop="0" name="capturesourcecode"></field>
    <field labelOnTop="0" name="centroidid"></field>
    <field labelOnTop="0" name="changetype"></field>
    <field labelOnTop="0" name="classsubtype"></field>
    <field labelOnTop="0" name="createdate"></field>
    <field labelOnTop="0" name="enddate"></field>
    <field labelOnTop="0" name="featuremoddate"></field>
    <field labelOnTop="0" name="featurereliabilitydate"></field>
    <field labelOnTop="0" name="fid"></field>
    <field labelOnTop="0" name="functionhierarchy"></field>
    <field labelOnTop="0" name="lanecount"></field>
    <field labelOnTop="0" name="lastupdate"></field>
    <field labelOnTop="0" name="msoid"></field>
    <field labelOnTop="0" name="objectid"></field>
    <field labelOnTop="0" name="objectmoddate"></field>
    <field labelOnTop="0" name="operationalstatus"></field>
    <field labelOnTop="0" name="planimetricaccuracy"></field>
    <field labelOnTop="0" name="processstate"></field>
    <field labelOnTop="0" name="relevance"></field>
    <field labelOnTop="0" name="roadnamebase"></field>
    <field labelOnTop="0" name="roadnameextentoid"></field>
    <field labelOnTop="0" name="roadnameoid"></field>
    <field labelOnTop="0" name="roadnamesuffix"></field>
    <field labelOnTop="0" name="roadnametype"></field>
    <field labelOnTop="0" name="roadontype"></field>
    <field labelOnTop="0" name="shape_Length"></field>
    <field labelOnTop="0" name="shapeuuid"></field>
    <field labelOnTop="0" name="startdate"></field>
    <field labelOnTop="0" name="surface"></field>
    <field labelOnTop="0" name="topoid"></field>
    <field labelOnTop="0" name="urbanity"></field>
    <field labelOnTop="0" name="verticalaccuracy"></field>
  </labelOnTop>
  <reuseLastValue>
    <field name="OBJECTID" reuseLastValue="0"></field>
    <field name="Shape__Length" reuseLastValue="0"></field>
    <field name="attributereliabilitydate" reuseLastValue="0"></field>
    <field name="capturemethodcode" reuseLastValue="0"></field>
    <field name="capturesourcecode" reuseLastValue="0"></field>
    <field name="centroidid" reuseLastValue="0"></field>
    <field name="changetype" reuseLastValue="0"></field>
    <field name="classsubtype" reuseLastValue="0"></field>
    <field name="createdate" reuseLastValue="0"></field>
    <field name="enddate" reuseLastValue="0"></field>
    <field name="featuremoddate" reuseLastValue="0"></field>
    <field name="featurereliabilitydate" reuseLastValue="0"></field>
    <field name="fid" reuseLastValue="0"></field>
    <field name="functionhierarchy" reuseLastValue="0"></field>
    <field name="lanecount" reuseLastValue="0"></field>
    <field name="lastupdate" reuseLastValue="0"></field>
    <field name="msoid" reuseLastValue="0"></field>
    <field name="objectid" reuseLastValue="0"></field>
    <field name="objectmoddate" reuseLastValue="0"></field>
    <field name="operationalstatus" reuseLastValue="0"></field>
    <field name="planimetricaccuracy" reuseLastValue="0"></field>
    <field name="processstate" reuseLastValue="0"></field>
    <field name="relevance" reuseLastValue="0"></field>
    <field name="roadnamebase" reuseLastValue="0"></field>
    <field name="roadnameextentoid" reuseLastValue="0"></field>
    <field name="roadnameoid" reuseLastValue="0"></field>
    <field name="roadnamesuffix" reuseLastValue="0"></field>
    <field name="roadnametype" reuseLastValue="0"></field>
    <field name="roadontype" reuseLastValue="0"></field>
    <field name="shape_Length" reuseLastValue="0"></field>
    <field name="shapeuuid" reuseLastValue="0"></field>
    <field name="startdate" reuseLastValue="0"></field>
    <field name="surface" reuseLastValue="0"></field>
    <field name="topoid" reuseLastValue="0"></field>
    <field name="urbanity" reuseLastValue="0"></field>
    <field name="verticalaccuracy" reuseLastValue="0"></field>
  </reuseLastValue>
  <dataDefinedFieldProperties></dataDefinedFieldProperties>
  <widgets></widgets>
  <previewExpression>"roadnameoid"</previewExpression>
  <mapTip enabled="1"></mapTip>
  <layerGeometryType>1</layerGeometryType>
</qgis>