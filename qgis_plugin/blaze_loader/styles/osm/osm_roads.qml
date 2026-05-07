<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="1" maxScale="0" minScale="100000000" readOnly="0" simplifyAlgorithm="0" simplifyDrawingHints="1" simplifyDrawingTol="1" simplifyLocal="1" simplifyMaxScale="1" styleCategories="LayerConfiguration|Symbology|Labeling|Fields|Rendering" symbologyReferenceScale="-1" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="1" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{osm-roads-root}">
      <rule filter="@map_scale > 20000 AND COALESCE(map_get(from_json(&quot;tags&quot;), '4wd_only'), '') = 'yes' AND COALESCE(map_get(from_json(&quot;tags&quot;), 'surface'), '') NOT IN ('unpaved','compacted','fine_gravel','gravel','pebblestone','dirt','earth','ground','grass','mud','sand','woodchips','rock','snow','ice','soil','clay')" key="{r-sealed-4wd}" label="Sealed (4WD only)" symbol="0"></rule>
      <rule filter="COALESCE(map_get(from_json(&quot;tags&quot;), '4wd_only'), '') = 'yes' AND COALESCE(map_get(from_json(&quot;tags&quot;), 'surface'), '') IN ('unpaved','compacted','fine_gravel','gravel','pebblestone','dirt','earth','ground','grass','mud','sand','woodchips','rock','snow','ice','soil','clay')" key="{r-unsealed-4wd}" label="Unsealed (4WD only)" symbol="1"></rule>
      <rule filter="COALESCE(map_get(from_json(&quot;tags&quot;), '4wd_only'), '') != 'yes'  AND COALESCE(map_get(from_json(&quot;tags&quot;), 'surface'), '') IN ('unpaved','compacted','fine_gravel','gravel','pebblestone','dirt','earth','ground','grass','mud','sand','woodchips','rock','snow','ice','soil','clay')" key="{r-unsealed}" label="Unsealed" symbol="2"></rule>
      <rule filter="COALESCE(map_get(from_json(&quot;tags&quot;), '4wd_only'), '') != 'yes'  AND  COALESCE(map_get(from_json(&quot;tags&quot;), 'surface'), '') IN ('paved','asphalt')" key="{9abd59fe-b80d-429a-90ac-3187244d58c1}" label="Sealed" symbol="3">
        <rule key="{50a0c56c-2b67-425f-9c82-6afe70cd887c}" label="0 - 20000" scalemaxdenom="20000" symbol="4"></rule>
        <rule key="{1f661119-57dd-4021-b66f-ca190070ce28}" scalemaxdenom="100000" scalemindenom="20000" symbol="5"></rule>
        <rule key="{f4ea129b-2d34-4ecb-aa9b-f806527e2716}" label="20000 - 0" scalemindenom="100000" symbol="6"></rule>
      </rule>
      <rule filter="COALESCE(map_get(from_json(&quot;tags&quot;), 'service'), '') IN ('driveway')" key="{d3d54848-2ab9-4df8-848d-7aad64f20cf2}" symbol="7"></rule>
      <rule filter="ELSE" key="{7d7fdb84-e8dc-437b-a9a4-f7664839dcd5}" symbol="8"></rule>
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
        <layer class="SimpleLine" enabled="1" id="{rd-sealed-4wd}" locked="0" pass="0">
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
            <Option name="line_color" type="QString" value="220,40,40,255"></Option>
            <Option name="line_style" type="QString" value="dash"></Option>
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
                  <Option name="expression" type="QString" value="case when &quot;highway&quot; in ('motorway','trunk','motorway_link','trunk_link') then 0.7 when &quot;highway&quot; in ('primary','primary_link') then 0.55 when &quot;highway&quot; in ('secondary','secondary_link') then 0.45 when &quot;highway&quot; in ('tertiary','tertiary_link') then 0.4 else 0.3 end"></Option>
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
        <layer class="SimpleLine" enabled="1" id="{rd-unsealed}" locked="0" pass="0">
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
            <Option name="line_style" type="QString" value="dash"></Option>
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
                  <Option name="expression" type="QString" value="case when &quot;highway&quot; in ('motorway','trunk','motorway_link','trunk_link') then 0.7 when &quot;highway&quot; in ('primary','primary_link') then 0.55 when &quot;highway&quot; in ('secondary','secondary_link') then 0.45 when &quot;highway&quot; in ('tertiary','tertiary_link') then 0.4 else 0.3 end"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
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
        <layer class="SimpleLine" enabled="1" id="{rd-unsealed}" locked="0" pass="0">
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
                  <Option name="expression" type="QString" value="case when &quot;highway&quot; in ('motorway','trunk','motorway_link','trunk_link') then 0.7 when &quot;highway&quot; in ('primary','primary_link') then 0.55 when &quot;highway&quot; in ('secondary','secondary_link') then 0.45 when &quot;highway&quot; in ('tertiary','tertiary_link') then 0.4 else 0.3 end"></Option>
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
        <layer class="SimpleLine" enabled="1" id="{rd-sealed}" locked="0" pass="5">
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
            <Option name="line_color" type="QString" value="214,0,0,0"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="4" type="line">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleLine" enabled="1" id="{rd-sealed}" locked="0" pass="10">
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
                  <Option name="expression" type="QString" value="( case  when &quot;highway&quot; in ('motorway','trunk','motorway_link','trunk_link')   then 0.8  when &quot;highway&quot; in ('primary','primary_link')   then 0.7  when &quot;highway&quot; in ('secondary','secondary_link')   then 0.7  when &quot;highway&quot; in ('tertiary','tertiary_link')   then 0.6  else 0.5 end) + 0.2"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
        <layer class="SimpleLine" enabled="1" id="{78ecb018-1b83-489a-addb-7b79027a1679}" locked="0" pass="11">
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
            <Option name="line_color" type="QString" value="244,226,179,255"></Option>
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
              <Option name="properties" type="Map">
                <Option name="outlineWidth" type="Map">
                  <Option name="active" type="bool" value="true"></Option>
                  <Option name="expression" type="QString" value="( case  when &quot;highway&quot; in ('motorway','trunk','motorway_link','trunk_link')   then 0.8  when &quot;highway&quot; in ('primary','primary_link')   then 0.7  when &quot;highway&quot; in ('secondary','secondary_link')   then 0.7  when &quot;highway&quot; in ('tertiary','tertiary_link')   then 0.6  else 0.5 end)"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
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
        <layer class="SimpleLine" enabled="1" id="{rd-sealed}" locked="0" pass="5">
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
            <Option name="line_color" type="QString" value="214,0,0,255"></Option>
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
                  <Option name="expression" type="QString" value="case  when &quot;highway&quot; in ('motorway','trunk','motorway_link','trunk_link')   then 0.7  when &quot;highway&quot; in ('primary','primary_link')   then 0.55  when &quot;highway&quot; in ('secondary','secondary_link')   then 0.45  when &quot;highway&quot; in ('tertiary','tertiary_link')   then 0.4  else 0.3 end"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
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
        <layer class="SimpleLine" enabled="1" id="{3b2466a5-9b12-4db5-9460-7398bb2875d7}" locked="0" pass="0">
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
            <Option name="line_color" type="QString" value="230,0,23,255"></Option>
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
              <Option name="properties" type="Map">
                <Option name="outlineWidth" type="Map">
                  <Option name="active" type="bool" value="true"></Option>
                  <Option name="expression" type="QString" value="(case when &quot;highway&quot; in ('motorway','trunk','motorway_link','trunk_link')   then 0.6 when &quot;highway&quot; in ('primary','primary_link')   then 0.4 when &quot;highway&quot; in ('secondary', 'secondary_link')   then 0.3 when &quot;highway&quot; in ('tertiary', 'tertiary_link')   then 0.3 else 0.0001 end)"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
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
        <layer class="SimpleLine" enabled="1" id="{22567543-93b3-4307-87be-0cb1173e7e13}" locked="0" pass="0">
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="8" type="line">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleLine" enabled="1" id="{rd-unsealed}" locked="0" pass="0">
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
                  <Option name="expression" type="QString" value="case when &quot;highway&quot; in ('motorway','trunk','motorway_link','trunk_link') then 0.7 when &quot;highway&quot; in ('primary','primary_link') then 0.55 when &quot;highway&quot; in ('secondary','secondary_link') then 0.45 when &quot;highway&quot; in ('tertiary','tertiary_link') then 0.4 else 0.3 end"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
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
        <layer class="SimpleLine" enabled="1" id="{ab3aa61a-4110-45cf-817d-2f1d8100a028}" locked="0" pass="0">
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
  <labeling type="simple">
    <settings calloutType="simple">
      <text-style allowHtml="0" blendMode="0" capitalization="1004" fieldName="name" fontFamily="Arial" fontItalic="0" fontKerning="1" fontLetterSpacing="0" fontSize="8" fontSizeMapUnitScale="3x:0,0,0,0,0,0" fontSizeUnit="Point" fontStrikeout="0" fontUnderline="0" fontWeight="50" fontWordSpacing="0" forcedBold="0" forcedItalic="0" isExpression="0" legendString="Aa" multilineHeight="1" multilineHeightUnit="Percentage" namedStyle="Regular" previewBkgrdColor="255,255,255,255" textColor="50,50,50,255" textOpacity="1" textOrientation="horizontal" useSubstitutions="0">
        <families></families>
        <text-buffer bufferBlendMode="0" bufferColor="250,250,250,255" bufferDraw="1" bufferJoinStyle="128" bufferNoFill="1" bufferOpacity="1" bufferSize="0.29999999999999999" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM"></text-buffer>
        <text-mask maskEnabled="0" maskJoinStyle="128" maskOpacity="1" maskSize="0" maskSizeMapUnitScale="3x:0,0,0,0,0,0" maskSizeUnits="MM" maskType="0" maskedSymbolLayers=""></text-mask>
        <background shapeBlendMode="0" shapeBorderColor="128,128,128,255" shapeBorderWidth="0" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="Point" shapeDraw="0" shapeFillColor="255,255,255,255" shapeJoinStyle="64" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetUnit="Point" shapeOffsetX="0" shapeOffsetY="0" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeRadiiUnit="Point" shapeRadiiX="0" shapeRadiiY="0" shapeRotation="0" shapeRotationType="0" shapeSVGFile="" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeSizeType="0" shapeSizeUnit="Point" shapeSizeX="0" shapeSizeY="0" shapeType="0">
          <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="markerSymbol" type="marker">
            <data_defined_properties>
              <Option type="Map">
                <Option name="name" type="QString" value=""></Option>
                <Option name="properties"></Option>
                <Option name="type" type="QString" value="collection"></Option>
              </Option>
            </data_defined_properties>
            <layer class="SimpleMarker" enabled="1" id="" locked="0" pass="0">
              <Option type="Map">
                <Option name="angle" type="QString" value="0"></Option>
                <Option name="cap_style" type="QString" value="square"></Option>
                <Option name="color" type="QString" value="213,180,60,255"></Option>
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
          <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="fillSymbol" type="fill">
            <data_defined_properties>
              <Option type="Map">
                <Option name="name" type="QString" value=""></Option>
                <Option name="properties"></Option>
                <Option name="type" type="QString" value="collection"></Option>
              </Option>
            </data_defined_properties>
            <layer class="SimpleFill" enabled="1" id="" locked="0" pass="0">
              <Option type="Map">
                <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
                <Option name="color" type="QString" value="255,255,255,255"></Option>
                <Option name="joinstyle" type="QString" value="bevel"></Option>
                <Option name="offset" type="QString" value="0,0"></Option>
                <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
                <Option name="offset_unit" type="QString" value="MM"></Option>
                <Option name="outline_color" type="QString" value="128,128,128,255"></Option>
                <Option name="outline_style" type="QString" value="no"></Option>
                <Option name="outline_width" type="QString" value="0"></Option>
                <Option name="outline_width_unit" type="QString" value="Point"></Option>
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
        </background>
        <shadow shadowBlendMode="6" shadowColor="0,0,0,255" shadowDraw="0" shadowOffsetAngle="135" shadowOffsetDist="1" shadowOffsetGlobal="1" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetUnit="Point" shadowOpacity="1" shadowRadius="1.5" shadowRadiusAlphaOnly="0" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusUnit="Point" shadowScale="100" shadowUnder="0"></shadow>
        <dd_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </dd_properties>
        <substitutions></substitutions>
      </text-style>
      <text-format addDirectionSymbol="0" autoWrapLength="0" decimals="3" formatNumbers="0" leftDirectionSymbol="&lt;" multilineAlign="0" placeDirectionSymbol="0" plussign="0" reverseDirectionSymbol="0" rightDirectionSymbol=">" useMaxLineLengthForAutoWrap="1" wrapChar=""></text-format>
      <placement allowDegraded="0" centroidInside="0" centroidWhole="0" dist="0" distMapUnitScale="3x:0,0,0,0,0,0" distUnits="MM" fitInPolygonOnly="0" geometryGenerator="" geometryGeneratorEnabled="0" geometryGeneratorType="PointGeometry" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" layerType="LineGeometry" lineAnchorClipping="0" lineAnchorPercent="0.5" lineAnchorTextPoint="CenterOfText" lineAnchorType="0" maxCurvedCharAngleIn="25" maxCurvedCharAngleOut="-25" offsetType="0" offsetUnits="MapUnit" overlapHandling="PreventOverlap" overrunDistance="0" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" placement="3" placementFlags="10" polygonPlacementFlags="2" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" preserveRotation="1" priority="5" quadOffset="4" repeatDistance="100" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" repeatDistanceUnits="Point" rotationAngle="0" rotationUnit="AngleDegrees" xOffset="0" yOffset="0"></placement>
      <rendering drawLabels="1" fontLimitPixelSize="0" fontMaxPixelSize="10000" fontMinPixelSize="3" labelPerPart="0" limitNumLabels="0" maxNumLabels="2000" mergeLines="0" minFeatureSize="20" obstacle="1" obstacleFactor="1" obstacleType="1" scaleMax="60000" scaleMin="0" scaleVisibility="1" unplacedVisibility="0" upsidedownLabels="0" zIndex="0"></rendering>
      <dd_properties>
        <Option type="Map">
          <Option name="name" type="QString" value=""></Option>
          <Option name="properties" type="Map">
            <Option name="Size" type="Map">
              <Option name="active" type="bool" value="true"></Option>
              <Option name="expression" type="QString" value="case when &quot;highway&quot; in ('motorway','trunk','motorway_link','trunk_link') then 9 when &quot;highway&quot; in ('primary','primary_link') then 8 when &quot;highway&quot; in ('secondary','secondary_link') then 7 when &quot;highway&quot; in ('tertiary','tertiary_link') then 7 else 6 end"></Option>
              <Option name="type" type="int" value="3"></Option>
            </Option>
          </Option>
          <Option name="type" type="QString" value="collection"></Option>
        </Option>
      </dd_properties>
      <callout type="simple">
        <Option type="Map">
          <Option name="anchorPoint" type="QString" value="pole_of_inaccessibility"></Option>
          <Option name="blendMode" type="int" value="0"></Option>
          <Option name="ddProperties" type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
          <Option name="drawToAllParts" type="bool" value="false"></Option>
          <Option name="enabled" type="QString" value="0"></Option>
          <Option name="labelAnchorPoint" type="QString" value="point_on_exterior"></Option>
          <Option name="lineSymbol" type="QString" value="&lt;symbol alpha=&quot;1&quot; name=&quot;symbol&quot; force_rhr=&quot;0&quot; type=&quot;line&quot; is_animated=&quot;0&quot; clip_to_extent=&quot;1&quot; frame_rate=&quot;10&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option name=&quot;name&quot; type=&quot;QString&quot; value=&quot;&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option name=&quot;type&quot; type=&quot;QString&quot; value=&quot;collection&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer class=&quot;SimpleLine&quot; locked=&quot;0&quot; pass=&quot;0&quot; enabled=&quot;1&quot; id=&quot;{3a68fdda-ca1d-4e5d-81cb-326af270edd9}&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option name=&quot;align_dash_pattern&quot; type=&quot;QString&quot; value=&quot;0&quot;/>&lt;Option name=&quot;capstyle&quot; type=&quot;QString&quot; value=&quot;square&quot;/>&lt;Option name=&quot;customdash&quot; type=&quot;QString&quot; value=&quot;5;2&quot;/>&lt;Option name=&quot;customdash_map_unit_scale&quot; type=&quot;QString&quot; value=&quot;3x:0,0,0,0,0,0&quot;/>&lt;Option name=&quot;customdash_unit&quot; type=&quot;QString&quot; value=&quot;MM&quot;/>&lt;Option name=&quot;dash_pattern_offset&quot; type=&quot;QString&quot; value=&quot;0&quot;/>&lt;Option name=&quot;dash_pattern_offset_map_unit_scale&quot; type=&quot;QString&quot; value=&quot;3x:0,0,0,0,0,0&quot;/>&lt;Option name=&quot;dash_pattern_offset_unit&quot; type=&quot;QString&quot; value=&quot;MM&quot;/>&lt;Option name=&quot;draw_inside_polygon&quot; type=&quot;QString&quot; value=&quot;0&quot;/>&lt;Option name=&quot;joinstyle&quot; type=&quot;QString&quot; value=&quot;bevel&quot;/>&lt;Option name=&quot;line_color&quot; type=&quot;QString&quot; value=&quot;60,60,60,255&quot;/>&lt;Option name=&quot;line_style&quot; type=&quot;QString&quot; value=&quot;solid&quot;/>&lt;Option name=&quot;line_width&quot; type=&quot;QString&quot; value=&quot;0.3&quot;/>&lt;Option name=&quot;line_width_unit&quot; type=&quot;QString&quot; value=&quot;MM&quot;/>&lt;Option name=&quot;offset&quot; type=&quot;QString&quot; value=&quot;0&quot;/>&lt;Option name=&quot;offset_map_unit_scale&quot; type=&quot;QString&quot; value=&quot;3x:0,0,0,0,0,0&quot;/>&lt;Option name=&quot;offset_unit&quot; type=&quot;QString&quot; value=&quot;MM&quot;/>&lt;Option name=&quot;ring_filter&quot; type=&quot;QString&quot; value=&quot;0&quot;/>&lt;Option name=&quot;trim_distance_end&quot; type=&quot;QString&quot; value=&quot;0&quot;/>&lt;Option name=&quot;trim_distance_end_map_unit_scale&quot; type=&quot;QString&quot; value=&quot;3x:0,0,0,0,0,0&quot;/>&lt;Option name=&quot;trim_distance_end_unit&quot; type=&quot;QString&quot; value=&quot;MM&quot;/>&lt;Option name=&quot;trim_distance_start&quot; type=&quot;QString&quot; value=&quot;0&quot;/>&lt;Option name=&quot;trim_distance_start_map_unit_scale&quot; type=&quot;QString&quot; value=&quot;3x:0,0,0,0,0,0&quot;/>&lt;Option name=&quot;trim_distance_start_unit&quot; type=&quot;QString&quot; value=&quot;MM&quot;/>&lt;Option name=&quot;tweak_dash_pattern_on_corners&quot; type=&quot;QString&quot; value=&quot;0&quot;/>&lt;Option name=&quot;use_custom_dash&quot; type=&quot;QString&quot; value=&quot;0&quot;/>&lt;Option name=&quot;width_map_unit_scale&quot; type=&quot;QString&quot; value=&quot;3x:0,0,0,0,0,0&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option name=&quot;name&quot; type=&quot;QString&quot; value=&quot;&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option name=&quot;type&quot; type=&quot;QString&quot; value=&quot;collection&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>"></Option>
          <Option name="minLength" type="double" value="0"></Option>
          <Option name="minLengthMapUnitScale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          <Option name="minLengthUnit" type="QString" value="MM"></Option>
          <Option name="offsetFromAnchor" type="double" value="0"></Option>
          <Option name="offsetFromAnchorMapUnitScale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          <Option name="offsetFromAnchorUnit" type="QString" value="MM"></Option>
          <Option name="offsetFromLabel" type="double" value="0"></Option>
          <Option name="offsetFromLabelMapUnitScale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          <Option name="offsetFromLabelUnit" type="QString" value="MM"></Option>
        </Option>
      </callout>
    </settings>
  </labeling>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
  <layerOpacity>1</layerOpacity>
  <fieldConfiguration>
    <field configurationFlags="NoFlag" name="fid"></field>
    <field configurationFlags="NoFlag" name="osm_id"></field>
    <field configurationFlags="NoFlag" name="osm_type"></field>
    <field configurationFlags="NoFlag" name="name"></field>
    <field configurationFlags="NoFlag" name="highway"></field>
    <field configurationFlags="NoFlag" name="tags"></field>
  </fieldConfiguration>
  <aliases>
    <alias field="fid" index="0" name=""></alias>
    <alias field="osm_id" index="1" name=""></alias>
    <alias field="osm_type" index="2" name=""></alias>
    <alias field="name" index="3" name=""></alias>
    <alias field="highway" index="4" name=""></alias>
    <alias field="tags" index="5" name=""></alias>
  </aliases>
  <splitPolicies>
    <policy field="fid" policy="Duplicate"></policy>
    <policy field="osm_id" policy="Duplicate"></policy>
    <policy field="osm_type" policy="Duplicate"></policy>
    <policy field="name" policy="Duplicate"></policy>
    <policy field="highway" policy="Duplicate"></policy>
    <policy field="tags" policy="Duplicate"></policy>
  </splitPolicies>
  <defaults>
    <default applyOnUpdate="0" expression="" field="fid"></default>
    <default applyOnUpdate="0" expression="" field="osm_id"></default>
    <default applyOnUpdate="0" expression="" field="osm_type"></default>
    <default applyOnUpdate="0" expression="" field="name"></default>
    <default applyOnUpdate="0" expression="" field="highway"></default>
    <default applyOnUpdate="0" expression="" field="tags"></default>
  </defaults>
  <constraints>
    <constraint constraints="3" exp_strength="0" field="fid" notnull_strength="1" unique_strength="1"></constraint>
    <constraint constraints="0" exp_strength="0" field="osm_id" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="osm_type" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="name" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="highway" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="tags" notnull_strength="0" unique_strength="0"></constraint>
  </constraints>
  <constraintExpressions>
    <constraint desc="" exp="" field="fid"></constraint>
    <constraint desc="" exp="" field="osm_id"></constraint>
    <constraint desc="" exp="" field="osm_type"></constraint>
    <constraint desc="" exp="" field="name"></constraint>
    <constraint desc="" exp="" field="highway"></constraint>
    <constraint desc="" exp="" field="tags"></constraint>
  </constraintExpressions>
  <expressionfields></expressionfields>
  <previewExpression>"name"</previewExpression>
  <layerGeometryType>1</layerGeometryType>
</qgis>