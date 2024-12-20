#include "Heroe.h"
#include "Laberinto.h"

bool Heroe::keyPressed(const OgreBites::KeyboardEvent& evt) {
    if (!visible) {
        return true;
    }

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

    return true;
}
void Heroe::frameRendered(const Ogre::FrameEvent& evt) {
    if (!visible) {
        return;
    }
    if (mNode == nullptr || lab == nullptr) {
        return;
    }
    if (light != nullptr) {
        light->setPosition(getPosition().x, 1000, getPosition().z);
    }
    if (fmod(getPosition().x, TILE_WIDTH) == 0 && fmod(getPosition().z, TILE_HEIGHT) == 0) {
        giro();
    }
    else {
        if (dir == -next_dir) {
            giro();
        }
    }
   
    if (lab->getBloque(getPosition())->getAABB().intersects(this->getAABB()) && lab->getBloque(getPosition())->isVisible()) {
        puntos += 10;
        lab->getBloque(getPosition())->setVisible(false);
        updateText();
    }

    for (int i = 0; i < lab->getVillanos().size(); i++)
    {
        if (lab->getVillanos()[i]->getAABB().intersects(this->getAABB())) {
            vidas -= 1;
            updateText();
            this->setPosition(initialPosition);
            for (int i = 0; i < lab->getVillanos().size(); i++) {
                lab->getVillanos()[i]->setPosition(lab->getVillanos()[i]->getInitialPos());
                dir = Vector3(0, 0, 0);
            }
        }
    }
    move(dir * speed);
    
}

void Heroe::updateText() {
    TextInfoPlayer->clearText();
    TextInfoPlayer->appendText("Puntos: " + std::to_string(puntos) + "\n");
    TextInfoPlayer->appendText("Vidas: " + std::to_string(vidas));
}
