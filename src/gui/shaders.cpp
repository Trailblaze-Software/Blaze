#include "gui/shaders.hpp"

#include "gui/point_cloud_visualization.hpp"

// Analytic ray-traced sphere impostors for point cloud rendering
const char* POINT_VERTEX_SHADER_PROLOGUE = R"(
    #version 330 core
    in vec3 local_position;
    in float classification;
    in vec3 file_color;
    in float has_file_rgb;
    uniform float point_radius_m;   // world-space sphere radius (metres)
    uniform float viewport_height;  // viewport height in pixels
    uniform float fov_rad;          // vertical field of view (radians)
    uniform mat4 u_view;
    uniform mat4 u_proj;
    uniform vec3 point_offset;
    uniform int color_mode;
    uniform vec3 fixed_color;
    uniform float point_alpha;
    out vec4 vtx_color;
    out vec3 eye_center;            // sphere centre in eye space
    out float eye_radius;
    flat out uint vtx_point_id;
)";

const char* POINT_VERTEX_SHADER_MAIN = R"(
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
        // Sprite diameter in pixels = 2 * R * focal_length / depth.
        float depth = max(-eye.z, 1e-4);
        float proj_scale = viewport_height / (2.0 * tan(fov_rad * 0.5));
        gl_PointSize = clamp(2.0 * point_radius_m * proj_scale / depth, 1.0, 4096.0);
        // gl_VertexID includes the glDrawArrays(first, ...) offset, so this
        // tracks the global index into octree.points() for FBO picking.
        vtx_point_id = uint(gl_VertexID) + 1u;
    }
)";

const char* POINT_FRAGMENT_SHADER = R"(
    #version 330 core
    in vec4 vtx_color;
    in vec3 eye_center;
    in float eye_radius;
    flat in uint vtx_point_id;
    uniform mat4 u_proj;
    uniform int u_layer_slot;      // 1-based, 0 suppresses pick output
    out vec4 fragColor;
    layout(location = 1) out uvec2 pickData;
    void main() {
        // Reconstruct the eye-space ray through this fragment. The sprite spans
        // the sphere's silhouette: UV in [-1,1] maps to a lateral offset of
        // R metres on the tangent plane at the sphere's depth.
        vec2 uv = gl_PointCoord * 2.0 - 1.0;
        uv.y = -uv.y;
        vec3 ray_dir = normalize(vec3(eye_center.xy + uv * eye_radius, eye_center.z));

        // Ray from the eye (origin) vs analytic sphere: |t*dir - center|^2 = r^2.
        float b = dot(ray_dir, eye_center);
        float c = dot(eye_center, eye_center) - eye_radius * eye_radius;
        float disc = b * b - c;
        if (disc < 0.0) discard;
        float t = b - sqrt(disc);
        vec3 hit = ray_dir * t;              // eye-space surface point
        vec3 normal = normalize(hit - eye_center);

        // Exact, projection-correct depth so spheres interlock without z-fighting.
        vec4 clip = u_proj * vec4(hit, 1.0);
        gl_FragDepth = 0.5 * (clip.z / clip.w) + 0.5;

        // Eye-space lighting stays consistent as the camera orbits.
        vec3 light_dir = normalize(vec3(0.3, 0.5, 0.8));
        float lighting = 0.4 + 0.6 * max(dot(normal, light_dir), 0.0);
        fragColor = vec4(vtx_color.rgb * lighting, vtx_color.a);
        // pickData.x = global point index + 1; pickData.y = layer slot (1-based).
        pickData = u_layer_slot > 0 ? uvec2(vtx_point_id, uint(u_layer_slot)) : uvec2(0u, 0u);
    }
)";

// Simple colored mesh shaders (used for DEM, slope, contours)
const char* MESH_VERTEX_SHADER = R"(
    #version 330 core
    in vec3 position;
    in vec3 color;
    uniform mat4 proj_matrix;
    out vec3 vtx_color;
    out vec3 vtx_world_pos;
    void main() {
        vtx_color = color;
        vtx_world_pos = position;
        gl_Position = proj_matrix * vec4(position, 1.0);
    }
)";

const char* MESH_FRAGMENT_SHADER = R"(
    #version 330 core
    in vec3 vtx_color;
    in vec3 vtx_world_pos;
    uniform float layer_alpha;
    out vec4 fragColor;
    void main() {
        vec3 dx = dFdx(vtx_world_pos);
        vec3 dy = dFdy(vtx_world_pos);
        vec3 n = normalize(cross(dx, dy));
        if (!gl_FrontFacing) {
            n = -n;
        }
        vec3 light_dir = normalize(vec3(0.65, 0.35, 0.67));
        float diffuse = clamp(dot(n, light_dir), 0.0, 1.0);
        float lighting = mix(0.45, 1.1, diffuse);
        fragColor = vec4(vtx_color * lighting, 0.92 * layer_alpha);
    }
)";

// Textured mesh shaders (used for textured DEM with orthophoto)
const char* TEXTURED_MESH_VERTEX_SHADER = R"(
    #version 330 core
    in vec3 position;
    in vec2 texcoord;
    uniform mat4 proj_matrix;
    out vec2 vtx_texcoord;
    out vec3 vtx_world_pos;
    void main() {
        vtx_texcoord = texcoord;
        vtx_world_pos = position;
        gl_Position = proj_matrix * vec4(position, 1.0);
    }
)";

const char* TEXTURED_MESH_FRAGMENT_SHADER = R"(
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
)";
