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
	int vidas;
public:
	Personaje(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh, Laberinto* lab, Vector3 dir, Vector3 next_dir, int _vidas);
	Personaje(Vector3 pos, SceneNode* node, SceneManager* sceneManager, Laberinto* lab, Vector3 dir, Vector3 next_dir, int vidas);
	virtual ~Personaje();
	virtual void init() {};

	void giro();
	int getVidas() const { return vidas; };

	/*virtual void frameRendered(const Ogre::FrameEvent& evt) const = 0;*/
};

