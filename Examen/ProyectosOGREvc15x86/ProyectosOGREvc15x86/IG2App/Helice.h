#pragma once
#include "IG2Object.h"
#include "Pala.h"
using namespace Ogre;
class Helice : public IG2Object
{
public:
	Helice(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int i, int numPalas);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	~Helice() {
		for (auto& p : palas) {
			delete p;
		}
		palas.clear();
	}
private:
	std::vector<Pala*> palas;
};

