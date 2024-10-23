#pragma once
#include "Pala.h"
#include "IG2Object.h"
#include <OgreVector3.h>

class Helices : public IG2Object {
private:
    std::vector<Pala*> palas;

public:
    Helices(Vector3 pos, SceneNode* node, SceneManager* sceneManager, int numPalas, Vector3 escala, int n);

    ~Helices() {
        for (auto& e : palas) {
            delete e;
        }
        palas.clear();
    }

    virtual void init() {}
    virtual void frameRendered(const Ogre::FrameEvent& evt);
};
