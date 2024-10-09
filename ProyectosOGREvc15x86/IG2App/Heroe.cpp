#include "Heroe.h"

bool Heroe::keyPressed(const OgreBites::KeyboardEvent& evt) {
    

    if (evt.keysym.sym == SDLK_UP) {
        next_dir = Vector3(0, 0, -1);
    }
    else if (evt.keysym.sym == SDLK_DOWN) {
        next_dir = Vector3(0, 0, 1);
    }
    else if (evt.keysym.sym == SDLK_LEFT) {
        next_dir = Vector3(-1, 0, 0);
    }
    else if (evt.keysym.sym == SDLK_RIGHT) {
        next_dir = Vector3(1, 0, 0);
    }
    else {
        return true; 
    }

    
    /*move(dir);*/

    

    return true;
}
void Heroe::frameRendered(const Ogre::FrameEvent& evt) {
    if (mNode == nullptr || lab == nullptr) {
        // Salir o manejar el error
        return;
    }
    if (fmod(getPosition().x, TILE_WIDTH) == 0 && fmod(getPosition().z, TILE_HEIGHT) == 0) {
        Vector3 nextPosition = Vector3(next_dir.x * TILE_WIDTH + getPosition().x, 0, next_dir.z * TILE_HEIGHT + getPosition().z);
        Vector3 enFrentePosition = Vector3(dir.x * TILE_WIDTH + getPosition().x, 0, dir.z * TILE_HEIGHT + getPosition().z);

        // Verificar si lab no es nulo antes de llamar a esTrapasable
        if (lab->esTrapasable(nextPosition)) {
            Quaternion q = this->getOrientation().getRotationTo(next_dir);
            mNode->rotate(q);

            dir = next_dir;
        }
        else if(!lab->esTrapasable(enFrentePosition)) {
                dir = Vector3(0, 0, 0);
        }
    }
    if (lab->getBloque(getPosition())->getAABB().intersects(this->getAABB()) && lab->getBloque(getPosition())->isVisible()) {
        puntos += 10;
        lab->getBloque(getPosition())->setVisible(false);
        cout << puntos << endl;
    }
    move(dir);
}
