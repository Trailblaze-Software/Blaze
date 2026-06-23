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
