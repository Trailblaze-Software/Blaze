<!DOCTYPE qgis PUBLIC 'http://mrcc.com/qgis.dtd' 'SYSTEM'>
<qgis hasScaleBasedVisibilityFlag="0" labelsEnabled="0" readOnly="0" version="3.34.3-Prizren" simplifyDrawingTol="1" maxScale="0" minScale="100000000" symbologyReferenceScale="-1" simplifyDrawingHints="1" simplifyAlgorithm="0" styleCategories="LayerConfiguration|Symbology|Symbology3D|Labeling|Fields|Forms|Actions|MapTips|Diagrams|AttributeTable|Rendering" simplifyLocal="1" simplifyMaxScale="1">
  <flags>
    <Identifiable>1</Identifiable>
    <Removable>1</Removable>
    <Searchable>1</Searchable>
    <Private>0</Private>
  </flags>
  <renderer-v2 forceraster="0" type="RuleRenderer" referencescale="-1" enableorderby="0" symbollevels="0">
    <rules key="{8ecc2b5d-e75d-4e22-bfc9-4fcac24df327}">
      <rule label="Intertidal" filter="classsubtype = 1" key="{c3301a52-196a-419d-80bb-f2a1f561452f}" symbol="0"/>
      <rule label="Subject to inundation" filter="classsubtype =2" key="{66159459-9065-4775-8754-9a98488403f5}" symbol="1"/>
      <rule label="Mangroves" filter="classsubtype = 3" key="{6f8d755b-6c60-4281-b544-e3a57cdc20b2}" symbol="2"/>
      <rule label="Reef" filter="classsubtype = 4" key="{edf5b7bc-db4a-4f7a-99b3-5cf6aa1ae715}" symbol="3"/>
      <rule label="Rock-Awash" filter="classsubtype = 5" key="{2b476709-9c22-4f7f-a78f-16a9277ca3ef}" symbol="4"/>
      <rule label="Rock-Inland" filter="classsubtype = 6" key="{0443436e-24fb-4595-a6d4-703ac1f5704e}" symbol="5"/>
      <rule label="Sand" filter="classsubtype = 7" key="{85984149-0eb5-4832-b528-2eab67dbef51}" symbol="6"/>
      <rule label="Samp-wet" filter="classsubtype = 8" key="{5bf45169-eb34-4ffd-a843-1c50656e4232}" symbol="7"/>
      <rule label="Samp-dry" filter="classsubtype = 9" key="{af0d8fbf-2d91-4790-973c-83e6b052a890}" symbol="8"/>
      <rule label="Cliff" filter="classsubtype = 11" key="{38f53e68-0dec-4c44-ba68-133f8bd1e949}" symbol="9"/>
      <rule label="unknown" filter="ELSE" key="{f4eb473e-37ea-4efc-b64d-8f1d742e75a5}" symbol="10"/>
    </rules>
    <symbols>
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="0" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{5f2a124f-8a7d-4f3a-9ca2-e0390f2c1624}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="0,0,255,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="no" type="QString" name="outline_style"/>
            <Option value="0.26" type="QString" name="outline_width"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="no" type="QString" name="style"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
        <layer id="{3261e199-39b8-4c00-bfeb-6a23594eb343}" locked="0" class="RasterFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="1" type="QString" name="alpha"/>
            <Option value="0" type="QString" name="angle"/>
            <Option value="1" type="QString" name="coordinate_mode"/>
            <Option value="base64:iVBORw0KGgoAAAANSUhEUgAAAJgAAACgCAYAAADw66XhAAAA4WlDQ1BzUkdCAAAYlWNgYDzNAARMDgwMuXklRUHuTgoRkVEKDEggMbm4gAE3YGRg+HYNRDIwXNYNLGHlx6MWG+AsAloIpD8AsUg6mM3IAmInQdgSIHZ5SUEJkK0DYicXFIHYQBcz8BSFBDkD2T5AtkI6EjsJiZ2SWpwMZOcA2fEIv+XPZ2Cw+MLAwDwRIZY0jYFhezsDg8QdhJjKQgYG/lYGhm2XEWKf/cH+ZRQ7VJJaUQIS8dN3ZChILEoESzODAjQtjYHh03IGBt5IBgbhCwwMXNEQd4ABazEwoEkMJ0IAAHLYNoSjH0ezAAAACXBIWXMAAB2HAAAdhwGP5fFlAAAFMElEQVR4nO3cS3LbMBCEYSb73ClH9518AGelpMyYJgFMz/SQ/7eMJQCUCq3Bo7JtL2/vH9vb+8eW7Wq/R69Tjbvq83AZx1m/F8f1M3RQwLDRGZSdNFdF979vb/a5qxNY/L2QYDDjnkSz46t+rlnqcS+2T4JBLLsG6LoadF3NVbXHKhLeTFYh4TVXViJUJXh1LbnrnwQDpKpnvKugz4UEQxKX/aWocahrmqzkU/WfNH4SDE2oVnNda6TqfUD1Lw77YECEJrXIU5FgSOa+c57Vr3qHPnu1rB7HwetJMIi5noGp9uWQigTDTVXd/1rdh1Lv360md/UJww4JhiJRO85PqZVckmW0f/G4SDCYqzpDq06EKO4112L7JBjE3Pevqs4aq29DqNpPXr2TYDDRpeZxG6fbeFYNPg8JhiaqapOuok8cqmrVEyQYirmvjqrONLPG0RwJhmRRO+nRyaRKOnVSqfev1LUaO/nwdrfaoep53HfaVU7GS4LBRFTNlT1Do88io3RLqkkkGJpTJ1uX9626uipUrSonn5sEQzK3WqrLjnrXGjXabvwkGMSiZ4zbTFXVLncV/P2RYCjmOoOrx1VVc50lr1kSk2BoLnsVqJqprqtTdfvcpoC3qsTIWm2q70vNvq+6hox28DwkGMy4zDyXcZzJTnj1mePg85BgaC6rNsk+kchO0C6JvUOCQerH4V9es+X3r+PXZLx+tN3R96+2z3i+bZcEg1jT3/by2xhRr49i2i8Jhua6rSJNk2D4dSZIMJhyrYFG3x+VsKp7WNGJvvp5sJMPb3dJpqj3u98vc6nJuE0BKLnM9FVZZ65BtRgJhmLq+0VR/V29FxU1ThX3mm8QCQapfyfk2af4d3H0uY3++2w/q+2qcJsCvdz9zFFdw2StDkf7W2yHBANCuKwSr4o+Qy1CgiFZ9K0A9fuixquu7arPXouQYDDXdGZNc91pz7rnNdgOCYabi66Vos9In5bQwUgwJFPVAndPAtVqOXuHP7g9EgwmshKoasa6rg5H2zNLPBIM+JZLslbfDpkl7p8Eg1Tc7cfom537v0fd2HS7+XmV6iasCjdakau6Fpjlcvtjtr3V8ZuvfkkwFMtONpdV4ejru/wCJJ/UkGAwUzVTuySEC5PPiwRDE6OroagZln0/bFR07WZ21niGBIOU3/9N4TKOF7fxHHE76WAnHx5MViNpNdtqO1E1p2q/Kro9brQCkVwS11Xy50OCQer/lcLoPa3of19936zq1eJo/+6fA6tIYIXbqnO2PZeaklUkPLnfc3I9a1Sfsa4y+V5JMJiK2snmftlnXWu0AyQYsG2bvtbKTgL3cQaNjwRDMvPf9GFRSTFbQ7rdilg1OB4SDCayVo1Z+1puyfCiXkVymwLAOrcEFY2HBINY9UyKXoWpa7Oqk4qqWmvxeUkwFKlaHapU9/9QJBgexq3mUomq2czPNEkw3FSXmmg1abo8515QTU2CQSx63+fq32fdPTnONHsuEgwPcfX+VXQ/2e1nJ1BxfyQYbqI6OdzavdpPdf+L4yHBYKK6tnDbsXZbzZquLkkwJLn76uaM23jUop/3oD0SDM2paxWX5LnZLYio/kgwFHv66tHtvlhVO5NIMEDi4ftTf0XXjpxF4l6qd9Kj23VLJLfx7JBgEKueAUk7ynKq1e7q8xSvwkkwFFmdWVUzr6rdq/1U/2Lsib8nEgxI4ZYsV5mPmwQDPsnep8qqpVT9FL+fBIPY7MypXmWOYvX4NfGtDRIMD1WdOF2Yj58Eg9QfHk42oCDWV4oAAAAASUVORK5CYII=" type="QString" name="imageFile"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="20" type="QString" name="width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
            <Option value="MM" type="QString" name="width_unit"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="1" clip_to_extent="1" alpha="0.559">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{f0e977b2-2539-4f9e-97e0-f23eea4c86f8}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="0,0,255,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="no" type="QString" name="outline_style"/>
            <Option value="0.26" type="QString" name="outline_width"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="no" type="QString" name="style"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
        <layer id="{af088dba-a7e6-4a7e-a9ec-a7e999f49bee}" locked="0" class="RasterFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="1" type="QString" name="alpha"/>
            <Option value="0" type="QString" name="angle"/>
            <Option value="1" type="QString" name="coordinate_mode"/>
            <Option value="base64:iVBORw0KGgoAAAANSUhEUgAAABIAAAAICAYAAAD0g6+qAAAA4WlDQ1BzUkdCAAAYlWNgYDzNAARMDgwMuXklRUHuTgoRkVEKDEggMbm4gAE3YGRg+HYNRDIwXNYNLGHlx6MWG+AsAloIpD8AsUg6mM3IAmInQdgSIHZ5SUEJkK0DYicXFIHYQBcz8BSFBDkD2T5AtkI6EjsJiZ2SWpwMZOcA2fEIv+XPZ2Cw+MLAwDwRIZY0jYFhezsDg8QdhJjKQgYG/lYGhm2XEWKf/cH+ZRQ7VJJaUQIS8dN3ZChILEoESzODAjQtjYHh03IGBt5IBgbhCwwMXNEQd4ABazEwoEkMJ0IAAHLYNoSjH0ezAAAACXBIWXMAAB2HAAAdhwGP5fFlAAAAaElEQVQokc3OPQ5AQACE0W9iC1oRZ3ADnVqtoFY5iPNwtc0mNCTWAfxkKzH1zMvA3yImWyFGILpvyLFvHW2+vEEGkQHFI+S9I4lj4BVSyG0AZtsDzXXjV6TBBEP4ElRfIa0cSsOdr3ICQzwTfEp1rzQAAAAASUVORK5CYII=" type="QString" name="imageFile"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="2" type="QString" name="width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
            <Option value="MM" type="QString" name="width_unit"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="10" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{f266f749-4b48-4eb4-845b-a3c424ff2e2d}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="255,0,0,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0.26" type="QString" name="outline_width"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="solid" type="QString" name="style"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="2" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{198a42f6-8cb8-4486-82dd-f4d3fbb8d752}" locked="0" class="SVGFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="QString" name="angle"/>
            <Option value="148,228,72,255" type="QString" name="color"/>
            <Option value="148,228,72,255" type="QString" name="outline_color"/>
            <Option value="0.26" type="QString" name="outline_width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option name="parameters"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="pattern_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="pattern_width_unit"/>
            <Option value="symbol/landuse_scrub.svg" type="QString" name="svgFile"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="svg_outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="svg_outline_width_unit"/>
            <Option value="2" type="QString" name="width"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="3" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{79b38b3e-7780-475a-98a5-e36d32d46d76}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="0,0,255,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="no" type="QString" name="outline_style"/>
            <Option value="0.26" type="QString" name="outline_width"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="no" type="QString" name="style"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
        <layer id="{36214a07-ee3a-48a4-af47-c2dcdeedadd2}" locked="0" class="RasterFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="1" type="QString" name="alpha"/>
            <Option value="0" type="QString" name="angle"/>
            <Option value="1" type="QString" name="coordinate_mode"/>
            <Option value="base64:iVBORw0KGgoAAAANSUhEUgAAAIQAAAB6CAYAAAB+3PvOAAAA4WlDQ1BzUkdCAAAYlWNgYDzNAARMDgwMuXklRUHuTgoRkVEKDEggMbm4gAE3YGRg+HYNRDIwXNYNLGHlx6MWG+AsAloIpD8AsUg6mM3IAmInQdgSIHZ5SUEJkK0DYicXFIHYQBcz8BSFBDkD2T5AtkI6EjsJiZ2SWpwMZOcA2fEIv+XPZ2Cw+MLAwDwRIZY0jYFhezsDg8QdhJjKQgYG/lYGhm2XEWKf/cH+ZRQ7VJJaUQIS8dN3ZChILEoESzODAjQtjYHh03IGBt5IBgbhCwwMXNEQd4ABazEwoEkMJ0IAAHLYNoSjH0ezAAAACXBIWXMAAB2HAAAdhwGP5fFlAAADwElEQVR4nO2dSW7jMBBFnT5Gzpbj9dlyjfTGDmACag41fVLvLWOJLAmuz5rgPB4vvr5/Hl/fP49sRve9ui7K7qr3UWzHn6yN4BRmv6HZnjyK9/7teqvPXa1wzXUoBBhR9/RV+6qfaxVnu1EIaMg+w3bNFtSzMKf1UAgYxFofyLLDKwtaxUsJRZQMhQB4Y9fsIggUAi5Qye+97Ig+k7OUJWr/i/tRCAgiKtrf9YyvrsMsrodCwGEEnaV3BYWADuqVwax9oyuQ2dnUoB0oBDSI1NCn1+PsDwGFABGq5h+sdYDo+olVGel2Qg5eFbW7nPXqMQ9ZBtRQVYOv9jgvimOGFhQCGtTrB94VR+fKnpud3izaiULAImoecIWanWr2dEAh4I0Pt5VeXvD382Po73en915m36f1PT/vRyFgkugzUHXi6aYVWRQCOnhVCqvqB7P2RCtB9LyJc70EhYCGQ86+X6qeR3XybBIUAhbxihmyPSBqcsmKqDKjEJBM9Qyiyn1WRrMGY9aBQkAHtVhgl4rhrjFWAwoBDdkTU1H7zu5jPXsPBYWASVQ9pNquqpihp2xGpUMhIJnsLEFlPmKXfalDwP+p8sisbMR5XmB6H6/rk0AhwIjKN1vFjh7ZCkqWAXuRdbZmV1x3meuYBIWAQaI9uzrL8Fr/MHtQCGjYJVpvqe6Wel3vhdO+KAQks1uWoe7hwfahEOCE6hk+e7+XgkVNXHkrZmc9FAI6nOL5Xverz1c424dCwE3Ztd7SEtyzQSFgEmv0HB3FX32+S4Uxyw7mIcCGiofsRlZdIqlLikJAEKf3LKIVNDh7GP0chYCbsluMVDRZhUJAh+zo2Hqfl73RsUl172YQFALesP8Pi9e39i7/DyPqea3r9u4f/ByFADG8z3rvHstu2YkRFAI6REXDp3uaeI9idD0UAhbZZdZydT312cnR9Yz7oRBwGCrKVd29XYWZSsjBe3LIOiM5a6c6SQqEQsAFp3mOypm+GnsUZUcoBEySrRwqWcPs9bsoLJVKiKXKE3bxQBUW3xcKAUF41yGs+87uU9XLqJr9vFgPhYALVM5oFTteqNlzhZOdKARMouIhar2M6JgpanKtAwoBh6OiaKpQqQQb3t05r3mI0ftWqVaW6nrEExQCboJaVrK6XrJyoRDQoN7nV+1VZMc4syy+NxQCnMjKNqJQ8eSW4hgDhYBNiY4VshVD1E4UAjqonq2reHmid8V11Y5gUAhYpLqHsXpd1P1RRGcZdDthhnv8tqQiLy9V+X3Ppz0oBLzxD+xjSNLTCW4cAAAAAElFTkSuQmCC" type="QString" name="imageFile"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="17" type="QString" name="width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
            <Option value="MM" type="QString" name="width_unit"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="4" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{9d004031-aebe-4f71-9954-97832d0ec523}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="0,0,255,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="no" type="QString" name="outline_style"/>
            <Option value="0.26" type="QString" name="outline_width"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="no" type="QString" name="style"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
        <layer id="{0128343c-48b8-456e-8e18-506159faeedd}" locked="0" class="RasterFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="1" type="QString" name="alpha"/>
            <Option value="0" type="QString" name="angle"/>
            <Option value="1" type="QString" name="coordinate_mode"/>
            <Option value="base64:iVBORw0KGgoAAAANSUhEUgAAAIQAAAB6CAYAAAB+3PvOAAAA4WlDQ1BzUkdCAAAYlWNgYDzNAARMDgwMuXklRUHuTgoRkVEKDEggMbm4gAE3YGRg+HYNRDIwXNYNLGHlx6MWG+AsAloIpD8AsUg6mM3IAmInQdgSIHZ5SUEJkK0DYicXFIHYQBcz8BSFBDkD2T5AtkI6EjsJiZ2SWpwMZOcA2fEIv+XPZ2Cw+MLAwDwRIZY0jYFhezsDg8QdhJjKQgYG/lYGhm2XEWKf/cH+ZRQ7VJJaUQIS8dN3ZChILEoESzODAjQtjYHh03IGBt5IBgbhCwwMXNEQd4ABazEwoEkMJ0IAAHLYNoSjH0ezAAAACXBIWXMAAB2HAAAdhwGP5fFlAAADyklEQVR4nO2dyXHcMBBFJcemgHRzDLopIOcmX8wqkzUkAfT2Ab531JBAkzX90VuN3t7+8fX58fP1+fHzlkzrvmfXRdld9T6q7fiVtREsQu83NNuTW/He/7je6HNXK9zxOhQCbKh7+qh91c81irfdKATsyT7DZs0W1LMwr/VQCGjDWh/IssMrCxrFSwlVlAyFAPifWbOLKFAIeI1Kfu9lR/SZnKUsUfuf3Y9CQAxR0f6sZ3x1HWZ0PRQC1iLqLH0qKARco14ZzNo3ugKZnU212oFCwB6VGnrvepz9MaAQoEHV/IO1DhBdP7EqI91OyMGrovaUs1495iHLgBqqavDVHudFdcxwBIWAPer1A++Ko3dlz8tOb0btRCFgDDUPOEPNTjV77kAhYMe710KbF/z+/vPe8venc/deet+n9T1v96MQ0Ef0Gag68fTUiiwKAdd4VQqr6ge99kQrQfS8iXe9BIWAPaucfRtVz6M6edYLCgFjeMUM2R4QNblkpVoJzkAhIJfqGUSV+6y0Zg3WrAOFgGvUYoFZKoazxlhHUAjYkz0xFbVv7z7Ws3dVUAjoQ9VDqu2qihnulM2qdCgE5JKdJajMR8yyL3UIuKbKI7OyEe95AS87q2OgM1AIsKHyzVax445sBSXLgLnIOluzK66zzHX0gkJAG9GeXZ1leK2/mj0oBOyZJVo/Ut0t9breC699UQjIZbYsQ93Do+1DIcAH1TO8934vBYuauPJWzLv1UAi4ZhXP97pffb7C2z4UAp7JrPWWI9E9GxQC+rBGz9FR/Nnns1QYs+xgHgJsqHjIbGTVJbK6pCgExLB6zyJaQaOzh9bPUQh4JrPFSFWTVSgEXJMdHVvv87I3Ojap7t20gkLADvP/sNi+tU/5fxhRz2td9+7+1s9RCNDC+6z37rHMlp1YQSHgmqhoeHVPU+9RtK6HQsAYs8xajq5XPYfgtZ51PxQC1kJFuaq7t6MwUwk5eE8OWWcke+1UJ0uBUAh4zWqeo3Kmj8YeVdkRCgF9ZCuHStbQe/0sCkulEmKp8oRZPFCF0feFQkAM3nUI6769+1T1MqpmP8/WQyHgNSpntIodG2r2nOFlJwoBfah4iFovIzpmippcuwOFgLVRUTRVqFSCDe/unNc8ROt9o1QrS3U9YgOFgGeglpWMrpetXCgE7FHv86v2KrJjnF5G3xsKAT5kZRtRqHjykeoYA4WAOYmOFbIVQ9VOFAKuUT1bR/HyRO+K66gd0aAQMEZ1D2P0uqj7o4jOMuh2QheP+G1JRTYvVfl9z80eFAJ2/AVBNkT7PfklLgAAAABJRU5ErkJggg==" type="QString" name="imageFile"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="17" type="QString" name="width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
            <Option value="MM" type="QString" name="width_unit"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="5" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{4c27dbd2-8de5-4540-9689-ac3f00f1f7c8}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="0,0,255,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="no" type="QString" name="outline_style"/>
            <Option value="0.26" type="QString" name="outline_width"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="no" type="QString" name="style"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
        <layer id="{daaef6c2-f169-4761-bc94-6ad7c672f06a}" locked="0" class="RasterFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="1" type="QString" name="alpha"/>
            <Option value="0" type="QString" name="angle"/>
            <Option value="1" type="QString" name="coordinate_mode"/>
            <Option value="base64:iVBORw0KGgoAAAANSUhEUgAAAIQAAAB6CAYAAAB+3PvOAAAA4WlDQ1BzUkdCAAAYlWNgYDzNAARMDgwMuXklRUHuTgoRkVEKDEggMbm4gAE3YGRg+HYNRDIwXNYNLGHlx6MWG+AsAloIpD8AsUg6mM3IAmInQdgSIHZ5SUEJkK0DYicXFIHYQBcz8BSFBDkD2T5AtkI6EjsJiZ2SWpwMZOcA2fEIv+XPZ2Cw+MLAwDwRIZY0jYFhezsDg8QdhJjKQgYG/lYGhm2XEWKf/cH+ZRQ7VJJaUQIS8dN3ZChILEoESzODAjQtjYHh03IGBt5IBgbhCwwMXNEQd4ABazEwoEkMJ0IAAHLYNoSjH0ezAAAACXBIWXMAAB2HAAAdhwGP5fFlAAADwElEQVR4nO2dW26kMBBFyWw568iaMz+DNKAGbNfr2pzzmQa7QF3X9VJn2/7xvW2/39v2uyXTuu/VdVF2V72Pajv+ZG0Ei9D7Dc325Fa89z+vN/rc1Qp3vg6FABvqnj5qX/VzjeJtNwoBR7LPsFmzBfUszGs9FALasNYHsuzwyoJG8VJCFSVDIQD+Z9bsIgoUAj6jkt972RF9JmcpS9T+V/ejEBBDVLQ/6xlfXYcZXQ+FgLWIOkvfCgoB96hXBrP2ja5AZmdTrXagEHBEpYbeux5nfwwoBGhQNf9grQNE10+syki3E3Lwqqi95axXj3nIMqCGqhp8tcd5UR0znEEh4Ih6/cC74uhd2fOy05tRO1EIGEPNA65Qs1PNnidQCDjw5bXQ7gU/pzWv/v52nt5L7/u0vuf9fhQC+og+A1Unnt5akUUh4B6vSmFV/aDXnmgliJ438a6XoBBwZJWzb6fqeVQnz3pBIWAMr5gh2wOiJpesVCvBFSgE5FI9g6hyn5XWrMGadaAQcI9aLDBLxXDWGOsMCgFHsiemovbt3cd69q4KCgF9qHpItV1VMcOTslmVDoWAXLKzBJX5iFn2pQ4B91R5ZFY24j0v4GVndQx0BQoBNlS+2Sp2PJGtoGQZMBdZZ2t2xXWWuY5eUAhoI9qzq7MMr/VXsweFgCOzROtnqrulXtd74bUvCgG5zJZlqHt4tH0oBPigeob33u+lYFETV96K+bQeCgH3rOL5Xverz1d424dCwDuZtd5yJrpng0JAH9boOTqKv/p8lgpjlh3MQ4ANFQ+Zjay6RFaXFIWAGFbvWUQraHT20Po5CgHvZLYYqWqyCoWAe7KjY+t9XvZGxybVvZtWUAg4YP4fFvu39i3/DyPqea3rPt3f+jkKAVp4n/XePZbZshMrKATcExUNr+5p6j2K1vVQCBhjllnL0fWq5xC81rPuh0LAWqgoV3X3dhRmKiEH78kh64xkr53qZCkQCgGfWc1zVM700dijKjtCIaCPbOVQyRp6r59FYalUQixVnjCLB6ow+r5QCIjBuw5h3bd3n6peRtXs59V6KAR8RuWMVrFjR82eK7zsRCGgDxUPUetlRMdMUZNrT6AQsDYqiqYKlUqw4d2d85qHaL1vlGplqa5H7KAQ8A7UspLR9bKVC4WAI+p9ftVeRXaM08voe0MhwIesbCMKFU8+Ux1joBAwJ9GxQrZiqNqJQsA9qmfrKF6e6F1xHbUjGhQCxqjuYYxeF3V/FNFZBt1O6OIVvy2pyO6lKr/vuduDQsCBv673rOD9wZQiAAAAAElFTkSuQmCC" type="QString" name="imageFile"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="17" type="QString" name="width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
            <Option value="MM" type="QString" name="width_unit"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="6" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{f3a470da-acd0-4c38-b020-3a4966f1ec98}" locked="0" class="PointPatternFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="0" type="double" name="angle"/>
            <Option value="shape" type="QString" name="clip_mode"/>
            <Option value="feature" type="QString" name="coordinate_reference"/>
            <Option value="0.5" type="QString" name="displacement_x"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="displacement_x_map_unit_scale"/>
            <Option value="MM" type="QString" name="displacement_x_unit"/>
            <Option value="0.5" type="QString" name="displacement_y"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="displacement_y_map_unit_scale"/>
            <Option value="MM" type="QString" name="displacement_y_unit"/>
            <Option value="1.2" type="QString" name="distance_x"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="distance_x_map_unit_scale"/>
            <Option value="MM" type="QString" name="distance_x_unit"/>
            <Option value="1.2" type="QString" name="distance_y"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="distance_y_map_unit_scale"/>
            <Option value="MM" type="QString" name="distance_y_unit"/>
            <Option value="0" type="QString" name="offset_x"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_x_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_x_unit"/>
            <Option value="0" type="QString" name="offset_y"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_y_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_y_unit"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="0" type="QString" name="random_deviation_x"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="random_deviation_x_map_unit_scale"/>
            <Option value="MM" type="QString" name="random_deviation_x_unit"/>
            <Option value="0" type="QString" name="random_deviation_y"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="random_deviation_y_map_unit_scale"/>
            <Option value="MM" type="QString" name="random_deviation_y_unit"/>
            <Option value="634708326" type="QString" name="seed"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
          <symbol frame_rate="10" force_rhr="0" is_animated="0" type="marker" name="@6@0" clip_to_extent="1" alpha="1">
            <data_defined_properties>
              <Option type="Map">
                <Option value="" type="QString" name="name"/>
                <Option name="properties"/>
                <Option value="collection" type="QString" name="type"/>
              </Option>
            </data_defined_properties>
            <layer id="{02f1c90c-2bf4-465b-a324-6df9220177ef}" locked="0" class="SimpleMarker" enabled="1" pass="0">
              <Option type="Map">
                <Option value="0" type="QString" name="angle"/>
                <Option value="square" type="QString" name="cap_style"/>
                <Option value="224,165,0,255" type="QString" name="color"/>
                <Option value="1" type="QString" name="horizontal_anchor_point"/>
                <Option value="bevel" type="QString" name="joinstyle"/>
                <Option value="circle" type="QString" name="name"/>
                <Option value="0,0" type="QString" name="offset"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
                <Option value="MM" type="QString" name="offset_unit"/>
                <Option value="0,0,0,255" type="QString" name="outline_color"/>
                <Option value="no" type="QString" name="outline_style"/>
                <Option value="0.2" type="QString" name="outline_width"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="outline_width_map_unit_scale"/>
                <Option value="MM" type="QString" name="outline_width_unit"/>
                <Option value="diameter" type="QString" name="scale_method"/>
                <Option value="0.6" type="QString" name="size"/>
                <Option value="3x:0,0,0,0,0,0" type="QString" name="size_map_unit_scale"/>
                <Option value="MM" type="QString" name="size_unit"/>
                <Option value="1" type="QString" name="vertical_anchor_point"/>
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
        </layer>
        <layer id="{acb22129-6aaa-4e9a-a6d4-6091a406344a}" locked="0" class="SimpleLine" enabled="1" pass="0">
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
            <Option value="no" type="QString" name="line_style"/>
            <Option value="0.1" type="QString" name="line_width"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="7" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{7578740b-7846-4fe7-9b30-99ca8d55f3cf}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="0,0,255,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="no" type="QString" name="outline_style"/>
            <Option value="0.26" type="QString" name="outline_width"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="no" type="QString" name="style"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
        <layer id="{56b592f8-fde0-4abb-adb5-45da1f615278}" locked="0" class="RasterFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="1" type="QString" name="alpha"/>
            <Option value="0" type="QString" name="angle"/>
            <Option value="1" type="QString" name="coordinate_mode"/>
            <Option value="base64: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" type="QString" name="imageFile"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="17" type="QString" name="width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
            <Option value="MM" type="QString" name="width_unit"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="8" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{2bbdf748-df7a-4a21-8b17-6f3f64f084d7}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="0,0,255,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="no" type="QString" name="outline_style"/>
            <Option value="0.26" type="QString" name="outline_width"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="no" type="QString" name="style"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
        <layer id="{f571b334-a330-4356-bb03-d6bd61ad8c81}" locked="0" class="RasterFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="1" type="QString" name="alpha"/>
            <Option value="0" type="QString" name="angle"/>
            <Option value="1" type="QString" name="coordinate_mode"/>
            <Option value="base64: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" type="QString" name="imageFile"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="17" type="QString" name="width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
            <Option value="MM" type="QString" name="width_unit"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="9" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{b05b9b91-b07f-42f5-91ea-1553af7425b9}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="0,0,255,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="no" type="QString" name="outline_style"/>
            <Option value="0.26" type="QString" name="outline_width"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="no" type="QString" name="style"/>
          </Option>
          <data_defined_properties>
            <Option type="Map">
              <Option value="" type="QString" name="name"/>
              <Option name="properties"/>
              <Option value="collection" type="QString" name="type"/>
            </Option>
          </data_defined_properties>
        </layer>
        <layer id="{51d74b2d-e5ba-40ad-8641-e5d56698621a}" locked="0" class="RasterFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="1" type="QString" name="alpha"/>
            <Option value="0" type="QString" name="angle"/>
            <Option value="1" type="QString" name="coordinate_mode"/>
            <Option value="base64:iVBORw0KGgoAAAANSUhEUgAAAIQAAAB6CAYAAAB+3PvOAAAA4WlDQ1BzUkdCAAAYlWNgYDzNAARMDgwMuXklRUHuTgoRkVEKDEggMbm4gAE3YGRg+HYNRDIwXNYNLGHlx6MWG+AsAloIpD8AsUg6mM3IAmInQdgSIHZ5SUEJkK0DYicXFIHYQBcz8BSFBDkD2T5AtkI6EjsJiZ2SWpwMZOcA2fEIv+XPZ2Cw+MLAwDwRIZY0jYFhezsDg8QdhJjKQgYG/lYGhm2XEWKf/cH+ZRQ7VJJaUQIS8dN3ZChILEoESzODAjQtjYHh03IGBt5IBgbhCwwMXNEQd4ABazEwoEkMJ0IAAHLYNoSjH0ezAAAACXBIWXMAAB2HAAAdhwGP5fFlAAADwklEQVR4nO2dW46jMBBF07PALDYb7PkZpAEFsF2va3POZwfsAqWu66X06/WP9/v9+36/f1/JtO57dl2U3VXvo9qOP1kbwSL0fkOzPbkV7/2P640+d7XCHa9DIcCGuqeP2lf9XKN4241CwJ7sM2zWbEE9C/NaD4WANqz1gSw7vLKgUbyUUEXJUAiA/5k1u4gChYDvqOT3XnZEn8lZyhK1/9n9KATEEBXtz3rGV9dhRtdDIWAtos7Sp4JCwDXqlcGsfaMrkNnZVKsdKATsUamh967H2R8DCgEaVM0/WOsA0fUTqzLS7YQcvCpqTznr1WMesgyooaoGX+1xXlTHDEdQCNijXj/wrjh6V/a87PRm1E4UAsZQ84Az1OxUs+cOFAJ2/HgttHnB5/P5afn707l7L73v0/qet/tRCOgj+gxUnXh6akUWhYBrvCqFVfWDXnuilSB63sS7XoJCwJ5Vzr6NqudRnTzrBYWAMbxihmwPiJpcslKtBGegEJBL9Qyiyn1WWrMGa9aBQsA1arHALBXDWWOsIygE7MmemIrat3cf69m7KigE9KHqIdV2VcUMd8pmVToUAnLJzhJU5iNm2Zc6BFxT5ZFZ2Yj3vICXndUx0BkoBNhQ+War2HFHtoKSZcBcZJ2t2RXXWeY6ekEhoI1oz67OMrzWX80eFAL2zBKtH6nulnpd74XXvigE5DJblqHu4dH2oRDgg+oZ3nu/l4JFTVx5K+bdeigEXLOK53vdrz5f4W0fCgHPZNZ6y5Hong0KAX1Yo+foKP7s81kqjFl2MA8BNlQ8ZDay6hJZXVIUAmJYvWcRraDR2UPr5ygEPJPZYqSqySoUAq7Jjo6t93nZGx2bVPduWkEhYIf5f1hs39qn/D+MqOe1rnt3f+vnKARo4X3We/dYZstOrKAQcE1UNLy6p6n3KFrXQyFgjFlmLUfXq55D8FrPuh8KAWuholzV3dtRmKmEHLwnh6wzkr12qpOlQCgEfGc1z1E500djj6rsCIWAPrKVQyVr6L1+FoWlUgmxVHnCLB6owuj7QiEgBu86hHXf3n2qehlVs59n66EQ8B2VM1rFjg01e87wshOFgD5UPEStlxEdM0VNrt2BQsDaqCiaKlQqwYZ3d85rHqL1vlGqlaW6HrGBQsAzUMtKRtfLVi4UAvao9/lVexXZMU4vo+8NhQAfsrKNKFQ8+Uh1jIFCwJxExwrZiqFqJwoB16ieraN4eaJ3xXXUjmhQCBijuocxel3U/VFEZxl0O6GLR/y2pCKbl6r8vudmDwoBO/4C2GM9+2WY/yEAAAAASUVORK5CYII=" type="QString" name="imageFile"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="17" type="QString" name="width"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="width_map_unit_scale"/>
            <Option value="MM" type="QString" name="width_unit"/>
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
      <symbol frame_rate="10" force_rhr="0" is_animated="0" type="fill" name="" clip_to_extent="1" alpha="1">
        <data_defined_properties>
          <Option type="Map">
            <Option value="" type="QString" name="name"/>
            <Option name="properties"/>
            <Option value="collection" type="QString" name="type"/>
          </Option>
        </data_defined_properties>
        <layer id="{d2e8d3c3-cf3d-48dd-ad32-6d2e95533e86}" locked="0" class="SimpleFill" enabled="1" pass="0">
          <Option type="Map">
            <Option value="3x:0,0,0,0,0,0" type="QString" name="border_width_map_unit_scale"/>
            <Option value="0,0,255,255" type="QString" name="color"/>
            <Option value="bevel" type="QString" name="joinstyle"/>
            <Option value="0,0" type="QString" name="offset"/>
            <Option value="3x:0,0,0,0,0,0" type="QString" name="offset_map_unit_scale"/>
            <Option value="MM" type="QString" name="offset_unit"/>
            <Option value="35,35,35,255" type="QString" name="outline_color"/>
            <Option value="solid" type="QString" name="outline_style"/>
            <Option value="0.26" type="QString" name="outline_width"/>
            <Option value="MM" type="QString" name="outline_width_unit"/>
            <Option value="solid" type="QString" name="style"/>
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
      <fontProperties underline="0" description="MS Shell Dlg 2,8.3,-1,5,50,0,0,0,0,0" bold="0" italic="0" strikethrough="0" style=""/>
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
          <layer id="{a15374a3-0b99-43a9-b217-b4b2c4561f90}" locked="0" class="SimpleLine" enabled="1" pass="0">
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
  <DiagramLayerSettings linePlacementFlags="18" dist="0" obstacle="0" zIndex="0" showAll="1" priority="0" placement="1">
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
    <field configurationFlags="NoFlag" name="shape_Area">
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
    <alias index="13" name="" field="generalnameoid"/>
    <alias index="14" name="" field="generalname"/>
    <alias index="15" name="" field="alternativelabel"/>
    <alias index="16" name="" field="relevance"/>
    <alias index="17" name="" field="startdate"/>
    <alias index="18" name="" field="enddate"/>
    <alias index="19" name="" field="lastupdate"/>
    <alias index="20" name="" field="msoid"/>
    <alias index="21" name="" field="centroidid"/>
    <alias index="22" name="" field="shapeuuid"/>
    <alias index="23" name="" field="changetype"/>
    <alias index="24" name="" field="processstate"/>
    <alias index="25" name="" field="urbanity"/>
    <alias index="26" name="" field="shape_Length"/>
    <alias index="27" name="" field="shape_Area"/>
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
    <policy policy="Duplicate" field="generalnameoid"/>
    <policy policy="Duplicate" field="generalname"/>
    <policy policy="Duplicate" field="alternativelabel"/>
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
    <policy policy="Duplicate" field="shape_Area"/>
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
    <default expression="" applyOnUpdate="0" field="generalnameoid"/>
    <default expression="" applyOnUpdate="0" field="generalname"/>
    <default expression="" applyOnUpdate="0" field="alternativelabel"/>
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
    <default expression="" applyOnUpdate="0" field="shape_Area"/>
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
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="generalnameoid" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="generalname" unique_strength="0"/>
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="alternativelabel" unique_strength="0"/>
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
    <constraint notnull_strength="0" exp_strength="0" constraints="0" field="shape_Area" unique_strength="0"/>
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
    <constraint desc="" field="generalnameoid" exp=""/>
    <constraint desc="" field="generalname" exp=""/>
    <constraint desc="" field="alternativelabel" exp=""/>
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
    <constraint desc="" field="shape_Area" exp=""/>
  </constraintExpressions>
  <expressionfields/>
  <attributeactions>
    <defaultAction value="{00000000-0000-0000-0000-000000000000}" key="Canvas"/>
  </attributeactions>
  <attributetableconfig sortExpression="" actionWidgetStyle="dropDown" sortOrder="0">
    <columns>
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
      <column width="-1" type="field" name="generalnameoid" hidden="0"/>
      <column width="-1" type="field" name="generalname" hidden="0"/>
      <column width="-1" type="field" name="alternativelabel" hidden="0"/>
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
      <column width="-1" type="field" name="fid" hidden="0"/>
      <column width="-1" type="field" name="objectid" hidden="0"/>
      <column width="-1" type="field" name="shape_Length" hidden="0"/>
      <column width="-1" type="field" name="shape_Area" hidden="0"/>
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
    <field editable="1" name="Shape__Area"/>
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
    <field editable="1" name="generalname"/>
    <field editable="1" name="generalnameoid"/>
    <field editable="1" name="lastupdate"/>
    <field editable="1" name="msoid"/>
    <field editable="1" name="objectid"/>
    <field editable="1" name="objectmoddate"/>
    <field editable="1" name="planimetricaccuracy"/>
    <field editable="1" name="processstate"/>
    <field editable="1" name="relevance"/>
    <field editable="1" name="shape_Area"/>
    <field editable="1" name="shape_Length"/>
    <field editable="1" name="shapeuuid"/>
    <field editable="1" name="startdate"/>
    <field editable="1" name="topoid"/>
    <field editable="1" name="urbanity"/>
    <field editable="1" name="verticalaccuracy"/>
  </editable>
  <labelOnTop>
    <field name="OBJECTID" labelOnTop="0"/>
    <field name="Shape__Area" labelOnTop="0"/>
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
    <field name="generalname" labelOnTop="0"/>
    <field name="generalnameoid" labelOnTop="0"/>
    <field name="lastupdate" labelOnTop="0"/>
    <field name="msoid" labelOnTop="0"/>
    <field name="objectid" labelOnTop="0"/>
    <field name="objectmoddate" labelOnTop="0"/>
    <field name="planimetricaccuracy" labelOnTop="0"/>
    <field name="processstate" labelOnTop="0"/>
    <field name="relevance" labelOnTop="0"/>
    <field name="shape_Area" labelOnTop="0"/>
    <field name="shape_Length" labelOnTop="0"/>
    <field name="shapeuuid" labelOnTop="0"/>
    <field name="startdate" labelOnTop="0"/>
    <field name="topoid" labelOnTop="0"/>
    <field name="urbanity" labelOnTop="0"/>
    <field name="verticalaccuracy" labelOnTop="0"/>
  </labelOnTop>
  <reuseLastValue>
    <field reuseLastValue="0" name="OBJECTID"/>
    <field reuseLastValue="0" name="Shape__Area"/>
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
    <field reuseLastValue="0" name="generalname"/>
    <field reuseLastValue="0" name="generalnameoid"/>
    <field reuseLastValue="0" name="lastupdate"/>
    <field reuseLastValue="0" name="msoid"/>
    <field reuseLastValue="0" name="objectid"/>
    <field reuseLastValue="0" name="objectmoddate"/>
    <field reuseLastValue="0" name="planimetricaccuracy"/>
    <field reuseLastValue="0" name="processstate"/>
    <field reuseLastValue="0" name="relevance"/>
    <field reuseLastValue="0" name="shape_Area"/>
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
  <layerGeometryType>2</layerGeometryType>
</qgis>
