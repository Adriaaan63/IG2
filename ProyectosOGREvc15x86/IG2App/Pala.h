#pragma once
#include "IG2Object.h"
class Pala: public IG2Object
{
public:
	Pala(Vector3 pos, SceneNode* node, SceneManager* sceneManager, Vector3 escala) :
		IG2Object(pos, node, sceneManager, "cube.mesh") {
		mNode->scale(escala);
	}
	~Pala() {

	}
	virtual void init(){}
};

