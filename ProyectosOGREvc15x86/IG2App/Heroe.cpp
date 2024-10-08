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
    if (fmod(getPosition().x, 100.0f) == 0 && fmod(getPosition().z, 100.0f) == 0) {
        Vector3 nextPosition(next_dir.x * 100 + getPosition().x, 0, next_dir.z * 100 + getPosition().z);

        // Verificar si lab no es nulo antes de llamar a esTrapasable
        if (lab->esTrapasable(nextPosition)) {
            float dot = dir.dotProduct(next_dir);
            float angle = Ogre::Math::ACos(dot).valueDegrees();

            Vector3 cross = dir.crossProduct(next_dir);
            if (cross.y < 0) {
                angle = -angle;
            }

            if (angle != 0) {
                mNode->yaw(Degree(angle));
            }

            dir = next_dir;
        }
        else {
            dir = Vector3(0, 0, 0);
        }
    }

    move(dir);
}
