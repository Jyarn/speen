#version 460 core
layout (location = 0) in vec2 aPos;
out vec4 vColor;

uniform vec2 screenCoord;
uniform vec2 trans;

vec2 toNDC (in vec2 i) {
    vec2 o;

    vec2 t = vec2(1/screenCoord.x, 1/screenCoord.y);

    o.x = (2.0*t.x*i.x) - 1.0;
    o.y = (2.0*t.y*i.y) - 1.0;
    return o;
}

void main() {
    vec2 d = toNDC(aPos+trans);
    gl_Position = vec4(d, 0.0, 1.0);
    vColor = vec4(d, d.x*d.y, 1.0);
}
