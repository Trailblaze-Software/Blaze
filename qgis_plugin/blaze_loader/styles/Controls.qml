<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="1" maxScale="0" minScale="100000000" readOnly="0" simplifyAlgorithm="0" simplifyDrawingHints="0" simplifyDrawingTol="1" simplifyLocal="1" simplifyMaxScale="1" styleCategories="LayerConfiguration|Symbology|Symbology3D|Labeling|Fields|Forms|Actions|MapTips|Diagrams|AttributeTable|Rendering" symbologyReferenceScale="-1" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{b59afb7a-8131-45d9-baf8-07543ca5f0d1}">
      <rule filter="setting_name is not NULL" key="{a6394195-f18b-4984-bce1-671b685863fc}" label="Setting" symbol="0">
        <rule description="new control, remove tape etc." filter="to_int(setting_name) > 0" key="{74e3c27e-d631-40b3-bdaf-0a3c6b662f4b}" label="Setting" symbol="1"></rule>
        <rule filter="setting_name like 'HH'" key="{77806d88-25a7-4f9e-8fb4-60de858a1905}" label="Hash House" symbol="2"></rule>
        <rule filter="setting_name like 'W%' and to_int(right(setting_name,length(setting_name) -1)) > 0" key="{f9027c88-c4de-4973-9e91-3f75c5e091e0}" label="Water" symbol="3"></rule>
        <rule filter="ELSE" key="{530aaba4-10bd-4f26-838c-40812ef52100}" label="Unknown" symbol="4"></rule>
      </rule>
      <rule filter="name is not Null" key="{268d3aea-ab42-4b83-8ec0-49ba75713faf}" label="Hanging/Final" symbol="5">
        <rule description="Gap NULL full circle, Gap = 0 then 90 degree gap  in cirlcl to top " filter=" to_int(name) > 9 and to_int (name ) &lt; 300 " key="{805adba4-8cdc-46f0-b6d4-656b01b4933f}" label="Control" symbol="6"></rule>
        <rule filter="name like 'HH'" key="{65e9ff24-4bcb-4e93-8295-be4874e35150}" label="HH" symbol="7"></rule>
        <rule filter="name like 'W%' and to_int(right(name,length(name) -1)) > 0" key="{11bff41f-e5cb-4c19-a85f-e85772abe0fb}" label="Water" symbol="8"></rule>
        <rule filter="ELSE" key="{d6f11cf6-8ead-4279-ad1b-670dc5e992ec}" label="Unknown" symbol="9"></rule>
      </rule>
      <rule filter="ELSE" key="{a0677e62-bfac-4247-875b-39447e8b5b24}" symbol="10"></rule>
    </rules>
    <symbols>
      <symbol alpha="0" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleMarker" enabled="1" id="{ec6681f2-c730-4a4e-871a-cd1d3624f61c}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="cap_style" type="QString" value="square"></Option>
            <Option name="color" type="QString" value="133,182,111,255"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleMarker" enabled="1" id="{33d06c15-6a6d-4c62-8e03-d12c1db800de}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="-180"></Option>
            <Option name="cap_style" type="QString" value="flat"></Option>
            <Option name="color" type="QString" value="139,0,139,6"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="name" type="QString" value="half_arc"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="139,0,139,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.4"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="8"></Option>
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
                  <Option name="expression" type="QString" value="225 + Gap"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
        <layer class="SimpleMarker" enabled="1" id="{bb93c3ae-5dfb-48e5-8845-47379772d7b5}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="cap_style" type="QString" value="square"></Option>
            <Option name="color" type="QString" value="255,0,0,0"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="name" type="QString" value="half_arc"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="139,0,139,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.4"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="8"></Option>
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
                  <Option name="expression" type="QString" value="135 + Gap"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol alpha="0.2" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="10" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleMarker" enabled="1" id="{b51dc317-7b8c-41c3-adea-b0564290fcea}" locked="0" pass="0">
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
            <Option name="size" type="QString" value="8"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="2" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleMarker" enabled="1" id="{ab821e6e-9793-4b59-8b94-e648bbe68a56}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="cap_style" type="QString" value="square"></Option>
            <Option name="color" type="QString" value="0,0,255,0"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="name" type="QString" value="triangle"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="139,0,139,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.4"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="9"></Option>
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
        <layer class="SimpleMarker" enabled="1" id="{4808d9f9-9ebb-486e-9cf2-222212241f90}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="cap_style" type="QString" value="square"></Option>
            <Option name="color" type="QString" value="255,255,255,0"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="name" type="QString" value="circle"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="0,0,253,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.4"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="8"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="4" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleMarker" enabled="1" id="{f4a4bc17-ef18-4164-b1ee-b0a1b7cf4f23}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="cap_style" type="QString" value="square"></Option>
            <Option name="color" type="QString" value="255,0,0,52"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="name" type="QString" value="circle"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="255,0,0,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.4"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="8"></Option>
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
      <symbol alpha="0" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="5" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleMarker" enabled="1" id="{ae3cedad-5f8a-4fdd-b998-5db56939c9b5}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="cap_style" type="QString" value="square"></Option>
            <Option name="color" type="QString" value="232,113,141,255"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="6" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleMarker" enabled="1" id="{e91ffb23-1d54-4608-a610-9b1e7d208e72}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="-180"></Option>
            <Option name="cap_style" type="QString" value="flat"></Option>
            <Option name="color" type="QString" value="139,0,139,6"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="name" type="QString" value="half_arc"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="139,0,139,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.4"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="8"></Option>
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
                  <Option name="expression" type="QString" value="225 + Gap"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
        <layer class="SimpleMarker" enabled="1" id="{954313fe-770a-44ca-a84f-3c3f4e42f7d5}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="cap_style" type="QString" value="square"></Option>
            <Option name="color" type="QString" value="255,0,0,0"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="name" type="QString" value="half_arc"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="139,0,139,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.4"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="8"></Option>
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
                  <Option name="expression" type="QString" value="135 + Gap"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="7" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleMarker" enabled="1" id="{94590e4c-94d9-48c5-a74c-fec63ef7c76f}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="cap_style" type="QString" value="square"></Option>
            <Option name="color" type="QString" value="0,0,255,0"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="name" type="QString" value="triangle"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="139,0,139,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.4"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="9"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="8" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleMarker" enabled="1" id="{7ed62310-663e-4590-80ad-e3428926a8ba}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="cap_style" type="QString" value="square"></Option>
            <Option name="color" type="QString" value="255,255,255,0"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="name" type="QString" value="circle"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="0,0,253,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.4"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="8"></Option>
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
      <symbol alpha="0.2" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="9" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleMarker" enabled="1" id="{9f48c1c3-6d98-498e-b483-26d4280bf404}" locked="0" pass="0">
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
            <Option name="outline_color" type="QString" value="128,17,25,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.4"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="8"></Option>
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
        <layer class="SimpleMarker" enabled="1" id="{c2f8c36c-2388-4439-99ff-836490fa7bf9}" locked="0" pass="0">
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
  <labeling type="rule-based">
    <rules key="{882f25e3-27a1-4ef1-91fa-551dae27eb7b}">
      <rule description="Setting" filter="setting_name is not NULL" key="{e9faaf3b-2f70-4b6e-b91c-a5bade92c1f9}">
        <rule description="controls" filter="to_int(setting_name) > 200" key="{bddf1809-44a2-4248-9657-b8edfd936f78}">
          <settings calloutType="simple">
            <text-style allowHtml="0" blendMode="0" capitalization="0" fieldName="setting_name" fontFamily="MS Shell Dlg 2" fontItalic="0" fontKerning="1" fontLetterSpacing="0" fontSize="15" fontSizeMapUnitScale="3x:0,0,0,0,0,0" fontSizeUnit="Point" fontStrikeout="0" fontUnderline="0" fontWeight="50" fontWordSpacing="0" forcedBold="0" forcedItalic="0" isExpression="0" legendString="Aa" multilineHeight="1" multilineHeightUnit="Percentage" namedStyle="Regular" previewBkgrdColor="255,255,255,255" textColor="139,0,139,255" textOpacity="1" textOrientation="horizontal" useSubstitutions="0">
              <families></families>
              <text-buffer bufferBlendMode="0" bufferColor="255,255,255,255" bufferDraw="0" bufferJoinStyle="128" bufferNoFill="1" bufferOpacity="1" bufferSize="1" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM"></text-buffer>
              <text-mask maskEnabled="0" maskJoinStyle="128" maskOpacity="1" maskSize="1.5" maskSizeMapUnitScale="3x:0,0,0,0,0,0" maskSizeUnits="MM" maskType="0" maskedSymbolLayers=""></text-mask>
              <background shapeBlendMode="0" shapeBorderColor="128,128,128,255" shapeBorderWidth="0" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="MM" shapeDraw="0" shapeFillColor="255,255,255,255" shapeJoinStyle="64" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetUnit="MM" shapeOffsetX="0" shapeOffsetY="0" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeRadiiUnit="MM" shapeRadiiX="0" shapeRadiiY="0" shapeRotation="0" shapeRotationType="0" shapeSVGFile="" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeSizeType="0" shapeSizeUnit="MM" shapeSizeX="0" shapeSizeY="0" shapeType="0">
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
                      <Option name="color" type="QString" value="152,125,183,255"></Option>
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
              </background>
              <shadow shadowBlendMode="6" shadowColor="0,0,0,255" shadowDraw="0" shadowOffsetAngle="135" shadowOffsetDist="1" shadowOffsetGlobal="1" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetUnit="MM" shadowOpacity="0.69999999999999996" shadowRadius="1.5" shadowRadiusAlphaOnly="0" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusUnit="MM" shadowScale="100" shadowUnder="0"></shadow>
              <dd_properties>
                <Option type="Map">
                  <Option name="name" type="QString" value=""></Option>
                  <Option name="properties"></Option>
                  <Option name="type" type="QString" value="collection"></Option>
                </Option>
              </dd_properties>
              <substitutions></substitutions>
            </text-style>
            <text-format addDirectionSymbol="0" autoWrapLength="0" decimals="3" formatNumbers="0" leftDirectionSymbol="&lt;" multilineAlign="3" placeDirectionSymbol="0" plussign="0" reverseDirectionSymbol="0" rightDirectionSymbol=">" useMaxLineLengthForAutoWrap="1" wrapChar=""></text-format>
            <placement allowDegraded="0" centroidInside="0" centroidWhole="0" dist="5" distMapUnitScale="3x:0,0,0,0,0,0" distUnits="MM" fitInPolygonOnly="0" geometryGenerator="" geometryGeneratorEnabled="0" geometryGeneratorType="PointGeometry" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" layerType="PointGeometry" lineAnchorClipping="0" lineAnchorPercent="0.5" lineAnchorTextPoint="CenterOfText" lineAnchorType="0" maxCurvedCharAngleIn="25" maxCurvedCharAngleOut="-25" offsetType="0" offsetUnits="MM" overlapHandling="PreventOverlap" overrunDistance="0" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" placement="1" placementFlags="10" polygonPlacementFlags="2" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" preserveRotation="1" priority="5" quadOffset="4" repeatDistance="0" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" repeatDistanceUnits="MM" rotationAngle="0" rotationUnit="AngleDegrees" xOffset="-7" yOffset="7"></placement>
            <rendering drawLabels="1" fontLimitPixelSize="0" fontMaxPixelSize="10000" fontMinPixelSize="3" labelPerPart="0" limitNumLabels="0" maxNumLabels="2000" mergeLines="0" minFeatureSize="0" obstacle="1" obstacleFactor="1" obstacleType="1" scaleMax="0" scaleMin="0" scaleVisibility="0" unplacedVisibility="0" upsidedownLabels="0" zIndex="0"></rendering>
            <dd_properties>
              <Option type="Map">
                <Option name="name" type="QString" value=""></Option>
                <Option name="properties" type="Map">
                  <Option name="PositionX" type="Map">
                    <Option name="active" type="bool" value="true"></Option>
                    <Option name="field" type="QString" value="auxiliary_storage_labeling_positionx"></Option>
                    <Option name="type" type="int" value="2"></Option>
                  </Option>
                  <Option name="PositionY" type="Map">
                    <Option name="active" type="bool" value="true"></Option>
                    <Option name="field" type="QString" value="auxiliary_storage_labeling_positiony"></Option>
                    <Option name="type" type="int" value="2"></Option>
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
                <Option name="lineSymbol" type="QString" value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{0a1ed788-77aa-41b7-8734-760227c92d93}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>"></Option>
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
        </rule>
        <rule description="HH" filter="setting_name like 'HH'" key="{c6e51ee0-1012-431a-901b-504bc01ef18e}">
          <settings calloutType="simple">
            <text-style allowHtml="0" blendMode="0" capitalization="0" fieldName="setting_name" fontFamily="MS Shell Dlg 2" fontItalic="0" fontKerning="1" fontLetterSpacing="0" fontSize="15" fontSizeMapUnitScale="3x:0,0,0,0,0,0" fontSizeUnit="Point" fontStrikeout="0" fontUnderline="0" fontWeight="50" fontWordSpacing="0" forcedBold="0" forcedItalic="0" isExpression="0" legendString="Aa" multilineHeight="1" multilineHeightUnit="Percentage" namedStyle="Regular" previewBkgrdColor="255,255,255,255" textColor="139,0,139,255" textOpacity="1" textOrientation="horizontal" useSubstitutions="0">
              <families></families>
              <text-buffer bufferBlendMode="0" bufferColor="255,255,255,255" bufferDraw="0" bufferJoinStyle="128" bufferNoFill="1" bufferOpacity="1" bufferSize="1" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM"></text-buffer>
              <text-mask maskEnabled="0" maskJoinStyle="128" maskOpacity="1" maskSize="1.5" maskSizeMapUnitScale="3x:0,0,0,0,0,0" maskSizeUnits="MM" maskType="0" maskedSymbolLayers=""></text-mask>
              <background shapeBlendMode="0" shapeBorderColor="128,128,128,255" shapeBorderWidth="0" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="MM" shapeDraw="0" shapeFillColor="255,255,255,255" shapeJoinStyle="64" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetUnit="MM" shapeOffsetX="0" shapeOffsetY="0" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeRadiiUnit="MM" shapeRadiiX="0" shapeRadiiY="0" shapeRotation="0" shapeRotationType="0" shapeSVGFile="" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeSizeType="0" shapeSizeUnit="MM" shapeSizeX="0" shapeSizeY="0" shapeType="0">
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
                      <Option name="color" type="QString" value="190,207,80,255"></Option>
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
              </background>
              <shadow shadowBlendMode="6" shadowColor="0,0,0,255" shadowDraw="0" shadowOffsetAngle="135" shadowOffsetDist="1" shadowOffsetGlobal="1" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetUnit="MM" shadowOpacity="0.69999999999999996" shadowRadius="1.5" shadowRadiusAlphaOnly="0" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusUnit="MM" shadowScale="100" shadowUnder="0"></shadow>
              <dd_properties>
                <Option type="Map">
                  <Option name="name" type="QString" value=""></Option>
                  <Option name="properties"></Option>
                  <Option name="type" type="QString" value="collection"></Option>
                </Option>
              </dd_properties>
              <substitutions></substitutions>
            </text-style>
            <text-format addDirectionSymbol="0" autoWrapLength="0" decimals="3" formatNumbers="0" leftDirectionSymbol="&lt;" multilineAlign="3" placeDirectionSymbol="0" plussign="0" reverseDirectionSymbol="0" rightDirectionSymbol=">" useMaxLineLengthForAutoWrap="1" wrapChar=""></text-format>
            <placement allowDegraded="0" centroidInside="0" centroidWhole="0" dist="5" distMapUnitScale="3x:0,0,0,0,0,0" distUnits="MM" fitInPolygonOnly="0" geometryGenerator="" geometryGeneratorEnabled="0" geometryGeneratorType="PointGeometry" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" layerType="PointGeometry" lineAnchorClipping="0" lineAnchorPercent="0.5" lineAnchorTextPoint="CenterOfText" lineAnchorType="0" maxCurvedCharAngleIn="25" maxCurvedCharAngleOut="-25" offsetType="0" offsetUnits="MM" overlapHandling="PreventOverlap" overrunDistance="0" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" placement="1" placementFlags="10" polygonPlacementFlags="2" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" preserveRotation="1" priority="5" quadOffset="4" repeatDistance="0" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" repeatDistanceUnits="MM" rotationAngle="0" rotationUnit="AngleDegrees" xOffset="-7" yOffset="7"></placement>
            <rendering drawLabels="1" fontLimitPixelSize="0" fontMaxPixelSize="10000" fontMinPixelSize="3" labelPerPart="0" limitNumLabels="0" maxNumLabels="2000" mergeLines="0" minFeatureSize="0" obstacle="1" obstacleFactor="1" obstacleType="1" scaleMax="0" scaleMin="0" scaleVisibility="0" unplacedVisibility="0" upsidedownLabels="0" zIndex="0"></rendering>
            <dd_properties>
              <Option type="Map">
                <Option name="name" type="QString" value=""></Option>
                <Option name="properties" type="Map">
                  <Option name="PositionX" type="Map">
                    <Option name="active" type="bool" value="true"></Option>
                    <Option name="field" type="QString" value="auxiliary_storage_labeling_positionx"></Option>
                    <Option name="type" type="int" value="2"></Option>
                  </Option>
                  <Option name="PositionY" type="Map">
                    <Option name="active" type="bool" value="true"></Option>
                    <Option name="field" type="QString" value="auxiliary_storage_labeling_positiony"></Option>
                    <Option name="type" type="int" value="2"></Option>
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
                <Option name="lineSymbol" type="QString" value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{4f99d1ec-19f1-43fa-9f9b-56216db3977c}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>"></Option>
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
        </rule>
        <rule description="Water" filter="setting_name liKe 'W%' and setting_name > 'W00' and setting_name &lt;  'W99'" key="{b0ad5113-8037-4cdf-9158-68926b45e9bc}">
          <settings calloutType="simple">
            <text-style allowHtml="0" blendMode="0" capitalization="0" fieldName="setting_name" fontFamily="MS Shell Dlg 2" fontItalic="0" fontKerning="1" fontLetterSpacing="0" fontSize="15" fontSizeMapUnitScale="3x:0,0,0,0,0,0" fontSizeUnit="Point" fontStrikeout="0" fontUnderline="0" fontWeight="50" fontWordSpacing="0" forcedBold="0" forcedItalic="0" isExpression="0" legendString="Aa" multilineHeight="1" multilineHeightUnit="Percentage" namedStyle="Regular" previewBkgrdColor="255,255,255,255" textColor="0,0,255,255" textOpacity="1" textOrientation="horizontal" useSubstitutions="0">
              <families></families>
              <text-buffer bufferBlendMode="0" bufferColor="255,255,255,255" bufferDraw="0" bufferJoinStyle="128" bufferNoFill="1" bufferOpacity="1" bufferSize="1" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM"></text-buffer>
              <text-mask maskEnabled="0" maskJoinStyle="128" maskOpacity="1" maskSize="1.5" maskSizeMapUnitScale="3x:0,0,0,0,0,0" maskSizeUnits="MM" maskType="0" maskedSymbolLayers=""></text-mask>
              <background shapeBlendMode="0" shapeBorderColor="128,128,128,255" shapeBorderWidth="0" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="MM" shapeDraw="0" shapeFillColor="255,255,255,255" shapeJoinStyle="64" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetUnit="MM" shapeOffsetX="0" shapeOffsetY="0" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeRadiiUnit="MM" shapeRadiiX="0" shapeRadiiY="0" shapeRotation="0" shapeRotationType="0" shapeSVGFile="" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeSizeType="0" shapeSizeUnit="MM" shapeSizeX="0" shapeSizeY="0" shapeType="0">
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
                      <Option name="color" type="QString" value="231,113,72,255"></Option>
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
              </background>
              <shadow shadowBlendMode="6" shadowColor="0,0,0,255" shadowDraw="0" shadowOffsetAngle="135" shadowOffsetDist="1" shadowOffsetGlobal="1" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetUnit="MM" shadowOpacity="0.69999999999999996" shadowRadius="1.5" shadowRadiusAlphaOnly="0" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusUnit="MM" shadowScale="100" shadowUnder="0"></shadow>
              <dd_properties>
                <Option type="Map">
                  <Option name="name" type="QString" value=""></Option>
                  <Option name="properties"></Option>
                  <Option name="type" type="QString" value="collection"></Option>
                </Option>
              </dd_properties>
              <substitutions></substitutions>
            </text-style>
            <text-format addDirectionSymbol="0" autoWrapLength="0" decimals="3" formatNumbers="0" leftDirectionSymbol="&lt;" multilineAlign="3" placeDirectionSymbol="0" plussign="0" reverseDirectionSymbol="0" rightDirectionSymbol=">" useMaxLineLengthForAutoWrap="1" wrapChar=""></text-format>
            <placement allowDegraded="0" centroidInside="0" centroidWhole="0" dist="5" distMapUnitScale="3x:0,0,0,0,0,0" distUnits="MM" fitInPolygonOnly="0" geometryGenerator="" geometryGeneratorEnabled="0" geometryGeneratorType="PointGeometry" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" layerType="PointGeometry" lineAnchorClipping="0" lineAnchorPercent="0.5" lineAnchorTextPoint="CenterOfText" lineAnchorType="0" maxCurvedCharAngleIn="25" maxCurvedCharAngleOut="-25" offsetType="0" offsetUnits="MM" overlapHandling="PreventOverlap" overrunDistance="0" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" placement="1" placementFlags="10" polygonPlacementFlags="2" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" preserveRotation="1" priority="5" quadOffset="4" repeatDistance="0" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" repeatDistanceUnits="MM" rotationAngle="0" rotationUnit="AngleDegrees" xOffset="-7" yOffset="7"></placement>
            <rendering drawLabels="1" fontLimitPixelSize="0" fontMaxPixelSize="10000" fontMinPixelSize="3" labelPerPart="0" limitNumLabels="0" maxNumLabels="2000" mergeLines="0" minFeatureSize="0" obstacle="1" obstacleFactor="1" obstacleType="1" scaleMax="0" scaleMin="0" scaleVisibility="0" unplacedVisibility="0" upsidedownLabels="0" zIndex="0"></rendering>
            <dd_properties>
              <Option type="Map">
                <Option name="name" type="QString" value=""></Option>
                <Option name="properties" type="Map">
                  <Option name="PositionX" type="Map">
                    <Option name="active" type="bool" value="true"></Option>
                    <Option name="field" type="QString" value="auxiliary_storage_labeling_positionx"></Option>
                    <Option name="type" type="int" value="2"></Option>
                  </Option>
                  <Option name="PositionY" type="Map">
                    <Option name="active" type="bool" value="true"></Option>
                    <Option name="field" type="QString" value="auxiliary_storage_labeling_positiony"></Option>
                    <Option name="type" type="int" value="2"></Option>
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
                <Option name="lineSymbol" type="QString" value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{db4385d6-5fe3-451c-83a3-09b5b98c1e22}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>"></Option>
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
        </rule>
        <rule description="Unkown" filter="ELSE" key="{b2ec0bba-20d0-498d-806d-0f0e0fefa60d}">
          <settings calloutType="simple">
            <text-style allowHtml="0" blendMode="0" capitalization="0" fieldName="setting_name" fontFamily="Arial" fontItalic="0" fontKerning="1" fontLetterSpacing="0" fontSize="14" fontSizeMapUnitScale="3x:0,0,0,0,0,0" fontSizeUnit="Point" fontStrikeout="0" fontUnderline="0" fontWeight="50" fontWordSpacing="0" forcedBold="0" forcedItalic="0" isExpression="0" legendString="Aa" multilineHeight="1" multilineHeightUnit="Percentage" namedStyle="Regular" previewBkgrdColor="255,255,255,255" textColor="255,0,0,255" textOpacity="1" textOrientation="horizontal" useSubstitutions="0">
              <families></families>
              <text-buffer bufferBlendMode="0" bufferColor="250,250,250,255" bufferDraw="0" bufferJoinStyle="128" bufferNoFill="1" bufferOpacity="1" bufferSize="1" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM"></text-buffer>
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
                      <Option name="color" type="QString" value="231,113,72,255"></Option>
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
              <shadow shadowBlendMode="6" shadowColor="0,0,0,255" shadowDraw="0" shadowOffsetAngle="135" shadowOffsetDist="1" shadowOffsetGlobal="1" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetUnit="MM" shadowOpacity="0.69999999999999996" shadowRadius="1.5" shadowRadiusAlphaOnly="0" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusUnit="MM" shadowScale="100" shadowUnder="0"></shadow>
              <dd_properties>
                <Option type="Map">
                  <Option name="name" type="QString" value=""></Option>
                  <Option name="properties"></Option>
                  <Option name="type" type="QString" value="collection"></Option>
                </Option>
              </dd_properties>
              <substitutions></substitutions>
            </text-style>
            <text-format addDirectionSymbol="0" autoWrapLength="0" decimals="3" formatNumbers="0" leftDirectionSymbol="&lt;" multilineAlign="3" placeDirectionSymbol="0" plussign="0" reverseDirectionSymbol="0" rightDirectionSymbol=">" useMaxLineLengthForAutoWrap="1" wrapChar=""></text-format>
            <placement allowDegraded="0" centroidInside="0" centroidWhole="0" dist="0" distMapUnitScale="3x:0,0,0,0,0,0" distUnits="MM" fitInPolygonOnly="0" geometryGenerator="" geometryGeneratorEnabled="0" geometryGeneratorType="PointGeometry" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" layerType="PointGeometry" lineAnchorClipping="0" lineAnchorPercent="0.5" lineAnchorTextPoint="FollowPlacement" lineAnchorType="0" maxCurvedCharAngleIn="25" maxCurvedCharAngleOut="-25" offsetType="1" offsetUnits="MM" overlapHandling="PreventOverlap" overrunDistance="0" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" placement="1" placementFlags="10" polygonPlacementFlags="2" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" preserveRotation="1" priority="5" quadOffset="4" repeatDistance="0" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" repeatDistanceUnits="MM" rotationAngle="0" rotationUnit="AngleDegrees" xOffset="-7" yOffset="7"></placement>
            <rendering drawLabels="1" fontLimitPixelSize="0" fontMaxPixelSize="10000" fontMinPixelSize="3" labelPerPart="0" limitNumLabels="0" maxNumLabels="2000" mergeLines="0" minFeatureSize="0" obstacle="1" obstacleFactor="1" obstacleType="1" scaleMax="0" scaleMin="0" scaleVisibility="0" unplacedVisibility="0" upsidedownLabels="0" zIndex="0"></rendering>
            <dd_properties>
              <Option type="Map">
                <Option name="name" type="QString" value=""></Option>
                <Option name="properties"></Option>
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
                <Option name="lineSymbol" type="QString" value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{be704c21-57e1-450c-9bff-61d7a91a3f02}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>"></Option>
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
        </rule>
      </rule>
      <rule description="Hanging" filter="name is not Null" key="{5b868ba0-f058-498b-a73b-d3b4e136ef0a}">
        <rule description="controls" filter="name> '0' and name &lt; '999'" key="{a3b0f6bf-8cab-4614-8be5-8748596383fe}">
          <settings calloutType="simple">
            <text-style allowHtml="0" blendMode="0" capitalization="0" fieldName="name" fontFamily="MS Shell Dlg 2" fontItalic="0" fontKerning="1" fontLetterSpacing="0" fontSize="15" fontSizeMapUnitScale="3x:0,0,0,0,0,0" fontSizeUnit="Point" fontStrikeout="0" fontUnderline="0" fontWeight="50" fontWordSpacing="0" forcedBold="0" forcedItalic="0" isExpression="0" legendString="Aa" multilineHeight="1" multilineHeightUnit="Percentage" namedStyle="Regular" previewBkgrdColor="255,255,255,255" textColor="139,0,139,255" textOpacity="1" textOrientation="horizontal" useSubstitutions="0">
              <families></families>
              <text-buffer bufferBlendMode="0" bufferColor="255,255,255,255" bufferDraw="0" bufferJoinStyle="128" bufferNoFill="1" bufferOpacity="1" bufferSize="1" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM"></text-buffer>
              <text-mask maskEnabled="0" maskJoinStyle="128" maskOpacity="1" maskSize="1.5" maskSizeMapUnitScale="3x:0,0,0,0,0,0" maskSizeUnits="MM" maskType="0" maskedSymbolLayers=""></text-mask>
              <background shapeBlendMode="0" shapeBorderColor="128,128,128,255" shapeBorderWidth="0" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="MM" shapeDraw="0" shapeFillColor="255,255,255,255" shapeJoinStyle="64" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetUnit="MM" shapeOffsetX="0" shapeOffsetY="0" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeRadiiUnit="MM" shapeRadiiX="0" shapeRadiiY="0" shapeRotation="0" shapeRotationType="0" shapeSVGFile="" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeSizeType="0" shapeSizeUnit="MM" shapeSizeX="0" shapeSizeY="0" shapeType="0">
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
                      <Option name="color" type="QString" value="152,125,183,255"></Option>
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
              </background>
              <shadow shadowBlendMode="6" shadowColor="0,0,0,255" shadowDraw="0" shadowOffsetAngle="135" shadowOffsetDist="1" shadowOffsetGlobal="1" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetUnit="MM" shadowOpacity="0.69999999999999996" shadowRadius="1.5" shadowRadiusAlphaOnly="0" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusUnit="MM" shadowScale="100" shadowUnder="0"></shadow>
              <dd_properties>
                <Option type="Map">
                  <Option name="name" type="QString" value=""></Option>
                  <Option name="properties"></Option>
                  <Option name="type" type="QString" value="collection"></Option>
                </Option>
              </dd_properties>
              <substitutions></substitutions>
            </text-style>
            <text-format addDirectionSymbol="0" autoWrapLength="0" decimals="3" formatNumbers="0" leftDirectionSymbol="&lt;" multilineAlign="3" placeDirectionSymbol="0" plussign="0" reverseDirectionSymbol="0" rightDirectionSymbol=">" useMaxLineLengthForAutoWrap="1" wrapChar=""></text-format>
            <placement allowDegraded="0" centroidInside="0" centroidWhole="0" dist="5" distMapUnitScale="3x:0,0,0,0,0,0" distUnits="MM" fitInPolygonOnly="0" geometryGenerator="" geometryGeneratorEnabled="0" geometryGeneratorType="PointGeometry" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" layerType="PointGeometry" lineAnchorClipping="0" lineAnchorPercent="0.5" lineAnchorTextPoint="CenterOfText" lineAnchorType="0" maxCurvedCharAngleIn="25" maxCurvedCharAngleOut="-25" offsetType="0" offsetUnits="MM" overlapHandling="PreventOverlap" overrunDistance="0" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" placement="1" placementFlags="10" polygonPlacementFlags="2" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" preserveRotation="1" priority="5" quadOffset="4" repeatDistance="0" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" repeatDistanceUnits="MM" rotationAngle="0" rotationUnit="AngleDegrees" xOffset="7" yOffset="-7"></placement>
            <rendering drawLabels="1" fontLimitPixelSize="0" fontMaxPixelSize="10000" fontMinPixelSize="3" labelPerPart="0" limitNumLabels="0" maxNumLabels="2000" mergeLines="0" minFeatureSize="0" obstacle="1" obstacleFactor="1" obstacleType="1" scaleMax="0" scaleMin="0" scaleVisibility="0" unplacedVisibility="0" upsidedownLabels="0" zIndex="0"></rendering>
            <dd_properties>
              <Option type="Map">
                <Option name="name" type="QString" value=""></Option>
                <Option name="properties" type="Map">
                  <Option name="PositionX" type="Map">
                    <Option name="active" type="bool" value="true"></Option>
                    <Option name="field" type="QString" value="auxiliary_storage_labeling_positionx"></Option>
                    <Option name="type" type="int" value="2"></Option>
                  </Option>
                  <Option name="PositionY" type="Map">
                    <Option name="active" type="bool" value="true"></Option>
                    <Option name="field" type="QString" value="auxiliary_storage_labeling_positiony"></Option>
                    <Option name="type" type="int" value="2"></Option>
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
                <Option name="lineSymbol" type="QString" value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{0a1ed788-77aa-41b7-8734-760227c92d93}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>"></Option>
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
        </rule>
        <rule description="HH" filter="name like 'HH'" key="{a5e7c910-a7a6-46f5-8b48-a2eeab0707a9}">
          <settings calloutType="simple">
            <text-style allowHtml="0" blendMode="0" capitalization="0" fieldName="name" fontFamily="MS Shell Dlg 2" fontItalic="0" fontKerning="1" fontLetterSpacing="0" fontSize="15" fontSizeMapUnitScale="3x:0,0,0,0,0,0" fontSizeUnit="Point" fontStrikeout="0" fontUnderline="0" fontWeight="50" fontWordSpacing="0" forcedBold="0" forcedItalic="0" isExpression="0" legendString="Aa" multilineHeight="1" multilineHeightUnit="Percentage" namedStyle="Regular" previewBkgrdColor="255,255,255,255" textColor="139,0,139,255" textOpacity="1" textOrientation="horizontal" useSubstitutions="0">
              <families></families>
              <text-buffer bufferBlendMode="0" bufferColor="255,255,255,255" bufferDraw="0" bufferJoinStyle="128" bufferNoFill="1" bufferOpacity="1" bufferSize="1" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM"></text-buffer>
              <text-mask maskEnabled="0" maskJoinStyle="128" maskOpacity="1" maskSize="1.5" maskSizeMapUnitScale="3x:0,0,0,0,0,0" maskSizeUnits="MM" maskType="0" maskedSymbolLayers=""></text-mask>
              <background shapeBlendMode="0" shapeBorderColor="128,128,128,255" shapeBorderWidth="0" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="MM" shapeDraw="0" shapeFillColor="255,255,255,255" shapeJoinStyle="64" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetUnit="MM" shapeOffsetX="0" shapeOffsetY="0" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeRadiiUnit="MM" shapeRadiiX="0" shapeRadiiY="0" shapeRotation="0" shapeRotationType="0" shapeSVGFile="" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeSizeType="0" shapeSizeUnit="MM" shapeSizeX="0" shapeSizeY="0" shapeType="0">
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
                      <Option name="color" type="QString" value="190,207,80,255"></Option>
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
              </background>
              <shadow shadowBlendMode="6" shadowColor="0,0,0,255" shadowDraw="0" shadowOffsetAngle="135" shadowOffsetDist="1" shadowOffsetGlobal="1" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetUnit="MM" shadowOpacity="0.69999999999999996" shadowRadius="1.5" shadowRadiusAlphaOnly="0" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusUnit="MM" shadowScale="100" shadowUnder="0"></shadow>
              <dd_properties>
                <Option type="Map">
                  <Option name="name" type="QString" value=""></Option>
                  <Option name="properties"></Option>
                  <Option name="type" type="QString" value="collection"></Option>
                </Option>
              </dd_properties>
              <substitutions></substitutions>
            </text-style>
            <text-format addDirectionSymbol="0" autoWrapLength="0" decimals="3" formatNumbers="0" leftDirectionSymbol="&lt;" multilineAlign="3" placeDirectionSymbol="0" plussign="0" reverseDirectionSymbol="0" rightDirectionSymbol=">" useMaxLineLengthForAutoWrap="1" wrapChar=""></text-format>
            <placement allowDegraded="0" centroidInside="0" centroidWhole="0" dist="5" distMapUnitScale="3x:0,0,0,0,0,0" distUnits="MM" fitInPolygonOnly="0" geometryGenerator="" geometryGeneratorEnabled="0" geometryGeneratorType="PointGeometry" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" layerType="PointGeometry" lineAnchorClipping="0" lineAnchorPercent="0.5" lineAnchorTextPoint="CenterOfText" lineAnchorType="0" maxCurvedCharAngleIn="25" maxCurvedCharAngleOut="-25" offsetType="0" offsetUnits="MM" overlapHandling="PreventOverlap" overrunDistance="0" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" placement="1" placementFlags="10" polygonPlacementFlags="2" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" preserveRotation="1" priority="5" quadOffset="4" repeatDistance="0" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" repeatDistanceUnits="MM" rotationAngle="0" rotationUnit="AngleDegrees" xOffset="7" yOffset="-7"></placement>
            <rendering drawLabels="1" fontLimitPixelSize="0" fontMaxPixelSize="10000" fontMinPixelSize="3" labelPerPart="0" limitNumLabels="0" maxNumLabels="2000" mergeLines="0" minFeatureSize="0" obstacle="1" obstacleFactor="1" obstacleType="1" scaleMax="0" scaleMin="0" scaleVisibility="0" unplacedVisibility="0" upsidedownLabels="0" zIndex="0"></rendering>
            <dd_properties>
              <Option type="Map">
                <Option name="name" type="QString" value=""></Option>
                <Option name="properties" type="Map">
                  <Option name="PositionX" type="Map">
                    <Option name="active" type="bool" value="true"></Option>
                    <Option name="field" type="QString" value="auxiliary_storage_labeling_positionx"></Option>
                    <Option name="type" type="int" value="2"></Option>
                  </Option>
                  <Option name="PositionY" type="Map">
                    <Option name="active" type="bool" value="true"></Option>
                    <Option name="field" type="QString" value="auxiliary_storage_labeling_positiony"></Option>
                    <Option name="type" type="int" value="2"></Option>
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
                <Option name="lineSymbol" type="QString" value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{4f99d1ec-19f1-43fa-9f9b-56216db3977c}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>"></Option>
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
        </rule>
        <rule description="Water" filter="name liKe 'W%' and name > 'W0' and name &lt;  'W9'" key="{f54b3b4c-679e-43bd-bb1d-e76ad6d09dd1}">
          <settings calloutType="simple">
            <text-style allowHtml="0" blendMode="0" capitalization="0" fieldName="name" fontFamily="MS Shell Dlg 2" fontItalic="0" fontKerning="1" fontLetterSpacing="0" fontSize="15" fontSizeMapUnitScale="3x:0,0,0,0,0,0" fontSizeUnit="Point" fontStrikeout="0" fontUnderline="0" fontWeight="50" fontWordSpacing="0" forcedBold="0" forcedItalic="0" isExpression="0" legendString="Aa" multilineHeight="1" multilineHeightUnit="Percentage" namedStyle="Regular" previewBkgrdColor="255,255,255,255" textColor="0,0,255,255" textOpacity="1" textOrientation="horizontal" useSubstitutions="0">
              <families></families>
              <text-buffer bufferBlendMode="0" bufferColor="255,255,255,255" bufferDraw="0" bufferJoinStyle="128" bufferNoFill="1" bufferOpacity="1" bufferSize="1" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM"></text-buffer>
              <text-mask maskEnabled="0" maskJoinStyle="128" maskOpacity="1" maskSize="1.5" maskSizeMapUnitScale="3x:0,0,0,0,0,0" maskSizeUnits="MM" maskType="0" maskedSymbolLayers=""></text-mask>
              <background shapeBlendMode="0" shapeBorderColor="128,128,128,255" shapeBorderWidth="0" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="MM" shapeDraw="0" shapeFillColor="255,255,255,255" shapeJoinStyle="64" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetUnit="MM" shapeOffsetX="0" shapeOffsetY="0" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeRadiiUnit="MM" shapeRadiiX="0" shapeRadiiY="0" shapeRotation="0" shapeRotationType="0" shapeSVGFile="" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeSizeType="0" shapeSizeUnit="MM" shapeSizeX="0" shapeSizeY="0" shapeType="0">
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
                      <Option name="color" type="QString" value="231,113,72,255"></Option>
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
              </background>
              <shadow shadowBlendMode="6" shadowColor="0,0,0,255" shadowDraw="0" shadowOffsetAngle="135" shadowOffsetDist="1" shadowOffsetGlobal="1" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetUnit="MM" shadowOpacity="0.69999999999999996" shadowRadius="1.5" shadowRadiusAlphaOnly="0" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusUnit="MM" shadowScale="100" shadowUnder="0"></shadow>
              <dd_properties>
                <Option type="Map">
                  <Option name="name" type="QString" value=""></Option>
                  <Option name="properties"></Option>
                  <Option name="type" type="QString" value="collection"></Option>
                </Option>
              </dd_properties>
              <substitutions></substitutions>
            </text-style>
            <text-format addDirectionSymbol="0" autoWrapLength="0" decimals="3" formatNumbers="0" leftDirectionSymbol="&lt;" multilineAlign="3" placeDirectionSymbol="0" plussign="0" reverseDirectionSymbol="0" rightDirectionSymbol=">" useMaxLineLengthForAutoWrap="1" wrapChar=""></text-format>
            <placement allowDegraded="0" centroidInside="0" centroidWhole="0" dist="5" distMapUnitScale="3x:0,0,0,0,0,0" distUnits="MM" fitInPolygonOnly="0" geometryGenerator="" geometryGeneratorEnabled="0" geometryGeneratorType="PointGeometry" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" layerType="PointGeometry" lineAnchorClipping="0" lineAnchorPercent="0.5" lineAnchorTextPoint="CenterOfText" lineAnchorType="0" maxCurvedCharAngleIn="25" maxCurvedCharAngleOut="-25" offsetType="0" offsetUnits="MM" overlapHandling="PreventOverlap" overrunDistance="0" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" placement="1" placementFlags="10" polygonPlacementFlags="2" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" preserveRotation="1" priority="5" quadOffset="4" repeatDistance="0" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" repeatDistanceUnits="MM" rotationAngle="0" rotationUnit="AngleDegrees" xOffset="7" yOffset="-7"></placement>
            <rendering drawLabels="1" fontLimitPixelSize="0" fontMaxPixelSize="10000" fontMinPixelSize="3" labelPerPart="0" limitNumLabels="0" maxNumLabels="2000" mergeLines="0" minFeatureSize="0" obstacle="1" obstacleFactor="1" obstacleType="1" scaleMax="0" scaleMin="0" scaleVisibility="0" unplacedVisibility="0" upsidedownLabels="0" zIndex="0"></rendering>
            <dd_properties>
              <Option type="Map">
                <Option name="name" type="QString" value=""></Option>
                <Option name="properties" type="Map">
                  <Option name="PositionX" type="Map">
                    <Option name="active" type="bool" value="true"></Option>
                    <Option name="field" type="QString" value="auxiliary_storage_labeling_positionx"></Option>
                    <Option name="type" type="int" value="2"></Option>
                  </Option>
                  <Option name="PositionY" type="Map">
                    <Option name="active" type="bool" value="true"></Option>
                    <Option name="field" type="QString" value="auxiliary_storage_labeling_positiony"></Option>
                    <Option name="type" type="int" value="2"></Option>
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
                <Option name="lineSymbol" type="QString" value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{db4385d6-5fe3-451c-83a3-09b5b98c1e22}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>"></Option>
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
        </rule>
        <rule description="Unkown" filter="ELSE" key="{7455f4dd-ac50-44ce-b4bc-e1000d729c48}">
          <settings calloutType="simple">
            <text-style allowHtml="0" blendMode="0" capitalization="0" fieldName="description" fontFamily="Arial" fontItalic="0" fontKerning="1" fontLetterSpacing="0" fontSize="10" fontSizeMapUnitScale="3x:0,0,0,0,0,0" fontSizeUnit="Point" fontStrikeout="0" fontUnderline="0" fontWeight="50" fontWordSpacing="0" forcedBold="0" forcedItalic="0" isExpression="0" legendString="Aa" multilineHeight="1" multilineHeightUnit="Percentage" namedStyle="Regular" previewBkgrdColor="255,255,255,255" textColor="255,0,0,255" textOpacity="1" textOrientation="horizontal" useSubstitutions="0">
              <families></families>
              <text-buffer bufferBlendMode="0" bufferColor="250,250,250,255" bufferDraw="0" bufferJoinStyle="128" bufferNoFill="1" bufferOpacity="1" bufferSize="1" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM"></text-buffer>
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
                      <Option name="color" type="QString" value="229,182,54,255"></Option>
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
              <shadow shadowBlendMode="6" shadowColor="0,0,0,255" shadowDraw="0" shadowOffsetAngle="135" shadowOffsetDist="1" shadowOffsetGlobal="1" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetUnit="MM" shadowOpacity="0.69999999999999996" shadowRadius="1.5" shadowRadiusAlphaOnly="0" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusUnit="MM" shadowScale="100" shadowUnder="0"></shadow>
              <dd_properties>
                <Option type="Map">
                  <Option name="name" type="QString" value=""></Option>
                  <Option name="properties"></Option>
                  <Option name="type" type="QString" value="collection"></Option>
                </Option>
              </dd_properties>
              <substitutions></substitutions>
            </text-style>
            <text-format addDirectionSymbol="0" autoWrapLength="0" decimals="3" formatNumbers="0" leftDirectionSymbol="&lt;" multilineAlign="3" placeDirectionSymbol="0" plussign="0" reverseDirectionSymbol="0" rightDirectionSymbol=">" useMaxLineLengthForAutoWrap="1" wrapChar=""></text-format>
            <placement allowDegraded="0" centroidInside="0" centroidWhole="0" dist="0" distMapUnitScale="3x:0,0,0,0,0,0" distUnits="MM" fitInPolygonOnly="0" geometryGenerator="" geometryGeneratorEnabled="0" geometryGeneratorType="PointGeometry" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" layerType="PointGeometry" lineAnchorClipping="0" lineAnchorPercent="0.5" lineAnchorTextPoint="FollowPlacement" lineAnchorType="0" maxCurvedCharAngleIn="25" maxCurvedCharAngleOut="-25" offsetType="1" offsetUnits="MM" overlapHandling="PreventOverlap" overrunDistance="0" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" placement="1" placementFlags="10" polygonPlacementFlags="2" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" preserveRotation="1" priority="5" quadOffset="4" repeatDistance="0" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" repeatDistanceUnits="MM" rotationAngle="0" rotationUnit="AngleDegrees" xOffset="7" yOffset="-7"></placement>
            <rendering drawLabels="1" fontLimitPixelSize="0" fontMaxPixelSize="10000" fontMinPixelSize="3" labelPerPart="0" limitNumLabels="0" maxNumLabels="2000" mergeLines="0" minFeatureSize="0" obstacle="1" obstacleFactor="1" obstacleType="1" scaleMax="0" scaleMin="0" scaleVisibility="0" unplacedVisibility="0" upsidedownLabels="0" zIndex="0"></rendering>
            <dd_properties>
              <Option type="Map">
                <Option name="name" type="QString" value=""></Option>
                <Option name="properties"></Option>
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
                <Option name="lineSymbol" type="QString" value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{be704c21-57e1-450c-9bff-61d7a91a3f02}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>"></Option>
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
        </rule>
      </rule>
      <rule filter="ELSE" key="{ccaf398f-edcf-41aa-b5f0-16154e22ed51}">
        <settings calloutType="simple">
          <text-style allowHtml="0" blendMode="0" capitalization="0" fieldName="'??' " fontFamily="MS Shell Dlg 2" fontItalic="0" fontKerning="1" fontLetterSpacing="0" fontSize="14" fontSizeMapUnitScale="3x:0,0,0,0,0,0" fontSizeUnit="Point" fontStrikeout="0" fontUnderline="0" fontWeight="50" fontWordSpacing="0" forcedBold="0" forcedItalic="0" isExpression="1" legendString="Aa" multilineHeight="1" multilineHeightUnit="Percentage" namedStyle="Regular" previewBkgrdColor="255,255,255,255" textColor="255,0,0,255" textOpacity="1" textOrientation="horizontal" useSubstitutions="0">
            <families></families>
            <text-buffer bufferBlendMode="0" bufferColor="255,255,255,255" bufferDraw="0" bufferJoinStyle="128" bufferNoFill="1" bufferOpacity="1" bufferSize="1" bufferSizeMapUnitScale="3x:0,0,0,0,0,0" bufferSizeUnits="MM"></text-buffer>
            <text-mask maskEnabled="0" maskJoinStyle="128" maskOpacity="1" maskSize="1.5" maskSizeMapUnitScale="3x:0,0,0,0,0,0" maskSizeUnits="MM" maskType="0" maskedSymbolLayers=""></text-mask>
            <background shapeBlendMode="0" shapeBorderColor="128,128,128,255" shapeBorderWidth="0" shapeBorderWidthMapUnitScale="3x:0,0,0,0,0,0" shapeBorderWidthUnit="MM" shapeDraw="0" shapeFillColor="255,255,255,255" shapeJoinStyle="64" shapeOffsetMapUnitScale="3x:0,0,0,0,0,0" shapeOffsetUnit="MM" shapeOffsetX="0" shapeOffsetY="0" shapeOpacity="1" shapeRadiiMapUnitScale="3x:0,0,0,0,0,0" shapeRadiiUnit="MM" shapeRadiiX="0" shapeRadiiY="0" shapeRotation="0" shapeRotationType="0" shapeSVGFile="" shapeSizeMapUnitScale="3x:0,0,0,0,0,0" shapeSizeType="0" shapeSizeUnit="MM" shapeSizeX="0" shapeSizeY="0" shapeType="0">
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
                    <Option name="color" type="QString" value="255,158,23,255"></Option>
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
            </background>
            <shadow shadowBlendMode="6" shadowColor="0,0,0,255" shadowDraw="0" shadowOffsetAngle="135" shadowOffsetDist="1" shadowOffsetGlobal="1" shadowOffsetMapUnitScale="3x:0,0,0,0,0,0" shadowOffsetUnit="MM" shadowOpacity="0.69999999999999996" shadowRadius="1.5" shadowRadiusAlphaOnly="0" shadowRadiusMapUnitScale="3x:0,0,0,0,0,0" shadowRadiusUnit="MM" shadowScale="100" shadowUnder="0"></shadow>
            <dd_properties>
              <Option type="Map">
                <Option name="name" type="QString" value=""></Option>
                <Option name="properties"></Option>
                <Option name="type" type="QString" value="collection"></Option>
              </Option>
            </dd_properties>
            <substitutions></substitutions>
          </text-style>
          <text-format addDirectionSymbol="0" autoWrapLength="0" decimals="3" formatNumbers="0" leftDirectionSymbol="&lt;" multilineAlign="3" placeDirectionSymbol="0" plussign="0" reverseDirectionSymbol="0" rightDirectionSymbol=">" useMaxLineLengthForAutoWrap="1" wrapChar=""></text-format>
          <placement allowDegraded="0" centroidInside="0" centroidWhole="0" dist="5" distMapUnitScale="3x:0,0,0,0,0,0" distUnits="MM" fitInPolygonOnly="0" geometryGenerator="" geometryGeneratorEnabled="0" geometryGeneratorType="PointGeometry" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" layerType="PointGeometry" lineAnchorClipping="0" lineAnchorPercent="0.5" lineAnchorTextPoint="CenterOfText" lineAnchorType="0" maxCurvedCharAngleIn="25" maxCurvedCharAngleOut="-25" offsetType="0" offsetUnits="MM" overlapHandling="PreventOverlap" overrunDistance="0" overrunDistanceMapUnitScale="3x:0,0,0,0,0,0" overrunDistanceUnit="MM" placement="1" placementFlags="10" polygonPlacementFlags="2" predefinedPositionOrder="TR,TL,BR,BL,R,L,TSR,BSR" preserveRotation="1" priority="5" quadOffset="4" repeatDistance="0" repeatDistanceMapUnitScale="3x:0,0,0,0,0,0" repeatDistanceUnits="MM" rotationAngle="0" rotationUnit="AngleDegrees" xOffset="7" yOffset="-7"></placement>
          <rendering drawLabels="1" fontLimitPixelSize="0" fontMaxPixelSize="10000" fontMinPixelSize="3" labelPerPart="0" limitNumLabels="0" maxNumLabels="2000" mergeLines="0" minFeatureSize="0" obstacle="1" obstacleFactor="1" obstacleType="1" scaleMax="0" scaleMin="0" scaleVisibility="0" unplacedVisibility="0" upsidedownLabels="0" zIndex="0"></rendering>
          <dd_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties" type="Map">
                <Option name="PositionX" type="Map">
                  <Option name="active" type="bool" value="true"></Option>
                  <Option name="field" type="QString" value="auxiliary_storage_labeling_positionx"></Option>
                  <Option name="type" type="int" value="2"></Option>
                </Option>
                <Option name="PositionY" type="Map">
                  <Option name="active" type="bool" value="true"></Option>
                  <Option name="field" type="QString" value="auxiliary_storage_labeling_positiony"></Option>
                  <Option name="type" type="int" value="2"></Option>
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
              <Option name="lineSymbol" type="QString" value="&lt;symbol frame_rate=&quot;10&quot; force_rhr=&quot;0&quot; is_animated=&quot;0&quot; type=&quot;line&quot; name=&quot;symbol&quot; clip_to_extent=&quot;1&quot; alpha=&quot;1&quot;>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;layer id=&quot;{ef00bc53-7213-485b-9c40-c041172b540d}&quot; locked=&quot;0&quot; class=&quot;SimpleLine&quot; enabled=&quot;1&quot; pass=&quot;0&quot;>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;align_dash_pattern&quot;/>&lt;Option value=&quot;square&quot; type=&quot;QString&quot; name=&quot;capstyle&quot;/>&lt;Option value=&quot;5;2&quot; type=&quot;QString&quot; name=&quot;customdash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;customdash_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;customdash_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;dash_pattern_offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;draw_inside_polygon&quot;/>&lt;Option value=&quot;bevel&quot; type=&quot;QString&quot; name=&quot;joinstyle&quot;/>&lt;Option value=&quot;60,60,60,255&quot; type=&quot;QString&quot; name=&quot;line_color&quot;/>&lt;Option value=&quot;solid&quot; type=&quot;QString&quot; name=&quot;line_style&quot;/>&lt;Option value=&quot;0.3&quot; type=&quot;QString&quot; name=&quot;line_width&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;line_width_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;offset&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;offset_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;offset_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;ring_filter&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_end_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_map_unit_scale&quot;/>&lt;Option value=&quot;MM&quot; type=&quot;QString&quot; name=&quot;trim_distance_start_unit&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;tweak_dash_pattern_on_corners&quot;/>&lt;Option value=&quot;0&quot; type=&quot;QString&quot; name=&quot;use_custom_dash&quot;/>&lt;Option value=&quot;3x:0,0,0,0,0,0&quot; type=&quot;QString&quot; name=&quot;width_map_unit_scale&quot;/>&lt;/Option>&lt;data_defined_properties>&lt;Option type=&quot;Map&quot;>&lt;Option value=&quot;&quot; type=&quot;QString&quot; name=&quot;name&quot;/>&lt;Option name=&quot;properties&quot;/>&lt;Option value=&quot;collection&quot; type=&quot;QString&quot; name=&quot;type&quot;/>&lt;/Option>&lt;/data_defined_properties>&lt;/layer>&lt;/symbol>"></Option>
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
      </rule>
    </rules>
  </labeling>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
  <layerOpacity>0.75</layerOpacity>
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
          <layer class="SimpleLine" enabled="1" id="{3455926b-a879-42fa-8bff-03a951eed6db}" locked="0" pass="0">
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
  <DiagramLayerSettings dist="0" linePlacementFlags="2" obstacle="0" placement="0" priority="0" showAll="1" zIndex="0">
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
    <field configurationFlags="NoFlag" name="name">
      <editWidget type="TextEdit">
        <config>
          <Option type="Map">
            <Option name="IsMultiline" type="bool" value="false"></Option>
            <Option name="UseHtml" type="bool" value="false"></Option>
          </Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="description">
      <editWidget type="TextEdit">
        <config>
          <Option type="Map">
            <Option name="IsMultiline" type="bool" value="false"></Option>
            <Option name="UseHtml" type="bool" value="false"></Option>
          </Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="gap">
      <editWidget type="Range">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="setting_name">
      <editWidget type="TextEdit">
        <config>
          <Option type="Map">
            <Option name="IsMultiline" type="bool" value="false"></Option>
            <Option name="UseHtml" type="bool" value="false"></Option>
          </Option>
        </config>
      </editWidget>
    </field>
  </fieldConfiguration>
  <aliases>
    <alias field="fid" index="0" name=""></alias>
    <alias field="name" index="1" name=""></alias>
    <alias field="description" index="2" name="desc"></alias>
    <alias field="gap" index="3" name=""></alias>
    <alias field="setting_name" index="4" name=""></alias>
  </aliases>
  <splitPolicies>
    <policy field="fid" policy="Duplicate"></policy>
    <policy field="name" policy="DefaultValue"></policy>
    <policy field="description" policy="DefaultValue"></policy>
    <policy field="gap" policy="Duplicate"></policy>
    <policy field="setting_name" policy="DefaultValue"></policy>
  </splitPolicies>
  <defaults>
    <default applyOnUpdate="0" expression="" field="fid"></default>
    <default applyOnUpdate="0" expression="" field="name"></default>
    <default applyOnUpdate="0" expression="" field="description"></default>
    <default applyOnUpdate="0" expression="" field="gap"></default>
    <default applyOnUpdate="0" expression="" field="setting_name"></default>
  </defaults>
  <constraints>
    <constraint constraints="3" exp_strength="0" field="fid" notnull_strength="1" unique_strength="1"></constraint>
    <constraint constraints="2" exp_strength="0" field="name" notnull_strength="0" unique_strength="1"></constraint>
    <constraint constraints="0" exp_strength="0" field="description" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="gap" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="2" exp_strength="0" field="setting_name" notnull_strength="0" unique_strength="1"></constraint>
  </constraints>
  <constraintExpressions>
    <constraint desc="" exp="" field="fid"></constraint>
    <constraint desc="" exp="" field="name"></constraint>
    <constraint desc="" exp="" field="description"></constraint>
    <constraint desc="" exp="" field="gap"></constraint>
    <constraint desc="" exp="" field="setting_name"></constraint>
  </constraintExpressions>
  <expressionfields></expressionfields>
  <attributeactions>
    <defaultAction key="Canvas" value="{00000000-0000-0000-0000-000000000000}"></defaultAction>
  </attributeactions>
  <attributetableconfig actionWidgetStyle="dropDown" sortExpression="" sortOrder="0">
    <columns>
      <column hidden="0" name="fid" type="field" width="-1"></column>
      <column hidden="0" name="name" type="field" width="-1"></column>
      <column hidden="0" name="description" type="field" width="-1"></column>
      <column hidden="0" name="gap" type="field" width="-1"></column>
      <column hidden="0" name="setting_name" type="field" width="-1"></column>
      <column hidden="1" type="actions" width="-1"></column>
    </columns>
  </attributetableconfig>
  <conditionalstyles>
    <rowstyles></rowstyles>
    <fieldstyles></fieldstyles>
  </conditionalstyles>
  <storedexpressions></storedexpressions>
  <editform tolerant="1">/Users/david/Dropbox/2017ARC/qgis</editform>
  <editforminit></editforminit>
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
    <field editable="1" name="Gap"></field>
    <field editable="0" name="auxiliary_storage_labeling_positionx"></field>
    <field editable="0" name="auxiliary_storage_labeling_positiony"></field>
    <field editable="1" name="cmt"></field>
    <field editable="1" name="description"></field>
    <field editable="1" name="fid"></field>
    <field editable="1" name="gap"></field>
    <field editable="1" name="name"></field>
    <field editable="1" name="setting_name"></field>
  </editable>
  <labelOnTop>
    <field labelOnTop="0" name="Gap"></field>
    <field labelOnTop="0" name="auxiliary_storage_labeling_positionx"></field>
    <field labelOnTop="0" name="auxiliary_storage_labeling_positiony"></field>
    <field labelOnTop="0" name="cmt"></field>
    <field labelOnTop="0" name="description"></field>
    <field labelOnTop="0" name="fid"></field>
    <field labelOnTop="0" name="gap"></field>
    <field labelOnTop="0" name="name"></field>
    <field labelOnTop="0" name="setting_name"></field>
  </labelOnTop>
  <reuseLastValue>
    <field name="Gap" reuseLastValue="0"></field>
    <field name="auxiliary_storage_labeling_positionx" reuseLastValue="0"></field>
    <field name="auxiliary_storage_labeling_positiony" reuseLastValue="0"></field>
    <field name="cmt" reuseLastValue="0"></field>
    <field name="description" reuseLastValue="0"></field>
    <field name="fid" reuseLastValue="0"></field>
    <field name="gap" reuseLastValue="0"></field>
    <field name="name" reuseLastValue="0"></field>
    <field name="setting_name" reuseLastValue="0"></field>
  </reuseLastValue>
  <dataDefinedFieldProperties></dataDefinedFieldProperties>
  <widgets></widgets>
  <previewExpression>"setting_name"</previewExpression>
  <mapTip enabled="1"></mapTip>
  <layerGeometryType>0</layerGeometryType>
</qgis>