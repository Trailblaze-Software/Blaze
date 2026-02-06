<!DOCTYPE qgis PUBLIC 'http://mrcc.com/qgis.dtd' 'SYSTEM'>
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="0" readOnly="0" version="3.34.3-Prizren" simplifyDrawingTol="1" maxScale="0" minScale="100000000" symbologyReferenceScale="-1" simplifyDrawingHints="1" simplifyAlgorithm="0" styleCategories="LayerConfiguration|Symbology|Symbology3D|Labeling|Fields|Forms|Actions|MapTips|Diagrams|AttributeTable|Rendering" simplifyLocal="1" simplifyMaxScale="1">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 forceraster="0" type="RuleRenderer" referencescale="-1" enableorderby="0" symbollevels="0">
    <rules key="{fc7f8887-5f44-45ee-abb4-ca68c9f97c15}">
      <rule label="Restricted Area" filter="classsubtype = 3" key="{ff490839-4880-4ac5-aa11-93a2b2b4b852}" symbol="0"/>
      <rule label="Building" filter="classsubtype = 5" key="{ee78b049-c4b8-42b1-94ef-2c25a9759551}" symbol="1"/>
      <rule label="Plantation" filter="classsubtype = 6" key="{7f5270df-bba7-44c5-97d4-caef0e153458}" symbol="2">
        <rule label="Pine" filter="generalculturaltype = 1" key="{b3417fa6-2b3c-4001-b7ca-db506364973b}" symbol="3"/>
        <rule label="Horticulture" filter="generalculturaltype = 4" key="{d31aa465-8640-41d7-a354-7d5aa8db2110}" symbol="4"/>
      </rule>
      <rule label="Urban" filter="classsubtype = 7" key="{861f1e29-98bd-4f2b-99c6-ad90d3a1671d}" symbol="5"/>
      <rule label="Water treatment pond" filter="classsubtype = 9 and (generalculturaltype = 0 or generalculturaltype = 1)" key="{71ddb56f-7aa1-4a51-9ea3-5c761128746f}" symbol="6"/>
      <rule label="Unknown" filter="ELSE" key="{37c0414f-269a-4713-b2cf-c47e26bccfca}" symbol="7"/>
    </rules>
    <symbols>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="0" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{91685feb-0984-4626-a087-727ac443cbfe}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="255,0,0,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0.26" type="QString" name="outline_width"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="1" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{aaa0aad4-e3b1-48d5-873f-1f9a90bdc185}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="0,0,0,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="112,112,112,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="2" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{decbc817-7b23-45c3-b832-7329dfe95d45}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="35,118,35,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,0,35,255" type="QString" name="outline_color"/>
            <Option value="no" type="QString" name="outline_style"/>
            <Option value="0" type="QString" name="outline_width"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="no" type="QString" name="style"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="3" clip_to_extent="1" alpha="0.4">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{57a9c90f-d340-4ae9-8e25-1a3e48f1cde6}" locked="0" class="SVGFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="angle"/>
            <Option value="0,136,0,255" type="QString" name="color"/>
            <Option value="255,255,255,255" type="QString" name="outline_color"/>
            <Option value="0" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option name="parameters"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="pattern_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="pattern_width_unit"/>
            <Option value="gpsicons/tree.svg" type="QString" name="svgFile"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="svg_outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="svg_outline_width_unit"/>
            <Option value="2" type="QString" name="width"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="4" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{3155aa06-85c4-42ca-b4b4-70ff5f82d97d}" locked="0" class="SVGFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="angle"/>
            <Option value="35,118,35,255" type="QString" name="color"/>
            <Option value="35,0,35,255" type="QString" name="outline_color"/>
            <Option value="0" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option name="parameters"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="pattern_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="pattern_width_unit"/>
            <Option value="symbol/landuse_deciduous.svg" type="QString" name="svgFile"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="svg_outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="svg_outline_width_unit"/>
            <Option value="1.5" type="QString" name="width"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="5" clip_to_extent="1" alpha="0.326">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{ba377a73-d66e-44a7-bae1-b1d1c56eaafc}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="255,202,11,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="254,243,169,255" type="QString" name="outline_color"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="6" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{446fae80-c39b-4c1b-a5b4-95a43c83b326}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="17,40,234,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="73,133,223,255" type="QString" name="outline_color"/>
            <Option value="no" type="QString" name="outline_style"/>
            <Option value="0.26" type="QString" name="outline_width"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="7" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{64d0fc3d-6cc9-4fc2-8502-c9832fcd34e3}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="255,0,0,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0.26" type="QString" name="outline_width"/>
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
    </symbols>
  </renderer-v2>
  <selection mode="Default">
    <selectionColor invalid="1"/>
    <selectionSymbol>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{32a57ac8-1f13-4f3e-a7e6-5831bdca5a4e}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="0,0,255,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0.26" type="QString" name="outline_width"/>
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
    </selectionSymbol>
  </selection>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
  <layerOpacity>1</layerOpacity>
  <SingleCategoryDiagramRenderer diagramType="Histogram" attributeLegend="1">
    <DiagramCategory sizeType="MM" enabled="0" opacity="1" lineSizeScale="3x:0,0,0,0,0,0" penWidth="0" height="15" penColor="#000000" sizeScale="3x:0,0,0,0,0,0" direction="0" maxScaleDenominator="1e+08" backgroundAlpha="255" scaleBasedVisibility="0" penAlpha="255" spacingUnit="MM" lineSizeType="MM" spacing="5" labelPlacementMethod="XHeight" barWidth="5" spacingUnitScale="3x:0,0,0,0,0,0" minScaleDenominator="0" rotationOffset="270" showAxis="1" backgroundColor="#ffffff" minimumSize="0" scaleDependency="Area" width="15" diagramOrientation="Up">
      <fontProperties underline="0" description="MS Shell Dlg 2,8.3,-1,5,50,0,0,0,0,0" bold="0" italic="0" strikethrough="0" style=""/>
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
          <layer id="{a489e696-3158-474e-a6c6-7e5369f49a92}" locked="0" class="SimpleLine" enabled="1" pass="0">
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
  <DiagramLayerSettings linePlacementFlags="18" dist="0" obstacle="0" zIndex="0" showAll="1" priority="0" placement="1">
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
    <field configurationFlags="NoFlag" name="generalnameoid">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="generalname">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="alternativelabel">
      <editWidget type="TextEdit">
        <config>
          <Option/>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="generalculturaltype">
      <editWidget type="Range">
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
    <field configurationFlags="NoFlag" name="shape_Area">
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
    <alias index="14" name="" field="generalnameoid"/>
    <alias index="15" name="" field="generalname"/>
    <alias index="16" name="" field="alternativelabel"/>
    <alias index="17" name="" field="generalculturaltype"/>
    <alias index="18" name="" field="relevance"/>
    <alias index="19" name="" field="startdate"/>
    <alias index="20" name="" field="enddate"/>
    <alias index="21" name="" field="lastupdate"/>
    <alias index="22" name="" field="msoid"/>
    <alias index="23" name="" field="centroidid"/>
    <alias index="24" name="" field="shapeuuid"/>
    <alias index="25" name="" field="changetype"/>
    <alias index="26" name="" field="processstate"/>
    <alias index="27" name="" field="urbanity"/>
    <alias index="28" name="" field="shape_Length"/>
    <alias index="29" name="" field="shape_Area"/>
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
    <policy policy="Duplicate" field="generalnameoid"/>
    <policy policy="Duplicate" field="generalname"/>
    <policy policy="Duplicate" field="alternativelabel"/>
    <policy policy="Duplicate" field="generalculturaltype"/>
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
    <policy policy="Duplicate" field="shape_Area"/>
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
    <default expression="" applyOnUpdate="0" field="generalnameoid"/>
    <default expression="" applyOnUpdate="0" field="generalname"/>
    <default expression="" applyOnUpdate="0" field="alternativelabel"/>
    <default expression="" applyOnUpdate="0" field="generalculturaltype"/>
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
    <default expression="" applyOnUpdate="0" field="shape_Area"/>
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
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="generalnameoid" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="generalname" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="alternativelabel" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="generalculturaltype" unique_strength="0"/>
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
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="shape_Area" unique_strength="0"/>
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
    <constraint desc="" field="generalnameoid" exp=""/>
    <constraint desc="" field="generalname" exp=""/>
    <constraint desc="" field="alternativelabel" exp=""/>
    <constraint desc="" field="generalculturaltype" exp=""/>
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
    <constraint desc="" field="shape_Area" exp=""/>
  </constraintExpressions>
  <expressionfields/>
  <attributeactions>
    <defaultAction value="{00000000-0000-0000-0000-000000000000}" key="Canvas"/>
  </attributeactions>
  <attributetableconfig sortExpression="" actionWidgetStyle="dropDown" sortOrder="0">
    <columns>
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
      <column width="-1" type="field" name="generalnameoid" hidden="0"/>
      <column width="-1" type="field" name="generalname" hidden="0"/>
      <column width="-1" type="field" name="alternativelabel" hidden="0"/>
      <column width="-1" type="field" name="generalculturaltype" hidden="0"/>
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
      <column width="-1" type="field" name="fid" hidden="0"/>
      <column width="-1" type="field" name="objectid" hidden="0"/>
      <column width="-1" type="field" name="shape_Length" hidden="0"/>
      <column width="-1" type="field" name="shape_Area" hidden="0"/>
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
    <field editable="1" name="Shape__Area"/>
    <field editable="1" name="Shape__Length"/>
    <field editable="1" name="alternativelabel"/>
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
    <field editable="1" name="generalculturaltype"/>
    <field editable="1" name="generalname"/>
    <field editable="1" name="generalnameoid"/>
    <field editable="1" name="lastupdate"/>
    <field editable="1" name="msoid"/>
    <field editable="1" name="objectid"/>
    <field editable="1" name="objectmoddate"/>
    <field editable="1" name="operationalstatus"/>
    <field editable="1" name="planimetricaccuracy"/>
    <field editable="1" name="processstate"/>
    <field editable="1" name="relevance"/>
    <field editable="1" name="shape_Area"/>
    <field editable="1" name="shape_Length"/>
    <field editable="1" name="shapeuuid"/>
    <field editable="1" name="startdate"/>
    <field editable="1" name="topoid"/>
    <field editable="1" name="urbanity"/>
    <field editable="1" name="verticalaccuracy"/>
  </editable>
  <labelOnTop>
    <field name="OBJECTID" labelOnTop="0"/>
    <field name="Shape__Area" labelOnTop="0"/>
    <field name="Shape__Length" labelOnTop="0"/>
    <field name="alternativelabel" labelOnTop="0"/>
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
    <field name="generalculturaltype" labelOnTop="0"/>
    <field name="generalname" labelOnTop="0"/>
    <field name="generalnameoid" labelOnTop="0"/>
    <field name="lastupdate" labelOnTop="0"/>
    <field name="msoid" labelOnTop="0"/>
    <field name="objectid" labelOnTop="0"/>
    <field name="objectmoddate" labelOnTop="0"/>
    <field name="operationalstatus" labelOnTop="0"/>
    <field name="planimetricaccuracy" labelOnTop="0"/>
    <field name="processstate" labelOnTop="0"/>
    <field name="relevance" labelOnTop="0"/>
    <field name="shape_Area" labelOnTop="0"/>
    <field name="shape_Length" labelOnTop="0"/>
    <field name="shapeuuid" labelOnTop="0"/>
    <field name="startdate" labelOnTop="0"/>
    <field name="topoid" labelOnTop="0"/>
    <field name="urbanity" labelOnTop="0"/>
    <field name="verticalaccuracy" labelOnTop="0"/>
  </labelOnTop>
  <reuseLastValue>
    <field reuseLastValue="0" name="OBJECTID"/>
    <field reuseLastValue="0" name="Shape__Area"/>
    <field reuseLastValue="0" name="Shape__Length"/>
    <field reuseLastValue="0" name="alternativelabel"/>
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
    <field reuseLastValue="0" name="generalculturaltype"/>
    <field reuseLastValue="0" name="generalname"/>
    <field reuseLastValue="0" name="generalnameoid"/>
    <field reuseLastValue="0" name="lastupdate"/>
    <field reuseLastValue="0" name="msoid"/>
    <field reuseLastValue="0" name="objectid"/>
    <field reuseLastValue="0" name="objectmoddate"/>
    <field reuseLastValue="0" name="operationalstatus"/>
    <field reuseLastValue="0" name="planimetricaccuracy"/>
    <field reuseLastValue="0" name="processstate"/>
    <field reuseLastValue="0" name="relevance"/>
    <field reuseLastValue="0" name="shape_Area"/>
    <field reuseLastValue="0" name="shape_Length"/>
    <field reuseLastValue="0" name="shapeuuid"/>
    <field reuseLastValue="0" name="startdate"/>
    <field reuseLastValue="0" name="topoid"/>
    <field reuseLastValue="0" name="urbanity"/>
    <field reuseLastValue="0" name="verticalaccuracy"/>
  </reuseLastValue>
  <dataDefinedFieldProperties/>
  <widgets/>
  <previewExpression>"generalnameoid"</previewExpression>
  <mapTip enabled="1"></mapTip>
  <layerGeometryType>2</layerGeometryType>
</qgis>
