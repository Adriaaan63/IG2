#include "Heroe.h"

bool Heroe::keyPressed(const OgreBites::KeyboardEvent& evt) {
    if (evt.keysym.sym == SDLK_UP) {
        move(Vector3(0, 0, -5));
    }
    else if (evt.keysym.sym == SDLK_DOWN) {
        move(Vector3(0, 0, 5));
    }
    else if (evt.keysym.sym == SDLK_LEFT) {
        move(Vector3(-5, 0, 0));
    }
    else if (evt.keysym.sym == SDLK_RIGHT) {
        move(Vector3(5, 0, 0));
    }
    return true;
}