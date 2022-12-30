#version 330 core
layout (location = 0) in vec2 aPos;
out vec4 vColor;

uniform vec2 screenCoord;
uniform vec2 trans;

void main() {
    gl_Position = vec4((aPos + trans) / screenCoord, 0.0, 1.0);
    vColor = vec4(aPos / screenCoord, (aPos.x*aPos.y) / (screenCoord.x*screenCoord.y), 1.0);
}
