#include "Personaje.h"
#include "Laberinto.h"
Personaje::Personaje(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh, Laberinto* lab, Vector3 dir, Vector3 next_dir) :
    IG2Object(pos, node, sceneManager, mesh), lab(lab), dir(dir), next_dir(next_dir) {
};
Personaje:: ~Personaje() {

};

void Personaje::giro() {
    
        Vector3 nextPosition = Vector3(next_dir.x * TILE_WIDTH + getPosition().x, 0, next_dir.z * TILE_HEIGHT + getPosition().z);
        Vector3 enFrentePosition = Vector3(dir.x * TILE_WIDTH + getPosition().x, 0, dir.z * TILE_HEIGHT + getPosition().z);

        // Verificar si lab no es nulo antes de llamar a esTrapasable
        if (lab->esTrapasable(nextPosition)) {
            Quaternion q = this->getOrientation().getRotationTo(next_dir);
            mNode->rotate(q);

            dir = next_dir;
        }
        else if (!lab->esTrapasable(enFrentePosition)) {
            dir = Vector3(0, 0, 0);
        }
    
}