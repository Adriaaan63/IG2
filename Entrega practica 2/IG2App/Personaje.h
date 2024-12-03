#pragma once
#include "IG2Object.h"
#include "OgreAxisAlignedBox.h"
#include <OgreAxisAlignedBox.h>
#include <OgreTrays.h>
#include <OgreOverlaySystem.h>
#include <OgreAnimation.h>
#include <OgreAnimationTrack.h>
#include <OgreKeyFrame.h> 
class Laberinto;
class Personaje: public IG2Object
{
protected:
	Vector3 dir;
	Vector3 next_dir;
	Laberinto* lab;
	int vidas;
	bool visible = true;
	void addkeyFrame(NodeAnimationTrack* track, TransformKeyFrame* kf, Vector3 pos, Quaternion q, Vector3 scale = Vector3(1, 1, 1)) {
		kf->setTranslate(pos);
		kf->setRotation(q);
		kf->setScale(scale);
	}
public:
	Personaje(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh, Laberinto* lab, Vector3 dir, Vector3 next_dir, int _vidas);
	Personaje(Vector3 pos, SceneNode* node, SceneManager* sceneManager, Laberinto* lab, Vector3 dir, Vector3 next_dir, int vidas);
	Personaje(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh);
	virtual ~Personaje();
	virtual void init() {};

	void giro();
	int getVidas() const { return vidas; };
	void setVisiblePersonaje(bool _visible) { 
		visible = _visible; 
		setVisible(_visible);
	};
	
	/*virtual void frameRendered(const Ogre::FrameEvent& evt) const = 0;*/
};

