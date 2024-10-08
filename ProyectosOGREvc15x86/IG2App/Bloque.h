#pragma once
#include "IG2Object.h"
class Bloque : public IG2Object
{
private:
    bool traspasable;
public:
    Bloque(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh, bool traspasable)
        : IG2Object(pos, node, sceneManager, mesh), traspasable(traspasable)  {}
    ~Bloque() {

    }
    void init() override {}
    bool esTraspasable() const {
        return traspasable;
    }
};

