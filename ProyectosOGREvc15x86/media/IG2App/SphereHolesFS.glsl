#version 330 core

in vec3 frag_position;  // Posición del fragmento
in vec3 frag_normal;    // Normal del fragmento
in float frontFace;     // Indica si la cara es frontal o trasera

uniform sampler2D corrosionTexture; // Textura de corrosión
uniform sampler2D bumpyTexture;     // Textura de metal rugoso
uniform sampler2D dirtTexture;      // Textura de suciedad

out vec4 frag_color; // Color final del fragmento

void main()
{
    // Calcular la distancia desde el centro de la esfera para determinar la aplicación de texturas
    float distanceFromCenter = length(frag_position);

    // Usar la normal para identificar si la cara es exterior o interior
    bool isOuter = (frontFace > 0.5);

    // Controlar qué textura aplicar basado en la ubicación (frontal o trasera)
    vec4 finalColor;

    if (isOuter)
    {
        // Aplicar la textura de corrosión en el exterior
        vec2 uv = frag_position.xy / frag_position.z; // Ejemplo de mapeo de coordenadas UV
        finalColor = texture(corrosionTexture, uv);
    }
    else
    {
        // Aplicar la textura de suciedad en el interior
        vec2 uv = frag_position.xy / frag_position.z; // Ejemplo de mapeo de coordenadas UV
        finalColor = texture(dirtTexture, uv);
    }

    // Composición final del color con la textura de metal rugoso para detalles
    vec4 bumpyColor = texture(bumpyTexture, frag_position.xy);
    frag_color = mix(finalColor, bumpyColor, 0.5); // Mezcla de texturas
}

