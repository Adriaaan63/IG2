#pragma once
#include "IG2Object.h"
#include <OgreParticleSystem.h>
class EmisoresParticulas : public IG2Object
{
private:
    int type;
public:
    EmisoresParticulas(Vector3 pos, SceneNode* node, SceneManager* sceneManager, int n_particle_system, int _type)
        : IG2Object(pos, node, sceneManager), type(_type) {
        if (type == 0) {
            ParticleSystem* pSys = mSM->createParticleSystem("pslaberintoSmoke" + n_particle_system, "laberintoSmoke");
            pSys->setEmitting(true);
            mNode->attachObject(pSys);
        }
        else if (type == 1) {
            ParticleSystem* pSys = mSM->createParticleSystem("psfire" + n_particle_system, "fireCinematica");
            pSys->setEmitting(true);
            mNode->attachObject(pSys);
        }
    }
    ~EmisoresParticulas() {}
    void init() override {}
};

