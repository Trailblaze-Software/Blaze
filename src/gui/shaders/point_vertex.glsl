#version 330 core
in vec3 local_position;
in float classification;
in vec3 file_color;
in float has_file_rgb;
uniform float point_radius_m;
uniform float viewport_height;
uniform float fov_rad;
uniform mat4 u_view;
uniform mat4 u_proj;
uniform vec3 point_offset;
uniform int color_mode;
uniform vec3 fixed_color;
uniform float point_alpha;
out vec4 vtx_color;
out vec3 eye_center;
out float eye_radius;
flat out uint vtx_point_id;

// CLASSIFICATION_COLOR_FUNCTION

void main() {
    vec3 position = local_position + point_offset;
    vec4 eye = u_view * vec4(position, 1.0);
    eye_center = eye.xyz;
    eye_radius = point_radius_m;

    vec3 rgb = fixed_color;
    if (color_mode == 0) {
        if (has_file_rgb > 0.5) {
            rgb = file_color;
        } else {
            rgb = classification_color(int(classification + 0.5));
        }
    } else if (color_mode == 1) {
        rgb = classification_color(int(classification + 0.5));
    }
    vtx_color = vec4(rgb, point_alpha);

    gl_Position = u_proj * eye;
    float depth = max(-eye.z, 1e-4);
    float proj_scale = viewport_height / (2.0 * tan(fov_rad * 0.5));
    gl_PointSize = clamp(2.0 * point_radius_m * proj_scale / depth, 1.0, 4096.0);
    vtx_point_id = uint(gl_VertexID) + 1u;
}
