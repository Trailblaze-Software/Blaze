<!DOCTYPE qgis PUBLIC "http://mrcc.com/qgis.dtd" "SYSTEM">
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="0" maxScale="0" minScale="100000000" readOnly="0" simplifyAlgorithm="0" simplifyDrawingHints="1" simplifyDrawingTol="1" simplifyLocal="1" simplifyMaxScale="1" styleCategories="LayerConfiguration|Symbology|Symbology3D|Labeling|Fields|Forms|Actions|MapTips|Diagrams|AttributeTable|Rendering" symbologyReferenceScale="-1" version="3.34.3-Prizren">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 enableorderby="0" forceraster="0" referencescale="-1" symbollevels="0" type="RuleRenderer">
    <rules key="{8ecc2b5d-e75d-4e22-bfc9-4fcac24df327}">
      <rule filter="classsubtype = 1" key="{c3301a52-196a-419d-80bb-f2a1f561452f}" label="Intertidal" symbol="0"></rule>
      <rule filter="classsubtype =2" key="{66159459-9065-4775-8754-9a98488403f5}" label="Subject to inundation" symbol="1"></rule>
      <rule filter="classsubtype = 3" key="{6f8d755b-6c60-4281-b544-e3a57cdc20b2}" label="Mangroves" symbol="2"></rule>
      <rule filter="classsubtype = 4" key="{edf5b7bc-db4a-4f7a-99b3-5cf6aa1ae715}" label="Reef" symbol="3"></rule>
      <rule filter="classsubtype = 5" key="{2b476709-9c22-4f7f-a78f-16a9277ca3ef}" label="Rock-Awash" symbol="4"></rule>
      <rule filter="classsubtype = 6" key="{0443436e-24fb-4595-a6d4-703ac1f5704e}" label="Rock-Inland" symbol="5"></rule>
      <rule filter="classsubtype = 7" key="{85984149-0eb5-4832-b528-2eab67dbef51}" label="Sand" symbol="6"></rule>
      <rule filter="classsubtype = 8" key="{5bf45169-eb34-4ffd-a843-1c50656e4232}" label="Samp-wet" symbol="7"></rule>
      <rule filter="classsubtype = 9" key="{af0d8fbf-2d91-4790-973c-83e6b052a890}" label="Samp-dry" symbol="8"></rule>
      <rule filter="classsubtype = 11" key="{38f53e68-0dec-4c44-ba68-133f8bd1e949}" label="Cliff" symbol="9"></rule>
      <rule filter="ELSE" key="{f4eb473e-37ea-4efc-b64d-8f1d742e75a5}" label="unknown" symbol="10"></rule>
    </rules>
    <symbols>
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="0" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{5f2a124f-8a7d-4f3a-9ca2-e0390f2c1624}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="0,0,255,255"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="35,35,35,255"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0.26"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="no"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
        <layer class="RasterFill" enabled="1" id="{3261e199-39b8-4c00-bfeb-6a23594eb343}" locked="0" pass="0">
          <Option type="Map">
            <Option name="alpha" type="QString" value="1"></Option>
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="coordinate_mode" type="QString" value="1"></Option>
            <Option name="imageFile" type="QString" value="base64:iVBORw0KGgoAAAANSUhEUgAAAJgAAACgCAYAAADw66XhAAAA4WlDQ1BzUkdCAAAYlWNgYDzNAARMDgwMuXklRUHuTgoRkVEKDEggMbm4gAE3YGRg+HYNRDIwXNYNLGHlx6MWG+AsAloIpD8AsUg6mM3IAmInQdgSIHZ5SUEJkK0DYicXFIHYQBcz8BSFBDkD2T5AtkI6EjsJiZ2SWpwMZOcA2fEIv+XPZ2Cw+MLAwDwRIZY0jYFhezsDg8QdhJjKQgYG/lYGhm2XEWKf/cH+ZRQ7VJJaUQIS8dN3ZChILEoESzODAjQtjYHh03IGBt5IBgbhCwwMXNEQd4ABazEwoEkMJ0IAAHLYNoSjH0ezAAAACXBIWXMAAB2HAAAdhwGP5fFlAAAFMElEQVR4nO3cS3LbMBCEYSb73ClH9518AGelpMyYJgFMz/SQ/7eMJQCUCq3Bo7JtL2/vH9vb+8eW7Wq/R69Tjbvq83AZx1m/F8f1M3RQwLDRGZSdNFdF979vb/a5qxNY/L2QYDDjnkSz46t+rlnqcS+2T4JBLLsG6LoadF3NVbXHKhLeTFYh4TVXViJUJXh1LbnrnwQDpKpnvKugz4UEQxKX/aWocahrmqzkU/WfNH4SDE2oVnNda6TqfUD1Lw77YECEJrXIU5FgSOa+c57Vr3qHPnu1rB7HwetJMIi5noGp9uWQigTDTVXd/1rdh1Lv360md/UJww4JhiJRO85PqZVckmW0f/G4SDCYqzpDq06EKO4112L7JBjE3Pevqs4aq29DqNpPXr2TYDDRpeZxG6fbeFYNPg8JhiaqapOuok8cqmrVEyQYirmvjqrONLPG0RwJhmRRO+nRyaRKOnVSqfev1LUaO/nwdrfaoep53HfaVU7GS4LBRFTNlT1Do88io3RLqkkkGJpTJ1uX9626uipUrSonn5sEQzK3WqrLjnrXGjXabvwkGMSiZ4zbTFXVLncV/P2RYCjmOoOrx1VVc50lr1kSk2BoLnsVqJqprqtTdfvcpoC3qsTIWm2q70vNvq+6hox28DwkGMy4zDyXcZzJTnj1mePg85BgaC6rNsk+kchO0C6JvUOCQerH4V9es+X3r+PXZLx+tN3R96+2z3i+bZcEg1jT3/by2xhRr49i2i8Jhua6rSJNk2D4dSZIMJhyrYFG3x+VsKp7WNGJvvp5sJMPb3dJpqj3u98vc6nJuE0BKLnM9FVZZ65BtRgJhmLq+0VR/V29FxU1ThX3mm8QCQapfyfk2af4d3H0uY3++2w/q+2qcJsCvdz9zFFdw2StDkf7W2yHBANCuKwSr4o+Qy1CgiFZ9K0A9fuixquu7arPXouQYDDXdGZNc91pz7rnNdgOCYabi66Vos9In5bQwUgwJFPVAndPAtVqOXuHP7g9EgwmshKoasa6rg5H2zNLPBIM+JZLslbfDpkl7p8Eg1Tc7cfom537v0fd2HS7+XmV6iasCjdakau6Fpjlcvtjtr3V8ZuvfkkwFMtONpdV4ejru/wCJJ/UkGAwUzVTuySEC5PPiwRDE6OroagZln0/bFR07WZ21niGBIOU3/9N4TKOF7fxHHE76WAnHx5MViNpNdtqO1E1p2q/Kro9brQCkVwS11Xy50OCQer/lcLoPa3of19936zq1eJo/+6fA6tIYIXbqnO2PZeaklUkPLnfc3I9a1Sfsa4y+V5JMJiK2snmftlnXWu0AyQYsG2bvtbKTgL3cQaNjwRDMvPf9GFRSTFbQ7rdilg1OB4SDCayVo1Z+1puyfCiXkVymwLAOrcEFY2HBINY9UyKXoWpa7Oqk4qqWmvxeUkwFKlaHapU9/9QJBgexq3mUomq2czPNEkw3FSXmmg1abo8515QTU2CQSx63+fq32fdPTnONHsuEgwPcfX+VXQ/2e1nJ1BxfyQYbqI6OdzavdpPdf+L4yHBYKK6tnDbsXZbzZquLkkwJLn76uaM23jUop/3oD0SDM2paxWX5LnZLYio/kgwFHv66tHtvlhVO5NIMEDi4ftTf0XXjpxF4l6qd9Kj23VLJLfx7JBgEKueAUk7ynKq1e7q8xSvwkkwFFmdWVUzr6rdq/1U/2Lsib8nEgxI4ZYsV5mPmwQDPsnep8qqpVT9FL+fBIPY7MypXmWOYvX4NfGtDRIMD1WdOF2Yj58Eg9QfHk42oCDWV4oAAAAASUVORK5CYII="></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="width" type="QString" value="20"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="width_unit" type="QString" value="MM"></Option>
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
      <symbol alpha="0.559" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="1" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{f0e977b2-2539-4f9e-97e0-f23eea4c86f8}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="0,0,255,255"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="35,35,35,255"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0.26"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="no"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
        <layer class="RasterFill" enabled="1" id="{af088dba-a7e6-4a7e-a9ec-a7e999f49bee}" locked="0" pass="0">
          <Option type="Map">
            <Option name="alpha" type="QString" value="1"></Option>
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="coordinate_mode" type="QString" value="1"></Option>
            <Option name="imageFile" type="QString" value="base64:iVBORw0KGgoAAAANSUhEUgAAABIAAAAICAYAAAD0g6+qAAAA4WlDQ1BzUkdCAAAYlWNgYDzNAARMDgwMuXklRUHuTgoRkVEKDEggMbm4gAE3YGRg+HYNRDIwXNYNLGHlx6MWG+AsAloIpD8AsUg6mM3IAmInQdgSIHZ5SUEJkK0DYicXFIHYQBcz8BSFBDkD2T5AtkI6EjsJiZ2SWpwMZOcA2fEIv+XPZ2Cw+MLAwDwRIZY0jYFhezsDg8QdhJjKQgYG/lYGhm2XEWKf/cH+ZRQ7VJJaUQIS8dN3ZChILEoESzODAjQtjYHh03IGBt5IBgbhCwwMXNEQd4ABazEwoEkMJ0IAAHLYNoSjH0ezAAAACXBIWXMAAB2HAAAdhwGP5fFlAAAAaElEQVQokc3OPQ5AQACE0W9iC1oRZ3ADnVqtoFY5iPNwtc0mNCTWAfxkKzH1zMvA3yImWyFGILpvyLFvHW2+vEEGkQHFI+S9I4lj4BVSyG0AZtsDzXXjV6TBBEP4ElRfIa0cSsOdr3ICQzwTfEp1rzQAAAAASUVORK5CYII="></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="width" type="QString" value="2"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="width_unit" type="QString" value="MM"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="10" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{f266f749-4b48-4eb4-845b-a3c424ff2e2d}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="255,0,0,255"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="2" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SVGFill" enabled="1" id="{198a42f6-8cb8-4486-82dd-f4d3fbb8d752}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="color" type="QString" value="148,228,72,255"></Option>
            <Option name="outline_color" type="QString" value="148,228,72,255"></Option>
            <Option name="outline_width" type="QString" value="0.26"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="parameters"></Option>
            <Option name="pattern_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="pattern_width_unit" type="QString" value="MM"></Option>
            <Option name="svgFile" type="QString" value="symbol/landuse_scrub.svg"></Option>
            <Option name="svg_outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="svg_outline_width_unit" type="QString" value="MM"></Option>
            <Option name="width" type="QString" value="2"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="3" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{79b38b3e-7780-475a-98a5-e36d32d46d76}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="0,0,255,255"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="35,35,35,255"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0.26"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="no"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
        <layer class="RasterFill" enabled="1" id="{36214a07-ee3a-48a4-af47-c2dcdeedadd2}" locked="0" pass="0">
          <Option type="Map">
            <Option name="alpha" type="QString" value="1"></Option>
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="coordinate_mode" type="QString" value="1"></Option>
            <Option name="imageFile" type="QString" value="base64:iVBORw0KGgoAAAANSUhEUgAAAIQAAAB6CAYAAAB+3PvOAAAA4WlDQ1BzUkdCAAAYlWNgYDzNAARMDgwMuXklRUHuTgoRkVEKDEggMbm4gAE3YGRg+HYNRDIwXNYNLGHlx6MWG+AsAloIpD8AsUg6mM3IAmInQdgSIHZ5SUEJkK0DYicXFIHYQBcz8BSFBDkD2T5AtkI6EjsJiZ2SWpwMZOcA2fEIv+XPZ2Cw+MLAwDwRIZY0jYFhezsDg8QdhJjKQgYG/lYGhm2XEWKf/cH+ZRQ7VJJaUQIS8dN3ZChILEoESzODAjQtjYHh03IGBt5IBgbhCwwMXNEQd4ABazEwoEkMJ0IAAHLYNoSjH0ezAAAACXBIWXMAAB2HAAAdhwGP5fFlAAADwElEQVR4nO2dSW7jMBBFnT5Gzpbj9dlyjfTGDmACag41fVLvLWOJLAmuz5rgPB4vvr5/Hl/fP49sRve9ui7K7qr3UWzHn6yN4BRmv6HZnjyK9/7teqvPXa1wzXUoBBhR9/RV+6qfaxVnu1EIaMg+w3bNFtSzMKf1UAgYxFofyLLDKwtaxUsJRZQMhQB4Y9fsIggUAi5Qye+97Ig+k7OUJWr/i/tRCAgiKtrf9YyvrsMsrodCwGEEnaV3BYWADuqVwax9oyuQ2dnUoB0oBDSI1NCn1+PsDwGFABGq5h+sdYDo+olVGel2Qg5eFbW7nPXqMQ9ZBtRQVYOv9jgvimOGFhQCGtTrB94VR+fKnpud3izaiULAImoecIWanWr2dEAh4I0Pt5VeXvD382Po73en915m36f1PT/vRyFgkugzUHXi6aYVWRQCOnhVCqvqB7P2RCtB9LyJc70EhYCGQ86+X6qeR3XybBIUAhbxihmyPSBqcsmKqDKjEJBM9Qyiyn1WRrMGY9aBQkAHtVhgl4rhrjFWAwoBDdkTU1H7zu5jPXsPBYWASVQ9pNquqpihp2xGpUMhIJnsLEFlPmKXfalDwP+p8sisbMR5XmB6H6/rk0AhwIjKN1vFjh7ZCkqWAXuRdbZmV1x3meuYBIWAQaI9uzrL8Fr/MHtQCGjYJVpvqe6Wel3vhdO+KAQks1uWoe7hwfahEOCE6hk+e7+XgkVNXHkrZmc9FAI6nOL5Xverz1c424dCwE3Ztd7SEtyzQSFgEmv0HB3FX32+S4Uxyw7mIcCGiofsRlZdIqlLikJAEKf3LKIVNDh7GP0chYCbsluMVDRZhUJAh+zo2Hqfl73RsUl172YQFALesP8Pi9e39i7/DyPqea3r9u4f/ByFADG8z3rvHstu2YkRFAI6REXDp3uaeI9idD0UAhbZZdZydT312cnR9Yz7oRBwGCrKVd29XYWZSsjBe3LIOiM5a6c6SQqEQsAFp3mOypm+GnsUZUcoBEySrRwqWcPs9bsoLJVKiKXKE3bxQBUW3xcKAUF41yGs+87uU9XLqJr9vFgPhYALVM5oFTteqNlzhZOdKARMouIhar2M6JgpanKtAwoBh6OiaKpQqQQb3t05r3mI0ftWqVaW6nrEExQCboJaVrK6XrJyoRDQoN7nV+1VZMc4syy+NxQCnMjKNqJQ8eSW4hgDhYBNiY4VshVD1E4UAjqonq2reHmid8V11Y5gUAhYpLqHsXpd1P1RRGcZdDthhnv8tqQiLy9V+X3Ppz0oBLzxD+xjSNLTCW4cAAAAAElFTkSuQmCC"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="width" type="QString" value="17"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="width_unit" type="QString" value="MM"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="4" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{9d004031-aebe-4f71-9954-97832d0ec523}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="0,0,255,255"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="35,35,35,255"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0.26"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="no"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
        <layer class="RasterFill" enabled="1" id="{0128343c-48b8-456e-8e18-506159faeedd}" locked="0" pass="0">
          <Option type="Map">
            <Option name="alpha" type="QString" value="1"></Option>
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="coordinate_mode" type="QString" value="1"></Option>
            <Option name="imageFile" type="QString" value="base64:iVBORw0KGgoAAAANSUhEUgAAAIQAAAB6CAYAAAB+3PvOAAAA4WlDQ1BzUkdCAAAYlWNgYDzNAARMDgwMuXklRUHuTgoRkVEKDEggMbm4gAE3YGRg+HYNRDIwXNYNLGHlx6MWG+AsAloIpD8AsUg6mM3IAmInQdgSIHZ5SUEJkK0DYicXFIHYQBcz8BSFBDkD2T5AtkI6EjsJiZ2SWpwMZOcA2fEIv+XPZ2Cw+MLAwDwRIZY0jYFhezsDg8QdhJjKQgYG/lYGhm2XEWKf/cH+ZRQ7VJJaUQIS8dN3ZChILEoESzODAjQtjYHh03IGBt5IBgbhCwwMXNEQd4ABazEwoEkMJ0IAAHLYNoSjH0ezAAAACXBIWXMAAB2HAAAdhwGP5fFlAAADyklEQVR4nO2dyXHcMBBFJcemgHRzDLopIOcmX8wqkzUkAfT2Ab531JBAkzX90VuN3t7+8fX58fP1+fHzlkzrvmfXRdld9T6q7fiVtREsQu83NNuTW/He/7je6HNXK9zxOhQCbKh7+qh91c81irfdKATsyT7DZs0W1LMwr/VQCGjDWh/IssMrCxrFSwlVlAyFAPifWbOLKFAIeI1Kfu9lR/SZnKUsUfuf3Y9CQAxR0f6sZ3x1HWZ0PRQC1iLqLH0qKARco14ZzNo3ugKZnU212oFCwB6VGnrvepz9MaAQoEHV/IO1DhBdP7EqI91OyMGrovaUs1495iHLgBqqavDVHudFdcxwBIWAPer1A++Ko3dlz8tOb0btRCFgDDUPOEPNTjV77kAhYMe710KbF/z+/vPe8venc/deet+n9T1v96MQ0Ef0Gag68fTUiiwKAdd4VQqr6ge99kQrQfS8iXe9BIWAPaucfRtVz6M6edYLCgFjeMUM2R4QNblkpVoJzkAhIJfqGUSV+6y0Zg3WrAOFgGvUYoFZKoazxlhHUAjYkz0xFbVv7z7Ws3dVUAjoQ9VDqu2qihnulM2qdCgE5JKdJajMR8yyL3UIuKbKI7OyEe95AS87q2OgM1AIsKHyzVax445sBSXLgLnIOluzK66zzHX0gkJAG9GeXZ1leK2/mj0oBOyZJVo/Ut0t9breC699UQjIZbYsQ93Do+1DIcAH1TO8934vBYuauPJWzLv1UAi4ZhXP97pffb7C2z4UAp7JrPWWI9E9GxQC+rBGz9FR/Nnns1QYs+xgHgJsqHjIbGTVJbK6pCgExLB6zyJaQaOzh9bPUQh4JrPFSFWTVSgEXJMdHVvv87I3Ojap7t20gkLADvP/sNi+tU/5fxhRz2td9+7+1s9RCNDC+6z37rHMlp1YQSHgmqhoeHVPU+9RtK6HQsAYs8xajq5XPYfgtZ51PxQC1kJFuaq7t6MwUwk5eE8OWWcke+1UJ0uBUAh4zWqeo3Kmj8YeVdkRCgF9ZCuHStbQe/0sCkulEmKp8oRZPFCF0feFQkAM3nUI6769+1T1MqpmP8/WQyHgNSpntIodG2r2nOFlJwoBfah4iFovIzpmippcuwOFgLVRUTRVqFSCDe/unNc8ROt9o1QrS3U9YgOFgGeglpWMrpetXCgE7FHv86v2KrJjnF5G3xsKAT5kZRtRqHjykeoYA4WAOYmOFbIVQ9VOFAKuUT1bR/HyRO+K66gd0aAQMEZ1D2P0uqj7o4jOMuh2QheP+G1JRTYvVfl9z80eFAJ2/AVBNkT7PfklLgAAAABJRU5ErkJggg=="></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="width" type="QString" value="17"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="width_unit" type="QString" value="MM"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="5" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{4c27dbd2-8de5-4540-9689-ac3f00f1f7c8}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="0,0,255,255"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="35,35,35,255"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0.26"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="no"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
        <layer class="RasterFill" enabled="1" id="{daaef6c2-f169-4761-bc94-6ad7c672f06a}" locked="0" pass="0">
          <Option type="Map">
            <Option name="alpha" type="QString" value="1"></Option>
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="coordinate_mode" type="QString" value="1"></Option>
            <Option name="imageFile" type="QString" value="base64:iVBORw0KGgoAAAANSUhEUgAAAIQAAAB6CAYAAAB+3PvOAAAA4WlDQ1BzUkdCAAAYlWNgYDzNAARMDgwMuXklRUHuTgoRkVEKDEggMbm4gAE3YGRg+HYNRDIwXNYNLGHlx6MWG+AsAloIpD8AsUg6mM3IAmInQdgSIHZ5SUEJkK0DYicXFIHYQBcz8BSFBDkD2T5AtkI6EjsJiZ2SWpwMZOcA2fEIv+XPZ2Cw+MLAwDwRIZY0jYFhezsDg8QdhJjKQgYG/lYGhm2XEWKf/cH+ZRQ7VJJaUQIS8dN3ZChILEoESzODAjQtjYHh03IGBt5IBgbhCwwMXNEQd4ABazEwoEkMJ0IAAHLYNoSjH0ezAAAACXBIWXMAAB2HAAAdhwGP5fFlAAADwElEQVR4nO2dW26kMBBFyWw568iaMz+DNKAGbNfr2pzzmQa7QF3X9VJn2/7xvW2/39v2uyXTuu/VdVF2V72Pajv+ZG0Ei9D7Dc325Fa89z+vN/rc1Qp3vg6FABvqnj5qX/VzjeJtNwoBR7LPsFmzBfUszGs9FALasNYHsuzwyoJG8VJCFSVDIQD+Z9bsIgoUAj6jkt972RF9JmcpS9T+V/ejEBBDVLQ/6xlfXYcZXQ+FgLWIOkvfCgoB96hXBrP2ja5AZmdTrXagEHBEpYbeux5nfwwoBGhQNf9grQNE10+syki3E3Lwqqi95axXj3nIMqCGqhp8tcd5UR0znEEh4Ih6/cC74uhd2fOy05tRO1EIGEPNA65Qs1PNnidQCDjw5bXQ7gU/pzWv/v52nt5L7/u0vuf9fhQC+og+A1Unnt5akUUh4B6vSmFV/aDXnmgliJ438a6XoBBwZJWzb6fqeVQnz3pBIWAMr5gh2wOiJpesVCvBFSgE5FI9g6hyn5XWrMGadaAQcI9aLDBLxXDWGOsMCgFHsiemovbt3cd69q4KCgF9qHpItV1VMcOTslmVDoWAXLKzBJX5iFn2pQ4B91R5ZFY24j0v4GVndQx0BQoBNlS+2Sp2PJGtoGQZMBdZZ2t2xXWWuY5eUAhoI9qzq7MMr/VXsweFgCOzROtnqrulXtd74bUvCgG5zJZlqHt4tH0oBPigeob33u+lYFETV96K+bQeCgH3rOL5Xverz1d424dCwDuZtd5yJrpng0JAH9boOTqKv/p8lgpjlh3MQ4ANFQ+Zjay6RFaXFIWAGFbvWUQraHT20Po5CgHvZLYYqWqyCoWAe7KjY+t9XvZGxybVvZtWUAg4YP4fFvu39i3/DyPqea3rPt3f+jkKAVp4n/XePZbZshMrKATcExUNr+5p6j2K1vVQCBhjllnL0fWq5xC81rPuh0LAWqgoV3X3dhRmKiEH78kh64xkr53qZCkQCgGfWc1zVM700dijKjtCIaCPbOVQyRp6r59FYalUQixVnjCLB6ow+r5QCIjBuw5h3bd3n6peRtXs59V6KAR8RuWMVrFjR82eK7zsRCGgDxUPUetlRMdMUZNrT6AQsDYqiqYKlUqw4d2d85qHaL1vlGplqa5H7KAQ8A7UspLR9bKVC4WAI+p9ftVeRXaM08voe0MhwIesbCMKFU8+Ux1joBAwJ9GxQrZiqNqJQsA9qmfrKF6e6F1xHbUjGhQCxqjuYYxeF3V/FNFZBt1O6OIVvy2pyO6lKr/vuduDQsCBv673rOD9wZQiAAAAAElFTkSuQmCC"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="width" type="QString" value="17"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="width_unit" type="QString" value="MM"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="6" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="PointPatternFill" enabled="1" id="{f3a470da-acd0-4c38-b020-3a4966f1ec98}" locked="0" pass="0">
          <Option type="Map">
            <Option name="angle" type="double" value="0"></Option>
            <Option name="clip_mode" type="QString" value="shape"></Option>
            <Option name="coordinate_reference" type="QString" value="feature"></Option>
            <Option name="displacement_x" type="QString" value="0.5"></Option>
            <Option name="displacement_x_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="displacement_x_unit" type="QString" value="MM"></Option>
            <Option name="displacement_y" type="QString" value="0.5"></Option>
            <Option name="displacement_y_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="displacement_y_unit" type="QString" value="MM"></Option>
            <Option name="distance_x" type="QString" value="1.2"></Option>
            <Option name="distance_x_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="distance_x_unit" type="QString" value="MM"></Option>
            <Option name="distance_y" type="QString" value="1.2"></Option>
            <Option name="distance_y_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="distance_y_unit" type="QString" value="MM"></Option>
            <Option name="offset_x" type="QString" value="0"></Option>
            <Option name="offset_x_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_x_unit" type="QString" value="MM"></Option>
            <Option name="offset_y" type="QString" value="0"></Option>
            <Option name="offset_y_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_y_unit" type="QString" value="MM"></Option>
            <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="random_deviation_x" type="QString" value="0"></Option>
            <Option name="random_deviation_x_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="random_deviation_x_unit" type="QString" value="MM"></Option>
            <Option name="random_deviation_y" type="QString" value="0"></Option>
            <Option name="random_deviation_y_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="random_deviation_y_unit" type="QString" value="MM"></Option>
            <Option name="seed" type="QString" value="634708326"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
          <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="@6@0" type="marker">
            <data_defined_properties>
              <Option type="Map">
                <Option name="name" type="QString" value=""></Option>
                <Option name="properties"></Option>
                <Option name="type" type="QString" value="collection"></Option>
              </Option>
            </data_defined_properties>
            <layer class="SimpleMarker" enabled="1" id="{02f1c90c-2bf4-465b-a324-6df9220177ef}" locked="0" pass="0">
              <Option type="Map">
                <Option name="angle" type="QString" value="0"></Option>
                <Option name="cap_style" type="QString" value="square"></Option>
                <Option name="color" type="QString" value="224,165,0,255"></Option>
                <Option name="horizontal_anchor_point" type="QString" value="1"></Option>
                <Option name="joinstyle" type="QString" value="bevel"></Option>
                <Option name="name" type="QString" value="circle"></Option>
                <Option name="offset" type="QString" value="0,0"></Option>
                <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
                <Option name="offset_unit" type="QString" value="MM"></Option>
                <Option name="outline_color" type="QString" value="0,0,0,255"></Option>
                <Option name="outline_style" type="QString" value="no"></Option>
                <Option name="outline_width" type="QString" value="0.2"></Option>
                <Option name="outline_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
                <Option name="outline_width_unit" type="QString" value="MM"></Option>
                <Option name="scale_method" type="QString" value="diameter"></Option>
                <Option name="size" type="QString" value="0.6"></Option>
                <Option name="size_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
                <Option name="size_unit" type="QString" value="MM"></Option>
                <Option name="vertical_anchor_point" type="QString" value="1"></Option>
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
        </layer>
        <layer class="SimpleLine" enabled="1" id="{acb22129-6aaa-4e9a-a6d4-6091a406344a}" locked="0" pass="0">
          <Option type="Map">
            <Option name="align_dash_pattern" type="QString" value="0"></Option>
            <Option name="capstyle" type="QString" value="square"></Option>
            <Option name="customdash" type="QString" value="5;2"></Option>
            <Option name="customdash_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="customdash_unit" type="QString" value="MM"></Option>
            <Option name="dash_pattern_offset" type="QString" value="0"></Option>
            <Option name="dash_pattern_offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="dash_pattern_offset_unit" type="QString" value="MM"></Option>
            <Option name="draw_inside_polygon" type="QString" value="0"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="line_color" type="QString" value="0,0,0,255"></Option>
            <Option name="line_style" type="QString" value="no"></Option>
            <Option name="line_width" type="QString" value="0.1"></Option>
            <Option name="line_width_unit" type="QString" value="MM"></Option>
            <Option name="offset" type="QString" value="0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="ring_filter" type="QString" value="0"></Option>
            <Option name="trim_distance_end" type="QString" value="0"></Option>
            <Option name="trim_distance_end_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="trim_distance_end_unit" type="QString" value="MM"></Option>
            <Option name="trim_distance_start" type="QString" value="0"></Option>
            <Option name="trim_distance_start_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="trim_distance_start_unit" type="QString" value="MM"></Option>
            <Option name="tweak_dash_pattern_on_corners" type="QString" value="0"></Option>
            <Option name="use_custom_dash" type="QString" value="0"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="7" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{7578740b-7846-4fe7-9b30-99ca8d55f3cf}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="0,0,255,255"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="35,35,35,255"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0.26"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="no"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
        <layer class="RasterFill" enabled="1" id="{56b592f8-fde0-4abb-adb5-45da1f615278}" locked="0" pass="0">
          <Option type="Map">
            <Option name="alpha" type="QString" value="1"></Option>
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="coordinate_mode" type="QString" value="1"></Option>
            <Option name="imageFile" type="QString" value="base64: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"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="width" type="QString" value="17"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="width_unit" type="QString" value="MM"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="8" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{2bbdf748-df7a-4a21-8b17-6f3f64f084d7}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="0,0,255,255"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="35,35,35,255"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0.26"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="no"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
        <layer class="RasterFill" enabled="1" id="{f571b334-a330-4356-bb03-d6bd61ad8c81}" locked="0" pass="0">
          <Option type="Map">
            <Option name="alpha" type="QString" value="1"></Option>
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="coordinate_mode" type="QString" value="1"></Option>
            <Option name="imageFile" type="QString" value="base64:iVBORw0KGgoAAAANSUhEUgAAAH4AAAB+CAYAAADiI6WIAAAA4WlDQ1BzUkdCAAAYlWNgYDzNAARMDgwMuXklRUHuTgoRkVEKDEggMbm4gAE3YGRg+HYNRDIwXNYNLGHlx6MWG+AsAloIpD8AsUg6mM3IAmInQdgSIHZ5SUEJkK0DYicXFIHYQBcz8BSFBDkD2T5AtkI6EjsJiZ2SWpwMZOcA2fEIv+XPZ2Cw+MLAwDwRIZY0jYFhezsDg8QdhJjKQgYG/lYGhm2XEWKf/cH+ZRQ7VJJaUQIS8dN3ZChILEoESzODAjQtjYHh03IGBt5IBgbhCwwMXNEQd4ABazEwoEkMJ0IAAHLYNoSjH0ezAAAACXBIWXMAAB2HAAAdhwGP5fFlAAAFcElEQVR4nO2dYY7cIAyFabWH7DHmKD3G3HL6p2lZhME2xhh4n7QSE5HEkORhbJJNaQPer/RZbcMIlP3l9vcrfWrbJMes1XvqPuX3K32+eKaDEX79Tj+ezv/1O/0YOZb0OHm9vPxzxAhwODW5yMuUZEklWiprOw4BLXmnytS+W0LdGJwGS/bl2sIpW10MzsXu3QSjQOrBGjSe7W4yyFUUbXlbehey1eAZMngDkPpLIefx+XyxV35+1/blGPHUe7/SRzLPldaPAtWHD60+t7JhWadJbixNWXveHE0dbX9YUnsg84fk/UofSD0AYBFUwMRjSnPb7ABSfyn/BvuUaEcg30Fb5zRmZNtGHM8RG4CA3YcGSP2ldC/8zne1BdIne3clUGPVaGmqlOPtS+u0tksSRRFvBEg9sCHi3S3FKjXck33pMWcon5hRqdyB1oXprZCJ3l5I/aV81QIxZUCgtl2TDeNsj4QmSLJDu8RYjXO9cU9yzF65NvZx2zijHAVI/aWI5agmZeVwQcXqj5TBQSxi9c/v2jGnGawp7wRn+Oh5+BGB1AMaiTOlKQN/wo61HL+hvHFq26XjXOmX7EzZD/lvSD2QIY0V7yLrGjupWIE0hgCc0AagPOyafQ5I/aWwLjzk6jymfgOnF1kqt3vTWw0828OXHt/KnvcLr1CB6Ow+3FD2jziYI31y3efOtImQ0RcYrF8yGT0OpB70aQVnrAIYUlnbcQjoyXsr8LVje6tQjeA0mLuvxAbPaKNHapvqN0g9WIfWs10pgxIFKusjtV3QupC9Bh/RAY5A6i9F9LasxquXGPPMlTWzAKvQqqdyUH24ytl0ZcSzHe0gyU12VKcnSD0AdxFuUaFn/Fx7LqqO1o4VQOovhXyD1fpp2OVJWElNOfIZC3f2gj6/BM0sBlJ/Kfe+7M/kVOduipFWN0rP59jdt6DGb+pGam2XfoIWUg/sOCZdeDBDT7w2oTJyTmADpP5mWqnAsh5nuyRF660AvcUdZWr0FJUaTu9yLqq2zsgxpWsFVuG5vqEFpB7IaD2RPamM8vSdCFdR1K9Qnfy5z13srFF+dpYqQ+pBn5Xr4zyJ5AyOQs1cQkuZRaz++d07T++ToNxcuMR+ymaPHASk/lLMs2c5luvjZjLriQcbIJmOWp5rFZB60Gf1XXorVgqRH2f6N3Ckq0m84Kx+yW2j6u9EbjOkHnzHIsM2yy7P83lC9ad0Owc88X+x9uo50cnasEJNjWv7PvVbx6TAhQd1VsXYuU+Jlz0Uo32yamFLCCRjGLfBEYIkErzXN0DqL+XbPN4im3TCd15XcPLCFhY9KWuNqTvL+4xyC0g9qBPBq7e808tzSJxHzwzeDHI73d6WbY27Pd9itDyjjTPw9Ksg9QAAAs9xrBy/8z+qjpdtVqy0GVIPviPxVHd82iJgNRPR1AEFs3IBFokWrs0cGyD1l0KuudPOKak6z28bs/to57hlfWr/SPEBri2RbGYj8epnjZ0WzJiVaGZAkHpwN7d5wkPr6kfG+Np2D3/AM+e9an0DB0g9OBNKvjlzaO6+O7B7eFuFNngyY4VPlFwDpB7syUhOQbKiZqU8Su3htMvsf9KMNe3/+WvHaq3e0ZwjpbNX8nCA1IMzkYZ4Z4WEe7bN5kqvPgLR1jdA6i9FFLbMsXKCcsetPI/28yQtZzBa6HQVRzUmMtHWN0DqwVzgScYCT7wBO+byceEv5UuyUIKDNLxqGY5dxcxwcnmeEAtbKIkbSXFqZZMbcYuWgFkFpB7osVrUEPnJQ6yboHchWx23o1c8A89+gNRfSterl76ec4tXz+mf1XH+1sIW8/9J4/HtmpGVQl6riVpQ55JuHwFSfyl/AAyljjn3OlTJAAAAAElFTkSuQmCC"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="width" type="QString" value="17"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="width_unit" type="QString" value="MM"></Option>
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
      <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="9" type="fill">
        <data_defined_properties>
          <Option type="Map">
            <Option name="name" type="QString" value=""></Option>
            <Option name="properties"></Option>
            <Option name="type" type="QString" value="collection"></Option>
          </Option>
        </data_defined_properties>
        <layer class="SimpleFill" enabled="1" id="{b05b9b91-b07f-42f5-91ea-1553af7425b9}" locked="0" pass="0">
          <Option type="Map">
            <Option name="border_width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="color" type="QString" value="0,0,255,255"></Option>
            <Option name="joinstyle" type="QString" value="bevel"></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="outline_color" type="QString" value="35,35,35,255"></Option>
            <Option name="outline_style" type="QString" value="no"></Option>
            <Option name="outline_width" type="QString" value="0.26"></Option>
            <Option name="outline_width_unit" type="QString" value="MM"></Option>
            <Option name="style" type="QString" value="no"></Option>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
        </layer>
        <layer class="RasterFill" enabled="1" id="{51d74b2d-e5ba-40ad-8641-e5d56698621a}" locked="0" pass="0">
          <Option type="Map">
            <Option name="alpha" type="QString" value="1"></Option>
            <Option name="angle" type="QString" value="0"></Option>
            <Option name="coordinate_mode" type="QString" value="1"></Option>
            <Option name="imageFile" type="QString" value="base64:iVBORw0KGgoAAAANSUhEUgAAAIQAAAB6CAYAAAB+3PvOAAAA4WlDQ1BzUkdCAAAYlWNgYDzNAARMDgwMuXklRUHuTgoRkVEKDEggMbm4gAE3YGRg+HYNRDIwXNYNLGHlx6MWG+AsAloIpD8AsUg6mM3IAmInQdgSIHZ5SUEJkK0DYicXFIHYQBcz8BSFBDkD2T5AtkI6EjsJiZ2SWpwMZOcA2fEIv+XPZ2Cw+MLAwDwRIZY0jYFhezsDg8QdhJjKQgYG/lYGhm2XEWKf/cH+ZRQ7VJJaUQIS8dN3ZChILEoESzODAjQtjYHh03IGBt5IBgbhCwwMXNEQd4ABazEwoEkMJ0IAAHLYNoSjH0ezAAAACXBIWXMAAB2HAAAdhwGP5fFlAAADwklEQVR4nO2dW46jMBBF07PALDYb7PkZpAEFsF2va3POZwfsAqWu66X06/WP9/v9+36/f1/JtO57dl2U3VXvo9qOP1kbwSL0fkOzPbkV7/2P640+d7XCHa9DIcCGuqeP2lf9XKN4241CwJ7sM2zWbEE9C/NaD4WANqz1gSw7vLKgUbyUUEXJUAiA/5k1u4gChYDvqOT3XnZEn8lZyhK1/9n9KATEEBXtz3rGV9dhRtdDIWAtos7Sp4JCwDXqlcGsfaMrkNnZVKsdKATsUamh967H2R8DCgEaVM0/WOsA0fUTqzLS7YQcvCpqTznr1WMesgyooaoGX+1xXlTHDEdQCNijXj/wrjh6V/a87PRm1E4UAsZQ84Az1OxUs+cOFAJ2/HgttHnB5/P5afn707l7L73v0/qet/tRCOgj+gxUnXh6akUWhYBrvCqFVfWDXnuilSB63sS7XoJCwJ5Vzr6NqudRnTzrBYWAMbxihmwPiJpcslKtBGegEJBL9Qyiyn1WWrMGa9aBQsA1arHALBXDWWOsIygE7MmemIrat3cf69m7KigE9KHqIdV2VcUMd8pmVToUAnLJzhJU5iNm2Zc6BFxT5ZFZ2Yj3vICXndUx0BkoBNhQ+War2HFHtoKSZcBcZJ2t2RXXWeY6ekEhoI1oz67OMrzWX80eFAL2zBKtH6nulnpd74XXvigE5DJblqHu4dH2oRDgg+oZ3nu/l4JFTVx5K+bdeigEXLOK53vdrz5f4W0fCgHPZNZ6y5Hong0KAX1Yo+foKP7s81kqjFl2MA8BNlQ8ZDay6hJZXVIUAmJYvWcRraDR2UPr5ygEPJPZYqSqySoUAq7Jjo6t93nZGx2bVPduWkEhYIf5f1hs39qn/D+MqOe1rnt3f+vnKARo4X3We/dYZstOrKAQcE1UNLy6p6n3KFrXQyFgjFlmLUfXq55D8FrPuh8KAWuholzV3dtRmKmEHLwnh6wzkr12qpOlQCgEfGc1z1E500djj6rsCIWAPrKVQyVr6L1+FoWlUgmxVHnCLB6owuj7QiEgBu86hHXf3n2qehlVs59n66EQ8B2VM1rFjg01e87wshOFgD5UPEStlxEdM0VNrt2BQsDaqCiaKlQqwYZ3d85rHqL1vlGqlaW6HrGBQsAzUMtKRtfLVi4UAvao9/lVexXZMU4vo+8NhQAfsrKNKFQ8+Uh1jIFCwJxExwrZiqFqJwoB16ieraN4eaJ3xXXUjmhQCBijuocxel3U/VFEZxl0O6GLR/y2pCKbl6r8vudmDwoBO/4C2GM9+2WY/yEAAAAASUVORK5CYII="></Option>
            <Option name="offset" type="QString" value="0,0"></Option>
            <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="offset_unit" type="QString" value="MM"></Option>
            <Option name="width" type="QString" value="17"></Option>
            <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
            <Option name="width_unit" type="QString" value="MM"></Option>
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
        <layer class="SimpleFill" enabled="1" id="{d2e8d3c3-cf3d-48dd-ad32-6d2e95533e86}" locked="0" pass="0">
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
  <SingleCategoryDiagramRenderer attributeLegend="1" diagramType="Histogram">
    <DiagramCategory backgroundAlpha="255" backgroundColor="#ffffff" barWidth="5" diagramOrientation="Up" direction="0" enabled="0" height="15" labelPlacementMethod="XHeight" lineSizeScale="3x:0,0,0,0,0,0" lineSizeType="MM" maxScaleDenominator="1e+08" minScaleDenominator="0" minimumSize="0" opacity="1" penAlpha="255" penColor="#000000" penWidth="0" rotationOffset="270" scaleBasedVisibility="0" scaleDependency="Area" showAxis="1" sizeScale="3x:0,0,0,0,0,0" sizeType="MM" spacing="5" spacingUnit="MM" spacingUnitScale="3x:0,0,0,0,0,0" width="15">
      <fontProperties bold="0" description="MS Shell Dlg 2,8.3,-1,5,50,0,0,0,0,0" italic="0" strikethrough="0" style="" underline="0"></fontProperties>
      <attribute color="#000000" colorOpacity="1" field="" label=""></attribute>
      <axisSymbol>
        <symbol alpha="1" clip_to_extent="1" force_rhr="0" frame_rate="10" is_animated="0" name="" type="line">
          <data_defined_properties>
            <Option type="Map">
              <Option name="name" type="QString" value=""></Option>
              <Option name="properties"></Option>
              <Option name="type" type="QString" value="collection"></Option>
            </Option>
          </data_defined_properties>
          <layer class="SimpleLine" enabled="1" id="{a15374a3-0b99-43a9-b217-b4b2c4561f90}" locked="0" pass="0">
            <Option type="Map">
              <Option name="align_dash_pattern" type="QString" value="0"></Option>
              <Option name="capstyle" type="QString" value="square"></Option>
              <Option name="customdash" type="QString" value="5;2"></Option>
              <Option name="customdash_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
              <Option name="customdash_unit" type="QString" value="MM"></Option>
              <Option name="dash_pattern_offset" type="QString" value="0"></Option>
              <Option name="dash_pattern_offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
              <Option name="dash_pattern_offset_unit" type="QString" value="MM"></Option>
              <Option name="draw_inside_polygon" type="QString" value="0"></Option>
              <Option name="joinstyle" type="QString" value="bevel"></Option>
              <Option name="line_color" type="QString" value="35,35,35,255"></Option>
              <Option name="line_style" type="QString" value="solid"></Option>
              <Option name="line_width" type="QString" value="0.26"></Option>
              <Option name="line_width_unit" type="QString" value="MM"></Option>
              <Option name="offset" type="QString" value="0"></Option>
              <Option name="offset_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
              <Option name="offset_unit" type="QString" value="MM"></Option>
              <Option name="ring_filter" type="QString" value="0"></Option>
              <Option name="trim_distance_end" type="QString" value="0"></Option>
              <Option name="trim_distance_end_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
              <Option name="trim_distance_end_unit" type="QString" value="MM"></Option>
              <Option name="trim_distance_start" type="QString" value="0"></Option>
              <Option name="trim_distance_start_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
              <Option name="trim_distance_start_unit" type="QString" value="MM"></Option>
              <Option name="tweak_dash_pattern_on_corners" type="QString" value="0"></Option>
              <Option name="use_custom_dash" type="QString" value="0"></Option>
              <Option name="width_map_unit_scale" type="QString" value="3x:0,0,0,0,0,0"></Option>
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
      </axisSymbol>
    </DiagramCategory>
  </SingleCategoryDiagramRenderer>
  <DiagramLayerSettings dist="0" linePlacementFlags="18" obstacle="0" placement="1" priority="0" showAll="1" zIndex="0">
    <properties>
      <Option type="Map">
        <Option name="name" type="QString" value=""></Option>
        <Option name="properties"></Option>
        <Option name="type" type="QString" value="collection"></Option>
      </Option>
    </properties>
  </DiagramLayerSettings>
  <fieldConfiguration>
    <field configurationFlags="NoFlag" name="fid">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="objectid">
      <editWidget type="Range">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="topoid">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="createdate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="objectmoddate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="featuremoddate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="classsubtype">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="featurereliabilitydate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="attributereliabilitydate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="capturesourcecode">
      <editWidget type="Range">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="capturemethodcode">
      <editWidget type="Range">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="planimetricaccuracy">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="verticalaccuracy">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="generalnameoid">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="generalname">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="alternativelabel">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="relevance">
      <editWidget type="Range">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="startdate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="enddate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="lastupdate">
      <editWidget type="DateTime">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="msoid">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="centroidid">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="shapeuuid">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="changetype">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="processstate">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="urbanity">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="shape_Length">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
    <field configurationFlags="NoFlag" name="shape_Area">
      <editWidget type="TextEdit">
        <config>
          <Option></Option>
        </config>
      </editWidget>
    </field>
  </fieldConfiguration>
  <aliases>
    <alias field="fid" index="0" name=""></alias>
    <alias field="objectid" index="1" name=""></alias>
    <alias field="topoid" index="2" name=""></alias>
    <alias field="createdate" index="3" name=""></alias>
    <alias field="objectmoddate" index="4" name=""></alias>
    <alias field="featuremoddate" index="5" name=""></alias>
    <alias field="classsubtype" index="6" name=""></alias>
    <alias field="featurereliabilitydate" index="7" name=""></alias>
    <alias field="attributereliabilitydate" index="8" name=""></alias>
    <alias field="capturesourcecode" index="9" name=""></alias>
    <alias field="capturemethodcode" index="10" name=""></alias>
    <alias field="planimetricaccuracy" index="11" name=""></alias>
    <alias field="verticalaccuracy" index="12" name=""></alias>
    <alias field="generalnameoid" index="13" name=""></alias>
    <alias field="generalname" index="14" name=""></alias>
    <alias field="alternativelabel" index="15" name=""></alias>
    <alias field="relevance" index="16" name=""></alias>
    <alias field="startdate" index="17" name=""></alias>
    <alias field="enddate" index="18" name=""></alias>
    <alias field="lastupdate" index="19" name=""></alias>
    <alias field="msoid" index="20" name=""></alias>
    <alias field="centroidid" index="21" name=""></alias>
    <alias field="shapeuuid" index="22" name=""></alias>
    <alias field="changetype" index="23" name=""></alias>
    <alias field="processstate" index="24" name=""></alias>
    <alias field="urbanity" index="25" name=""></alias>
    <alias field="shape_Length" index="26" name=""></alias>
    <alias field="shape_Area" index="27" name=""></alias>
  </aliases>
  <splitPolicies>
    <policy field="fid" policy="Duplicate"></policy>
    <policy field="objectid" policy="Duplicate"></policy>
    <policy field="topoid" policy="Duplicate"></policy>
    <policy field="createdate" policy="Duplicate"></policy>
    <policy field="objectmoddate" policy="Duplicate"></policy>
    <policy field="featuremoddate" policy="Duplicate"></policy>
    <policy field="classsubtype" policy="Duplicate"></policy>
    <policy field="featurereliabilitydate" policy="Duplicate"></policy>
    <policy field="attributereliabilitydate" policy="Duplicate"></policy>
    <policy field="capturesourcecode" policy="Duplicate"></policy>
    <policy field="capturemethodcode" policy="Duplicate"></policy>
    <policy field="planimetricaccuracy" policy="Duplicate"></policy>
    <policy field="verticalaccuracy" policy="Duplicate"></policy>
    <policy field="generalnameoid" policy="Duplicate"></policy>
    <policy field="generalname" policy="Duplicate"></policy>
    <policy field="alternativelabel" policy="Duplicate"></policy>
    <policy field="relevance" policy="Duplicate"></policy>
    <policy field="startdate" policy="Duplicate"></policy>
    <policy field="enddate" policy="Duplicate"></policy>
    <policy field="lastupdate" policy="Duplicate"></policy>
    <policy field="msoid" policy="Duplicate"></policy>
    <policy field="centroidid" policy="Duplicate"></policy>
    <policy field="shapeuuid" policy="Duplicate"></policy>
    <policy field="changetype" policy="Duplicate"></policy>
    <policy field="processstate" policy="Duplicate"></policy>
    <policy field="urbanity" policy="Duplicate"></policy>
    <policy field="shape_Length" policy="Duplicate"></policy>
    <policy field="shape_Area" policy="Duplicate"></policy>
  </splitPolicies>
  <defaults>
    <default applyOnUpdate="0" expression="" field="fid"></default>
    <default applyOnUpdate="0" expression="" field="objectid"></default>
    <default applyOnUpdate="0" expression="" field="topoid"></default>
    <default applyOnUpdate="0" expression="" field="createdate"></default>
    <default applyOnUpdate="0" expression="" field="objectmoddate"></default>
    <default applyOnUpdate="0" expression="" field="featuremoddate"></default>
    <default applyOnUpdate="0" expression="" field="classsubtype"></default>
    <default applyOnUpdate="0" expression="" field="featurereliabilitydate"></default>
    <default applyOnUpdate="0" expression="" field="attributereliabilitydate"></default>
    <default applyOnUpdate="0" expression="" field="capturesourcecode"></default>
    <default applyOnUpdate="0" expression="" field="capturemethodcode"></default>
    <default applyOnUpdate="0" expression="" field="planimetricaccuracy"></default>
    <default applyOnUpdate="0" expression="" field="verticalaccuracy"></default>
    <default applyOnUpdate="0" expression="" field="generalnameoid"></default>
    <default applyOnUpdate="0" expression="" field="generalname"></default>
    <default applyOnUpdate="0" expression="" field="alternativelabel"></default>
    <default applyOnUpdate="0" expression="" field="relevance"></default>
    <default applyOnUpdate="0" expression="" field="startdate"></default>
    <default applyOnUpdate="0" expression="" field="enddate"></default>
    <default applyOnUpdate="0" expression="" field="lastupdate"></default>
    <default applyOnUpdate="0" expression="" field="msoid"></default>
    <default applyOnUpdate="0" expression="" field="centroidid"></default>
    <default applyOnUpdate="0" expression="" field="shapeuuid"></default>
    <default applyOnUpdate="0" expression="" field="changetype"></default>
    <default applyOnUpdate="0" expression="" field="processstate"></default>
    <default applyOnUpdate="0" expression="" field="urbanity"></default>
    <default applyOnUpdate="0" expression="" field="shape_Length"></default>
    <default applyOnUpdate="0" expression="" field="shape_Area"></default>
  </defaults>
  <constraints>
    <constraint constraints="3" exp_strength="0" field="fid" notnull_strength="1" unique_strength="1"></constraint>
    <constraint constraints="0" exp_strength="0" field="objectid" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="topoid" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="createdate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="objectmoddate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="featuremoddate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="classsubtype" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="featurereliabilitydate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="attributereliabilitydate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="capturesourcecode" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="capturemethodcode" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="planimetricaccuracy" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="verticalaccuracy" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="generalnameoid" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="generalname" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="alternativelabel" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="relevance" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="startdate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="enddate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="lastupdate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="msoid" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="centroidid" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="shapeuuid" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="changetype" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="processstate" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="urbanity" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="shape_Length" notnull_strength="0" unique_strength="0"></constraint>
    <constraint constraints="0" exp_strength="0" field="shape_Area" notnull_strength="0" unique_strength="0"></constraint>
  </constraints>
  <constraintExpressions>
    <constraint desc="" exp="" field="fid"></constraint>
    <constraint desc="" exp="" field="objectid"></constraint>
    <constraint desc="" exp="" field="topoid"></constraint>
    <constraint desc="" exp="" field="createdate"></constraint>
    <constraint desc="" exp="" field="objectmoddate"></constraint>
    <constraint desc="" exp="" field="featuremoddate"></constraint>
    <constraint desc="" exp="" field="classsubtype"></constraint>
    <constraint desc="" exp="" field="featurereliabilitydate"></constraint>
    <constraint desc="" exp="" field="attributereliabilitydate"></constraint>
    <constraint desc="" exp="" field="capturesourcecode"></constraint>
    <constraint desc="" exp="" field="capturemethodcode"></constraint>
    <constraint desc="" exp="" field="planimetricaccuracy"></constraint>
    <constraint desc="" exp="" field="verticalaccuracy"></constraint>
    <constraint desc="" exp="" field="generalnameoid"></constraint>
    <constraint desc="" exp="" field="generalname"></constraint>
    <constraint desc="" exp="" field="alternativelabel"></constraint>
    <constraint desc="" exp="" field="relevance"></constraint>
    <constraint desc="" exp="" field="startdate"></constraint>
    <constraint desc="" exp="" field="enddate"></constraint>
    <constraint desc="" exp="" field="lastupdate"></constraint>
    <constraint desc="" exp="" field="msoid"></constraint>
    <constraint desc="" exp="" field="centroidid"></constraint>
    <constraint desc="" exp="" field="shapeuuid"></constraint>
    <constraint desc="" exp="" field="changetype"></constraint>
    <constraint desc="" exp="" field="processstate"></constraint>
    <constraint desc="" exp="" field="urbanity"></constraint>
    <constraint desc="" exp="" field="shape_Length"></constraint>
    <constraint desc="" exp="" field="shape_Area"></constraint>
  </constraintExpressions>
  <expressionfields></expressionfields>
  <attributeactions>
    <defaultAction key="Canvas" value="{00000000-0000-0000-0000-000000000000}"></defaultAction>
  </attributeactions>
  <attributetableconfig actionWidgetStyle="dropDown" sortExpression="" sortOrder="0">
    <columns>
      <column hidden="0" name="topoid" type="field" width="-1"></column>
      <column hidden="0" name="createdate" type="field" width="-1"></column>
      <column hidden="0" name="objectmoddate" type="field" width="-1"></column>
      <column hidden="0" name="featuremoddate" type="field" width="-1"></column>
      <column hidden="0" name="classsubtype" type="field" width="-1"></column>
      <column hidden="0" name="featurereliabilitydate" type="field" width="-1"></column>
      <column hidden="0" name="attributereliabilitydate" type="field" width="-1"></column>
      <column hidden="0" name="capturesourcecode" type="field" width="-1"></column>
      <column hidden="0" name="capturemethodcode" type="field" width="-1"></column>
      <column hidden="0" name="planimetricaccuracy" type="field" width="-1"></column>
      <column hidden="0" name="verticalaccuracy" type="field" width="-1"></column>
      <column hidden="0" name="generalnameoid" type="field" width="-1"></column>
      <column hidden="0" name="generalname" type="field" width="-1"></column>
      <column hidden="0" name="alternativelabel" type="field" width="-1"></column>
      <column hidden="0" name="relevance" type="field" width="-1"></column>
      <column hidden="0" name="startdate" type="field" width="-1"></column>
      <column hidden="0" name="enddate" type="field" width="-1"></column>
      <column hidden="0" name="lastupdate" type="field" width="-1"></column>
      <column hidden="0" name="msoid" type="field" width="-1"></column>
      <column hidden="0" name="centroidid" type="field" width="-1"></column>
      <column hidden="0" name="shapeuuid" type="field" width="-1"></column>
      <column hidden="0" name="changetype" type="field" width="-1"></column>
      <column hidden="0" name="processstate" type="field" width="-1"></column>
      <column hidden="0" name="urbanity" type="field" width="-1"></column>
      <column hidden="0" name="fid" type="field" width="-1"></column>
      <column hidden="0" name="objectid" type="field" width="-1"></column>
      <column hidden="0" name="shape_Length" type="field" width="-1"></column>
      <column hidden="0" name="shape_Area" type="field" width="-1"></column>
      <column hidden="1" type="actions" width="-1"></column>
    </columns>
  </attributetableconfig>
  <conditionalstyles>
    <rowstyles></rowstyles>
    <fieldstyles></fieldstyles>
  </conditionalstyles>
  <storedexpressions></storedexpressions>
  <editform tolerant="1"></editform>
  <editforminit></editforminit>
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
    <field editable="1" name="OBJECTID"></field>
    <field editable="1" name="Shape__Area"></field>
    <field editable="1" name="Shape__Length"></field>
    <field editable="1" name="alternativelabel"></field>
    <field editable="1" name="attributereliabilitydate"></field>
    <field editable="1" name="capturemethodcode"></field>
    <field editable="1" name="capturesourcecode"></field>
    <field editable="1" name="centroidid"></field>
    <field editable="1" name="changetype"></field>
    <field editable="1" name="classsubtype"></field>
    <field editable="1" name="createdate"></field>
    <field editable="1" name="enddate"></field>
    <field editable="1" name="featuremoddate"></field>
    <field editable="1" name="featurereliabilitydate"></field>
    <field editable="1" name="fid"></field>
    <field editable="1" name="generalname"></field>
    <field editable="1" name="generalnameoid"></field>
    <field editable="1" name="lastupdate"></field>
    <field editable="1" name="msoid"></field>
    <field editable="1" name="objectid"></field>
    <field editable="1" name="objectmoddate"></field>
    <field editable="1" name="planimetricaccuracy"></field>
    <field editable="1" name="processstate"></field>
    <field editable="1" name="relevance"></field>
    <field editable="1" name="shape_Area"></field>
    <field editable="1" name="shape_Length"></field>
    <field editable="1" name="shapeuuid"></field>
    <field editable="1" name="startdate"></field>
    <field editable="1" name="topoid"></field>
    <field editable="1" name="urbanity"></field>
    <field editable="1" name="verticalaccuracy"></field>
  </editable>
  <labelOnTop>
    <field labelOnTop="0" name="OBJECTID"></field>
    <field labelOnTop="0" name="Shape__Area"></field>
    <field labelOnTop="0" name="Shape__Length"></field>
    <field labelOnTop="0" name="alternativelabel"></field>
    <field labelOnTop="0" name="attributereliabilitydate"></field>
    <field labelOnTop="0" name="capturemethodcode"></field>
    <field labelOnTop="0" name="capturesourcecode"></field>
    <field labelOnTop="0" name="centroidid"></field>
    <field labelOnTop="0" name="changetype"></field>
    <field labelOnTop="0" name="classsubtype"></field>
    <field labelOnTop="0" name="createdate"></field>
    <field labelOnTop="0" name="enddate"></field>
    <field labelOnTop="0" name="featuremoddate"></field>
    <field labelOnTop="0" name="featurereliabilitydate"></field>
    <field labelOnTop="0" name="fid"></field>
    <field labelOnTop="0" name="generalname"></field>
    <field labelOnTop="0" name="generalnameoid"></field>
    <field labelOnTop="0" name="lastupdate"></field>
    <field labelOnTop="0" name="msoid"></field>
    <field labelOnTop="0" name="objectid"></field>
    <field labelOnTop="0" name="objectmoddate"></field>
    <field labelOnTop="0" name="planimetricaccuracy"></field>
    <field labelOnTop="0" name="processstate"></field>
    <field labelOnTop="0" name="relevance"></field>
    <field labelOnTop="0" name="shape_Area"></field>
    <field labelOnTop="0" name="shape_Length"></field>
    <field labelOnTop="0" name="shapeuuid"></field>
    <field labelOnTop="0" name="startdate"></field>
    <field labelOnTop="0" name="topoid"></field>
    <field labelOnTop="0" name="urbanity"></field>
    <field labelOnTop="0" name="verticalaccuracy"></field>
  </labelOnTop>
  <reuseLastValue>
    <field name="OBJECTID" reuseLastValue="0"></field>
    <field name="Shape__Area" reuseLastValue="0"></field>
    <field name="Shape__Length" reuseLastValue="0"></field>
    <field name="alternativelabel" reuseLastValue="0"></field>
    <field name="attributereliabilitydate" reuseLastValue="0"></field>
    <field name="capturemethodcode" reuseLastValue="0"></field>
    <field name="capturesourcecode" reuseLastValue="0"></field>
    <field name="centroidid" reuseLastValue="0"></field>
    <field name="changetype" reuseLastValue="0"></field>
    <field name="classsubtype" reuseLastValue="0"></field>
    <field name="createdate" reuseLastValue="0"></field>
    <field name="enddate" reuseLastValue="0"></field>
    <field name="featuremoddate" reuseLastValue="0"></field>
    <field name="featurereliabilitydate" reuseLastValue="0"></field>
    <field name="fid" reuseLastValue="0"></field>
    <field name="generalname" reuseLastValue="0"></field>
    <field name="generalnameoid" reuseLastValue="0"></field>
    <field name="lastupdate" reuseLastValue="0"></field>
    <field name="msoid" reuseLastValue="0"></field>
    <field name="objectid" reuseLastValue="0"></field>
    <field name="objectmoddate" reuseLastValue="0"></field>
    <field name="planimetricaccuracy" reuseLastValue="0"></field>
    <field name="processstate" reuseLastValue="0"></field>
    <field name="relevance" reuseLastValue="0"></field>
    <field name="shape_Area" reuseLastValue="0"></field>
    <field name="shape_Length" reuseLastValue="0"></field>
    <field name="shapeuuid" reuseLastValue="0"></field>
    <field name="startdate" reuseLastValue="0"></field>
    <field name="topoid" reuseLastValue="0"></field>
    <field name="urbanity" reuseLastValue="0"></field>
    <field name="verticalaccuracy" reuseLastValue="0"></field>
  </reuseLastValue>
  <dataDefinedFieldProperties></dataDefinedFieldProperties>
  <widgets></widgets>
  <previewExpression>"generalnameoid"</previewExpression>
  <mapTip enabled="1"></mapTip>
  <layerGeometryType>2</layerGeometryType>
</qgis>