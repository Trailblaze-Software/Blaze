#version 330 core
in vec3 position;
in vec2 texcoord;
in vec3 normal;
uniform mat4 proj_matrix;
uniform float vertical_offset;
out vec2 vtx_texcoord;
out vec3 vtx_normal;
out vec3 vtx_world_pos;

void main() {
    vec3 world_pos = position + vec3(0.0, 0.0, vertical_offset);
    vtx_texcoord = texcoord;
    vtx_normal = normal;
    vtx_world_pos = world_pos;
    gl_Position = proj_matrix * vec4(world_pos, 1.0);
}
