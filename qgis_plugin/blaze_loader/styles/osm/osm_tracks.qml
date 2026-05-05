<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="1" maxScale="0" minScale="1e+08" readOnly="0" styleCategories="LayerConfiguration|Symbology|Labeling|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{osm-tracks-root}">
      <rule filter="&quot;highway&quot; = 'track'" key="{tk-trk}" label="Vehicle track" symbol="0"></rule>
      <rule filter="&quot;highway&quot; IN ('path','bridleway','footway','pedestrian')" key="{tk-pth}" label="Footpath" symbol="1"></rule>
      <rule filter="&quot;highway&quot; = 'cycleway'" key="{tk-cyc}" label="Cycleway" symbol="2"></rule>
      <rule filter="&quot;highway&quot; = 'steps'" key="{tk-stp}" label="Steps" symbol="3"></rule>
      <rule filter="ELSE" key="{tk-oth}" label="Other" symbol="4"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="line">
        <layer class="SimpleLine" enabled="1" id="{tr-trk}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="0,0,0,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.4"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="0"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="line">
        <layer class="SimpleLine" enabled="1" id="{tr-pth}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="square"></Option>
            <Option name="customdash" type="QString" value="2;1"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="line_color" type="QString" value="0,0,0,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.3"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="1"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="2" type="line">
        <layer class="SimpleLine" enabled="1" id="{tr-cyc}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="square"></Option>
            <Option name="customdash" type="QString" value="2;1"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="line_color" type="QString" value="0,0,0,255"></Option>
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
        <layer class="SimpleLine" enabled="1" id="{tr-stp}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="square"></Option>
            <Option name="customdash" type="QString" value="0.6;0.6"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="line_color" type="QString" value="0,0,0,255"></Option>
            <Option name="line_style" type="QString" value="solid"></Option>
            <Option name="line_width" type="QString" value="0.6"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="1"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
          </Option>
        </layer>
      </symbol>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="4" type="line">
        <layer class="SimpleLine" enabled="1" id="{tr-oth}" locked="0" pass="0">
          <Option type="Map">
            <Option name="capstyle" type="QString" value="round"></Option>
            <Option name="joinstyle" type="QString" value="round"></Option>
            <Option name="line_color" type="QString" value="0,0,0,200"></Option>
            <Option name="line_style" type="QString" value="dot"></Option>
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
      <text-style allowHtml="0" capitalization="1004" fieldName="name" fontFamily="Arial" fontItalic="1" fontSize="8" fontSizeUnit="Point" fontWeight="50" textColor="0,0,0,255" textOpacity="0.9">
        <text-buffer bufferColor="255,255,255,255" bufferDraw="1" bufferNoFill="0" bufferOpacity="0.7" bufferSize="0.3" bufferSizeUnits="MM"></text-buffer>
      </text-style>
      <placement allowDegraded="1" maxCurvedCharAngleIn="40" maxCurvedCharAngleOut="-40" overlapHandling="PreventOverlap" placement="3" placementFlags="10" preserveRotation="1" priority="5" repeatDistance="150" repeatDistanceUnit="MM"></placement>
      <rendering drawLabels="1" obstacle="1" scaleMax="30000" scaleMin="0" scaleVisibility="1"></rendering>
    </settings>
  </labeling>
  <blendMode>0</blendMode>
  <featureBlendMode>0</featureBlendMode>
</qgis>