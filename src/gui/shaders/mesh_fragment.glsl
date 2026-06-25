#version 330 core
in vec3 vtx_color;
in vec3 vtx_normal;
in vec3 vtx_world_pos;
uniform vec3 light_direction;
uniform vec3 camera_position;
uniform float ambient_light;
uniform float diffuse_light;
uniform float layer_alpha;
out vec4 fragColor;

void main() {
    vec3 n = normalize(vtx_normal);
    vec3 view_dir = normalize(camera_position - vtx_world_pos);
    if (dot(n, view_dir) < 0.0) {
        n = -n;
    }
    float diffuse = clamp(dot(n, light_direction), 0.0, 1.0);
    float lighting = ambient_light + diffuse_light * diffuse;
    fragColor = vec4(vtx_color * lighting * layer_alpha, layer_alpha);
}
