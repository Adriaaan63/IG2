#pragma once
#include "IG2Object.h"
class Rueda : public IG2Object
{
public:
	Rueda(Vector3 pos, SceneNode* node, SceneManager* sceneManager, Vector3 escala, int n, int n_villano) :
		IG2Object(pos, node->createChildSceneNode("rueda" + to_string(n_villano) + to_string(n)), sceneManager, "sphere.mesh") {
		setMaterialName("materialAspasEnemigo");
		setScale(escala);
	}
	~Rueda() {}
	virtual void init() {}
};


