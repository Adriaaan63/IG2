#pragma once
#include "IG2Object.h"
#include "Laberinto.h"

class Heroe : public IG2Object 
{
private:
	Vector3 dir;
	Vector3 next_dir;
	Laberinto* lab;

public:
	Heroe(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh,Laberinto* lab ): 
		IG2Object(pos, node, sceneManager, mesh), lab(lab){
		dir = Vector3(0, 0, 1);
		next_dir = Vector3(0, 0, 1);
	}
	~Heroe() {

	}
	void init() override {}

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	virtual void frameRendered(const Ogre::FrameEvent& evt);
};

