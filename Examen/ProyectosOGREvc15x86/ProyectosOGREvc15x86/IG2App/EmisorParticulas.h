#pragma once
#include "IG2Object.h"
#include <OgreParticleSystem.h>
class EmisorParticulas: public IG2Object
{
public:
	EmisorParticulas(Vector3 pos, SceneNode* node, SceneManager* sceneManager, int n_particle_system_bloques, string emisorParticulas):
		IG2Object(pos, node->createChildSceneNode("sistemaParticulas" + std::to_string(n_particle_system_bloques)), sceneManager) {
		ParticleSystem* sys = mSM->createParticleSystem("sistemaParticulas" + std::to_string(n_particle_system_bloques), emisorParticulas);
		sys->setEmitting(true);
		mNode->attachObject(sys);
	}
};

