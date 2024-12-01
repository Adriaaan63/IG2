#version 330 core

in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjMat;
uniform float zoomFactor; 
out vec2 vUv0;

void main() {
    vec2 zoomedUv = uv0 * zoomFactor + (1.0 - zoomFactor) * 0.5;
    vUv0 = zoomedUv;
    gl_Position = modelViewProjMat * vertex;
}
