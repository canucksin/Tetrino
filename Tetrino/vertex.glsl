#version 150  //GLSL Version 1.5

in vec4 vPosition;
in vec4 vColor;
out vec4 color;

void main() {
    gl_Position = vPosition;
    color = vColor;
}