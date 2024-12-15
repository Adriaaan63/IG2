#pragma once
#include "IG2Object.h"
#include "Helice.h"
#include "EmisorParticulas.h"
class Avion: public IG2Object
{
public:
	Avion(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);
	~Avion() {
		for (auto& p : composicion) {
			delete p;
		}
		composicion.clear();
		for (auto& p : emisoresPart) {
			delete p;
		}
		emisoresPart.clear();
	}
	void createAvion(SceneManager* sceneMng);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
private:
	std::vector<IG2Object*> composicion;
	std::vector<IG2Object*> emisoresPart;

};

