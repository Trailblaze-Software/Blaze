<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="1" maxScale="0" minScale="1e+08" readOnly="0" styleCategories="LayerConfiguration|Symbology|Labeling|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{pl-root}">
      <rule filter="&quot;place&quot; IN ('city','town')" key="{pl-c}" label="City / Town" symbol="0"></rule>
      <rule filter="&quot;place&quot; IN ('village','suburb','neighbourhood')" key="{pl-v}" label="Village / Suburb" symbol="1"></rule>
      <rule filter="ELSE" key="{pl-h}" label="Hamlet / Locality / Other" symbol="2"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="marker">
        <layer class="SimpleMarker" enabled="1" id="{pl-city}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="color" type="QString" value="40,40,40,255"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="name" type="QString" value="circle"></Option>
            <Option name="outline_color" type="QString" value="20,20,20,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.3"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="size" type="QString" value="2.5"></Option>
            <Option name="size_unit" type="QString" value="MM"></Option>
            <Option name="vertical_anchor_point" type="QString" value="1"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="marker">
        <layer class="SimpleMarker" enabled="1" id="{pl-village}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="color" type="QString" value="80,80,80,255"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="name" type="QString" value="circle"></Option>
            <Option name="outline_color" type="QString" value="40,40,40,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.2"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="size" type="QString" value="1.8"></Option>
            <Option name="size_unit" type="QString" value="MM"></Option>
            <Option name="vertical_anchor_point" type="QString" value="1"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="2" type="marker">
        <layer class="SimpleMarker" enabled="1" id="{pl-hamlet}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="color" type="QString" value="120,120,120,255"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="name" type="QString" value="circle"></Option>
            <Option name="outline_color" type="QString" value="60,60,60,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.15"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="size" type="QString" value="1.2"></Option>
            <Option name="size_unit" type="QString" value="MM"></Option>
            <Option name="vertical_anchor_point" type="QString" value="1"></Option>
          </Option>
        </layer>
      </symbol>
    </symbols>
  </renderer-v2>
  <labeling type="simple">
    <settings calloutType="simple">
      <text-style allowHtml="0" blendMode="0" capitalization="1004" fieldName="name" fontFamily="Arial" fontItalic="0" fontKerning="1" fontLetterSpacing="0" fontSize="10" fontSizeUnit="Point" fontStrikeout="0" fontUnderline="0" fontWeight="63" fontWordSpacing="0" forcedBold="0" forcedItalic="0" isExpression="0" multilineHeight="1" multilineHeightUnit="Percentage" namedStyle="SemiBold" previewBkgrdColor="255,255,255,255" textColor="20,20,20,255" textOpacity="1" textOrientation="horizontal" useSubstitutions="0">
        <text-buffer bufferBlendMode="0" bufferColor="250,250,250,255" bufferDraw="1" bufferJoinStyle="128" bufferNoFill="1" bufferOpacity="1" bufferSize="0.45" bufferSizeUnits="MM"></text-buffer>
      </text-style>
      <text-format addDirectionSymbol="0" decimals="3" multilineAlign="3" placeDirectionSymbol="0" plural="0" wrapChar=""></text-format>
      <placement allowDegradedPlacement="0" centroidInside="0" centroidWhole="0" dist="2" distUnits="MM" geometryGenerator="" geometryGeneratorEnabled="0" geometryGeneratorType="PointGeometry" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" lineAnchorClipping="0" lineAnchorPercent="0.5" lineAnchorTextPoint="CenterOfText" lineAnchorType="0" maxCurvedCharAngleIn="25" maxCurvedCharAngleOut="-25" offsetType="0" overlapHandling="PreventOverlap" overrunDistance="0" overrunDistanceUnit="MM" placement="6" placementFlags="10" polygonPlacementFlags="2" preserveRotation="1" priority="8" quadOffset="2" repeatDistance="0" repeatDistanceUnit="MM" rotationAngle="0" rotationUnit="AngleDegrees" xOffset="0" yOffset="0"></placement>
      <rendering drawLabels="1" fontLimitPixelSize="0" fontMaxPixelSize="10000" fontMinPixelSize="3" labelPerPart="0" maxNumLabels="2000" mergeLines="0" minFeatureSize="0" obstacle="1" obstacleFactor="1" obstacleType="1" scaleMax="10000000" scaleMin="0" scaleVisibility="0" upsidedownLabels="0" zIndex="0"></rendering>
      <dd_properties>
        <Option type="Map">
          <Option name="name" type="QString" value=""></Option>
          <Option name="properties" type="Map">
            <Option name="Size" type="Map">
              <Option name="active" type="bool" value="true"></Option>
              <Option name="expression" type="QString" value="case when &quot;place&quot; in ('city') then 12 when &quot;place&quot; in ('town') then 11 when &quot;place&quot; in ('village','suburb') then 10 when &quot;place&quot; in ('neighbourhood') then 9 when &quot;place&quot; in ('hamlet','locality') then 8 else 8 end"></Option>
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