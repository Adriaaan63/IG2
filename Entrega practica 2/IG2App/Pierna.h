#pragma once
#include "IG2Object.h"
class Pierna: public IG2Object
{
public:
	Pierna(Vector3 pos, SceneNode* node, SceneManager* sceneManager):
		IG2Object(pos, node, sceneManager)
	{
	//composicion de la pierna
		/*pierna.push_back(new IG2Object())*/
	}
	~Pierna() {

	}
private:
	std::vector<IG2Object*> pierna;
};

