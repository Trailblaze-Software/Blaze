<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="1" maxScale="0" minScale="1e+08" readOnly="0" styleCategories="LayerConfiguration|Symbology|Labeling|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{emb-root}">
      <rule filter="&quot;man_made&quot; = 'cutline'" key="{emb-cut}" label="Cutline" symbol="0"></rule>
      <rule filter="ELSE" key="{emb-bank}" label="Embankment" symbol="1"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="line">
        <layer class="SimpleLine" enabled="1" id="{emb-cut-base}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="customdash" type="QString" value="2;1.2"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="187,100,25,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.25"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="use_custom_dash" type="QString" value="1"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="line">
        <layer class="SimpleLine" enabled="1" id="{emb-bank-base}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="187,100,25,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.3"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="use_custom_dash" type="QString" value="0"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
        <layer class="MarkerLine" enabled="1" id="{emb-bank-tags}" locked="0" pass="0">
          <Option type="Map">
            <Option name="average_angle_length" type="QString" value="4"></Option>
            <Option name="average_angle_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="average_angle_unit" type="QString" value="MM"></Option>
            <Option name="interval" type="QString" value="1.8"></Option>
            <Option name="interval_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="interval_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="offset_along_line" type="QString" value="0"></Option>
            <Option name="offset_along_line_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_along_line_unit" type="QString" value="MM"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="place_on_every_part" type="bool" value="true"></Option>
            <Option name="placements" type="QString" value="Interval"></Option>
            <Option name="ring_filter" type="QString" value="0"></Option>
            <Option name="rotate" type="QString" value="1"></Option>
          </Option>
          <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="@1@1" type="marker">
            <layer class="SimpleMarker" enabled="1" id="{emb-bank-tag-marker}" locked="0" pass="0">
              <Option type="Map">
                <Option name="angle" type="QString" value="0"></Option>
                <Option name="cap_style" type="QString" value="square"></Option>
                <Option name="color" type="QString" value="187,100,25,255"></Option>
                <Option name="horizontal_anchor_point" type="QString" value="2"></Option>
                <Option name="joinstyle" type="QString" value="bevel"></Option>
                <Option name="name" type="QString" value="line"></Option>
                <Option name="offset" type="QString" value="0,0"></Option>
                <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
                <Option name="offset_unit" type="QString" value="MM"></Option>
                <Option name="outline_color" type="QString" value="187,100,25,255"></Option>
                <Option name="outline_style" type="QString" value="solid"></Option>
                <Option name="outline_width" type="QString" value="0.22"></Option>
                <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
                <Option name="outline_width_unit" type="QString" value="MM"></Option>
                <Option name="scale_method" type="QString" value="diameter"></Option>
                <Option name="size" type="QString" value="1.0"></Option>
                <Option name="size_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
                <Option name="size_unit" type="QString" value="MM"></Option>
                <Option name="vertical_anchor_point" type="QString" value="1"></Option>
              </Option>
            </layer>
          </symbol>
        </layer>
      </symbol>
    </symbols>
  </renderer-v2>
  <labeling type="simple">
    <settings calloutType="simple">
      <text-style allowHtml="0" capitalization="1004" fieldName="name" fontFamily="Arial" fontSize="7" fontSizeUnit="Point" fontWeight="50" textColor="120,65,15,255" textOpacity="1">
        <text-buffer bufferColor="250,250,250,255" bufferDraw="1" bufferNoFill="1" bufferOpacity="1" bufferSize="0.3" bufferSizeUnits="MM"></text-buffer>
      </text-style>
      <placement maxCurvedCharAngleIn="40" maxCurvedCharAngleOut="-40" overlapHandling="PreventOverlap" placement="3" placementFlags="10" preserveRotation="1" priority="2" repeatDistance="400" repeatDistanceUnit="MM"></placement>
      <rendering drawLabels="1" obstacle="1" scaleMax="25000" scaleMin="0" scaleVisibility="1"></rendering>
    </settings>
  </labeling>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
</qgis>