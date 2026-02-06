<!DOCTYPE qgis PUBLIC 'http://mrcc.com/qgis.dtd' 'SYSTEM'>
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="0" readOnly="0" version="3.34.3-Prizren" simplifyDrawingTol="1" maxScale="0" minScale="100000000" symbologyReferenceScale="-1" simplifyDrawingHints="1" simplifyAlgorithm="0" styleCategories="LayerConfiguration|Symbology|Symbology3D|Labeling|Fields|Forms|Actions|MapTips|Diagrams|AttributeTable|Rendering" simplifyLocal="1" simplifyMaxScale="1">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 forceraster="0" type="RuleRenderer" referencescale="-1" enableorderby="1" symbollevels="0">
    <rules key="{90a5cbaa-c1d8-49da-820e-fd9b053d63e8}">
      <rule label="Ford/Floodway" filter="roadontype in (4,7)" key="{855240d1-685f-48e1-b9da-fc329ea593e5}" symbol="0"/>
      <rule label="Bridge" description="Bridge width set by 'Data defined override', layer variable @road_width" filter="roadontype in (2,5,6)" key="{6bf31a68-44aa-4dc1-a641-4511ccc5c2d5}" symbol="1"/>
      <rule label="Sealed" description="Road width set by 'Data defined override', layer variable @road_width" filter="surface in (0, 1) and (functionhierarchy &lt; 8 or functionhierarchy = 10)" key="{f6d75ae4-08e2-48c3-8753-895dc1a193cf}" symbol="2"/>
      <rule label="Unsealed" description="Road width set by 'Data defined override', layer variable @road_width" filter="surface = 2 and (functionhierarchy &lt; 9 ) and not classsubtype = 5" key="{43bec151-7591-4f3c-a021-99fafda9dac1}" symbol="3"/>
      <rule label="2wd - dry weather" filter="surface = 2  and functionhierarchy &lt; 9 and classsubtype = 5" key="{ca095e73-3de9-426e-9ac5-8a8ae8b3b196}" symbol="4"/>
      <rule label="4wd" filter="surface in (3, 4) and functionhierarchy = 8" key="{b3d3b67f-b93f-452f-b527-5eda2138dfcd}" symbol="5"/>
      <rule label="Path" filter="functionhierarchy = 9" key="{db68cda4-6d6e-498b-879f-bc4510eaa904}" symbol="6"/>
      <rule label="Overgrown" filter="functionhierarchy = 98" key="{ab0284d8-24a9-488c-ada1-540683173abe}" symbol="7"/>
      <rule label="Delete" filter="functionhierarchy = 99" checkstate="0" key="{33d3ba80-0bef-4110-8661-0471d10ae14b}" symbol="8"/>
      <rule label="Safety patrol" filter="relevance = 100" key="{6219d35d-4246-4c07-bf90-e7011bc6c6ea}" symbol="9"/>
      <rule label="Unkown" filter="ELSE" key="{5c0dfca1-a5ab-4b68-9e2c-a8ce46eacb60}" symbol="10"/>
    </rules>
    <symbols>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="0" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{e7d9f626-ce94-4003-b033-f6fa1a7cb96e}" locked="0" class="SimpleLine" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="align_dash_pattern"/>
            <Option value="square" type="QString" name="capstyle"/>
            <Option value="5;2" type="QString" name="customdash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="customdash_map_unit_scale"/>
            <Option value="MM" type="QString" name="customdash_unit"/>
            <Option value="0" type="QString" name="dash_pattern_offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="dash_pattern_offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="dash_pattern_offset_unit"/>
            <Option value="0" type="QString" name="draw_inside_polygon"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="1,115,255,255" type="QString" name="line_color"/>
            <Option value="solid" type="QString" name="line_style"/>
            <Option value="1.2" type="QString" name="line_width"/>
            <Option value="MM" type="QString" name="line_width_unit"/>
            <Option value="0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="0" type="QString" name="ring_filter"/>
            <Option value="0" type="QString" name="trim_distance_end"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_end_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_end_unit"/>
            <Option value="0" type="QString" name="trim_distance_start"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_start_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_start_unit"/>
            <Option value="0" type="QString" name="tweak_dash_pattern_on_corners"/>
            <Option value="0" type="QString" name="use_custom_dash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option type="Map" name="properties">
                <Option type="Map" name="outlineWidth">
                  <Option value="true" type="bool" name="active"/>
                  <Option value="array_get(string_to_array(@road_width), functionhierarchy) + 0.6" type="QString" name="expression"/>
                  <Option value="3" type="int" name="type"/>
                </Option>
              </Option>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="1" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{5e280985-06e3-4541-835a-7380f2a045c8}" locked="0" class="SimpleLine" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="align_dash_pattern"/>
            <Option value="square" type="QString" name="capstyle"/>
            <Option value="5;2" type="QString" name="customdash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="customdash_map_unit_scale"/>
            <Option value="MM" type="QString" name="customdash_unit"/>
            <Option value="0" type="QString" name="dash_pattern_offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="dash_pattern_offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="dash_pattern_offset_unit"/>
            <Option value="0" type="QString" name="draw_inside_polygon"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0,0,255" type="QString" name="line_color"/>
            <Option value="solid" type="QString" name="line_style"/>
            <Option value="1.2" type="QString" name="line_width"/>
            <Option value="MM" type="QString" name="line_width_unit"/>
            <Option value="0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="0" type="QString" name="ring_filter"/>
            <Option value="0" type="QString" name="trim_distance_end"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_end_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_end_unit"/>
            <Option value="0" type="QString" name="trim_distance_start"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_start_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_start_unit"/>
            <Option value="0" type="QString" name="tweak_dash_pattern_on_corners"/>
            <Option value="0" type="QString" name="use_custom_dash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option type="Map" name="properties">
                <Option type="Map" name="outlineWidth">
                  <Option value="true" type="bool" name="active"/>
                  <Option value="array_get(string_to_array(@road_width), functionhierarchy) + 0.6" type="QString" name="expression"/>
                  <Option value="3" type="int" name="type"/>
                </Option>
              </Option>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="10" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{3200153a-4c20-4989-9c15-8b8d53a34ce5}" locked="0" class="SimpleLine" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="align_dash_pattern"/>
            <Option value="square" type="QString" name="capstyle"/>
            <Option value="5;2" type="QString" name="customdash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="customdash_map_unit_scale"/>
            <Option value="MM" type="QString" name="customdash_unit"/>
            <Option value="0" type="QString" name="dash_pattern_offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="dash_pattern_offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="dash_pattern_offset_unit"/>
            <Option value="0" type="QString" name="draw_inside_polygon"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,255,0,255" type="QString" name="line_color"/>
            <Option value="solid" type="QString" name="line_style"/>
            <Option value="3" type="QString" name="line_width"/>
            <Option value="MM" type="QString" name="line_width_unit"/>
            <Option value="0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="0" type="QString" name="ring_filter"/>
            <Option value="0" type="QString" name="trim_distance_end"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_end_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_end_unit"/>
            <Option value="0" type="QString" name="trim_distance_start"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_start_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_start_unit"/>
            <Option value="0" type="QString" name="tweak_dash_pattern_on_corners"/>
            <Option value="0" type="QString" name="use_custom_dash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="2" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{c5286670-a2d8-4b22-9f8f-f45fdaf3b7c0}" locked="0" class="SimpleLine" enabled="1" pass="10">
          <Option type="Map">
            <Option value="0" type="QString" name="align_dash_pattern"/>
            <Option value="square" type="QString" name="capstyle"/>
            <Option value="5;2" type="QString" name="customdash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="customdash_map_unit_scale"/>
            <Option value="MM" type="QString" name="customdash_unit"/>
            <Option value="0" type="QString" name="dash_pattern_offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="dash_pattern_offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="dash_pattern_offset_unit"/>
            <Option value="0" type="QString" name="draw_inside_polygon"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="255,0,0,255" type="QString" name="line_color"/>
            <Option value="solid" type="QString" name="line_style"/>
            <Option value="0.4" type="QString" name="line_width"/>
            <Option value="MM" type="QString" name="line_width_unit"/>
            <Option value="0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="0" type="QString" name="ring_filter"/>
            <Option value="0" type="QString" name="trim_distance_end"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_end_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_end_unit"/>
            <Option value="0" type="QString" name="trim_distance_start"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_start_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_start_unit"/>
            <Option value="0" type="QString" name="tweak_dash_pattern_on_corners"/>
            <Option value="0" type="QString" name="use_custom_dash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option type="Map" name="properties">
                <Option type="Map" name="outlineWidth">
                  <Option value="true" type="bool" name="active"/>
                  <Option value="array_get(string_to_array(@road_width), functionhierarchy)" type="QString" name="expression"/>
                  <Option value="3" type="int" name="type"/>
                </Option>
              </Option>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="3" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{68d87203-2384-4dfc-81b2-6d374743821a}" locked="0" class="SimpleLine" enabled="1" pass="9">
          <Option type="Map">
            <Option value="0" type="QString" name="align_dash_pattern"/>
            <Option value="square" type="QString" name="capstyle"/>
            <Option value="5;2" type="QString" name="customdash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="customdash_map_unit_scale"/>
            <Option value="MM" type="QString" name="customdash_unit"/>
            <Option value="0" type="QString" name="dash_pattern_offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="dash_pattern_offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="dash_pattern_offset_unit"/>
            <Option value="0" type="QString" name="draw_inside_polygon"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0,0,255" type="QString" name="line_color"/>
            <Option value="solid" type="QString" name="line_style"/>
            <Option value="0.4" type="QString" name="line_width"/>
            <Option value="MM" type="QString" name="line_width_unit"/>
            <Option value="0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="0" type="QString" name="ring_filter"/>
            <Option value="0" type="QString" name="trim_distance_end"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_end_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_end_unit"/>
            <Option value="0" type="QString" name="trim_distance_start"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_start_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_start_unit"/>
            <Option value="0" type="QString" name="tweak_dash_pattern_on_corners"/>
            <Option value="0" type="QString" name="use_custom_dash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option type="Map" name="properties">
                <Option type="Map" name="outlineWidth">
                  <Option value="true" type="bool" name="active"/>
                  <Option value="array_get(string_to_array(@road_width), functionhierarchy)" type="QString" name="expression"/>
                  <Option value="3" type="int" name="type"/>
                </Option>
              </Option>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="4" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{bdb9283e-2b02-40c5-98a7-7e87d1b1f3f2}" locked="0" class="SimpleLine" enabled="1" pass="8">
          <Option type="Map">
            <Option value="0" type="QString" name="align_dash_pattern"/>
            <Option value="square" type="QString" name="capstyle"/>
            <Option value="4;1.4" type="QString" name="customdash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="customdash_map_unit_scale"/>
            <Option value="MM" type="QString" name="customdash_unit"/>
            <Option value="0" type="QString" name="dash_pattern_offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="dash_pattern_offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="dash_pattern_offset_unit"/>
            <Option value="0" type="QString" name="draw_inside_polygon"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0,0,255" type="QString" name="line_color"/>
            <Option value="solid" type="QString" name="line_style"/>
            <Option value="0.35" type="QString" name="line_width"/>
            <Option value="MM" type="QString" name="line_width_unit"/>
            <Option value="0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="0" type="QString" name="ring_filter"/>
            <Option value="0" type="QString" name="trim_distance_end"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_end_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_end_unit"/>
            <Option value="0" type="QString" name="trim_distance_start"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_start_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_start_unit"/>
            <Option value="0" type="QString" name="tweak_dash_pattern_on_corners"/>
            <Option value="1" type="QString" name="use_custom_dash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="5" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{2326a95b-323c-4d99-8a2b-f41efa47494c}" locked="0" class="SimpleLine" enabled="1" pass="7">
          <Option type="Map">
            <Option value="0" type="QString" name="align_dash_pattern"/>
            <Option value="square" type="QString" name="capstyle"/>
            <Option value="2;0.7" type="QString" name="customdash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="customdash_map_unit_scale"/>
            <Option value="MM" type="QString" name="customdash_unit"/>
            <Option value="0" type="QString" name="dash_pattern_offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="dash_pattern_offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="dash_pattern_offset_unit"/>
            <Option value="0" type="QString" name="draw_inside_polygon"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0,0,255" type="QString" name="line_color"/>
            <Option value="solid" type="QString" name="line_style"/>
            <Option value="0.3" type="QString" name="line_width"/>
            <Option value="MM" type="QString" name="line_width_unit"/>
            <Option value="0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="0" type="QString" name="ring_filter"/>
            <Option value="0" type="QString" name="trim_distance_end"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_end_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_end_unit"/>
            <Option value="0" type="QString" name="trim_distance_start"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_start_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_start_unit"/>
            <Option value="0" type="QString" name="tweak_dash_pattern_on_corners"/>
            <Option value="1" type="QString" name="use_custom_dash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="6" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{d253d42d-f5d0-42c7-a7df-af6d92c9e4fd}" locked="0" class="SimpleLine" enabled="1" pass="6">
          <Option type="Map">
            <Option value="0" type="QString" name="align_dash_pattern"/>
            <Option value="square" type="QString" name="capstyle"/>
            <Option value="1.5;0.5" type="QString" name="customdash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="customdash_map_unit_scale"/>
            <Option value="MM" type="QString" name="customdash_unit"/>
            <Option value="0" type="QString" name="dash_pattern_offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="dash_pattern_offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="dash_pattern_offset_unit"/>
            <Option value="0" type="QString" name="draw_inside_polygon"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0,0,255" type="QString" name="line_color"/>
            <Option value="dot" type="QString" name="line_style"/>
            <Option value="0.3" type="QString" name="line_width"/>
            <Option value="MM" type="QString" name="line_width_unit"/>
            <Option value="0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="0" type="QString" name="ring_filter"/>
            <Option value="0" type="QString" name="trim_distance_end"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_end_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_end_unit"/>
            <Option value="0" type="QString" name="trim_distance_start"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_start_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_start_unit"/>
            <Option value="0" type="QString" name="tweak_dash_pattern_on_corners"/>
            <Option value="0" type="QString" name="use_custom_dash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="7" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{1d34bb36-2774-4200-812e-095f8a2b5b19}" locked="0" class="SimpleLine" enabled="1" pass="5">
          <Option type="Map">
            <Option value="0" type="QString" name="align_dash_pattern"/>
            <Option value="square" type="QString" name="capstyle"/>
            <Option value="2;2" type="QString" name="customdash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="customdash_map_unit_scale"/>
            <Option value="MM" type="QString" name="customdash_unit"/>
            <Option value="0" type="QString" name="dash_pattern_offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="dash_pattern_offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="dash_pattern_offset_unit"/>
            <Option value="0" type="QString" name="draw_inside_polygon"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="4,5,4,255" type="QString" name="line_color"/>
            <Option value="solid" type="QString" name="line_style"/>
            <Option value="0.25" type="QString" name="line_width"/>
            <Option value="MM" type="QString" name="line_width_unit"/>
            <Option value="0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="0" type="QString" name="ring_filter"/>
            <Option value="0" type="QString" name="trim_distance_end"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_end_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_end_unit"/>
            <Option value="0" type="QString" name="trim_distance_start"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_start_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_start_unit"/>
            <Option value="0" type="QString" name="tweak_dash_pattern_on_corners"/>
            <Option value="1" type="QString" name="use_custom_dash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="8" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{689fc948-09b2-4ff0-8324-17da7df8007a}" locked="0" class="HashLine" enabled="1" pass="0">
          <Option type="Map">
            <Option value="4" type="QString" name="average_angle_length"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="average_angle_map_unit_scale"/>
            <Option value="MM" type="QString" name="average_angle_unit"/>
            <Option value="0" type="QString" name="hash_angle"/>
            <Option value="1" type="QString" name="hash_length"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="hash_length_map_unit_scale"/>
            <Option value="MM" type="QString" name="hash_length_unit"/>
            <Option value="3" type="QString" name="interval"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="interval_map_unit_scale"/>
            <Option value="MM" type="QString" name="interval_unit"/>
            <Option value="0" type="QString" name="offset"/>
            <Option value="0" type="QString" name="offset_along_line"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_along_line_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_along_line_unit"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="true" type="bool" name="place_on_every_part"/>
            <Option value="Interval" type="QString" name="placements"/>
            <Option value="0" type="QString" name="ring_filter"/>
            <Option value="1" type="QString" name="rotate"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
          <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="@8@0" clip_to_extent="1" alpha="1">
            <data_defined_properties>
              <Option type="Map">
                <Option value="" type="QString" name="name"/>
                <Option name="properties"/>
                <Option value="collection" type="QString" name="type"/>
              </Option>
            </data_defined_properties>
            <layer id="{b6e84f08-f24a-4b2b-8faa-6db58c1df7fb}" locked="0" class="SimpleLine" enabled="1" pass="0">
              <Option type="Map">
                <Option value="0" type="QString" name="align_dash_pattern"/>
                <Option value="square" type="QString" name="capstyle"/>
                <Option value="5;2" type="QString" name="customdash"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="customdash_map_unit_scale"/>
                <Option value="MM" type="QString" name="customdash_unit"/>
                <Option value="0" type="QString" name="dash_pattern_offset"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="dash_pattern_offset_map_unit_scale"/>
                <Option value="MM" type="QString" name="dash_pattern_offset_unit"/>
                <Option value="0" type="QString" name="draw_inside_polygon"/>
                <Option value="bevel" type="QString" name="joinstyle"/>
                <Option value="255,0,0,255" type="QString" name="line_color"/>
                <Option value="solid" type="QString" name="line_style"/>
                <Option value="0.5" type="QString" name="line_width"/>
                <Option value="MM" type="QString" name="line_width_unit"/>
                <Option value="0" type="QString" name="offset"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                <Option value="MM" type="QString" name="offset_unit"/>
                <Option value="0" type="QString" name="ring_filter"/>
                <Option value="0" type="QString" name="trim_distance_end"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_end_map_unit_scale"/>
                <Option value="MM" type="QString" name="trim_distance_end_unit"/>
                <Option value="0" type="QString" name="trim_distance_start"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_start_map_unit_scale"/>
                <Option value="MM" type="QString" name="trim_distance_start_unit"/>
                <Option value="0" type="QString" name="tweak_dash_pattern_on_corners"/>
                <Option value="0" type="QString" name="use_custom_dash"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
              </Option>
              <data_defined_properties>
                <Option type="Map">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
              </data_defined_properties>
            </layer>
          </symbol>
        </layer>
      </symbol>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="9" clip_to_extent="1" alpha="0.3">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{3eff52f4-6bd0-43e3-bb45-1d996eb70735}" locked="0" class="SimpleLine" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="align_dash_pattern"/>
            <Option value="square" type="QString" name="capstyle"/>
            <Option value="5;2" type="QString" name="customdash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="customdash_map_unit_scale"/>
            <Option value="MM" type="QString" name="customdash_unit"/>
            <Option value="0" type="QString" name="dash_pattern_offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="dash_pattern_offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="dash_pattern_offset_unit"/>
            <Option value="0" type="QString" name="draw_inside_polygon"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="255,255,0,255" type="QString" name="line_color"/>
            <Option value="solid" type="QString" name="line_style"/>
            <Option value="3.5" type="QString" name="line_width"/>
            <Option value="MM" type="QString" name="line_width_unit"/>
            <Option value="0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="0" type="QString" name="ring_filter"/>
            <Option value="0" type="QString" name="trim_distance_end"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_end_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_end_unit"/>
            <Option value="0" type="QString" name="trim_distance_start"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_start_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_start_unit"/>
            <Option value="0" type="QString" name="tweak_dash_pattern_on_corners"/>
            <Option value="0" type="QString" name="use_custom_dash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
    </symbols>
  </renderer-v2>
  <selection mode="Default">
    <selectionColor invalid="1"/>
    <selectionSymbol>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{045dbd13-7732-4d98-8c20-32abcc3fb36b}" locked="0" class="SimpleLine" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="align_dash_pattern"/>
            <Option value="square" type="QString" name="capstyle"/>
            <Option value="5;2" type="QString" name="customdash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="customdash_map_unit_scale"/>
            <Option value="MM" type="QString" name="customdash_unit"/>
            <Option value="0" type="QString" name="dash_pattern_offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="dash_pattern_offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="dash_pattern_offset_unit"/>
            <Option value="0" type="QString" name="draw_inside_polygon"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="35,35,35,255" type="QString" name="line_color"/>
            <Option value="solid" type="QString" name="line_style"/>
            <Option value="0.26" type="QString" name="line_width"/>
            <Option value="MM" type="QString" name="line_width_unit"/>
            <Option value="0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="0" type="QString" name="ring_filter"/>
            <Option value="0" type="QString" name="trim_distance_end"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_end_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_end_unit"/>
            <Option value="0" type="QString" name="trim_distance_start"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_start_map_unit_scale"/>
            <Option value="MM" type="QString" name="trim_distance_start_unit"/>
            <Option value="0" type="QString" name="tweak_dash_pattern_on_corners"/>
            <Option value="0" type="QString" name="use_custom_dash"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
    </selectionSymbol>
  </selection>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
  <layerOpacity>1</layerOpacity>
  <SingleCategoryDiagramRenderer diagramType="Histogram" attributeLegend="1">
    <DiagramCategory sizeType="MM" enabled="0" opacity="1" lineSizeScale="3x:0,0,0,0,0,0" penWidth="0" height="15" penColor="#000000" sizeScale="3x:0,0,0,0,0,0" direction="0" maxScaleDenominator="1e+08" backgroundAlpha="255" scaleBasedVisibility="0" penAlpha="255" spacingUnit="MM" lineSizeType="MM" spacing="5" labelPlacementMethod="XHeight" barWidth="5" spacingUnitScale="3x:0,0,0,0,0,0" minScaleDenominator="0" rotationOffset="270" showAxis="1" backgroundColor="#ffffff" minimumSize="0" scaleDependency="Area" width="15" diagramOrientation="Up">
      <fontProperties underline="0" description="MS Shell Dlg 2,8.25,-1,5,50,0,0,0,0,0" bold="0" italic="0" strikethrough="0" style=""/>
      <attribute label="" color="#000000" field="" colorOpacity="1"/>
      <axisSymbol>
        <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="" clip_to_extent="1" alpha="1">
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
          <layer id="{03860f5a-f41d-4aea-8226-063aecbf4220}" locked="0" class="SimpleLine" enabled="1" pass="0">
            <Option type="Map">
              <Option value="0" type="QString" name="align_dash_pattern"/>
              <Option value="square" type="QString" name="capstyle"/>
              <Option value="5;2" type="QString" name="customdash"/>
              <Option value="3x:0,0,0,0,0,0" type="QString" name="customdash_map_unit_scale"/>
              <Option value="MM" type="QString" name="customdash_unit"/>
              <Option value="0" type="QString" name="dash_pattern_offset"/>
              <Option value="3x:0,0,0,0,0,0" type="QString" name="dash_pattern_offset_map_unit_scale"/>
              <Option value="MM" type="QString" name="dash_pattern_offset_unit"/>
              <Option value="0" type="QString" name="draw_inside_polygon"/>
              <Option value="bevel" type="QString" name="joinstyle"/>
              <Option value="35,35,35,255" type="QString" name="line_color"/>
              <Option value="solid" type="QString" name="line_style"/>
              <Option value="0.26" type="QString" name="line_width"/>
              <Option value="MM" type="QString" name="line_width_unit"/>
              <Option value="0" type="QString" name="offset"/>
              <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
              <Option value="MM" type="QString" name="offset_unit"/>
              <Option value="0" type="QString" name="ring_filter"/>
              <Option value="0" type="QString" name="trim_distance_end"/>
              <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_end_map_unit_scale"/>
              <Option value="MM" type="QString" name="trim_distance_end_unit"/>
              <Option value="0" type="QString" name="trim_distance_start"/>
              <Option value="3x:0,0,0,0,0,0" type="QString" name="trim_distance_start_map_unit_scale"/>
              <Option value="MM" type="QString" name="trim_distance_start_unit"/>
              <Option value="0" type="QString" name="tweak_dash_pattern_on_corners"/>
              <Option value="0" type="QString" name="use_custom_dash"/>
              <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
            </Option>
            <data_defined_properties>
              <Option type="Map">
                <Option value="" type="QString" name="name"/>
                <Option name="properties"/>
                <Option value="collection" type="QString" name="type"/>
              </Option>
            </data_defined_properties>
          </layer>
        </symbol>
      </axisSymbol>
    </DiagramCategory>
  </SingleCategoryDiagramRenderer>
  <DiagramLayerSettings linePlacementFlags="18" dist="0" obstacle="0" zIndex="0" showAll="1" priority="0" placement="2">
    <properties>
      <Option type="Map">
        <Option value="" type="QString" name="name"/>
        <Option name="properties"/>
        <Option value="collection" type="QString" name="type"/>
      </Option>
    </properties>
  </DiagramLayerSettings>
  <fieldConfiguration>
    <field configurationFlags="NoFlag" name="fid">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="objectid">
      <editWidget type="Range">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="topoid">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="createdate">
      <editWidget type="DateTime">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="objectmoddate">
      <editWidget type="DateTime">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="featuremoddate">
      <editWidget type="DateTime">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="classsubtype">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="featurereliabilitydate">
      <editWidget type="DateTime">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="attributereliabilitydate">
      <editWidget type="DateTime">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="capturesourcecode">
      <editWidget type="Range">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="capturemethodcode">
      <editWidget type="Range">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="planimetricaccuracy">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="verticalaccuracy">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="operationalstatus">
      <editWidget type="Range">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="roadnameoid">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="roadnamebase">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="roadnametype">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="roadnamesuffix">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="functionhierarchy">
      <editWidget type="Range">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="roadontype">
      <editWidget type="Range">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="surface">
      <editWidget type="Range">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="lanecount">
      <editWidget type="Range">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="roadnameextentoid">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="relevance">
      <editWidget type="Range">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="startdate">
      <editWidget type="DateTime">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="enddate">
      <editWidget type="DateTime">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="lastupdate">
      <editWidget type="DateTime">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="msoid">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="centroidid">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="shapeuuid">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="changetype">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="processstate">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="urbanity">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="shape_Length">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
  </fieldConfiguration>
  <aliases>
    <alias index="0" name="" field="fid"/>
    <alias index="1" name="" field="objectid"/>
    <alias index="2" name="" field="topoid"/>
    <alias index="3" name="" field="createdate"/>
    <alias index="4" name="" field="objectmoddate"/>
    <alias index="5" name="" field="featuremoddate"/>
    <alias index="6" name="" field="classsubtype"/>
    <alias index="7" name="" field="featurereliabilitydate"/>
    <alias index="8" name="" field="attributereliabilitydate"/>
    <alias index="9" name="" field="capturesourcecode"/>
    <alias index="10" name="" field="capturemethodcode"/>
    <alias index="11" name="" field="planimetricaccuracy"/>
    <alias index="12" name="" field="verticalaccuracy"/>
    <alias index="13" name="" field="operationalstatus"/>
    <alias index="14" name="" field="roadnameoid"/>
    <alias index="15" name="" field="roadnamebase"/>
    <alias index="16" name="" field="roadnametype"/>
    <alias index="17" name="" field="roadnamesuffix"/>
    <alias index="18" name="" field="functionhierarchy"/>
    <alias index="19" name="" field="roadontype"/>
    <alias index="20" name="" field="surface"/>
    <alias index="21" name="" field="lanecount"/>
    <alias index="22" name="" field="roadnameextentoid"/>
    <alias index="23" name="" field="relevance"/>
    <alias index="24" name="" field="startdate"/>
    <alias index="25" name="" field="enddate"/>
    <alias index="26" name="" field="lastupdate"/>
    <alias index="27" name="" field="msoid"/>
    <alias index="28" name="" field="centroidid"/>
    <alias index="29" name="" field="shapeuuid"/>
    <alias index="30" name="" field="changetype"/>
    <alias index="31" name="" field="processstate"/>
    <alias index="32" name="" field="urbanity"/>
    <alias index="33" name="" field="shape_Length"/>
  </aliases>
  <splitPolicies>
    <policy policy="Duplicate" field="fid"/>
    <policy policy="Duplicate" field="objectid"/>
    <policy policy="Duplicate" field="topoid"/>
    <policy policy="Duplicate" field="createdate"/>
    <policy policy="Duplicate" field="objectmoddate"/>
    <policy policy="Duplicate" field="featuremoddate"/>
    <policy policy="Duplicate" field="classsubtype"/>
    <policy policy="Duplicate" field="featurereliabilitydate"/>
    <policy policy="Duplicate" field="attributereliabilitydate"/>
    <policy policy="Duplicate" field="capturesourcecode"/>
    <policy policy="Duplicate" field="capturemethodcode"/>
    <policy policy="Duplicate" field="planimetricaccuracy"/>
    <policy policy="Duplicate" field="verticalaccuracy"/>
    <policy policy="Duplicate" field="operationalstatus"/>
    <policy policy="Duplicate" field="roadnameoid"/>
    <policy policy="Duplicate" field="roadnamebase"/>
    <policy policy="Duplicate" field="roadnametype"/>
    <policy policy="Duplicate" field="roadnamesuffix"/>
    <policy policy="Duplicate" field="functionhierarchy"/>
    <policy policy="Duplicate" field="roadontype"/>
    <policy policy="Duplicate" field="surface"/>
    <policy policy="Duplicate" field="lanecount"/>
    <policy policy="Duplicate" field="roadnameextentoid"/>
    <policy policy="Duplicate" field="relevance"/>
    <policy policy="Duplicate" field="startdate"/>
    <policy policy="Duplicate" field="enddate"/>
    <policy policy="Duplicate" field="lastupdate"/>
    <policy policy="Duplicate" field="msoid"/>
    <policy policy="Duplicate" field="centroidid"/>
    <policy policy="Duplicate" field="shapeuuid"/>
    <policy policy="Duplicate" field="changetype"/>
    <policy policy="Duplicate" field="processstate"/>
    <policy policy="Duplicate" field="urbanity"/>
    <policy policy="Duplicate" field="shape_Length"/>
  </splitPolicies>
  <defaults>
    <default expression="" applyOnUpdate="0" field="fid"/>
    <default expression="" applyOnUpdate="0" field="objectid"/>
    <default expression="" applyOnUpdate="0" field="topoid"/>
    <default expression="" applyOnUpdate="0" field="createdate"/>
    <default expression="" applyOnUpdate="0" field="objectmoddate"/>
    <default expression="" applyOnUpdate="0" field="featuremoddate"/>
    <default expression="" applyOnUpdate="0" field="classsubtype"/>
    <default expression="" applyOnUpdate="0" field="featurereliabilitydate"/>
    <default expression="" applyOnUpdate="0" field="attributereliabilitydate"/>
    <default expression="" applyOnUpdate="0" field="capturesourcecode"/>
    <default expression="" applyOnUpdate="0" field="capturemethodcode"/>
    <default expression="" applyOnUpdate="0" field="planimetricaccuracy"/>
    <default expression="" applyOnUpdate="0" field="verticalaccuracy"/>
    <default expression="" applyOnUpdate="0" field="operationalstatus"/>
    <default expression="" applyOnUpdate="0" field="roadnameoid"/>
    <default expression="" applyOnUpdate="0" field="roadnamebase"/>
    <default expression="" applyOnUpdate="0" field="roadnametype"/>
    <default expression="" applyOnUpdate="0" field="roadnamesuffix"/>
    <default expression="" applyOnUpdate="0" field="functionhierarchy"/>
    <default expression="" applyOnUpdate="0" field="roadontype"/>
    <default expression="" applyOnUpdate="0" field="surface"/>
    <default expression="" applyOnUpdate="0" field="lanecount"/>
    <default expression="" applyOnUpdate="0" field="roadnameextentoid"/>
    <default expression="" applyOnUpdate="0" field="relevance"/>
    <default expression="" applyOnUpdate="0" field="startdate"/>
    <default expression="" applyOnUpdate="0" field="enddate"/>
    <default expression="" applyOnUpdate="0" field="lastupdate"/>
    <default expression="" applyOnUpdate="0" field="msoid"/>
    <default expression="" applyOnUpdate="0" field="centroidid"/>
    <default expression="" applyOnUpdate="0" field="shapeuuid"/>
    <default expression="" applyOnUpdate="0" field="changetype"/>
    <default expression="" applyOnUpdate="0" field="processstate"/>
    <default expression="" applyOnUpdate="0" field="urbanity"/>
    <default expression="" applyOnUpdate="0" field="shape_Length"/>
  </defaults>
  <constraints>
    <constraint notnull_strength="1" exp_strength="0" constraints="3" field="fid" unique_strength="1"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="objectid" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="topoid" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="createdate" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="objectmoddate" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="featuremoddate" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="classsubtype" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="featurereliabilitydate" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="attributereliabilitydate" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="capturesourcecode" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="capturemethodcode" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="planimetricaccuracy" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="verticalaccuracy" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="operationalstatus" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="roadnameoid" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="roadnamebase" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="roadnametype" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="roadnamesuffix" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="functionhierarchy" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="roadontype" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="surface" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="lanecount" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="roadnameextentoid" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="relevance" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="startdate" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="enddate" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="lastupdate" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="msoid" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="centroidid" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="shapeuuid" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="changetype" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="processstate" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="urbanity" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="shape_Length" unique_strength="0"/>
  </constraints>
  <constraintExpressions>
    <constraint desc="" field="fid" exp=""/>
    <constraint desc="" field="objectid" exp=""/>
    <constraint desc="" field="topoid" exp=""/>
    <constraint desc="" field="createdate" exp=""/>
    <constraint desc="" field="objectmoddate" exp=""/>
    <constraint desc="" field="featuremoddate" exp=""/>
    <constraint desc="" field="classsubtype" exp=""/>
    <constraint desc="" field="featurereliabilitydate" exp=""/>
    <constraint desc="" field="attributereliabilitydate" exp=""/>
    <constraint desc="" field="capturesourcecode" exp=""/>
    <constraint desc="" field="capturemethodcode" exp=""/>
    <constraint desc="" field="planimetricaccuracy" exp=""/>
    <constraint desc="" field="verticalaccuracy" exp=""/>
    <constraint desc="" field="operationalstatus" exp=""/>
    <constraint desc="" field="roadnameoid" exp=""/>
    <constraint desc="" field="roadnamebase" exp=""/>
    <constraint desc="" field="roadnametype" exp=""/>
    <constraint desc="" field="roadnamesuffix" exp=""/>
    <constraint desc="" field="functionhierarchy" exp=""/>
    <constraint desc="" field="roadontype" exp=""/>
    <constraint desc="" field="surface" exp=""/>
    <constraint desc="" field="lanecount" exp=""/>
    <constraint desc="" field="roadnameextentoid" exp=""/>
    <constraint desc="" field="relevance" exp=""/>
    <constraint desc="" field="startdate" exp=""/>
    <constraint desc="" field="enddate" exp=""/>
    <constraint desc="" field="lastupdate" exp=""/>
    <constraint desc="" field="msoid" exp=""/>
    <constraint desc="" field="centroidid" exp=""/>
    <constraint desc="" field="shapeuuid" exp=""/>
    <constraint desc="" field="changetype" exp=""/>
    <constraint desc="" field="processstate" exp=""/>
    <constraint desc="" field="urbanity" exp=""/>
    <constraint desc="" field="shape_Length" exp=""/>
  </constraintExpressions>
  <expressionfields/>
  <attributeactions>
    <defaultAction value="{00000000-0000-0000-0000-000000000000}" key="Canvas"/>
  </attributeactions>
  <attributetableconfig sortExpression="" actionWidgetStyle="dropDown" sortOrder="0">
    <columns>
      <column width="-1" type="field" name="fid" hidden="0"/>
      <column width="-1" type="field" name="topoid" hidden="0"/>
      <column width="-1" type="field" name="createdate" hidden="0"/>
      <column width="-1" type="field" name="objectmoddate" hidden="0"/>
      <column width="-1" type="field" name="featuremoddate" hidden="0"/>
      <column width="-1" type="field" name="classsubtype" hidden="0"/>
      <column width="-1" type="field" name="featurereliabilitydate" hidden="0"/>
      <column width="-1" type="field" name="attributereliabilitydate" hidden="0"/>
      <column width="-1" type="field" name="capturesourcecode" hidden="0"/>
      <column width="-1" type="field" name="capturemethodcode" hidden="0"/>
      <column width="-1" type="field" name="planimetricaccuracy" hidden="0"/>
      <column width="-1" type="field" name="verticalaccuracy" hidden="0"/>
      <column width="-1" type="field" name="operationalstatus" hidden="0"/>
      <column width="-1" type="field" name="roadnameoid" hidden="0"/>
      <column width="-1" type="field" name="roadnamebase" hidden="0"/>
      <column width="-1" type="field" name="roadnametype" hidden="0"/>
      <column width="-1" type="field" name="roadnamesuffix" hidden="0"/>
      <column width="-1" type="field" name="functionhierarchy" hidden="0"/>
      <column width="-1" type="field" name="roadontype" hidden="0"/>
      <column width="-1" type="field" name="surface" hidden="0"/>
      <column width="-1" type="field" name="lanecount" hidden="0"/>
      <column width="-1" type="field" name="roadnameextentoid" hidden="0"/>
      <column width="-1" type="field" name="relevance" hidden="0"/>
      <column width="-1" type="field" name="startdate" hidden="0"/>
      <column width="-1" type="field" name="enddate" hidden="0"/>
      <column width="-1" type="field" name="lastupdate" hidden="0"/>
      <column width="-1" type="field" name="msoid" hidden="0"/>
      <column width="-1" type="field" name="centroidid" hidden="0"/>
      <column width="-1" type="field" name="shapeuuid" hidden="0"/>
      <column width="-1" type="field" name="changetype" hidden="0"/>
      <column width="-1" type="field" name="processstate" hidden="0"/>
      <column width="-1" type="field" name="urbanity" hidden="0"/>
      <column width="-1" type="field" name="objectid" hidden="0"/>
      <column width="-1" type="field" name="shape_Length" hidden="0"/>
      <column width="-1" type="actions" hidden="1"/>
    </columns>
  </attributetableconfig>
  <conditionalstyles>
    <rowstyles/>
    <fieldstyles/>
  </conditionalstyles>
  <storedexpressions/>
  <editform tolerant="1"></editform>
  <editforminit/>
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
    <field editable="1" name="OBJECTID"/>
    <field editable="1" name="Shape__Length"/>
    <field editable="1" name="attributereliabilitydate"/>
    <field editable="1" name="capturemethodcode"/>
    <field editable="1" name="capturesourcecode"/>
    <field editable="1" name="centroidid"/>
    <field editable="1" name="changetype"/>
    <field editable="1" name="classsubtype"/>
    <field editable="1" name="createdate"/>
    <field editable="1" name="enddate"/>
    <field editable="1" name="featuremoddate"/>
    <field editable="1" name="featurereliabilitydate"/>
    <field editable="1" name="fid"/>
    <field editable="1" name="functionhierarchy"/>
    <field editable="1" name="lanecount"/>
    <field editable="1" name="lastupdate"/>
    <field editable="1" name="msoid"/>
    <field editable="1" name="objectid"/>
    <field editable="1" name="objectmoddate"/>
    <field editable="1" name="operationalstatus"/>
    <field editable="1" name="planimetricaccuracy"/>
    <field editable="1" name="processstate"/>
    <field editable="1" name="relevance"/>
    <field editable="1" name="roadnamebase"/>
    <field editable="1" name="roadnameextentoid"/>
    <field editable="1" name="roadnameoid"/>
    <field editable="1" name="roadnamesuffix"/>
    <field editable="1" name="roadnametype"/>
    <field editable="1" name="roadontype"/>
    <field editable="1" name="shape_Length"/>
    <field editable="1" name="shapeuuid"/>
    <field editable="1" name="startdate"/>
    <field editable="1" name="surface"/>
    <field editable="1" name="topoid"/>
    <field editable="1" name="urbanity"/>
    <field editable="1" name="verticalaccuracy"/>
  </editable>
  <labelOnTop>
    <field name="OBJECTID" labelOnTop="0"/>
    <field name="Shape__Length" labelOnTop="0"/>
    <field name="attributereliabilitydate" labelOnTop="0"/>
    <field name="capturemethodcode" labelOnTop="0"/>
    <field name="capturesourcecode" labelOnTop="0"/>
    <field name="centroidid" labelOnTop="0"/>
    <field name="changetype" labelOnTop="0"/>
    <field name="classsubtype" labelOnTop="0"/>
    <field name="createdate" labelOnTop="0"/>
    <field name="enddate" labelOnTop="0"/>
    <field name="featuremoddate" labelOnTop="0"/>
    <field name="featurereliabilitydate" labelOnTop="0"/>
    <field name="fid" labelOnTop="0"/>
    <field name="functionhierarchy" labelOnTop="0"/>
    <field name="lanecount" labelOnTop="0"/>
    <field name="lastupdate" labelOnTop="0"/>
    <field name="msoid" labelOnTop="0"/>
    <field name="objectid" labelOnTop="0"/>
    <field name="objectmoddate" labelOnTop="0"/>
    <field name="operationalstatus" labelOnTop="0"/>
    <field name="planimetricaccuracy" labelOnTop="0"/>
    <field name="processstate" labelOnTop="0"/>
    <field name="relevance" labelOnTop="0"/>
    <field name="roadnamebase" labelOnTop="0"/>
    <field name="roadnameextentoid" labelOnTop="0"/>
    <field name="roadnameoid" labelOnTop="0"/>
    <field name="roadnamesuffix" labelOnTop="0"/>
    <field name="roadnametype" labelOnTop="0"/>
    <field name="roadontype" labelOnTop="0"/>
    <field name="shape_Length" labelOnTop="0"/>
    <field name="shapeuuid" labelOnTop="0"/>
    <field name="startdate" labelOnTop="0"/>
    <field name="surface" labelOnTop="0"/>
    <field name="topoid" labelOnTop="0"/>
    <field name="urbanity" labelOnTop="0"/>
    <field name="verticalaccuracy" labelOnTop="0"/>
  </labelOnTop>
  <reuseLastValue>
    <field reuseLastValue="0" name="OBJECTID"/>
    <field reuseLastValue="0" name="Shape__Length"/>
    <field reuseLastValue="0" name="attributereliabilitydate"/>
    <field reuseLastValue="0" name="capturemethodcode"/>
    <field reuseLastValue="0" name="capturesourcecode"/>
    <field reuseLastValue="0" name="centroidid"/>
    <field reuseLastValue="0" name="changetype"/>
    <field reuseLastValue="0" name="classsubtype"/>
    <field reuseLastValue="0" name="createdate"/>
    <field reuseLastValue="0" name="enddate"/>
    <field reuseLastValue="0" name="featuremoddate"/>
    <field reuseLastValue="0" name="featurereliabilitydate"/>
    <field reuseLastValue="0" name="fid"/>
    <field reuseLastValue="0" name="functionhierarchy"/>
    <field reuseLastValue="0" name="lanecount"/>
    <field reuseLastValue="0" name="lastupdate"/>
    <field reuseLastValue="0" name="msoid"/>
    <field reuseLastValue="0" name="objectid"/>
    <field reuseLastValue="0" name="objectmoddate"/>
    <field reuseLastValue="0" name="operationalstatus"/>
    <field reuseLastValue="0" name="planimetricaccuracy"/>
    <field reuseLastValue="0" name="processstate"/>
    <field reuseLastValue="0" name="relevance"/>
    <field reuseLastValue="0" name="roadnamebase"/>
    <field reuseLastValue="0" name="roadnameextentoid"/>
    <field reuseLastValue="0" name="roadnameoid"/>
    <field reuseLastValue="0" name="roadnamesuffix"/>
    <field reuseLastValue="0" name="roadnametype"/>
    <field reuseLastValue="0" name="roadontype"/>
    <field reuseLastValue="0" name="shape_Length"/>
    <field reuseLastValue="0" name="shapeuuid"/>
    <field reuseLastValue="0" name="startdate"/>
    <field reuseLastValue="0" name="surface"/>
    <field reuseLastValue="0" name="topoid"/>
    <field reuseLastValue="0" name="urbanity"/>
    <field reuseLastValue="0" name="verticalaccuracy"/>
  </reuseLastValue>
  <dataDefinedFieldProperties/>
  <widgets/>
  <previewExpression>"roadnameoid"</previewExpression>
  <mapTip enabled="1"></mapTip>
  <layerGeometryType>1</layerGeometryType>
</qgis>
