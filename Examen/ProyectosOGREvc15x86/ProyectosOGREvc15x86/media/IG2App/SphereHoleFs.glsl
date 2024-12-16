#version 330 core
uniform sampler2D texturaL;  // Textura 1
uniform sampler2D texturaM;  // Textura 2
uniform sampler2D texturaN;  // Textura 3

uniform float BF;            // Factor de mezcla (Blending factor)
uniform float intLuzAmb;
uniform float flipping;
in vec2 vUv0;                // Coordenadas UV modificadas desde el vertex shader
out vec4 fFragColor;         // Color final del fragmento

void main() {
    // Obtener los colores de las texturas usando las coordenadas UV
   bool frontFacing = (flipping > -1)? gl_FrontFacing : !gl_FrontFacing;
    vec3 colorL = vec3(texture(texturaL, vUv0));
    vec3 colorM = vec3(texture(texturaM, vUv0));
    vec3 colorN = vec3(texture(texturaN, vUv0));

    // Mezclar los colores de las texturas usando el blending factor
    vec3 colorchecker = colorL;
    vec3 color;
    if(frontFacing){
        if(colorchecker == vec3(0,0,0)){
                discard;
            }
        else if(colorchecker == vec3(1,1,1)){
            color = colorN;
        }
    }
    else{
         if(colorchecker == vec3(0,0,0)){
                discard;
            }
        else if(colorchecker == vec3(1,1,1)){
            color = colorN;
        }
    }
    
    color *= intLuzAmb;
    // Establecer el color final del fragmento
    fFragColor = vec4(color, 1.0);
}
