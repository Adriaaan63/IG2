#pragma once
#include "IG2Object.h"
#include "Helice.h"
class Avion: public IG2Object
{
public:
	Avion(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);
	~Avion() {

	}
	void createAvion(SceneManager* sceneMng);
	void frameRendered(const Ogre::FrameEvent& evt);
private:
	std::vector<IG2Object*> composicion;
};

