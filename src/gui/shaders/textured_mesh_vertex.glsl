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
