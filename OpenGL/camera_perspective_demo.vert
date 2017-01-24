#version 410
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;

uniform mat4 translate_matrix;
uniform mat4 scale_matrix;
uniform mat4 rot_x_matrix;
uniform mat4 rot_y_matrix;
uniform mat4 rot_z_matrix;

out vec3 colour;

void main() {
    colour = vertex_colour;
    gl_Position = (scale_matrix * translate_matrix * rot_x_matrix * rot_y_matrix * rot_z_matrix) * vec4(vertex_position, 1.0f);
}
