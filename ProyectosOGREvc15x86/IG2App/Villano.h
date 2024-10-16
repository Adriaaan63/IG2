#pragma once
#include "Personaje.h"
#include "OgreAxisAlignedBox.h"


class Villano : public Personaje
{
private:
	std::vector<IG2Object*> bodyVillano;
	void createVillano();

public:
	Villano(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh, Laberinto* lab) :
		Personaje(pos, node, sceneManager, mesh, lab, Vector3(0,0,0), Vector3(0, 0, 0),1) {
		
	};
	Villano(Vector3 pos, SceneNode* node, SceneManager* sceneManager, Laberinto* lab) :
		Personaje(pos, node, sceneManager, lab, Vector3(0, 0, 0), Vector3(0, 0, 0), 1) {
		createVillano();

	};

	~Villano() {

	};
	virtual void init() {};

	virtual void frameRendered(const Ogre::FrameEvent& evt);

	Vector3 nuevaDireccion();
};

