#version 330 core
in vec4 vtx_color;
in vec3 eye_center;
in float eye_radius;
flat in uint vtx_point_id;
uniform mat4 u_proj;
uniform int u_layer_slot;
out vec4 fragColor;
layout(location = 1) out uvec2 pickData;

void main() {
    vec2 uv = gl_PointCoord * 2.0 - 1.0;
    uv.y = -uv.y;
    vec3 ray_dir = normalize(vec3(eye_center.xy + uv * eye_radius, eye_center.z));

    float b = dot(ray_dir, eye_center);
    float c = dot(eye_center, eye_center) - eye_radius * eye_radius;
    float disc = b * b - c;
    if (disc < 0.0) discard;
    float t = b - sqrt(disc);
    vec3 hit = ray_dir * t;
    vec3 normal = normalize(hit - eye_center);

    vec4 clip = u_proj * vec4(hit, 1.0);
    gl_FragDepth = 0.5 * (clip.z / clip.w) + 0.5;

    vec3 light_dir = normalize(vec3(0.3, 0.5, 0.8));
    float lighting = 0.4 + 0.6 * max(dot(normal, light_dir), 0.0);
    fragColor = vec4(vtx_color.rgb * lighting, vtx_color.a);
    pickData = u_layer_slot > 0 ? uvec2(vtx_point_id, uint(u_layer_slot)) : uvec2(0u, 0u);
}
