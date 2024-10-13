#pragma once
#include "Personaje.h"
#include "OgreAxisAlignedBox.h"

class Heroe : public Personaje 
{
private:
	int puntos;

public:
	Heroe(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh,Laberinto* lab ): 
		Personaje(pos, node, sceneManager, mesh, lab, Vector3(0, 0, 1), Vector3(0, 0, 1)), puntos(0){
		
	}
	~Heroe() {

	}
	void init() override {}

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	virtual void frameRendered(const Ogre::FrameEvent& evt);
};

