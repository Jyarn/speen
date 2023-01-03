#version 460 core
out vec4 FragColour;
in vec4 vColor;

void main () {
    FragColour = vColor;
}