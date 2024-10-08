#include "Heroe.h"

bool Heroe::keyPressed(const OgreBites::KeyboardEvent& evt) {
    Vector3 newDir;

    if (evt.keysym.sym == SDLK_UP) {
        newDir = Vector3(0, 0, -100);
    }
    else if (evt.keysym.sym == SDLK_DOWN) {
        newDir = Vector3(0, 0, 100);
    }
    else if (evt.keysym.sym == SDLK_LEFT) {
        newDir = Vector3(-100, 0, 0);
    }
    else if (evt.keysym.sym == SDLK_RIGHT) {
        newDir = Vector3(100, 0, 0);
    }
    else {
        return true; 
    }

    float dot = dir.dotProduct(newDir);
    float angle = Ogre::Math::ACos(dot).valueDegrees();

    Vector3 cross = dir.crossProduct(newDir);
    if (cross.y < 0) {
        angle = -angle;
    }

    if (angle != 0) {
        mNode->yaw(Degree(angle));
    }

    dir = newDir;
    move(dir);

    return true;
}
