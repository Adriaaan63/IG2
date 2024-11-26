#pragma once
#include "IG2Object.h"
#include <OgreParticleSystem.h>
class EmisoresParticulas : public IG2Object
{
public:
    EmisoresParticulas(Vector3 pos, SceneNode* node, SceneManager* sceneManager, int n_particle_system_bloques)
        : IG2Object(pos, node, sceneManager) {
        ParticleSystem* pSys = mSM->createParticleSystem("pslaberintoSmoke" + n_particle_system_bloques, "example/laberintoSmoke");
        pSys->setEmitting(true);
        mNode->attachObject(pSys);
    }
    ~EmisoresParticulas() {}
    void init() override {}
};

