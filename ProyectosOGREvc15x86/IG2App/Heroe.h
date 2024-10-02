#pragma once
#include "IG2Object.h"

class Heroe : public IG2Object
{
private:

public:
	Heroe(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh): 
		IG2Object(pos, node, sceneManager, mesh){}
	~Heroe() {

	}
	void init() override {}
};

