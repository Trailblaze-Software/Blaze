<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="0" maxScale="0" minScale="100000000" readOnly="0" simplifyAlgorithm="0" simplifyDrawingHints="1" simplifyDrawingTol="1" simplifyLocal="1" simplifyMaxScale="1" styleCategories="LayerConfiguration|Symbology|Labeling|Fields|Rendering" symbologyReferenceScale="-1" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="1" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{90a5cbaa-c1d8-49da-820e-fd9b053d63e8}">
      <rule filter="roadontype in (4,7)" key="{855240d1-685f-48e1-b9da-fc329ea593e5}" label="Ford/Floodway" scalemaxdenom="75000" symbol="0"></rule>
      <rule description="Bridge width set by 'Data defined override', layer variable @road_width" filter="roadontype in (2,5,6)" key="{6bf31a68-44aa-4dc1-a641-4511ccc5c2d5}" label="Bridge" scalemaxdenom="75000" scalemindenom="1000" symbol="1"></rule>
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
            <Option name="capstyle" type="QString" value="flat"></Option>
            <Option name="customdash" type="QString" value="1.2;0.3;1.2;0.8"></Option>
            <Option name="customdash_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="dash_pattern_offset" type="QString" value="0"></Option>
            <Option name="dash_pattern_offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="dash_pattern_offset_unit" type="QString" value="MM"></Option>
            <Option name="draw_inside_polygon" type="QString" value="0"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="line_color" type="QString" value="4,5,4,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.28"></Option>
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
  <fieldConfiguration>
    <field configurationFlags="NoFlag" name="fid"></field>
    <field configurationFlags="NoFlag" name="objectid"></field>
    <field configurationFlags="NoFlag" name="topoid"></field>
    <field configurationFlags="NoFlag" name="createdate"></field>
    <field configurationFlags="NoFlag" name="objectmoddate"></field>
    <field configurationFlags="NoFlag" name="featuremoddate"></field>
    <field configurationFlags="NoFlag" name="classsubtype"></field>
    <field configurationFlags="NoFlag" name="featurereliabilitydate"></field>
    <field configurationFlags="NoFlag" name="attributereliabilitydate"></field>
    <field configurationFlags="NoFlag" name="capturesourcecode"></field>
    <field configurationFlags="NoFlag" name="capturemethodcode"></field>
    <field configurationFlags="NoFlag" name="planimetricaccuracy"></field>
    <field configurationFlags="NoFlag" name="verticalaccuracy"></field>
    <field configurationFlags="NoFlag" name="operationalstatus"></field>
    <field configurationFlags="NoFlag" name="roadnameoid"></field>
    <field configurationFlags="NoFlag" name="roadnamebase"></field>
    <field configurationFlags="NoFlag" name="roadnametype"></field>
    <field configurationFlags="NoFlag" name="roadnamesuffix"></field>
    <field configurationFlags="NoFlag" name="functionhierarchy"></field>
    <field configurationFlags="NoFlag" name="roadontype"></field>
    <field configurationFlags="NoFlag" name="surface"></field>
    <field configurationFlags="NoFlag" name="lanecount"></field>
    <field configurationFlags="NoFlag" name="roadnameextentoid"></field>
    <field configurationFlags="NoFlag" name="relevance"></field>
    <field configurationFlags="NoFlag" name="startdate"></field>
    <field configurationFlags="NoFlag" name="enddate"></field>
    <field configurationFlags="NoFlag" name="lastupdate"></field>
    <field configurationFlags="NoFlag" name="msoid"></field>
    <field configurationFlags="NoFlag" name="centroidid"></field>
    <field configurationFlags="NoFlag" name="shapeuuid"></field>
    <field configurationFlags="NoFlag" name="changetype"></field>
    <field configurationFlags="NoFlag" name="processstate"></field>
    <field configurationFlags="NoFlag" name="urbanity"></field>
    <field configurationFlags="NoFlag" name="shape_Length"></field>
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
  <previewExpression>"roadnameoid"</previewExpression>
  <layerGeometryType>1</layerGeometryType>
</qgis>