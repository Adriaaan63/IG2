#pragma once
#include "IG2Object.h"
using namespace Ogre;
class Pala: public IG2Object
{
public:
	Pala(Vector3 initPos, SceneNode* node, SceneManager* sceneMng,Vector3 tam, int i, int helice);
	~Pala() {
		delete cabeza;
	};
	SceneNode* getMNode() const {
		return mNode;
	}
private:
	IG2Object* cabeza;
};

