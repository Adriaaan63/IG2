#pragma once
#include "IG2Object.h"
class Rueda : public IG2Object
{
public:
	Rueda(Vector3 pos, SceneNode* node, SceneManager* sceneManager, Vector3 escala, int n) :
		IG2Object(pos, node->createChildSceneNode("rueda" + to_string(n)), sceneManager, "sphere.mesh") {
		/*mNode->scale(escala);*/
		setScale(escala);
	}
	~Rueda() {}
	virtual void init() {}
};


