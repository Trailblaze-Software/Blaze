#version 330 core
in vec2 vtx_texcoord;
in vec3 vtx_world_pos;
uniform sampler2D dem_texture;
uniform float layer_alpha;
out vec4 fragColor;

void main() {
    vec3 color = texture(dem_texture, vtx_texcoord).rgb;
    vec3 dx = dFdx(vtx_world_pos);
    vec3 dy = dFdy(vtx_world_pos);
    vec3 n = normalize(cross(dx, dy));
    if (!gl_FrontFacing) {
        n = -n;
    }
    vec3 light_dir = normalize(vec3(0.65, 0.35, 0.67));
    float diffuse = clamp(dot(n, light_dir), 0.0, 1.0);
    float lighting = mix(0.45, 1.1, diffuse);
    fragColor = vec4(color * lighting, 0.95 * layer_alpha);
}
