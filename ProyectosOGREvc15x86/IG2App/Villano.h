#pragma once
#include "Personaje.h"
#include "OgreAxisAlignedBox.h"


class Villano : public Personaje
{
private:
	std::vector<IG2Object*> bodyVillano;
	void createVillano();

public:
	Villano(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh, Laberinto* lab, Vector3 dir, Vector3 next_dir) :
		Personaje(pos, node, sceneManager, mesh, lab, dir, next_dir) {
		/*createVillano();*/
		
	};

	~Villano() {

	};
	virtual void init() {};

	virtual void frameRendered(const Ogre::FrameEvent& evt);

	Vector3 nuevaDireccion();
};

