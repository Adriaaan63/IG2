#pragma once
#include "IG2Object.h"
class Bloque : public IG2Object
{
private:

public:
    Bloque(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh)
        : IG2Object(pos, node, sceneManager, mesh)  {}
    void init() override {}
};

