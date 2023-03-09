uniform float off;
void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = vec4(
        (cos(2.0 * gl_Position.x - 0.5 + 1.5 + off) + 1.0) / 2.5f,
        (cos(2.0 * gl_Position.x - 0.5       + off) + 1.0) / 2.5f,
        (cos(2.0 * gl_Position.x - 0.5 - 1.0 + off) + 1.0) / 2.5f,
        1.0
    );
}
