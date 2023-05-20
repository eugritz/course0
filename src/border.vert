#version 120

uniform float off;

void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = vec4(
        (cos(3.0 * gl_Position.x - 0.5 + 1.5 + off) + 1.3) / 3.0,
        (cos(3.0 * gl_Position.x - 0.5       + off) + 1.4) / 3.2,
        (cos(3.0 * gl_Position.x - 0.5 - 1.0 + off) + 1.3) / 3.0,
        1.0
    );
}
