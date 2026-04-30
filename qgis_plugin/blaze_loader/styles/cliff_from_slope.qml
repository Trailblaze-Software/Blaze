<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" maxScale="0" minScale="1e+08" styleCategories="LayerConfiguration|Symbology|Symbology3D|Labeling|Fields|Forms|Actions|MapTips|Diagrams|AttributeTable|Rendering" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <mapTip enabled="1"></mapTip>
  <pipe-data-defined-properties>
    <Option type="Map">
      <Option name="name" type="QString" value=""></Option>
      <Option name="properties"></Option>
      <Option name="type" type="QString" value="collection"></Option>
    </Option>
  </pipe-data-defined-properties>
  <pipe>
    <provider>
      <resampling enabled="false" maxOversampling="2" zoomedInResamplingMethod="nearestNeighbour" zoomedOutResamplingMethod="nearestNeighbour"></resampling>
    </provider>
    <rasterrenderer alphaBand="-1" band="1" classificationMax="255" classificationMin="0" nodataColor="" opacity="1" type="singlebandpseudocolor">
      <rasterTransparency></rasterTransparency>
      <minMaxOrigin>
        <limits>MinMax</limits>
        <extent>WholeRaster</extent>
        <statAccuracy>Estimated</statAccuracy>
        <cumulativeCutLower>0.02</cumulativeCutLower>
        <cumulativeCutUpper>0.98</cumulativeCutUpper>
        <stdDevFactor>2</stdDevFactor>
      </minMaxOrigin>
      <rastershader>
        <colorrampshader classificationMode="1" clip="0" colorRampType="INTERPOLATED" labelPrecision="0" maximumValue="255" minimumValue="0">
          <colorramp name="[source]" type="gradient">
            <Option type="Map">
              <Option name="color1" type="QString" value="0,0,0,255"></Option>
              <Option name="color2" type="QString" value="255,255,255,0"></Option>
              <Option name="direction" type="QString" value="ccw"></Option>
              <Option name="discrete" type="QString" value="0"></Option>
              <Option name="rampType" type="QString" value="gradient"></Option>
              <Option name="spec" type="QString" value="rgb"></Option>
              <Option name="stops" type="QString" value="0.335337;0,0,0,255;rgb;ccw:0.479567;248,248,248,0;rgb;ccw"></Option>
            </Option>
          </colorramp>
          <item alpha="255" color="#000000" label="0" value="0"></item>
          <item alpha="255" color="#000000" label="33" value="33.15"></item>
          <item alpha="255" color="#000000" label="66" value="66.3"></item>
          <item alpha="158" color="#5e5e5e" label="99" value="99.45"></item>
          <item alpha="0" color="#f9f9f9" label="133" value="132.6"></item>
          <item alpha="0" color="#fafafa" label="166" value="165.75"></item>
          <item alpha="0" color="#fcfcfc" label="199" value="198.9"></item>
          <item alpha="0" color="#fefefe" label="230" value="229.5"></item>
          <item alpha="0" color="#ffffff" label="255" value="255"></item>
          <rampLegendSettings direction="0" maximumLabel="" minimumLabel="" orientation="2" prefix="" suffix="" useContinuousLegend="1">
            <numericFormat id="basic">
              <Option type="Map">
                <Option name="decimal_separator" type="invalid"></Option>
                <Option name="decimals" type="int" value="6"></Option>
                <Option name="rounding_type" type="int" value="0"></Option>
                <Option name="show_plus" type="bool" value="false"></Option>
                <Option name="show_thousand_separator" type="bool" value="true"></Option>
                <Option name="show_trailing_zeros" type="bool" value="false"></Option>
                <Option name="thousand_separator" type="invalid"></Option>
              </Option>
            </numericFormat>
          </rampLegendSettings>
        </colorrampshader>
      </rastershader>
    </rasterrenderer>
    <brightnesscontrast brightness="0" contrast="0" gamma="1"></brightnesscontrast>
    <huesaturation colorizeBlue="128" colorizeGreen="128" colorizeOn="0" colorizeRed="255" colorizeStrength="100" grayscaleMode="0" invertColors="0" saturation="0"></huesaturation>
    <rasterresampler maxOversampling="2"></rasterresampler>
    <resamplingStage>resamplingFilter</resamplingStage>
  </pipe>
  <blendMode>0</blendMode>
</qgis>