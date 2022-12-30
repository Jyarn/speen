#version 330 core
layout (location = 0) in vec2 aPos;
out vec4 vColor;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    vColor = vec4(aPos, aPos.x*aPos.y, 1.0);
}
