#pragma once
#include "IG2Object.h"
#include "OgreAxisAlignedBox.h"
class Laberinto;
class Personaje: public IG2Object
{
protected:
	Vector3 dir;
	Vector3 next_dir;
	Laberinto* lab;

public:
	Personaje(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh, Laberinto* lab, Vector3 dir, Vector3 next_dir);
	virtual ~Personaje();
	virtual void init() {};

	void giro();

	/*virtual void frameRendered(const Ogre::FrameEvent& evt) const = 0;*/
};

