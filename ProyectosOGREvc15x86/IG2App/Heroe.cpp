#include "Heroe.h"
#include "Laberinto.h"

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

    return true;
}
void Heroe::frameRendered(const Ogre::FrameEvent& evt) {
    if (mNode == nullptr || lab == nullptr) {
        return;
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
        cout << puntos << endl;
        InfoTextBox->setCaption("Puntos: " + std::to_string(puntos));
    }
    move(dir * speed);
}
