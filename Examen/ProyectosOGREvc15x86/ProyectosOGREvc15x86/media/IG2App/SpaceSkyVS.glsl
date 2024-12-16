#version 330 core
in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjMat;
uniform float sintime; // Variable para el tiempo
out vec2 vUv0;
out float zf;
out float tiempo;

void main() {
    // Calcular el factor de zoom ZF a partir de sintime
    float ZF = sintime * 1 + 2.0;

    // Centrar las coordenadas UV en el rango [-0.5, 0.5]
    vec2 uvCentered = uv0 - vec2(0.5, 0.5);

    // Aplicar el zoom
    uvCentered *= ZF;

    // Trasladar las coordenadas UV al rango [0, 1]
    vUv0 = uvCentered + vec2(0.5, 0.5);

    // Pasar el valor del factor de zoom para el fragment shader
    zf = ZF;
    tiempo = sintime;
    // Calcular la posición final del vértice
    gl_Position = modelViewProjMat * vertex;
}
