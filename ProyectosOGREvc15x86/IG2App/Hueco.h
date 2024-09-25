#pragma once
#include "Bloque.h"
class Hueco : public Bloque
{
public:
    Hueco(Vector3 pos, SceneNode* node, SceneManager* sceneManager)
        : Bloque(pos, node, sceneManager, "sphere.mesh") {}
    void init() override {}
};
