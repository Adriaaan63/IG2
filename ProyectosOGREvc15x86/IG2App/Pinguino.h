#pragma once
#include "IG2Object.h"
class Pinguino : public IG2Object
{
public:
	Pinguino(Vector3 pos, SceneNode* node, SceneManager* sceneManager, Vector3 escala, int n_villano) :
		IG2Object(pos, node->createChildSceneNode("pinguino" + to_string(n_villano)), sceneManager, "penguin.mesh") {
		/*mNode->scale(escala);*/
		setScale(escala);
	}
	~Pinguino() {}
	virtual void init() {}
};

