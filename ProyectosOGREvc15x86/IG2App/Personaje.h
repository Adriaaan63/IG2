#pragma once
#include "IG2Object.h"
#include "Laberinto.h"
#include "OgreAxisAlignedBox.h"

class Personaje: public IG2Object
{
protected:
	Vector3 dir;
	Vector3 next_dir;
	Laberinto* lab;

public:
	Personaje(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh, Laberinto* lab, Vector3 dir, Vector3 next_dir) :
		IG2Object(pos, node, sceneManager, mesh), lab(lab), dir(dir), next_dir(next_dir) {
	}
	~Personaje() {

	}
	void init() override {};

	void giro();

	/*virtual void frameRendered(const Ogre::FrameEvent& evt) const = 0;*/
};

