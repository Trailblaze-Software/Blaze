<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="1" labelsEnabled="0" maxScale="0" minScale="20000" readOnly="0" simplifyAlgorithm="0" simplifyDrawingHints="1" simplifyDrawingTol="1" simplifyLocal="1" simplifyMaxScale="1" styleCategories="LayerConfiguration|Symbology|Labeling|Fields|Rendering" symbologyReferenceScale="-1" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="singleSymbol">
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{lw-pool-fill}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="0,158,224,255"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="0,0,0,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.3"></Option>
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
    </symbols>
    <rotation></rotation>
    <sizescale></sizescale>
  </renderer-v2>
  <selection mode="Default">
    <selectionColor invalid="1"></selectionColor>
    <selectionSymbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{f6310dba-df28-4257-bb55-c7caad78e121}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="0,0,255,255"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="35,35,35,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.26"></Option>
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
    <field configurationFlags="NoFlag" name="leisure"></field>
    <field configurationFlags="NoFlag" name="tags"></field>
  </fieldConfiguration>
  <aliases>
    <alias field="fid" index="0" name=""></alias>
    <alias field="osm_id" index="1" name=""></alias>
    <alias field="osm_type" index="2" name=""></alias>
    <alias field="name" index="3" name=""></alias>
    <alias field="leisure" index="4" name=""></alias>
    <alias field="tags" index="5" name=""></alias>
  </aliases>
  <splitPolicies>
    <policy field="fid" policy="Duplicate"></policy>
    <policy field="osm_id" policy="Duplicate"></policy>
    <policy field="osm_type" policy="Duplicate"></policy>
    <policy field="name" policy="Duplicate"></policy>
    <policy field="leisure" policy="Duplicate"></policy>
    <policy field="tags" policy="Duplicate"></policy>
  </splitPolicies>
  <defaults>
    <default applyOnUpdate="0" expression="" field="fid"></default>
    <default applyOnUpdate="0" expression="" field="osm_id"></default>
    <default applyOnUpdate="0" expression="" field="osm_type"></default>
    <default applyOnUpdate="0" expression="" field="name"></default>
    <default applyOnUpdate="0" expression="" field="leisure"></default>
    <default applyOnUpdate="0" expression="" field="tags"></default>
  </defaults>
  <constraints>
    <constraint constraints="3" exp_strength="0" field="fid" notnull_strength="1" unique_strength="1"></constraint>
    <constraint constraints="0" exp_strength="0" field="osm_id" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="osm_type" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="name" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="leisure" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="tags" notnull_strength="0" unique_strength="0"></constraint>
  </constraints>
  <constraintExpressions>
    <constraint desc="" exp="" field="fid"></constraint>
    <constraint desc="" exp="" field="osm_id"></constraint>
    <constraint desc="" exp="" field="osm_type"></constraint>
    <constraint desc="" exp="" field="name"></constraint>
    <constraint desc="" exp="" field="leisure"></constraint>
    <constraint desc="" exp="" field="tags"></constraint>
  </constraintExpressions>
  <expressionfields></expressionfields>
  <previewExpression>"name"</previewExpression>
  <layerGeometryType>2</layerGeometryType>
</qgis>