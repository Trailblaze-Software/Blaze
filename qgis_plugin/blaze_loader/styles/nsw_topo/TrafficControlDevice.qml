<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="1" labelsEnabled="0" maxScale="0" minScale="75000" readOnly="0" simplifyAlgorithm="0" simplifyDrawingHints="0" simplifyDrawingTol="1" simplifyLocal="1" simplifyMaxScale="1" styleCategories="LayerConfiguration|Symbology|Labeling|Fields|Rendering" symbologyReferenceScale="-1" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{06a8d04e-f3fd-409b-a6f7-8ea26265cfb6}">
      <rule filter="classsubtype = 1" key="{ce450f86-3735-4f12-bad1-c6a827b5c291}" label="gate" symbol="0"></rule>
      <rule filter="classsubtype = 2" key="{291545be-d188-4e24-a649-3c075faeac3d}" label="grid" symbol="1"></rule>
      <rule filter="classsubtype = 4" key="{a8e760d1-b84e-42f1-b65d-b16039131597}" label="Barrier" symbol="2"></rule>
      <rule filter="classsubtype =5 " key="{27d65991-63a0-4a69-8d98-37e9adc6f191}" label="Level crossing" symbol="3"></rule>
      <rule checkstate="0" filter="classsubtype = 6" key="{58195861-b486-4a8e-a436-b81dcd02d7e3}" label="Roundabout" symbol="4"></rule>
      <rule filter="ELSE" key="{d3ec6c6f-96a2-4891-8911-7c3d994ca71e}" label="Unkown" symbol="5"></rule>
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
            <Option name="offset" type="QString" value="0,0"></Option>
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
        <layer class="SimpleMarker" enabled="1" id="{ab6c7001-8993-4c8d-ac9b-a0d08ec74246}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="cap_style" type="QString" value="square"></Option>
            <Option name="color" type="QString" value="255,0,0,0"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="name" type="QString" value="half_square"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="35,35,35,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.2"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="3"></Option>
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
                  <Option name="expression" type="QString" value="-1 * symbolrotation"></Option>
                  <Option name="type" type="int" value="3"></Option>
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
        <layer class="SvgMarker" enabled="1" id="{83da0eef-b770-419d-b899-6bd3b38a02b7}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="color" type="QString" value="0,0,0,255"></Option>
            <Option name="fixedAspectRatio" type="QString" value="0"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="name" type="QString" value="transport/barrier_stile.svg"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="35,35,35,255"></Option>
            <Option name="outline_width" type="QString" value="0"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="parameters"></Option>
            <Option name="scale_method" type="QString" value="diameter"></Option>
            <Option name="size" type="QString" value="3"></Option>
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
                  <Option name="expression" type="QString" value="symbolrotation"></Option>
                  <Option name="type" type="int" value="3"></Option>
                </Option>
              </Option>
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
        <layer class="SimpleMarker" enabled="1" id="{6f0f4886-b8c6-4121-8f27-1b4def9b9cce}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="cap_style" type="QString" value="square"></Option>
            <Option name="color" type="QString" value="141,90,153,255"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="name" type="QString" value="cross2"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="125,139,143,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.4"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="4" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleMarker" enabled="1" id="{40279d7e-cc72-4ff1-b003-cef03ef487d8}" locked="0" pass="0">
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="5" type="marker">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleMarker" enabled="1" id="{ff26bfd0-1867-40a6-9c5d-abd12685dd55}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="cap_style" type="QString" value="square"></Option>
            <Option name="color" type="QString" value="164,113,88,255"></Option>
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
            <Option name="size" type="QString" value="5"></Option>
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
        <layer class="SimpleMarker" enabled="1" id="{52c866a3-f050-4bbd-9ff0-a7caea136205}" locked="0" pass="0">
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
    <field configurationFlags="NoFlag" name="generalnameoid"></field>
    <field configurationFlags="NoFlag" name="generalname"></field>
    <field configurationFlags="NoFlag" name="alternativelabel"></field>
    <field configurationFlags="NoFlag" name="symbolrotation"></field>
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
    <alias field="generalnameoid" index="14" name=""></alias>
    <alias field="generalname" index="15" name=""></alias>
    <alias field="alternativelabel" index="16" name=""></alias>
    <alias field="symbolrotation" index="17" name=""></alias>
    <alias field="relevance" index="18" name=""></alias>
    <alias field="startdate" index="19" name=""></alias>
    <alias field="enddate" index="20" name=""></alias>
    <alias field="lastupdate" index="21" name=""></alias>
    <alias field="msoid" index="22" name=""></alias>
    <alias field="centroidid" index="23" name=""></alias>
    <alias field="shapeuuid" index="24" name=""></alias>
    <alias field="changetype" index="25" name=""></alias>
    <alias field="processstate" index="26" name=""></alias>
    <alias field="urbanity" index="27" name=""></alias>
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
    <policy field="generalnameoid" policy="Duplicate"></policy>
    <policy field="generalname" policy="Duplicate"></policy>
    <policy field="alternativelabel" policy="Duplicate"></policy>
    <policy field="symbolrotation" policy="Duplicate"></policy>
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
    <default applyOnUpdate="0" expression="" field="generalnameoid"></default>
    <default applyOnUpdate="0" expression="" field="generalname"></default>
    <default applyOnUpdate="0" expression="" field="alternativelabel"></default>
    <default applyOnUpdate="0" expression="" field="symbolrotation"></default>
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
    <constraint constraints="0" exp_strength="0" field="generalnameoid" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="generalname" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="alternativelabel" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="symbolrotation" notnull_strength="0" unique_strength="0"></constraint>
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
    <constraint desc="" exp="" field="generalnameoid"></constraint>
    <constraint desc="" exp="" field="generalname"></constraint>
    <constraint desc="" exp="" field="alternativelabel"></constraint>
    <constraint desc="" exp="" field="symbolrotation"></constraint>
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
  </constraintExpressions>
  <expressionfields></expressionfields>
  <previewExpression>"category"</previewExpression>
  <layerGeometryType>0</layerGeometryType>
</qgis>