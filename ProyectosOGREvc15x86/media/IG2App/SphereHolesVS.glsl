#version 330 core

layout(location = 0) in vec3 in_position; // Posición del vértice
layout(location = 1) in vec3 in_normal;   // Normal del vértice

uniform mat4 worldViewProj; // Matriz de transformación de la cámara
uniform float flipping; // Parámetro para la inversión de la cara

out vec3 frag_position;  // Posición del fragmento
out vec3 frag_normal;    // Normal del fragmento
out float frontFace;     // Indica si la cara es frontal o trasera

void main()
{
    // Transformar la posición del vértice
    vec4 worldPos = vec4(in_position, 1.0);
    gl_Position = worldViewProj * worldPos;

    // Pasar la posición y la normal al fragmento
    frag_position = in_position;
    frag_normal = normalize(in_normal);

    // Determinar si la cara es frontal o trasera
    frontFace = float(gl_FrontFacing);
}


