#pragma once
#include "IG2Object.h"
class Brazo : public IG2Object
{
public:
	Brazo(Vector3 pos, SceneNode* node, SceneManager* sceneManager) :
		IG2Object(pos, node, sceneManager)
	{
		//composicion de la pierna
			/*pierna.push_back(new IG2Object())*/
	}
	~Brazo() {

	}
private:
	std::vector<IG2Object*> brazo;
};

