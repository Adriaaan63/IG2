#version 330 core

in vec4 vertex;
uniform mat4 modelViewProjMat;
out vec4 vPosition;

void main() {
    gl_Position = modelViewProjMat * vertex;
    vPosition = gl_Position;
}

