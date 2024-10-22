#pragma once
#include "IG2Object.h"
class Pinguino : public IG2Object
{
public:
	Pinguino(Vector3 pos, SceneNode* node, SceneManager* sceneManager, Vector3 escala) :
		IG2Object(pos, node->createChildSceneNode("pinguino"), sceneManager, "penguin.mesh") {
		/*mNode->scale(escala);*/
		setScale(escala);
	}
	~Pinguino() {}
	virtual void init() {}
};

