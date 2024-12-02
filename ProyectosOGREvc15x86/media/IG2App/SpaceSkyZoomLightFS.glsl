#version 330 core

in vec2 vUv0;
uniform sampler2D texturaL;
uniform sampler2D texturaM;
uniform float BF;          
uniform float intLuzAmb;   
uniform float zoomFactor; 
out vec4 fFragColor;

void main() {
    vec3 colorL = vec3(texture(texturaL, vUv0));
    vec3 colorM = vec3(texture(texturaM, vUv0));

    vec3 color = mix(colorL, colorM, BF);

    float zoomFactorAdjusted = zoomFactor;  
    float iluminacionFinal = mix(0.3, 1.0, zoomFactorAdjusted);  
    color *= iluminacionFinal;

    fFragColor = vec4(color, 1.0);
}

