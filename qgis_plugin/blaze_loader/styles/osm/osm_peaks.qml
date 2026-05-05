<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="1" maxScale="0" minScale="1e+08" readOnly="0" styleCategories="LayerConfiguration|Symbology|Labeling|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="singleSymbol">
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="marker">
        <layer class="SimpleMarker" enabled="1" id="{pk}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="color" type="QString" value="120,80,40,255"></Option>
            <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
            <Option name="name" type="QString" value="triangle"></Option>
            <Option name="outline_color" type="QString" value="60,40,20,255"></Option>
            <Option name="outline_style" type="QString" value="solid"></Option>
            <Option name="outline_width" type="QString" value="0.2"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="size" type="QString" value="3"></Option>
            <Option name="size_unit" type="QString" value="MM"></Option>
            <Option name="vertical_anchor_point" type="QString" value="1"></Option>
          </Option>
        </layer>
      </symbol>
    </symbols>
  </renderer-v2>
  <labeling type="simple">
    <settings calloutType="simple">
      <text-style fieldName="name" fontFamily="Arial" fontItalic="1" fontSize="9" fontWeight="50" textColor="80,40,10,255" textOpacity="1">
        <text-buffer bufferColor="255,255,255,200" bufferDraw="1" bufferSize="1" bufferSizeUnits="MM"></text-buffer>
      </text-style>
      <text-format addDirectionSymbol="0" decimals="3" multilineAlign="3" placeDirectionSymbol="0" plural="0" wrapChar=""></text-format>
      <placement allowDegradedPlacement="0" centroidInside="0" centroidWhole="0" dist="2" distUnits="MM" geometryGenerator="" geometryGeneratorEnabled="0" geometryGeneratorType="PointGeometry" labelOffsetMapUnitScale="3x:0,0,0,0,0,0" lineAnchorClipping="0" lineAnchorPercent="0.5" lineAnchorTextPoint="CenterOfText" lineAnchorType="0" maxCurvedCharAngleIn="25" maxCurvedCharAngleOut="-25" offsetType="0" overlapHandling="PreventOverlap" overrunDistance="0" overrunDistanceUnit="MM" placement="6" placementFlags="10" polygonPlacementFlags="2" preserveRotation="1" priority="5" quadOffset="2" repeatDistance="0" repeatDistanceUnit="MM" rotationAngle="0" rotationUnit="AngleDegrees" xOffset="0" yOffset="0"></placement>
      <rendering drawLabels="1" fontLimitPixelSize="0" labelPerPart="0" maxNumLabels="2000" minFeatureSize="0" obstacle="1" obstacleFactor="1" obstacleType="1" scaleMax="10000000" scaleMin="0" scaleVisibility="0" upsidedownLabels="0" zIndex="0"></rendering>
    </settings>
  </labeling>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
</qgis>