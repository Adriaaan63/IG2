#pragma once
#include "IG2Object.h"
#include <OgreParticleSystem.h>
class Bloque : public IG2Object
{
private:
    bool traspasable;
public:
    Bloque(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh, bool _traspasable, string material)
        : IG2Object(pos, node, sceneManager, mesh), traspasable(_traspasable) { 
          setMaterialName(material);
    }
    ~Bloque() {

    }
    void init() override {}
    bool esTraspasable() const {
        return traspasable;
    }
};

