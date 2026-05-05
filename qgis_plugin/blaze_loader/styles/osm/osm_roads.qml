<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="1" maxScale="0" minScale="1e+08" readOnly="0" styleCategories="LayerConfiguration|Symbology|Labeling|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{osm-roads-root}">
      <rule filter="&quot;highway&quot; IN ('motorway','trunk','motorway_link','trunk_link')" key="{r-mw}" label="Motorway / Trunk" symbol="0"></rule>
      <rule filter="&quot;highway&quot; IN ('primary','primary_link')" key="{r-pri}" label="Primary" symbol="1"></rule>
      <rule filter="&quot;highway&quot; IN ('secondary','secondary_link')" key="{r-sec}" label="Secondary" symbol="2"></rule>
      <rule filter="&quot;highway&quot; IN ('tertiary','tertiary_link')" key="{r-ter}" label="Tertiary" symbol="3"></rule>
      <rule filter="ELSE" key="{r-oth}" label="Residential / Other" symbol="4"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="line">
        <layer class="SimpleLine" enabled="1" id="{rd-mw}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="220,40,40,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.7"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="0"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="line">
        <layer class="SimpleLine" enabled="1" id="{rd-pri}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="240,140,40,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.55"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="0"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="2" type="line">
        <layer class="SimpleLine" enabled="1" id="{rd-sec}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="240,200,80,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.45"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="0"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="3" type="line">
        <layer class="SimpleLine" enabled="1" id="{rd-ter}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="250,230,160,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.4"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="0"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="4" type="line">
        <layer class="SimpleLine" enabled="1" id="{rd-oth}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="120,120,120,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.3"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="0"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
    </symbols>
  </renderer-v2>
  <labeling type="simple">
    <settings calloutType="simple">
      <text-style allowHtml="0" blendMode="0" capitalization="1004" fieldName="name" fontFamily="Arial" fontItalic="0" fontKerning="1" fontLetterSpacing="0" fontSize="8" fontSizeUnit="Point" fontStrikeout="0" fontUnderline="0" fontWeight="63" fontWordSpacing="0" forcedBold="0" forcedItalic="0" isExpression="0" multilineHeight="1" multilineHeightUnit="Percentage" namedStyle="SemiBold" previewBkgrdColor="255,255,255,255" textColor="50,50,50,255" textOpacity="1" textOrientation="horizontal" useSubstitutions="0">
        <text-buffer bufferBlendMode="0" bufferColor="250,250,250,255" bufferDraw="1" bufferJoinStyle="128" bufferNoFill="1" bufferOpacity="1" bufferSize="0.3" bufferSizeUnits="MM"></text-buffer>
      </text-style>
      <text-format addDirectionSymbol="0" decimals="3" multilineAlign="3" placeDirectionSymbol="0" plural="0" wrapChar=""></text-format>
      <placement allowDegradedPlacement="0" centroidInside="0" centroidWhole="0" dist="0" geometryGenerator="" geometryGeneratorEnabled="0" geometryGeneratorType="PointGeometry" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" lineAnchorClipping="0" lineAnchorPercent="0.5" lineAnchorTextPoint="CenterOfText" lineAnchorType="0" maxCurvedCharAngleIn="25" maxCurvedCharAngleOut="-25" offsetType="0" overlapHandling="PreventOverlap" overrunDistance="0" overrunDistanceUnit="MM" placement="3" placementFlags="10" polygonPlacementFlags="2" preserveRotation="1" priority="5" quadOffset="4" repeatDistance="100" repeatDistanceUnit="MM" rotationAngle="0" rotationUnit="AngleDegrees" xOffset="0" yOffset="0"></placement>
      <rendering drawLabels="1" fontLimitPixelSize="0" fontMaxPixelSize="10000" fontMinPixelSize="3" labelPerPart="0" maxNumLabels="2000" mergeLines="0" minFeatureSize="20" obstacle="1" obstacleFactor="1" obstacleType="1" scaleMax="60000" scaleMin="0" scaleVisibility="1" upsidedownLabels="0" zIndex="0"></rendering>
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
    </settings>
  </labeling>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
</qgis>