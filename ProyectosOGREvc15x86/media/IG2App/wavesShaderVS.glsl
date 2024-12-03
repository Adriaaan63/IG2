#version 330 core
in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjMat;
uniform float time; // Variable para el tiempo
uniform vec4 centro;
out vec2 vUv0;

void main() {
    vUv0 = uv0;
    vec4 vertexCoord = vertex;
     float distanceCenter = length(vertex.xyz - centro.xyz);
    vertexCoord.y += sin(vertexCoord.x + (time*0.25)) * 1.0 + sin(vertexCoord.z + (distanceCenter) + (time*25)) * 1.0; 
    gl_Position = modelViewProjMat * vertexCoord;
}