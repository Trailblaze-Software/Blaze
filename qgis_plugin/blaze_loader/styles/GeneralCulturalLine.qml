<!DOCTYPE qgis PUBLIC 'http://mrcc.com/qgis.dtd' 'SYSTEM'>
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="0" readOnly="0" version="3.34.3-Prizren" simplifyDrawingTol="1" maxScale="0" minScale="100000000" symbologyReferenceScale="-1" simplifyDrawingHints="1" simplifyAlgorithm="0" styleCategories="LayerConfiguration|Symbology|Symbology3D|Labeling|Fields|Forms|Actions|MapTips|Diagrams|AttributeTable|Rendering" simplifyLocal="1" simplifyMaxScale="1">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 forceraster="0" type="RuleRenderer" referencescale="-1" enableorderby="0" symbollevels="0">
    <rules key="{3eb20fec-c02c-4471-93bb-3b6cdf59a56f}">
      <rule label="Perimeter/Fence" filter="classsubtype in ('2', '3')" key="{75862fdd-18fa-4539-9fca-17414def8832}" symbol="0"/>
      <rule label="Dam wall" filter="classsubtype = 4" key="{01369c5a-de80-4c46-9035-e3c4fb4afa55}" symbol="1"/>
      <rule label="Unkown" filter="ELSE" checkstate="0" key="{a3efb512-f0a0-4b1a-83ea-c639407c235b}" symbol="2"/>
      <rule label="Race track" filter="classsubtype = 6" key="{3b3fb8a7-4a40-47ce-95ba-8895503c506a}" symbol="3"/>
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
        <layer id="{c5512dd5-f264-4502-8a94-f31d57d5f107}" locked="0" class="SimpleLine" enabled="1" pass="0">
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
            <Option value="166,166,166,255" type="QString" name="line_color"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="1" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{c91418e9-fd78-4dec-93ac-d684af905d64}" locked="0" class="SimpleLine" enabled="1" pass="0">
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="2" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{052701e8-0917-418a-bea3-0b871affd015}" locked="0" class="SimpleLine" enabled="1" pass="0">
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
            <Option value="1" type="QString" name="line_width"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="line" name="3" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{51785892-e432-4934-a0c7-c6697410ad94}" locked="0" class="SimpleLine" enabled="1" pass="0">
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
            <Option value="159,133,3,255" type="QString" name="line_color"/>
            <Option value="dash" type="QString" name="line_style"/>
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
        <layer id="{c980b6b7-f353-4c18-94da-fb0ada6da647}" locked="0" class="SimpleLine" enabled="1" pass="0">
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
      <fontProperties underline="0" description=".AppleSystemUIFont,13,-1,5,50,0,0,0,0,0" bold="0" italic="0" strikethrough="0" style=""/>
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
          <layer id="{146797cb-7d70-4989-81c5-df2b2cf866f0}" locked="0" class="SimpleLine" enabled="1" pass="0">
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
    <field editable="1" name="shape_Length"/>
    <field editable="1" name="shapeuuid"/>
    <field editable="1" name="startdate"/>
    <field editable="1" name="topoid"/>
    <field editable="1" name="urbanity"/>
    <field editable="1" name="verticalaccuracy"/>
  </editable>
  <labelOnTop>
    <field name="OBJECTID" labelOnTop="0"/>
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
    <field name="shape_Length" labelOnTop="0"/>
    <field name="shapeuuid" labelOnTop="0"/>
    <field name="startdate" labelOnTop="0"/>
    <field name="topoid" labelOnTop="0"/>
    <field name="urbanity" labelOnTop="0"/>
    <field name="verticalaccuracy" labelOnTop="0"/>
  </labelOnTop>
  <reuseLastValue>
    <field reuseLastValue="0" name="OBJECTID"/>
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
  <layerGeometryType>1</layerGeometryType>
</qgis>
