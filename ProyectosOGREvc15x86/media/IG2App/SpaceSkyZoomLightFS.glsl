#version 330 core
uniform sampler2D texturaL;  // Textura 1
uniform sampler2D texturaM;  // Textura 2

uniform float BF;            // Factor de mezcla (Blending factor)

uniform float minL;
uniform float maxL;

in vec2 vUv0;                // Coordenadas UV modificadas desde el vertex shader
in float zf;                 // Factor de zoom desde el vertex shader
in float tiempo;

out vec4 fFragColor;         // Color final del fragmento

void main() {
    // Obtener los colores de las texturas usando las coordenadas UV
    vec3 colorL = vec3(texture(texturaL, vUv0));
    vec3 colorM = vec3(texture(texturaM, vUv0));

    // Mezclar los colores de las texturas usando el blending factor
    vec3 color = mix(colorL, colorM, BF);

    float diff = maxL - minL;
    float lf = minL + (diff*((tiempo + 1) / 2));

    // Aplicar el factor de zoom y la luz
    color *= zf * lf;

    // Establecer el color final del fragmento
    fFragColor = vec4(color, 1.0);
}
