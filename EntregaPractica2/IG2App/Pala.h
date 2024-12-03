#pragma once
#include "IG2Object.h"
class Pala: public IG2Object
{
public:
	Pala(Vector3 pos, SceneNode* node, SceneManager* sceneManager, Vector3 escala,int n, int i,int n_villano) :
		IG2Object(pos, node->createChildSceneNode(to_string(n_villano) + to_string(n) + "pala" + std::to_string(i)), sceneManager, "cube.mesh") {
		setMaterialName("materialAspasEnemigo");
		setScale(escala);
	}
	~Pala() {}
	virtual void init(){}
};

