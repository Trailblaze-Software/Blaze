<!DOCTYPE qgis PUBLIC 'http://mrcc.com/qgis.dtd' 'SYSTEM'>
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="1" readOnly="0" version="3.34.3-Prizren" simplifyDrawingTol="1" maxScale="0" minScale="100000000" symbologyReferenceScale="-1" simplifyDrawingHints="0" simplifyAlgorithm="0" styleCategories="LayerConfiguration|Symbology|Symbology3D|Labeling|Fields|Forms|Actions|MapTips|Diagrams|AttributeTable|Rendering" simplifyLocal="1" simplifyMaxScale="1">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 forceraster="0" type="RuleRenderer" referencescale="-1" enableorderby="0" symbollevels="0">
    <rules key="{b59afb7a-8131-45d9-baf8-07543ca5f0d1}">
      <rule label="Setting" filter="setting_name is not NULL" key="{a6394195-f18b-4984-bce1-671b685863fc}" symbol="0">
        <rule label="Setting" description="new control, remove tape etc." filter="to_int(setting_name) > 0" key="{74e3c27e-d631-40b3-bdaf-0a3c6b662f4b}" symbol="1"/>
        <rule label="Hash House" filter="setting_name like 'HH'" key="{77806d88-25a7-4f9e-8fb4-60de858a1905}" symbol="2"/>
        <rule label="Water" filter="setting_name like 'W%' and to_int(right(setting_name,length(setting_name) -1)) > 0" key="{f9027c88-c4de-4973-9e91-3f75c5e091e0}" symbol="3"/>
        <rule label="Unknown" filter="ELSE" key="{530aaba4-10bd-4f26-838c-40812ef52100}" symbol="4"/>
      </rule>
      <rule label="Hanging/Final" filter="name is not Null" key="{268d3aea-ab42-4b83-8ec0-49ba75713faf}" symbol="5">
        <rule label="Control" description="Gap NULL full circle, Gap = 0 then 90 degree gap  in cirlcl to top " filter=" to_int(name) > 9 and to_int (name ) &lt; 300 " key="{805adba4-8cdc-46f0-b6d4-656b01b4933f}" symbol="6"/>
        <rule label="HH" filter="name like 'HH'" key="{65e9ff24-4bcb-4e93-8295-be4874e35150}" symbol="7"/>
        <rule label="Water" filter="name like 'W%' and to_int(right(name,length(name) -1)) > 0" key="{11bff41f-e5cb-4c19-a85f-e85772abe0fb}" symbol="8"/>
        <rule label="Unknown" filter="ELSE" key="{d6f11cf6-8ead-4279-ad1b-670dc5e992ec}" symbol="9"/>
      </rule>
      <rule filter="ELSE" key="{a0677e62-bfac-4247-875b-39447e8b5b24}" symbol="10"/>
    </rules>
    <symbols>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="0" clip_to_extent="1" alpha="0">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{ec6681f2-c730-4a4e-871a-cd1d3624f61c}" locked="0" class="SimpleMarker" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="angle"/>
            <Option value="square" type="QString" name="cap_style"/>
            <Option value="133,182,111,255" type="QString" name="color"/>
            <Option value="1" type="QString" name="horizontal_anchor_point"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="circle" type="QString" name="name"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="diameter" type="QString" name="scale_method"/>
            <Option value="2" type="QString" name="size"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
            <Option value="MM" type="QString" name="size_unit"/>
            <Option value="1" type="QString" name="vertical_anchor_point"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="1" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{33d06c15-6a6d-4c62-8e03-d12c1db800de}" locked="0" class="SimpleMarker" enabled="1" pass="0">
          <Option type="Map">
            <Option value="-180" type="QString" name="angle"/>
            <Option value="flat" type="QString" name="cap_style"/>
            <Option value="139,0,139,6" type="QString" name="color"/>
            <Option value="1" type="QString" name="horizontal_anchor_point"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="half_arc" type="QString" name="name"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="139,0,139,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0.4" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="diameter" type="QString" name="scale_method"/>
            <Option value="8" type="QString" name="size"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
            <Option value="MM" type="QString" name="size_unit"/>
            <Option value="1" type="QString" name="vertical_anchor_point"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option type="Map" name="properties">
                <Option type="Map" name="angle">
                  <Option value="true" type="bool" name="active"/>
                  <Option value="225 + Gap" type="QString" name="expression"/>
                  <Option value="3" type="int" name="type"/>
                </Option>
              </Option>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
        <layer id="{bb93c3ae-5dfb-48e5-8845-47379772d7b5}" locked="0" class="SimpleMarker" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="angle"/>
            <Option value="square" type="QString" name="cap_style"/>
            <Option value="255,0,0,0" type="QString" name="color"/>
            <Option value="1" type="QString" name="horizontal_anchor_point"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="half_arc" type="QString" name="name"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="139,0,139,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0.4" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="diameter" type="QString" name="scale_method"/>
            <Option value="8" type="QString" name="size"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
            <Option value="MM" type="QString" name="size_unit"/>
            <Option value="1" type="QString" name="vertical_anchor_point"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option type="Map" name="properties">
                <Option type="Map" name="angle">
                  <Option value="true" type="bool" name="active"/>
                  <Option value="135 + Gap" type="QString" name="expression"/>
                  <Option value="3" type="int" name="type"/>
                </Option>
              </Option>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="10" clip_to_extent="1" alpha="0.2">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{b51dc317-7b8c-41c3-adea-b0564290fcea}" locked="0" class="SimpleMarker" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="angle"/>
            <Option value="square" type="QString" name="cap_style"/>
            <Option value="255,0,0,255" type="QString" name="color"/>
            <Option value="1" type="QString" name="horizontal_anchor_point"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="circle" type="QString" name="name"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="diameter" type="QString" name="scale_method"/>
            <Option value="8" type="QString" name="size"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
            <Option value="MM" type="QString" name="size_unit"/>
            <Option value="1" type="QString" name="vertical_anchor_point"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="2" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{ab821e6e-9793-4b59-8b94-e648bbe68a56}" locked="0" class="SimpleMarker" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="angle"/>
            <Option value="square" type="QString" name="cap_style"/>
            <Option value="0,0,255,0" type="QString" name="color"/>
            <Option value="1" type="QString" name="horizontal_anchor_point"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="triangle" type="QString" name="name"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="139,0,139,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0.4" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="diameter" type="QString" name="scale_method"/>
            <Option value="9" type="QString" name="size"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
            <Option value="MM" type="QString" name="size_unit"/>
            <Option value="1" type="QString" name="vertical_anchor_point"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="3" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{4808d9f9-9ebb-486e-9cf2-222212241f90}" locked="0" class="SimpleMarker" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="angle"/>
            <Option value="square" type="QString" name="cap_style"/>
            <Option value="255,255,255,0" type="QString" name="color"/>
            <Option value="1" type="QString" name="horizontal_anchor_point"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="circle" type="QString" name="name"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="0,0,253,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0.4" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="diameter" type="QString" name="scale_method"/>
            <Option value="8" type="QString" name="size"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
            <Option value="MM" type="QString" name="size_unit"/>
            <Option value="1" type="QString" name="vertical_anchor_point"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="4" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{f4a4bc17-ef18-4164-b1ee-b0a1b7cf4f23}" locked="0" class="SimpleMarker" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="angle"/>
            <Option value="square" type="QString" name="cap_style"/>
            <Option value="255,0,0,52" type="QString" name="color"/>
            <Option value="1" type="QString" name="horizontal_anchor_point"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="circle" type="QString" name="name"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="255,0,0,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0.4" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="diameter" type="QString" name="scale_method"/>
            <Option value="8" type="QString" name="size"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
            <Option value="MM" type="QString" name="size_unit"/>
            <Option value="1" type="QString" name="vertical_anchor_point"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="5" clip_to_extent="1" alpha="0">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{ae3cedad-5f8a-4fdd-b998-5db56939c9b5}" locked="0" class="SimpleMarker" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="angle"/>
            <Option value="square" type="QString" name="cap_style"/>
            <Option value="232,113,141,255" type="QString" name="color"/>
            <Option value="1" type="QString" name="horizontal_anchor_point"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="circle" type="QString" name="name"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="diameter" type="QString" name="scale_method"/>
            <Option value="2" type="QString" name="size"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
            <Option value="MM" type="QString" name="size_unit"/>
            <Option value="1" type="QString" name="vertical_anchor_point"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="6" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{e91ffb23-1d54-4608-a610-9b1e7d208e72}" locked="0" class="SimpleMarker" enabled="1" pass="0">
          <Option type="Map">
            <Option value="-180" type="QString" name="angle"/>
            <Option value="flat" type="QString" name="cap_style"/>
            <Option value="139,0,139,6" type="QString" name="color"/>
            <Option value="1" type="QString" name="horizontal_anchor_point"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="half_arc" type="QString" name="name"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="139,0,139,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0.4" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="diameter" type="QString" name="scale_method"/>
            <Option value="8" type="QString" name="size"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
            <Option value="MM" type="QString" name="size_unit"/>
            <Option value="1" type="QString" name="vertical_anchor_point"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option type="Map" name="properties">
                <Option type="Map" name="angle">
                  <Option value="true" type="bool" name="active"/>
                  <Option value="225 + Gap" type="QString" name="expression"/>
                  <Option value="3" type="int" name="type"/>
                </Option>
              </Option>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
        <layer id="{954313fe-770a-44ca-a84f-3c3f4e42f7d5}" locked="0" class="SimpleMarker" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="angle"/>
            <Option value="square" type="QString" name="cap_style"/>
            <Option value="255,0,0,0" type="QString" name="color"/>
            <Option value="1" type="QString" name="horizontal_anchor_point"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="half_arc" type="QString" name="name"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="139,0,139,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0.4" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="diameter" type="QString" name="scale_method"/>
            <Option value="8" type="QString" name="size"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
            <Option value="MM" type="QString" name="size_unit"/>
            <Option value="1" type="QString" name="vertical_anchor_point"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option type="Map" name="properties">
                <Option type="Map" name="angle">
                  <Option value="true" type="bool" name="active"/>
                  <Option value="135 + Gap" type="QString" name="expression"/>
                  <Option value="3" type="int" name="type"/>
                </Option>
              </Option>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="7" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{94590e4c-94d9-48c5-a74c-fec63ef7c76f}" locked="0" class="SimpleMarker" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="angle"/>
            <Option value="square" type="QString" name="cap_style"/>
            <Option value="0,0,255,0" type="QString" name="color"/>
            <Option value="1" type="QString" name="horizontal_anchor_point"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="triangle" type="QString" name="name"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="139,0,139,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0.4" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="diameter" type="QString" name="scale_method"/>
            <Option value="9" type="QString" name="size"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
            <Option value="MM" type="QString" name="size_unit"/>
            <Option value="1" type="QString" name="vertical_anchor_point"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="8" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{7ed62310-663e-4590-80ad-e3428926a8ba}" locked="0" class="SimpleMarker" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="angle"/>
            <Option value="square" type="QString" name="cap_style"/>
            <Option value="255,255,255,0" type="QString" name="color"/>
            <Option value="1" type="QString" name="horizontal_anchor_point"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="circle" type="QString" name="name"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="0,0,253,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0.4" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="diameter" type="QString" name="scale_method"/>
            <Option value="8" type="QString" name="size"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
            <Option value="MM" type="QString" name="size_unit"/>
            <Option value="1" type="QString" name="vertical_anchor_point"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="9" clip_to_extent="1" alpha="0.2">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{9f48c1c3-6d98-498e-b483-26d4280bf404}" locked="0" class="SimpleMarker" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="angle"/>
            <Option value="square" type="QString" name="cap_style"/>
            <Option value="255,0,0,255" type="QString" name="color"/>
            <Option value="1" type="QString" name="horizontal_anchor_point"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="circle" type="QString" name="name"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="128,17,25,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0.4" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="diameter" type="QString" name="scale_method"/>
            <Option value="8" type="QString" name="size"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
            <Option value="MM" type="QString" name="size_unit"/>
            <Option value="1" type="QString" name="vertical_anchor_point"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{c2f8c36c-2388-4439-99ff-836490fa7bf9}" locked="0" class="SimpleMarker" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="angle"/>
            <Option value="square" type="QString" name="cap_style"/>
            <Option value="255,0,0,255" type="QString" name="color"/>
            <Option value="1" type="QString" name="horizontal_anchor_point"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="circle" type="QString" name="name"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="diameter" type="QString" name="scale_method"/>
            <Option value="2" type="QString" name="size"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
            <Option value="MM" type="QString" name="size_unit"/>
            <Option value="1" type="QString" name="vertical_anchor_point"/>
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
  <labeling type="rule-based">
    <rules key="{882f25e3-27a1-4ef1-91fa-551dae27eb7b}">
      <rule description="Setting" filter="setting_name is not NULL" key="{e9faaf3b-2f70-4b6e-b91c-a5bade92c1f9}">
        <rule description="controls" filter="to_int(setting_name) > 200" key="{bddf1809-44a2-4248-9657-b8edfd936f78}">
          <settings calloutType="simple">
            <text-style textOrientation="horizontal" fontSizeUnit="Point" fontSize="15" capitalization="0" multilineHeightUnit="Percentage" fontLetterSpacing="0" fontSizeMapUnitScale="3x:0,0,0,0,0,0" previewBkgrdColor="255,255,255,255" fontWeight="50" fontFamily="MS Shell Dlg 2" textColor="139,0,139,255" fontKerning="1" useSubstitutions="0" fontWordSpacing="0" namedStyle="Regular" fontItalic="0" multilineHeight="1" forcedBold="0" textOpacity="1" fontStrikeout="0" fieldName="setting_name" fontUnderline="0" isExpression="0" forcedItalic="0" allowHtml="0" blendMode="0" legendString="Aa">
              <families/>
              <text-buffer bufferOpacity="1" bufferNoFill="1" bufferBlendMode="0" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM" bufferDraw="0" bufferSize="1" bufferColor="255,255,255,255" bufferJoinStyle="128"/>
              <text-mask maskSize="1.5" maskSizeUnits="MM" maskEnabled="0" maskedSymbolLayers="" maskType="0" maskJoinStyle="128" maskOpacity="1" maskSizeMapUnitScale="3x:0,0,0,0,0,0"/>
              <background shapeSizeType="0" shapeRadiiY="0" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetX="0" shapeBorderColor="128,128,128,255" shapeRotationType="0" shapeBlendMode="0" shapeType="0" shapeFillColor="255,255,255,255" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="MM" shapeRadiiUnit="MM" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeSizeUnit="MM" shapeRadiiX="0" shapeOffsetUnit="MM" shapeSizeX="0" shapeRotation="0" shapeJoinStyle="64" shapeOffsetY="0" shapeSizeY="0" shapeDraw="0" shapeSVGFile="" shapeBorderWidth="0">
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="markerSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleMarker" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="0" type="QString" name="angle"/>
                      <Option value="square" type="QString" name="cap_style"/>
                      <Option value="152,125,183,255" type="QString" name="color"/>
                      <Option value="1" type="QString" name="horizontal_anchor_point"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="circle" type="QString" name="name"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="35,35,35,255" type="QString" name="outline_color"/>
                      <Option value="solid" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
                      <Option value="MM" type="QString" name="outline_width_unit"/>
                      <Option value="diameter" type="QString" name="scale_method"/>
                      <Option value="2" type="QString" name="size"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
                      <Option value="MM" type="QString" name="size_unit"/>
                      <Option value="1" type="QString" name="vertical_anchor_point"/>
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
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="fillSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleFill" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
                      <Option value="255,255,255,255" type="QString" name="color"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="128,128,128,255" type="QString" name="outline_color"/>
                      <Option value="no" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="MM" type="QString" name="outline_width_unit"/>
                      <Option value="solid" type="QString" name="style"/>
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
              </background>
              <shadow shadowOffsetGlobal="1" shadowUnder="0" shadowOffsetAngle="135" shadowScale="100" shadowDraw="0" shadowColor="0,0,0,255" shadowOffsetUnit="MM" shadowRadiusUnit="MM" shadowOpacity="0.69999999999999996" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetDist="1" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusAlphaOnly="0" shadowRadius="1.5" shadowBlendMode="6"/>
              <dd_properties>
                <Option type="Map">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
              </dd_properties>
              <substitutions/>
            </text-style>
            <text-format useMaxLineLengthForAutoWrap="1" decimals="3" addDirectionSymbol="0" rightDirectionSymbol=">" plussign="0" wrapChar="" placeDirectionSymbol="0" autoWrapLength="0" multilineAlign="3" formatNumbers="0" reverseDirectionSymbol="0" leftDirectionSymbol="&lt;"/>
            <placement repeatDistance="0" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" offsetType="0" yOffset="7" centroidWhole="0" polygonPlacementFlags="2" offsetUnits="MM" repeatDistanceUnits="MM" dist="5" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" centroidInside="0" placementFlags="10" geometryGenerator="" maxCurvedCharAngleOut="-25" xOffset="-7" preserveRotation="1" lineAnchorType="0" geometryGeneratorEnabled="0" overrunDistance="0" maxCurvedCharAngleIn="25" lineAnchorTextPoint="CenterOfText" distUnits="MM" priority="5" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" lineAnchorClipping="0" allowDegraded="0" fitInPolygonOnly="0" rotationAngle="0" geometryGeneratorType="PointGeometry" layerType="PointGeometry" placement="1" lineAnchorPercent="0.5" quadOffset="4" overlapHandling="PreventOverlap" distMapUnitScale="3x:0,0,0,0,0,0" rotationUnit="AngleDegrees" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0"/>
            <rendering scaleMax="0" scaleVisibility="0" fontLimitPixelSize="0" minFeatureSize="0" upsidedownLabels="0" obstacle="1" maxNumLabels="2000" fontMinPixelSize="3" limitNumLabels="0" mergeLines="0" unplacedVisibility="0" scaleMin="0" zIndex="0" obstacleType="1" drawLabels="1" labelPerPart="0" fontMaxPixelSize="10000" obstacleFactor="1"/>
            <dd_properties>
              <Option type="Map">
                <Option value="" type="QString" name="name"/>
                <Option type="Map" name="properties">
                  <Option type="Map" name="PositionX">
                    <Option value="true" type="bool" name="active"/>
                    <Option value="auxiliary_storage_labeling_positionx" type="QString" name="field"/>
                    <Option value="2" type="int" name="type"/>
                  </Option>
                  <Option type="Map" name="PositionY">
                    <Option value="true" type="bool" name="active"/>
                    <Option value="auxiliary_storage_labeling_positiony" type="QString" name="field"/>
                    <Option value="2" type="int" name="type"/>
                  </Option>
                </Option>
                <Option value="collection" type="QString" name="type"/>
              </Option>
            </dd_properties>
            <callout type="simple">
              <Option type="Map">
                <Option value="pole_of_inaccessibility" type="QString" name="anchorPoint"/>
                <Option value="0" type="int" name="blendMode"/>
                <Option type="Map" name="ddProperties">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
                <Option value="false" type="bool" name="drawToAllParts"/>
                <Option value="0" type="QString" name="enabled"/>
                <Option value="point_on_exterior" type="QString" name="labelAnchorPoint"/>
                <Option value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{0a1ed788-77aa-41b7-8734-760227c92d93}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>" type="QString" name="lineSymbol"/>
                <Option value="0" type="double" name="minLength"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="minLengthMapUnitScale"/>
                <Option value="MM" type="QString" name="minLengthUnit"/>
                <Option value="0" type="double" name="offsetFromAnchor"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromAnchorMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromAnchorUnit"/>
                <Option value="0" type="double" name="offsetFromLabel"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromLabelMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromLabelUnit"/>
              </Option>
            </callout>
          </settings>
        </rule>
        <rule description="HH" filter="setting_name like 'HH'" key="{c6e51ee0-1012-431a-901b-504bc01ef18e}">
          <settings calloutType="simple">
            <text-style textOrientation="horizontal" fontSizeUnit="Point" fontSize="15" capitalization="0" multilineHeightUnit="Percentage" fontLetterSpacing="0" fontSizeMapUnitScale="3x:0,0,0,0,0,0" previewBkgrdColor="255,255,255,255" fontWeight="50" fontFamily="MS Shell Dlg 2" textColor="139,0,139,255" fontKerning="1" useSubstitutions="0" fontWordSpacing="0" namedStyle="Regular" fontItalic="0" multilineHeight="1" forcedBold="0" textOpacity="1" fontStrikeout="0" fieldName="setting_name" fontUnderline="0" isExpression="0" forcedItalic="0" allowHtml="0" blendMode="0" legendString="Aa">
              <families/>
              <text-buffer bufferOpacity="1" bufferNoFill="1" bufferBlendMode="0" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM" bufferDraw="0" bufferSize="1" bufferColor="255,255,255,255" bufferJoinStyle="128"/>
              <text-mask maskSize="1.5" maskSizeUnits="MM" maskEnabled="0" maskedSymbolLayers="" maskType="0" maskJoinStyle="128" maskOpacity="1" maskSizeMapUnitScale="3x:0,0,0,0,0,0"/>
              <background shapeSizeType="0" shapeRadiiY="0" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetX="0" shapeBorderColor="128,128,128,255" shapeRotationType="0" shapeBlendMode="0" shapeType="0" shapeFillColor="255,255,255,255" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="MM" shapeRadiiUnit="MM" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeSizeUnit="MM" shapeRadiiX="0" shapeOffsetUnit="MM" shapeSizeX="0" shapeRotation="0" shapeJoinStyle="64" shapeOffsetY="0" shapeSizeY="0" shapeDraw="0" shapeSVGFile="" shapeBorderWidth="0">
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="markerSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleMarker" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="0" type="QString" name="angle"/>
                      <Option value="square" type="QString" name="cap_style"/>
                      <Option value="190,207,80,255" type="QString" name="color"/>
                      <Option value="1" type="QString" name="horizontal_anchor_point"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="circle" type="QString" name="name"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="35,35,35,255" type="QString" name="outline_color"/>
                      <Option value="solid" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
                      <Option value="MM" type="QString" name="outline_width_unit"/>
                      <Option value="diameter" type="QString" name="scale_method"/>
                      <Option value="2" type="QString" name="size"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
                      <Option value="MM" type="QString" name="size_unit"/>
                      <Option value="1" type="QString" name="vertical_anchor_point"/>
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
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="fillSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleFill" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
                      <Option value="255,255,255,255" type="QString" name="color"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="128,128,128,255" type="QString" name="outline_color"/>
                      <Option value="no" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="MM" type="QString" name="outline_width_unit"/>
                      <Option value="solid" type="QString" name="style"/>
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
              </background>
              <shadow shadowOffsetGlobal="1" shadowUnder="0" shadowOffsetAngle="135" shadowScale="100" shadowDraw="0" shadowColor="0,0,0,255" shadowOffsetUnit="MM" shadowRadiusUnit="MM" shadowOpacity="0.69999999999999996" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetDist="1" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusAlphaOnly="0" shadowRadius="1.5" shadowBlendMode="6"/>
              <dd_properties>
                <Option type="Map">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
              </dd_properties>
              <substitutions/>
            </text-style>
            <text-format useMaxLineLengthForAutoWrap="1" decimals="3" addDirectionSymbol="0" rightDirectionSymbol=">" plussign="0" wrapChar="" placeDirectionSymbol="0" autoWrapLength="0" multilineAlign="3" formatNumbers="0" reverseDirectionSymbol="0" leftDirectionSymbol="&lt;"/>
            <placement repeatDistance="0" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" offsetType="0" yOffset="7" centroidWhole="0" polygonPlacementFlags="2" offsetUnits="MM" repeatDistanceUnits="MM" dist="5" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" centroidInside="0" placementFlags="10" geometryGenerator="" maxCurvedCharAngleOut="-25" xOffset="-7" preserveRotation="1" lineAnchorType="0" geometryGeneratorEnabled="0" overrunDistance="0" maxCurvedCharAngleIn="25" lineAnchorTextPoint="CenterOfText" distUnits="MM" priority="5" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" lineAnchorClipping="0" allowDegraded="0" fitInPolygonOnly="0" rotationAngle="0" geometryGeneratorType="PointGeometry" layerType="PointGeometry" placement="1" lineAnchorPercent="0.5" quadOffset="4" overlapHandling="PreventOverlap" distMapUnitScale="3x:0,0,0,0,0,0" rotationUnit="AngleDegrees" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0"/>
            <rendering scaleMax="0" scaleVisibility="0" fontLimitPixelSize="0" minFeatureSize="0" upsidedownLabels="0" obstacle="1" maxNumLabels="2000" fontMinPixelSize="3" limitNumLabels="0" mergeLines="0" unplacedVisibility="0" scaleMin="0" zIndex="0" obstacleType="1" drawLabels="1" labelPerPart="0" fontMaxPixelSize="10000" obstacleFactor="1"/>
            <dd_properties>
              <Option type="Map">
                <Option value="" type="QString" name="name"/>
                <Option type="Map" name="properties">
                  <Option type="Map" name="PositionX">
                    <Option value="true" type="bool" name="active"/>
                    <Option value="auxiliary_storage_labeling_positionx" type="QString" name="field"/>
                    <Option value="2" type="int" name="type"/>
                  </Option>
                  <Option type="Map" name="PositionY">
                    <Option value="true" type="bool" name="active"/>
                    <Option value="auxiliary_storage_labeling_positiony" type="QString" name="field"/>
                    <Option value="2" type="int" name="type"/>
                  </Option>
                </Option>
                <Option value="collection" type="QString" name="type"/>
              </Option>
            </dd_properties>
            <callout type="simple">
              <Option type="Map">
                <Option value="pole_of_inaccessibility" type="QString" name="anchorPoint"/>
                <Option value="0" type="int" name="blendMode"/>
                <Option type="Map" name="ddProperties">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
                <Option value="false" type="bool" name="drawToAllParts"/>
                <Option value="0" type="QString" name="enabled"/>
                <Option value="point_on_exterior" type="QString" name="labelAnchorPoint"/>
                <Option value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{4f99d1ec-19f1-43fa-9f9b-56216db3977c}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>" type="QString" name="lineSymbol"/>
                <Option value="0" type="double" name="minLength"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="minLengthMapUnitScale"/>
                <Option value="MM" type="QString" name="minLengthUnit"/>
                <Option value="0" type="double" name="offsetFromAnchor"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromAnchorMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromAnchorUnit"/>
                <Option value="0" type="double" name="offsetFromLabel"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromLabelMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromLabelUnit"/>
              </Option>
            </callout>
          </settings>
        </rule>
        <rule description="Water" filter="setting_name liKe 'W%' and setting_name > 'W00' and setting_name &lt;  'W99'" key="{b0ad5113-8037-4cdf-9158-68926b45e9bc}">
          <settings calloutType="simple">
            <text-style textOrientation="horizontal" fontSizeUnit="Point" fontSize="15" capitalization="0" multilineHeightUnit="Percentage" fontLetterSpacing="0" fontSizeMapUnitScale="3x:0,0,0,0,0,0" previewBkgrdColor="255,255,255,255" fontWeight="50" fontFamily="MS Shell Dlg 2" textColor="0,0,255,255" fontKerning="1" useSubstitutions="0" fontWordSpacing="0" namedStyle="Regular" fontItalic="0" multilineHeight="1" forcedBold="0" textOpacity="1" fontStrikeout="0" fieldName="setting_name" fontUnderline="0" isExpression="0" forcedItalic="0" allowHtml="0" blendMode="0" legendString="Aa">
              <families/>
              <text-buffer bufferOpacity="1" bufferNoFill="1" bufferBlendMode="0" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM" bufferDraw="0" bufferSize="1" bufferColor="255,255,255,255" bufferJoinStyle="128"/>
              <text-mask maskSize="1.5" maskSizeUnits="MM" maskEnabled="0" maskedSymbolLayers="" maskType="0" maskJoinStyle="128" maskOpacity="1" maskSizeMapUnitScale="3x:0,0,0,0,0,0"/>
              <background shapeSizeType="0" shapeRadiiY="0" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetX="0" shapeBorderColor="128,128,128,255" shapeRotationType="0" shapeBlendMode="0" shapeType="0" shapeFillColor="255,255,255,255" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="MM" shapeRadiiUnit="MM" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeSizeUnit="MM" shapeRadiiX="0" shapeOffsetUnit="MM" shapeSizeX="0" shapeRotation="0" shapeJoinStyle="64" shapeOffsetY="0" shapeSizeY="0" shapeDraw="0" shapeSVGFile="" shapeBorderWidth="0">
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="markerSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleMarker" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="0" type="QString" name="angle"/>
                      <Option value="square" type="QString" name="cap_style"/>
                      <Option value="231,113,72,255" type="QString" name="color"/>
                      <Option value="1" type="QString" name="horizontal_anchor_point"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="circle" type="QString" name="name"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="35,35,35,255" type="QString" name="outline_color"/>
                      <Option value="solid" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
                      <Option value="MM" type="QString" name="outline_width_unit"/>
                      <Option value="diameter" type="QString" name="scale_method"/>
                      <Option value="2" type="QString" name="size"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
                      <Option value="MM" type="QString" name="size_unit"/>
                      <Option value="1" type="QString" name="vertical_anchor_point"/>
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
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="fillSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleFill" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
                      <Option value="255,255,255,255" type="QString" name="color"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="128,128,128,255" type="QString" name="outline_color"/>
                      <Option value="no" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="MM" type="QString" name="outline_width_unit"/>
                      <Option value="solid" type="QString" name="style"/>
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
              </background>
              <shadow shadowOffsetGlobal="1" shadowUnder="0" shadowOffsetAngle="135" shadowScale="100" shadowDraw="0" shadowColor="0,0,0,255" shadowOffsetUnit="MM" shadowRadiusUnit="MM" shadowOpacity="0.69999999999999996" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetDist="1" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusAlphaOnly="0" shadowRadius="1.5" shadowBlendMode="6"/>
              <dd_properties>
                <Option type="Map">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
              </dd_properties>
              <substitutions/>
            </text-style>
            <text-format useMaxLineLengthForAutoWrap="1" decimals="3" addDirectionSymbol="0" rightDirectionSymbol=">" plussign="0" wrapChar="" placeDirectionSymbol="0" autoWrapLength="0" multilineAlign="3" formatNumbers="0" reverseDirectionSymbol="0" leftDirectionSymbol="&lt;"/>
            <placement repeatDistance="0" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" offsetType="0" yOffset="7" centroidWhole="0" polygonPlacementFlags="2" offsetUnits="MM" repeatDistanceUnits="MM" dist="5" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" centroidInside="0" placementFlags="10" geometryGenerator="" maxCurvedCharAngleOut="-25" xOffset="-7" preserveRotation="1" lineAnchorType="0" geometryGeneratorEnabled="0" overrunDistance="0" maxCurvedCharAngleIn="25" lineAnchorTextPoint="CenterOfText" distUnits="MM" priority="5" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" lineAnchorClipping="0" allowDegraded="0" fitInPolygonOnly="0" rotationAngle="0" geometryGeneratorType="PointGeometry" layerType="PointGeometry" placement="1" lineAnchorPercent="0.5" quadOffset="4" overlapHandling="PreventOverlap" distMapUnitScale="3x:0,0,0,0,0,0" rotationUnit="AngleDegrees" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0"/>
            <rendering scaleMax="0" scaleVisibility="0" fontLimitPixelSize="0" minFeatureSize="0" upsidedownLabels="0" obstacle="1" maxNumLabels="2000" fontMinPixelSize="3" limitNumLabels="0" mergeLines="0" unplacedVisibility="0" scaleMin="0" zIndex="0" obstacleType="1" drawLabels="1" labelPerPart="0" fontMaxPixelSize="10000" obstacleFactor="1"/>
            <dd_properties>
              <Option type="Map">
                <Option value="" type="QString" name="name"/>
                <Option type="Map" name="properties">
                  <Option type="Map" name="PositionX">
                    <Option value="true" type="bool" name="active"/>
                    <Option value="auxiliary_storage_labeling_positionx" type="QString" name="field"/>
                    <Option value="2" type="int" name="type"/>
                  </Option>
                  <Option type="Map" name="PositionY">
                    <Option value="true" type="bool" name="active"/>
                    <Option value="auxiliary_storage_labeling_positiony" type="QString" name="field"/>
                    <Option value="2" type="int" name="type"/>
                  </Option>
                </Option>
                <Option value="collection" type="QString" name="type"/>
              </Option>
            </dd_properties>
            <callout type="simple">
              <Option type="Map">
                <Option value="pole_of_inaccessibility" type="QString" name="anchorPoint"/>
                <Option value="0" type="int" name="blendMode"/>
                <Option type="Map" name="ddProperties">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
                <Option value="false" type="bool" name="drawToAllParts"/>
                <Option value="0" type="QString" name="enabled"/>
                <Option value="point_on_exterior" type="QString" name="labelAnchorPoint"/>
                <Option value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{db4385d6-5fe3-451c-83a3-09b5b98c1e22}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>" type="QString" name="lineSymbol"/>
                <Option value="0" type="double" name="minLength"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="minLengthMapUnitScale"/>
                <Option value="MM" type="QString" name="minLengthUnit"/>
                <Option value="0" type="double" name="offsetFromAnchor"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromAnchorMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromAnchorUnit"/>
                <Option value="0" type="double" name="offsetFromLabel"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromLabelMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromLabelUnit"/>
              </Option>
            </callout>
          </settings>
        </rule>
        <rule description="Unkown" filter="ELSE" key="{b2ec0bba-20d0-498d-806d-0f0e0fefa60d}">
          <settings calloutType="simple">
            <text-style textOrientation="horizontal" fontSizeUnit="Point" fontSize="14" capitalization="0" multilineHeightUnit="Percentage" fontLetterSpacing="0" fontSizeMapUnitScale="3x:0,0,0,0,0,0" previewBkgrdColor="255,255,255,255" fontWeight="50" fontFamily="Arial" textColor="255,0,0,255" fontKerning="1" useSubstitutions="0" fontWordSpacing="0" namedStyle="Regular" fontItalic="0" multilineHeight="1" forcedBold="0" textOpacity="1" fontStrikeout="0" fieldName="setting_name" fontUnderline="0" isExpression="0" forcedItalic="0" allowHtml="0" blendMode="0" legendString="Aa">
              <families/>
              <text-buffer bufferOpacity="1" bufferNoFill="1" bufferBlendMode="0" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM" bufferDraw="0" bufferSize="1" bufferColor="250,250,250,255" bufferJoinStyle="128"/>
              <text-mask maskSize="0" maskSizeUnits="MM" maskEnabled="0" maskedSymbolLayers="" maskType="0" maskJoinStyle="128" maskOpacity="1" maskSizeMapUnitScale="3x:0,0,0,0,0,0"/>
              <background shapeSizeType="0" shapeRadiiY="0" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetX="0" shapeBorderColor="128,128,128,255" shapeRotationType="0" shapeBlendMode="0" shapeType="0" shapeFillColor="255,255,255,255" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="Point" shapeRadiiUnit="Point" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeSizeUnit="Point" shapeRadiiX="0" shapeOffsetUnit="Point" shapeSizeX="0" shapeRotation="0" shapeJoinStyle="64" shapeOffsetY="0" shapeSizeY="0" shapeDraw="0" shapeSVGFile="" shapeBorderWidth="0">
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="markerSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleMarker" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="0" type="QString" name="angle"/>
                      <Option value="square" type="QString" name="cap_style"/>
                      <Option value="231,113,72,255" type="QString" name="color"/>
                      <Option value="1" type="QString" name="horizontal_anchor_point"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="circle" type="QString" name="name"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="35,35,35,255" type="QString" name="outline_color"/>
                      <Option value="solid" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
                      <Option value="MM" type="QString" name="outline_width_unit"/>
                      <Option value="diameter" type="QString" name="scale_method"/>
                      <Option value="2" type="QString" name="size"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
                      <Option value="MM" type="QString" name="size_unit"/>
                      <Option value="1" type="QString" name="vertical_anchor_point"/>
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
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="fillSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleFill" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
                      <Option value="255,255,255,255" type="QString" name="color"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="128,128,128,255" type="QString" name="outline_color"/>
                      <Option value="no" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="Point" type="QString" name="outline_width_unit"/>
                      <Option value="solid" type="QString" name="style"/>
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
              </background>
              <shadow shadowOffsetGlobal="1" shadowUnder="0" shadowOffsetAngle="135" shadowScale="100" shadowDraw="0" shadowColor="0,0,0,255" shadowOffsetUnit="MM" shadowRadiusUnit="MM" shadowOpacity="0.69999999999999996" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetDist="1" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusAlphaOnly="0" shadowRadius="1.5" shadowBlendMode="6"/>
              <dd_properties>
                <Option type="Map">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
              </dd_properties>
              <substitutions/>
            </text-style>
            <text-format useMaxLineLengthForAutoWrap="1" decimals="3" addDirectionSymbol="0" rightDirectionSymbol=">" plussign="0" wrapChar="" placeDirectionSymbol="0" autoWrapLength="0" multilineAlign="3" formatNumbers="0" reverseDirectionSymbol="0" leftDirectionSymbol="&lt;"/>
            <placement repeatDistance="0" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" offsetType="1" yOffset="7" centroidWhole="0" polygonPlacementFlags="2" offsetUnits="MM" repeatDistanceUnits="MM" dist="0" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" centroidInside="0" placementFlags="10" geometryGenerator="" maxCurvedCharAngleOut="-25" xOffset="-7" preserveRotation="1" lineAnchorType="0" geometryGeneratorEnabled="0" overrunDistance="0" maxCurvedCharAngleIn="25" lineAnchorTextPoint="FollowPlacement" distUnits="MM" priority="5" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" lineAnchorClipping="0" allowDegraded="0" fitInPolygonOnly="0" rotationAngle="0" geometryGeneratorType="PointGeometry" layerType="PointGeometry" placement="1" lineAnchorPercent="0.5" quadOffset="4" overlapHandling="PreventOverlap" distMapUnitScale="3x:0,0,0,0,0,0" rotationUnit="AngleDegrees" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0"/>
            <rendering scaleMax="0" scaleVisibility="0" fontLimitPixelSize="0" minFeatureSize="0" upsidedownLabels="0" obstacle="1" maxNumLabels="2000" fontMinPixelSize="3" limitNumLabels="0" mergeLines="0" unplacedVisibility="0" scaleMin="0" zIndex="0" obstacleType="1" drawLabels="1" labelPerPart="0" fontMaxPixelSize="10000" obstacleFactor="1"/>
            <dd_properties>
              <Option type="Map">
                <Option value="" type="QString" name="name"/>
                <Option name="properties"/>
                <Option value="collection" type="QString" name="type"/>
              </Option>
            </dd_properties>
            <callout type="simple">
              <Option type="Map">
                <Option value="pole_of_inaccessibility" type="QString" name="anchorPoint"/>
                <Option value="0" type="int" name="blendMode"/>
                <Option type="Map" name="ddProperties">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
                <Option value="false" type="bool" name="drawToAllParts"/>
                <Option value="0" type="QString" name="enabled"/>
                <Option value="point_on_exterior" type="QString" name="labelAnchorPoint"/>
                <Option value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{be704c21-57e1-450c-9bff-61d7a91a3f02}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>" type="QString" name="lineSymbol"/>
                <Option value="0" type="double" name="minLength"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="minLengthMapUnitScale"/>
                <Option value="MM" type="QString" name="minLengthUnit"/>
                <Option value="0" type="double" name="offsetFromAnchor"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromAnchorMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromAnchorUnit"/>
                <Option value="0" type="double" name="offsetFromLabel"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromLabelMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromLabelUnit"/>
              </Option>
            </callout>
          </settings>
        </rule>
      </rule>
      <rule description="Hanging" filter="name is not Null" key="{5b868ba0-f058-498b-a73b-d3b4e136ef0a}">
        <rule description="controls" filter="name> '0' and name &lt; '999'" key="{a3b0f6bf-8cab-4614-8be5-8748596383fe}">
          <settings calloutType="simple">
            <text-style textOrientation="horizontal" fontSizeUnit="Point" fontSize="15" capitalization="0" multilineHeightUnit="Percentage" fontLetterSpacing="0" fontSizeMapUnitScale="3x:0,0,0,0,0,0" previewBkgrdColor="255,255,255,255" fontWeight="50" fontFamily="MS Shell Dlg 2" textColor="139,0,139,255" fontKerning="1" useSubstitutions="0" fontWordSpacing="0" namedStyle="Regular" fontItalic="0" multilineHeight="1" forcedBold="0" textOpacity="1" fontStrikeout="0" fieldName="name" fontUnderline="0" isExpression="0" forcedItalic="0" allowHtml="0" blendMode="0" legendString="Aa">
              <families/>
              <text-buffer bufferOpacity="1" bufferNoFill="1" bufferBlendMode="0" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM" bufferDraw="0" bufferSize="1" bufferColor="255,255,255,255" bufferJoinStyle="128"/>
              <text-mask maskSize="1.5" maskSizeUnits="MM" maskEnabled="0" maskedSymbolLayers="" maskType="0" maskJoinStyle="128" maskOpacity="1" maskSizeMapUnitScale="3x:0,0,0,0,0,0"/>
              <background shapeSizeType="0" shapeRadiiY="0" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetX="0" shapeBorderColor="128,128,128,255" shapeRotationType="0" shapeBlendMode="0" shapeType="0" shapeFillColor="255,255,255,255" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="MM" shapeRadiiUnit="MM" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeSizeUnit="MM" shapeRadiiX="0" shapeOffsetUnit="MM" shapeSizeX="0" shapeRotation="0" shapeJoinStyle="64" shapeOffsetY="0" shapeSizeY="0" shapeDraw="0" shapeSVGFile="" shapeBorderWidth="0">
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="markerSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleMarker" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="0" type="QString" name="angle"/>
                      <Option value="square" type="QString" name="cap_style"/>
                      <Option value="152,125,183,255" type="QString" name="color"/>
                      <Option value="1" type="QString" name="horizontal_anchor_point"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="circle" type="QString" name="name"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="35,35,35,255" type="QString" name="outline_color"/>
                      <Option value="solid" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
                      <Option value="MM" type="QString" name="outline_width_unit"/>
                      <Option value="diameter" type="QString" name="scale_method"/>
                      <Option value="2" type="QString" name="size"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
                      <Option value="MM" type="QString" name="size_unit"/>
                      <Option value="1" type="QString" name="vertical_anchor_point"/>
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
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="fillSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleFill" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
                      <Option value="255,255,255,255" type="QString" name="color"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="128,128,128,255" type="QString" name="outline_color"/>
                      <Option value="no" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="MM" type="QString" name="outline_width_unit"/>
                      <Option value="solid" type="QString" name="style"/>
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
              </background>
              <shadow shadowOffsetGlobal="1" shadowUnder="0" shadowOffsetAngle="135" shadowScale="100" shadowDraw="0" shadowColor="0,0,0,255" shadowOffsetUnit="MM" shadowRadiusUnit="MM" shadowOpacity="0.69999999999999996" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetDist="1" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusAlphaOnly="0" shadowRadius="1.5" shadowBlendMode="6"/>
              <dd_properties>
                <Option type="Map">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
              </dd_properties>
              <substitutions/>
            </text-style>
            <text-format useMaxLineLengthForAutoWrap="1" decimals="3" addDirectionSymbol="0" rightDirectionSymbol=">" plussign="0" wrapChar="" placeDirectionSymbol="0" autoWrapLength="0" multilineAlign="3" formatNumbers="0" reverseDirectionSymbol="0" leftDirectionSymbol="&lt;"/>
            <placement repeatDistance="0" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" offsetType="0" yOffset="-7" centroidWhole="0" polygonPlacementFlags="2" offsetUnits="MM" repeatDistanceUnits="MM" dist="5" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" centroidInside="0" placementFlags="10" geometryGenerator="" maxCurvedCharAngleOut="-25" xOffset="7" preserveRotation="1" lineAnchorType="0" geometryGeneratorEnabled="0" overrunDistance="0" maxCurvedCharAngleIn="25" lineAnchorTextPoint="CenterOfText" distUnits="MM" priority="5" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" lineAnchorClipping="0" allowDegraded="0" fitInPolygonOnly="0" rotationAngle="0" geometryGeneratorType="PointGeometry" layerType="PointGeometry" placement="1" lineAnchorPercent="0.5" quadOffset="4" overlapHandling="PreventOverlap" distMapUnitScale="3x:0,0,0,0,0,0" rotationUnit="AngleDegrees" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0"/>
            <rendering scaleMax="0" scaleVisibility="0" fontLimitPixelSize="0" minFeatureSize="0" upsidedownLabels="0" obstacle="1" maxNumLabels="2000" fontMinPixelSize="3" limitNumLabels="0" mergeLines="0" unplacedVisibility="0" scaleMin="0" zIndex="0" obstacleType="1" drawLabels="1" labelPerPart="0" fontMaxPixelSize="10000" obstacleFactor="1"/>
            <dd_properties>
              <Option type="Map">
                <Option value="" type="QString" name="name"/>
                <Option type="Map" name="properties">
                  <Option type="Map" name="PositionX">
                    <Option value="true" type="bool" name="active"/>
                    <Option value="auxiliary_storage_labeling_positionx" type="QString" name="field"/>
                    <Option value="2" type="int" name="type"/>
                  </Option>
                  <Option type="Map" name="PositionY">
                    <Option value="true" type="bool" name="active"/>
                    <Option value="auxiliary_storage_labeling_positiony" type="QString" name="field"/>
                    <Option value="2" type="int" name="type"/>
                  </Option>
                </Option>
                <Option value="collection" type="QString" name="type"/>
              </Option>
            </dd_properties>
            <callout type="simple">
              <Option type="Map">
                <Option value="pole_of_inaccessibility" type="QString" name="anchorPoint"/>
                <Option value="0" type="int" name="blendMode"/>
                <Option type="Map" name="ddProperties">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
                <Option value="false" type="bool" name="drawToAllParts"/>
                <Option value="0" type="QString" name="enabled"/>
                <Option value="point_on_exterior" type="QString" name="labelAnchorPoint"/>
                <Option value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{0a1ed788-77aa-41b7-8734-760227c92d93}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>" type="QString" name="lineSymbol"/>
                <Option value="0" type="double" name="minLength"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="minLengthMapUnitScale"/>
                <Option value="MM" type="QString" name="minLengthUnit"/>
                <Option value="0" type="double" name="offsetFromAnchor"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromAnchorMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromAnchorUnit"/>
                <Option value="0" type="double" name="offsetFromLabel"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromLabelMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromLabelUnit"/>
              </Option>
            </callout>
          </settings>
        </rule>
        <rule description="HH" filter="name like 'HH'" key="{a5e7c910-a7a6-46f5-8b48-a2eeab0707a9}">
          <settings calloutType="simple">
            <text-style textOrientation="horizontal" fontSizeUnit="Point" fontSize="15" capitalization="0" multilineHeightUnit="Percentage" fontLetterSpacing="0" fontSizeMapUnitScale="3x:0,0,0,0,0,0" previewBkgrdColor="255,255,255,255" fontWeight="50" fontFamily="MS Shell Dlg 2" textColor="139,0,139,255" fontKerning="1" useSubstitutions="0" fontWordSpacing="0" namedStyle="Regular" fontItalic="0" multilineHeight="1" forcedBold="0" textOpacity="1" fontStrikeout="0" fieldName="name" fontUnderline="0" isExpression="0" forcedItalic="0" allowHtml="0" blendMode="0" legendString="Aa">
              <families/>
              <text-buffer bufferOpacity="1" bufferNoFill="1" bufferBlendMode="0" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM" bufferDraw="0" bufferSize="1" bufferColor="255,255,255,255" bufferJoinStyle="128"/>
              <text-mask maskSize="1.5" maskSizeUnits="MM" maskEnabled="0" maskedSymbolLayers="" maskType="0" maskJoinStyle="128" maskOpacity="1" maskSizeMapUnitScale="3x:0,0,0,0,0,0"/>
              <background shapeSizeType="0" shapeRadiiY="0" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetX="0" shapeBorderColor="128,128,128,255" shapeRotationType="0" shapeBlendMode="0" shapeType="0" shapeFillColor="255,255,255,255" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="MM" shapeRadiiUnit="MM" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeSizeUnit="MM" shapeRadiiX="0" shapeOffsetUnit="MM" shapeSizeX="0" shapeRotation="0" shapeJoinStyle="64" shapeOffsetY="0" shapeSizeY="0" shapeDraw="0" shapeSVGFile="" shapeBorderWidth="0">
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="markerSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleMarker" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="0" type="QString" name="angle"/>
                      <Option value="square" type="QString" name="cap_style"/>
                      <Option value="190,207,80,255" type="QString" name="color"/>
                      <Option value="1" type="QString" name="horizontal_anchor_point"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="circle" type="QString" name="name"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="35,35,35,255" type="QString" name="outline_color"/>
                      <Option value="solid" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
                      <Option value="MM" type="QString" name="outline_width_unit"/>
                      <Option value="diameter" type="QString" name="scale_method"/>
                      <Option value="2" type="QString" name="size"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
                      <Option value="MM" type="QString" name="size_unit"/>
                      <Option value="1" type="QString" name="vertical_anchor_point"/>
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
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="fillSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleFill" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
                      <Option value="255,255,255,255" type="QString" name="color"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="128,128,128,255" type="QString" name="outline_color"/>
                      <Option value="no" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="MM" type="QString" name="outline_width_unit"/>
                      <Option value="solid" type="QString" name="style"/>
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
              </background>
              <shadow shadowOffsetGlobal="1" shadowUnder="0" shadowOffsetAngle="135" shadowScale="100" shadowDraw="0" shadowColor="0,0,0,255" shadowOffsetUnit="MM" shadowRadiusUnit="MM" shadowOpacity="0.69999999999999996" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetDist="1" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusAlphaOnly="0" shadowRadius="1.5" shadowBlendMode="6"/>
              <dd_properties>
                <Option type="Map">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
              </dd_properties>
              <substitutions/>
            </text-style>
            <text-format useMaxLineLengthForAutoWrap="1" decimals="3" addDirectionSymbol="0" rightDirectionSymbol=">" plussign="0" wrapChar="" placeDirectionSymbol="0" autoWrapLength="0" multilineAlign="3" formatNumbers="0" reverseDirectionSymbol="0" leftDirectionSymbol="&lt;"/>
            <placement repeatDistance="0" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" offsetType="0" yOffset="-7" centroidWhole="0" polygonPlacementFlags="2" offsetUnits="MM" repeatDistanceUnits="MM" dist="5" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" centroidInside="0" placementFlags="10" geometryGenerator="" maxCurvedCharAngleOut="-25" xOffset="7" preserveRotation="1" lineAnchorType="0" geometryGeneratorEnabled="0" overrunDistance="0" maxCurvedCharAngleIn="25" lineAnchorTextPoint="CenterOfText" distUnits="MM" priority="5" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" lineAnchorClipping="0" allowDegraded="0" fitInPolygonOnly="0" rotationAngle="0" geometryGeneratorType="PointGeometry" layerType="PointGeometry" placement="1" lineAnchorPercent="0.5" quadOffset="4" overlapHandling="PreventOverlap" distMapUnitScale="3x:0,0,0,0,0,0" rotationUnit="AngleDegrees" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0"/>
            <rendering scaleMax="0" scaleVisibility="0" fontLimitPixelSize="0" minFeatureSize="0" upsidedownLabels="0" obstacle="1" maxNumLabels="2000" fontMinPixelSize="3" limitNumLabels="0" mergeLines="0" unplacedVisibility="0" scaleMin="0" zIndex="0" obstacleType="1" drawLabels="1" labelPerPart="0" fontMaxPixelSize="10000" obstacleFactor="1"/>
            <dd_properties>
              <Option type="Map">
                <Option value="" type="QString" name="name"/>
                <Option type="Map" name="properties">
                  <Option type="Map" name="PositionX">
                    <Option value="true" type="bool" name="active"/>
                    <Option value="auxiliary_storage_labeling_positionx" type="QString" name="field"/>
                    <Option value="2" type="int" name="type"/>
                  </Option>
                  <Option type="Map" name="PositionY">
                    <Option value="true" type="bool" name="active"/>
                    <Option value="auxiliary_storage_labeling_positiony" type="QString" name="field"/>
                    <Option value="2" type="int" name="type"/>
                  </Option>
                </Option>
                <Option value="collection" type="QString" name="type"/>
              </Option>
            </dd_properties>
            <callout type="simple">
              <Option type="Map">
                <Option value="pole_of_inaccessibility" type="QString" name="anchorPoint"/>
                <Option value="0" type="int" name="blendMode"/>
                <Option type="Map" name="ddProperties">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
                <Option value="false" type="bool" name="drawToAllParts"/>
                <Option value="0" type="QString" name="enabled"/>
                <Option value="point_on_exterior" type="QString" name="labelAnchorPoint"/>
                <Option value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{4f99d1ec-19f1-43fa-9f9b-56216db3977c}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>" type="QString" name="lineSymbol"/>
                <Option value="0" type="double" name="minLength"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="minLengthMapUnitScale"/>
                <Option value="MM" type="QString" name="minLengthUnit"/>
                <Option value="0" type="double" name="offsetFromAnchor"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromAnchorMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromAnchorUnit"/>
                <Option value="0" type="double" name="offsetFromLabel"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromLabelMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromLabelUnit"/>
              </Option>
            </callout>
          </settings>
        </rule>
        <rule description="Water" filter="name liKe 'W%' and name > 'W0' and name &lt;  'W9'" key="{f54b3b4c-679e-43bd-bb1d-e76ad6d09dd1}">
          <settings calloutType="simple">
            <text-style textOrientation="horizontal" fontSizeUnit="Point" fontSize="15" capitalization="0" multilineHeightUnit="Percentage" fontLetterSpacing="0" fontSizeMapUnitScale="3x:0,0,0,0,0,0" previewBkgrdColor="255,255,255,255" fontWeight="50" fontFamily="MS Shell Dlg 2" textColor="0,0,255,255" fontKerning="1" useSubstitutions="0" fontWordSpacing="0" namedStyle="Regular" fontItalic="0" multilineHeight="1" forcedBold="0" textOpacity="1" fontStrikeout="0" fieldName="name" fontUnderline="0" isExpression="0" forcedItalic="0" allowHtml="0" blendMode="0" legendString="Aa">
              <families/>
              <text-buffer bufferOpacity="1" bufferNoFill="1" bufferBlendMode="0" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM" bufferDraw="0" bufferSize="1" bufferColor="255,255,255,255" bufferJoinStyle="128"/>
              <text-mask maskSize="1.5" maskSizeUnits="MM" maskEnabled="0" maskedSymbolLayers="" maskType="0" maskJoinStyle="128" maskOpacity="1" maskSizeMapUnitScale="3x:0,0,0,0,0,0"/>
              <background shapeSizeType="0" shapeRadiiY="0" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetX="0" shapeBorderColor="128,128,128,255" shapeRotationType="0" shapeBlendMode="0" shapeType="0" shapeFillColor="255,255,255,255" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="MM" shapeRadiiUnit="MM" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeSizeUnit="MM" shapeRadiiX="0" shapeOffsetUnit="MM" shapeSizeX="0" shapeRotation="0" shapeJoinStyle="64" shapeOffsetY="0" shapeSizeY="0" shapeDraw="0" shapeSVGFile="" shapeBorderWidth="0">
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="markerSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleMarker" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="0" type="QString" name="angle"/>
                      <Option value="square" type="QString" name="cap_style"/>
                      <Option value="231,113,72,255" type="QString" name="color"/>
                      <Option value="1" type="QString" name="horizontal_anchor_point"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="circle" type="QString" name="name"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="35,35,35,255" type="QString" name="outline_color"/>
                      <Option value="solid" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
                      <Option value="MM" type="QString" name="outline_width_unit"/>
                      <Option value="diameter" type="QString" name="scale_method"/>
                      <Option value="2" type="QString" name="size"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
                      <Option value="MM" type="QString" name="size_unit"/>
                      <Option value="1" type="QString" name="vertical_anchor_point"/>
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
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="fillSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleFill" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
                      <Option value="255,255,255,255" type="QString" name="color"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="128,128,128,255" type="QString" name="outline_color"/>
                      <Option value="no" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="MM" type="QString" name="outline_width_unit"/>
                      <Option value="solid" type="QString" name="style"/>
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
              </background>
              <shadow shadowOffsetGlobal="1" shadowUnder="0" shadowOffsetAngle="135" shadowScale="100" shadowDraw="0" shadowColor="0,0,0,255" shadowOffsetUnit="MM" shadowRadiusUnit="MM" shadowOpacity="0.69999999999999996" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetDist="1" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusAlphaOnly="0" shadowRadius="1.5" shadowBlendMode="6"/>
              <dd_properties>
                <Option type="Map">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
              </dd_properties>
              <substitutions/>
            </text-style>
            <text-format useMaxLineLengthForAutoWrap="1" decimals="3" addDirectionSymbol="0" rightDirectionSymbol=">" plussign="0" wrapChar="" placeDirectionSymbol="0" autoWrapLength="0" multilineAlign="3" formatNumbers="0" reverseDirectionSymbol="0" leftDirectionSymbol="&lt;"/>
            <placement repeatDistance="0" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" offsetType="0" yOffset="-7" centroidWhole="0" polygonPlacementFlags="2" offsetUnits="MM" repeatDistanceUnits="MM" dist="5" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" centroidInside="0" placementFlags="10" geometryGenerator="" maxCurvedCharAngleOut="-25" xOffset="7" preserveRotation="1" lineAnchorType="0" geometryGeneratorEnabled="0" overrunDistance="0" maxCurvedCharAngleIn="25" lineAnchorTextPoint="CenterOfText" distUnits="MM" priority="5" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" lineAnchorClipping="0" allowDegraded="0" fitInPolygonOnly="0" rotationAngle="0" geometryGeneratorType="PointGeometry" layerType="PointGeometry" placement="1" lineAnchorPercent="0.5" quadOffset="4" overlapHandling="PreventOverlap" distMapUnitScale="3x:0,0,0,0,0,0" rotationUnit="AngleDegrees" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0"/>
            <rendering scaleMax="0" scaleVisibility="0" fontLimitPixelSize="0" minFeatureSize="0" upsidedownLabels="0" obstacle="1" maxNumLabels="2000" fontMinPixelSize="3" limitNumLabels="0" mergeLines="0" unplacedVisibility="0" scaleMin="0" zIndex="0" obstacleType="1" drawLabels="1" labelPerPart="0" fontMaxPixelSize="10000" obstacleFactor="1"/>
            <dd_properties>
              <Option type="Map">
                <Option value="" type="QString" name="name"/>
                <Option type="Map" name="properties">
                  <Option type="Map" name="PositionX">
                    <Option value="true" type="bool" name="active"/>
                    <Option value="auxiliary_storage_labeling_positionx" type="QString" name="field"/>
                    <Option value="2" type="int" name="type"/>
                  </Option>
                  <Option type="Map" name="PositionY">
                    <Option value="true" type="bool" name="active"/>
                    <Option value="auxiliary_storage_labeling_positiony" type="QString" name="field"/>
                    <Option value="2" type="int" name="type"/>
                  </Option>
                </Option>
                <Option value="collection" type="QString" name="type"/>
              </Option>
            </dd_properties>
            <callout type="simple">
              <Option type="Map">
                <Option value="pole_of_inaccessibility" type="QString" name="anchorPoint"/>
                <Option value="0" type="int" name="blendMode"/>
                <Option type="Map" name="ddProperties">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
                <Option value="false" type="bool" name="drawToAllParts"/>
                <Option value="0" type="QString" name="enabled"/>
                <Option value="point_on_exterior" type="QString" name="labelAnchorPoint"/>
                <Option value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{db4385d6-5fe3-451c-83a3-09b5b98c1e22}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>" type="QString" name="lineSymbol"/>
                <Option value="0" type="double" name="minLength"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="minLengthMapUnitScale"/>
                <Option value="MM" type="QString" name="minLengthUnit"/>
                <Option value="0" type="double" name="offsetFromAnchor"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromAnchorMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromAnchorUnit"/>
                <Option value="0" type="double" name="offsetFromLabel"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromLabelMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromLabelUnit"/>
              </Option>
            </callout>
          </settings>
        </rule>
        <rule description="Unkown" filter="ELSE" key="{7455f4dd-ac50-44ce-b4bc-e1000d729c48}">
          <settings calloutType="simple">
            <text-style textOrientation="horizontal" fontSizeUnit="Point" fontSize="10" capitalization="0" multilineHeightUnit="Percentage" fontLetterSpacing="0" fontSizeMapUnitScale="3x:0,0,0,0,0,0" previewBkgrdColor="255,255,255,255" fontWeight="50" fontFamily="Arial" textColor="255,0,0,255" fontKerning="1" useSubstitutions="0" fontWordSpacing="0" namedStyle="Regular" fontItalic="0" multilineHeight="1" forcedBold="0" textOpacity="1" fontStrikeout="0" fieldName="description" fontUnderline="0" isExpression="0" forcedItalic="0" allowHtml="0" blendMode="0" legendString="Aa">
              <families/>
              <text-buffer bufferOpacity="1" bufferNoFill="1" bufferBlendMode="0" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM" bufferDraw="0" bufferSize="1" bufferColor="250,250,250,255" bufferJoinStyle="128"/>
              <text-mask maskSize="0" maskSizeUnits="MM" maskEnabled="0" maskedSymbolLayers="" maskType="0" maskJoinStyle="128" maskOpacity="1" maskSizeMapUnitScale="3x:0,0,0,0,0,0"/>
              <background shapeSizeType="0" shapeRadiiY="0" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetX="0" shapeBorderColor="128,128,128,255" shapeRotationType="0" shapeBlendMode="0" shapeType="0" shapeFillColor="255,255,255,255" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="Point" shapeRadiiUnit="Point" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeSizeUnit="Point" shapeRadiiX="0" shapeOffsetUnit="Point" shapeSizeX="0" shapeRotation="0" shapeJoinStyle="64" shapeOffsetY="0" shapeSizeY="0" shapeDraw="0" shapeSVGFile="" shapeBorderWidth="0">
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="markerSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleMarker" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="0" type="QString" name="angle"/>
                      <Option value="square" type="QString" name="cap_style"/>
                      <Option value="229,182,54,255" type="QString" name="color"/>
                      <Option value="1" type="QString" name="horizontal_anchor_point"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="circle" type="QString" name="name"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="35,35,35,255" type="QString" name="outline_color"/>
                      <Option value="solid" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
                      <Option value="MM" type="QString" name="outline_width_unit"/>
                      <Option value="diameter" type="QString" name="scale_method"/>
                      <Option value="2" type="QString" name="size"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
                      <Option value="MM" type="QString" name="size_unit"/>
                      <Option value="1" type="QString" name="vertical_anchor_point"/>
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
                <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="fillSymbol" clip_to_extent="1" alpha="1">
                  <data_defined_properties>
                    <Option type="Map">
                      <Option value="" type="QString" name="name"/>
                      <Option name="properties"/>
                      <Option value="collection" type="QString" name="type"/>
                    </Option>
                  </data_defined_properties>
                  <layer id="" locked="0" class="SimpleFill" enabled="1" pass="0">
                    <Option type="Map">
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
                      <Option value="255,255,255,255" type="QString" name="color"/>
                      <Option value="bevel" type="QString" name="joinstyle"/>
                      <Option value="0,0" type="QString" name="offset"/>
                      <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                      <Option value="MM" type="QString" name="offset_unit"/>
                      <Option value="128,128,128,255" type="QString" name="outline_color"/>
                      <Option value="no" type="QString" name="outline_style"/>
                      <Option value="0" type="QString" name="outline_width"/>
                      <Option value="Point" type="QString" name="outline_width_unit"/>
                      <Option value="solid" type="QString" name="style"/>
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
              </background>
              <shadow shadowOffsetGlobal="1" shadowUnder="0" shadowOffsetAngle="135" shadowScale="100" shadowDraw="0" shadowColor="0,0,0,255" shadowOffsetUnit="MM" shadowRadiusUnit="MM" shadowOpacity="0.69999999999999996" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetDist="1" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusAlphaOnly="0" shadowRadius="1.5" shadowBlendMode="6"/>
              <dd_properties>
                <Option type="Map">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
              </dd_properties>
              <substitutions/>
            </text-style>
            <text-format useMaxLineLengthForAutoWrap="1" decimals="3" addDirectionSymbol="0" rightDirectionSymbol=">" plussign="0" wrapChar="" placeDirectionSymbol="0" autoWrapLength="0" multilineAlign="3" formatNumbers="0" reverseDirectionSymbol="0" leftDirectionSymbol="&lt;"/>
            <placement repeatDistance="0" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" offsetType="1" yOffset="-7" centroidWhole="0" polygonPlacementFlags="2" offsetUnits="MM" repeatDistanceUnits="MM" dist="0" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" centroidInside="0" placementFlags="10" geometryGenerator="" maxCurvedCharAngleOut="-25" xOffset="7" preserveRotation="1" lineAnchorType="0" geometryGeneratorEnabled="0" overrunDistance="0" maxCurvedCharAngleIn="25" lineAnchorTextPoint="FollowPlacement" distUnits="MM" priority="5" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" lineAnchorClipping="0" allowDegraded="0" fitInPolygonOnly="0" rotationAngle="0" geometryGeneratorType="PointGeometry" layerType="PointGeometry" placement="1" lineAnchorPercent="0.5" quadOffset="4" overlapHandling="PreventOverlap" distMapUnitScale="3x:0,0,0,0,0,0" rotationUnit="AngleDegrees" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0"/>
            <rendering scaleMax="0" scaleVisibility="0" fontLimitPixelSize="0" minFeatureSize="0" upsidedownLabels="0" obstacle="1" maxNumLabels="2000" fontMinPixelSize="3" limitNumLabels="0" mergeLines="0" unplacedVisibility="0" scaleMin="0" zIndex="0" obstacleType="1" drawLabels="1" labelPerPart="0" fontMaxPixelSize="10000" obstacleFactor="1"/>
            <dd_properties>
              <Option type="Map">
                <Option value="" type="QString" name="name"/>
                <Option name="properties"/>
                <Option value="collection" type="QString" name="type"/>
              </Option>
            </dd_properties>
            <callout type="simple">
              <Option type="Map">
                <Option value="pole_of_inaccessibility" type="QString" name="anchorPoint"/>
                <Option value="0" type="int" name="blendMode"/>
                <Option type="Map" name="ddProperties">
                  <Option value="" type="QString" name="name"/>
                  <Option name="properties"/>
                  <Option value="collection" type="QString" name="type"/>
                </Option>
                <Option value="false" type="bool" name="drawToAllParts"/>
                <Option value="0" type="QString" name="enabled"/>
                <Option value="point_on_exterior" type="QString" name="labelAnchorPoint"/>
                <Option value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{be704c21-57e1-450c-9bff-61d7a91a3f02}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>" type="QString" name="lineSymbol"/>
                <Option value="0" type="double" name="minLength"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="minLengthMapUnitScale"/>
                <Option value="MM" type="QString" name="minLengthUnit"/>
                <Option value="0" type="double" name="offsetFromAnchor"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromAnchorMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromAnchorUnit"/>
                <Option value="0" type="double" name="offsetFromLabel"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromLabelMapUnitScale"/>
                <Option value="MM" type="QString" name="offsetFromLabelUnit"/>
              </Option>
            </callout>
          </settings>
        </rule>
      </rule>
      <rule filter="ELSE" key="{ccaf398f-edcf-41aa-b5f0-16154e22ed51}">
        <settings calloutType="simple">
          <text-style textOrientation="horizontal" fontSizeUnit="Point" fontSize="14" capitalization="0" multilineHeightUnit="Percentage" fontLetterSpacing="0" fontSizeMapUnitScale="3x:0,0,0,0,0,0" previewBkgrdColor="255,255,255,255" fontWeight="50" fontFamily="MS Shell Dlg 2" textColor="255,0,0,255" fontKerning="1" useSubstitutions="0" fontWordSpacing="0" namedStyle="Regular" fontItalic="0" multilineHeight="1" forcedBold="0" textOpacity="1" fontStrikeout="0" fieldName="'??' " fontUnderline="0" isExpression="1" forcedItalic="0" allowHtml="0" blendMode="0" legendString="Aa">
            <families/>
            <text-buffer bufferOpacity="1" bufferNoFill="1" bufferBlendMode="0" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM" bufferDraw="0" bufferSize="1" bufferColor="255,255,255,255" bufferJoinStyle="128"/>
            <text-mask maskSize="1.5" maskSizeUnits="MM" maskEnabled="0" maskedSymbolLayers="" maskType="0" maskJoinStyle="128" maskOpacity="1" maskSizeMapUnitScale="3x:0,0,0,0,0,0"/>
            <background shapeSizeType="0" shapeRadiiY="0" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetX="0" shapeBorderColor="128,128,128,255" shapeRotationType="0" shapeBlendMode="0" shapeType="0" shapeFillColor="255,255,255,255" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="MM" shapeRadiiUnit="MM" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeSizeUnit="MM" shapeRadiiX="0" shapeOffsetUnit="MM" shapeSizeX="0" shapeRotation="0" shapeJoinStyle="64" shapeOffsetY="0" shapeSizeY="0" shapeDraw="0" shapeSVGFile="" shapeBorderWidth="0">
              <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="markerSymbol" clip_to_extent="1" alpha="1">
                <data_defined_properties>
                  <Option type="Map">
                    <Option value="" type="QString" name="name"/>
                    <Option name="properties"/>
                    <Option value="collection" type="QString" name="type"/>
                  </Option>
                </data_defined_properties>
                <layer id="" locked="0" class="SimpleMarker" enabled="1" pass="0">
                  <Option type="Map">
                    <Option value="0" type="QString" name="angle"/>
                    <Option value="square" type="QString" name="cap_style"/>
                    <Option value="255,158,23,255" type="QString" name="color"/>
                    <Option value="1" type="QString" name="horizontal_anchor_point"/>
                    <Option value="bevel" type="QString" name="joinstyle"/>
                    <Option value="circle" type="QString" name="name"/>
                    <Option value="0,0" type="QString" name="offset"/>
                    <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                    <Option value="MM" type="QString" name="offset_unit"/>
                    <Option value="35,35,35,255" type="QString" name="outline_color"/>
                    <Option value="solid" type="QString" name="outline_style"/>
                    <Option value="0" type="QString" name="outline_width"/>
                    <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
                    <Option value="MM" type="QString" name="outline_width_unit"/>
                    <Option value="diameter" type="QString" name="scale_method"/>
                    <Option value="2" type="QString" name="size"/>
                    <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
                    <Option value="MM" type="QString" name="size_unit"/>
                    <Option value="1" type="QString" name="vertical_anchor_point"/>
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
              <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="fillSymbol" clip_to_extent="1" alpha="1">
                <data_defined_properties>
                  <Option type="Map">
                    <Option value="" type="QString" name="name"/>
                    <Option name="properties"/>
                    <Option value="collection" type="QString" name="type"/>
                  </Option>
                </data_defined_properties>
                <layer id="" locked="0" class="SimpleFill" enabled="1" pass="0">
                  <Option type="Map">
                    <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
                    <Option value="255,255,255,255" type="QString" name="color"/>
                    <Option value="bevel" type="QString" name="joinstyle"/>
                    <Option value="0,0" type="QString" name="offset"/>
                    <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                    <Option value="MM" type="QString" name="offset_unit"/>
                    <Option value="128,128,128,255" type="QString" name="outline_color"/>
                    <Option value="no" type="QString" name="outline_style"/>
                    <Option value="0" type="QString" name="outline_width"/>
                    <Option value="MM" type="QString" name="outline_width_unit"/>
                    <Option value="solid" type="QString" name="style"/>
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
            </background>
            <shadow shadowOffsetGlobal="1" shadowUnder="0" shadowOffsetAngle="135" shadowScale="100" shadowDraw="0" shadowColor="0,0,0,255" shadowOffsetUnit="MM" shadowRadiusUnit="MM" shadowOpacity="0.69999999999999996" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetDist="1" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusAlphaOnly="0" shadowRadius="1.5" shadowBlendMode="6"/>
            <dd_properties>
              <Option type="Map">
                <Option value="" type="QString" name="name"/>
                <Option name="properties"/>
                <Option value="collection" type="QString" name="type"/>
              </Option>
            </dd_properties>
            <substitutions/>
          </text-style>
          <text-format useMaxLineLengthForAutoWrap="1" decimals="3" addDirectionSymbol="0" rightDirectionSymbol=">" plussign="0" wrapChar="" placeDirectionSymbol="0" autoWrapLength="0" multilineAlign="3" formatNumbers="0" reverseDirectionSymbol="0" leftDirectionSymbol="&lt;"/>
          <placement repeatDistance="0" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" offsetType="0" yOffset="-7" centroidWhole="0" polygonPlacementFlags="2" offsetUnits="MM" repeatDistanceUnits="MM" dist="5" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" centroidInside="0" placementFlags="10" geometryGenerator="" maxCurvedCharAngleOut="-25" xOffset="7" preserveRotation="1" lineAnchorType="0" geometryGeneratorEnabled="0" overrunDistance="0" maxCurvedCharAngleIn="25" lineAnchorTextPoint="CenterOfText" distUnits="MM" priority="5" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" lineAnchorClipping="0" allowDegraded="0" fitInPolygonOnly="0" rotationAngle="0" geometryGeneratorType="PointGeometry" layerType="PointGeometry" placement="1" lineAnchorPercent="0.5" quadOffset="4" overlapHandling="PreventOverlap" distMapUnitScale="3x:0,0,0,0,0,0" rotationUnit="AngleDegrees" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0"/>
          <rendering scaleMax="0" scaleVisibility="0" fontLimitPixelSize="0" minFeatureSize="0" upsidedownLabels="0" obstacle="1" maxNumLabels="2000" fontMinPixelSize="3" limitNumLabels="0" mergeLines="0" unplacedVisibility="0" scaleMin="0" zIndex="0" obstacleType="1" drawLabels="1" labelPerPart="0" fontMaxPixelSize="10000" obstacleFactor="1"/>
          <dd_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option type="Map" name="properties">
                <Option type="Map" name="PositionX">
                  <Option value="true" type="bool" name="active"/>
                  <Option value="auxiliary_storage_labeling_positionx" type="QString" name="field"/>
                  <Option value="2" type="int" name="type"/>
                </Option>
                <Option type="Map" name="PositionY">
                  <Option value="true" type="bool" name="active"/>
                  <Option value="auxiliary_storage_labeling_positiony" type="QString" name="field"/>
                  <Option value="2" type="int" name="type"/>
                </Option>
              </Option>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </dd_properties>
          <callout type="simple">
            <Option type="Map">
              <Option value="pole_of_inaccessibility" type="QString" name="anchorPoint"/>
              <Option value="0" type="int" name="blendMode"/>
              <Option type="Map" name="ddProperties">
                <Option value="" type="QString" name="name"/>
                <Option name="properties"/>
                <Option value="collection" type="QString" name="type"/>
              </Option>
              <Option value="false" type="bool" name="drawToAllParts"/>
              <Option value="0" type="QString" name="enabled"/>
              <Option value="point_on_exterior" type="QString" name="labelAnchorPoint"/>
              <Option value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{ef00bc53-7213-485b-9c40-c041172b540d}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>" type="QString" name="lineSymbol"/>
              <Option value="0" type="double" name="minLength"/>
              <Option value="3x:0,0,0,0,0,0" type="QString" name="minLengthMapUnitScale"/>
              <Option value="MM" type="QString" name="minLengthUnit"/>
              <Option value="0" type="double" name="offsetFromAnchor"/>
              <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromAnchorMapUnitScale"/>
              <Option value="MM" type="QString" name="offsetFromAnchorUnit"/>
              <Option value="0" type="double" name="offsetFromLabel"/>
              <Option value="3x:0,0,0,0,0,0" type="QString" name="offsetFromLabelMapUnitScale"/>
              <Option value="MM" type="QString" name="offsetFromLabelUnit"/>
            </Option>
          </callout>
        </settings>
      </rule>
    </rules>
  </labeling>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
  <layerOpacity>0.75</layerOpacity>
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
          <layer id="{3455926b-a879-42fa-8bff-03a951eed6db}" locked="0" class="SimpleLine" enabled="1" pass="0">
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
  <DiagramLayerSettings linePlacementFlags="2" dist="0" obstacle="0" zIndex="0" showAll="1" priority="0" placement="0">
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
    <field configurationFlags="NoFlag" name="name">
      <editWidget type="TextEdit">
        <config>
          <Option type="Map">
            <Option value="false" type="bool" name="IsMultiline"/>
            <Option value="false" type="bool" name="UseHtml"/>
          </Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="description">
      <editWidget type="TextEdit">
        <config>
          <Option type="Map">
            <Option value="false" type="bool" name="IsMultiline"/>
            <Option value="false" type="bool" name="UseHtml"/>
          </Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="gap">
      <editWidget type="Range">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="setting_name">
      <editWidget type="TextEdit">
        <config>
          <Option type="Map">
            <Option value="false" type="bool" name="IsMultiline"/>
            <Option value="false" type="bool" name="UseHtml"/>
          </Option>
        </config>
      </editWidget>
    </field>
  </fieldConfiguration>
  <aliases>
    <alias index="0" name="" field="fid"/>
    <alias index="1" name="" field="name"/>
    <alias index="2" name="desc" field="description"/>
    <alias index="3" name="" field="gap"/>
    <alias index="4" name="" field="setting_name"/>
  </aliases>
  <splitPolicies>
    <policy policy="Duplicate" field="fid"/>
    <policy policy="DefaultValue" field="name"/>
    <policy policy="DefaultValue" field="description"/>
    <policy policy="Duplicate" field="gap"/>
    <policy policy="DefaultValue" field="setting_name"/>
  </splitPolicies>
  <defaults>
    <default expression="" applyOnUpdate="0" field="fid"/>
    <default expression="" applyOnUpdate="0" field="name"/>
    <default expression="" applyOnUpdate="0" field="description"/>
    <default expression="" applyOnUpdate="0" field="gap"/>
    <default expression="" applyOnUpdate="0" field="setting_name"/>
  </defaults>
  <constraints>
    <constraint notnull_strength="1" exp_strength="0" constraints="3" field="fid" unique_strength="1"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="2" field="name" unique_strength="1"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="description" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="gap" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="2" field="setting_name" unique_strength="1"/>
  </constraints>
  <constraintExpressions>
    <constraint desc="" field="fid" exp=""/>
    <constraint desc="" field="name" exp=""/>
    <constraint desc="" field="description" exp=""/>
    <constraint desc="" field="gap" exp=""/>
    <constraint desc="" field="setting_name" exp=""/>
  </constraintExpressions>
  <expressionfields/>
  <attributeactions>
    <defaultAction value="{00000000-0000-0000-0000-000000000000}" key="Canvas"/>
  </attributeactions>
  <attributetableconfig sortExpression="" actionWidgetStyle="dropDown" sortOrder="0">
    <columns>
      <column width="-1" type="field" name="fid" hidden="0"/>
      <column width="-1" type="field" name="name" hidden="0"/>
      <column width="-1" type="field" name="description" hidden="0"/>
      <column width="-1" type="field" name="gap" hidden="0"/>
      <column width="-1" type="field" name="setting_name" hidden="0"/>
      <column width="-1" type="actions" hidden="1"/>
    </columns>
  </attributetableconfig>
  <conditionalstyles>
    <rowstyles/>
    <fieldstyles/>
  </conditionalstyles>
  <storedexpressions/>
  <editform tolerant="1">/Users/david/Dropbox/2017ARC/qgis</editform>
  <editforminit/>
  <editforminitcodesource>0</editforminitcodesource>
  <editforminitfilepath>/Users/david/Dropbox/2017ARC/qgis</editforminitfilepath>
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
    <field editable="1" name="Gap"/>
    <field editable="0" name="auxiliary_storage_labeling_positionx"/>
    <field editable="0" name="auxiliary_storage_labeling_positiony"/>
    <field editable="1" name="cmt"/>
    <field editable="1" name="description"/>
    <field editable="1" name="fid"/>
    <field editable="1" name="gap"/>
    <field editable="1" name="name"/>
    <field editable="1" name="setting_name"/>
  </editable>
  <labelOnTop>
    <field name="Gap" labelOnTop="0"/>
    <field name="auxiliary_storage_labeling_positionx" labelOnTop="0"/>
    <field name="auxiliary_storage_labeling_positiony" labelOnTop="0"/>
    <field name="cmt" labelOnTop="0"/>
    <field name="description" labelOnTop="0"/>
    <field name="fid" labelOnTop="0"/>
    <field name="gap" labelOnTop="0"/>
    <field name="name" labelOnTop="0"/>
    <field name="setting_name" labelOnTop="0"/>
  </labelOnTop>
  <reuseLastValue>
    <field reuseLastValue="0" name="Gap"/>
    <field reuseLastValue="0" name="auxiliary_storage_labeling_positionx"/>
    <field reuseLastValue="0" name="auxiliary_storage_labeling_positiony"/>
    <field reuseLastValue="0" name="cmt"/>
    <field reuseLastValue="0" name="description"/>
    <field reuseLastValue="0" name="fid"/>
    <field reuseLastValue="0" name="gap"/>
    <field reuseLastValue="0" name="name"/>
    <field reuseLastValue="0" name="setting_name"/>
  </reuseLastValue>
  <dataDefinedFieldProperties/>
  <widgets/>
  <previewExpression>"setting_name"</previewExpression>
  <mapTip enabled="1"></mapTip>
  <layerGeometryType>0</layerGeometryType>
</qgis>
