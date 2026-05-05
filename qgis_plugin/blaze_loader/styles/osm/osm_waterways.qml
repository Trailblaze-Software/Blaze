<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="1" maxScale="0" minScale="1e+08" readOnly="0" styleCategories="LayerConfiguration|Symbology|Labeling|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{osm-ww-root}">
      <rule filter="&quot;waterway&quot; IN ('river','canal')" key="{ww-r}" label="River / Canal" symbol="0"></rule>
      <rule filter="&quot;waterway&quot; IN ('stream','tidal_channel')" key="{ww-s}" label="Stream" symbol="1"></rule>
      <rule filter="&quot;waterway&quot; IN ('drain','ditch')" key="{ww-d}" label="Drain / Ditch" symbol="2"></rule>
      <rule filter="ELSE" key="{ww-o}" label="Other waterway" symbol="3"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="line">
        <layer class="SimpleLine" enabled="1" id="{ww-river}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="0,158,224,255"></Option>
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
        <layer class="SimpleLine" enabled="1" id="{ww-stream}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="0,158,224,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.35"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="0"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="2" type="line">
        <layer class="SimpleLine" enabled="1" id="{ww-drain}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="square"></Option>
            <Option name="customdash" type="QString" value="2.4;1.2"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="0,158,224,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.3"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="1"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="3" type="line">
        <layer class="SimpleLine" enabled="1" id="{ww-other}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="0,158,224,255"></Option>
            <Option name="line_style" type="QString" value="dash"></Option>
            <Option name="line_width" type="QString" value="0.25"></Option>
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
      <text-style allowHtml="0" blendMode="0" capitalization="1004" fieldName="name" fontFamily="Arial" fontItalic="1" fontKerning="1" fontLetterSpacing="0.25" fontSize="8" fontSizeUnit="Point" fontStrikeout="0" fontUnderline="0" fontWeight="50" fontWordSpacing="0" forcedBold="0" forcedItalic="0" isExpression="0" multilineHeight="1" multilineHeightUnit="Percentage" namedStyle="Italic" previewBkgrdColor="255,255,255,255" textColor="0,75,140,255" textOpacity="0.95" textOrientation="horizontal" useSubstitutions="0">
        <text-buffer bufferBlendMode="0" bufferColor="255,255,255,255" bufferDraw="1" bufferJoinStyle="128" bufferNoFill="0" bufferOpacity="0.65" bufferSize="0.35" bufferSizeUnits="MM"></text-buffer>
      </text-style>
      <text-format addDirectionSymbol="0" decimals="3" multilineAlign="0" placeDirectionSymbol="0" plural="0" wrapChar=""></text-format>
      <placement allowDegraded="0" centroidInside="0" centroidWhole="0" dist="0" distUnits="MM" geometryGenerator="" geometryGeneratorEnabled="0" geometryGeneratorType="LineGeometry" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" lineAnchorClipping="0" lineAnchorPercent="0.5" lineAnchorTextPoint="FollowPlacement" lineAnchorType="0" maxCurvedCharAngleIn="40" maxCurvedCharAngleOut="-40" offsetType="0" overlapHandling="PreventOverlap" overrunDistance="0" overrunDistanceUnit="MM" placement="3" placementFlags="10" polygonPlacementFlags="2" preserveRotation="1" priority="6" quadOffset="4" repeatDistance="150" repeatDistanceUnit="MM" rotationAngle="0" rotationUnit="AngleDegrees" xOffset="0" yOffset="0"></placement>
      <rendering drawLabels="1" fontLimitPixelSize="0" fontMaxPixelSize="10000" fontMinPixelSize="3" labelPerPart="1" maxNumLabels="2000" mergeLines="1" minFeatureSize="0" obstacle="1" obstacleFactor="1" obstacleType="0" scaleMax="60000" scaleMin="0" scaleVisibility="1" upsidedownLabels="0" zIndex="0"></rendering>
      <dd_properties>
        <Option type="Map">
          <Option name="name" type="QString" value=""></Option>
          <Option name="properties" type="Map">
            <Option name="Size" type="Map">
              <Option name="active" type="bool" value="true"></Option>
              <Option name="expression" type="QString" value="case when &quot;waterway&quot; in ('river','canal') then 9 when &quot;waterway&quot; in ('stream') then 8 when &quot;waterway&quot; in ('drain','ditch','tidal_channel') then 7 else 7 end"></Option>
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