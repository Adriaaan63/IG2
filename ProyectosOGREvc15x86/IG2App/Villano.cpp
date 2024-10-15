#include "Villano.h"
#include "Laberinto.h"
void Villano::createVillano() {

}
void Villano::frameRendered(const Ogre::FrameEvent& evt) {
    if (mNode == nullptr || lab == nullptr) {
        return;
    }
    //calcular la nueva direccion que minimice la distancia con el heroe
    if (fmod(getPosition().x, TILE_WIDTH) == 0 && fmod(getPosition().z, TILE_HEIGHT) == 0) {
        next_dir= nuevaDireccion();
        giro();
    }
    move(dir);
}
Vector3 Villano::nuevaDireccion() {
    std::vector<Vector3> posiblesDirecciones = lab->getDireccionesTraspasables(getPosition());
    Vector3 posicionHeroe = lab->getHeroe()->getPosition();
    float distanciaMinima = std::numeric_limits<float>::max();
    Vector3 mejorDireccion;
    for (const auto& dir : posiblesDirecciones) {
        // Evitar giros de 180 grados
        if (dir != -this->dir) {
            Vector3 siguientePosicion = Vector3(dir.x * TILE_WIDTH + getPosition().x, 0, dir.z * TILE_HEIGHT + getPosition().z);
            // Calcular la distancia al héroe
            float distancia = hypot(posicionHeroe.x - siguientePosicion.x, posicionHeroe.z - siguientePosicion.z);
            if (distancia < distanciaMinima) {
                distanciaMinima = distancia;
                mejorDireccion = dir;
            }
        }
    }
    return mejorDireccion;
}