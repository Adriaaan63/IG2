#pragma once
#include "IG2Object.h"
#include "OgreAxisAlignedBox.h"
#include <OgreTrays.h>
#include <OgreOverlaySystem.h>
#include <OgreAnimation.h>
#include <OgreAnimationTrack.h>
#include <OgreKeyFrame.h> 
using namespace Ogre;
enum class PlayerState {
	Jumping,
	Running,
	Fighting,
	Idle
};
class playerAnimation: public IG2Object
{
public:
	playerAnimation(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);
	~playerAnimation() {

	}

	void addkeyFrame(NodeAnimationTrack* track, TransformKeyFrame* kf, Vector3 pos, Quaternion q, Vector3 scale = {17,19,17}) {
		kf->setTranslate(pos);
		kf->setRotation(q);
		kf->setScale(scale);
	}

	void createAnimation(string animation, AnimationState*& animatioState) {
		animatioState = entity->getAnimationState(animation);
	}
	void activeAnimation(bool loop, bool enable, AnimationState* animatioState) {
		animatioState->setLoop(loop);
		animatioState->setEnabled(enable);
	}

	void createMoveAnimation();
	virtual void frameRendered(const Ogre::FrameEvent& evt);
private:
	AnimationState* moveAnimation;
	AnimationState* danceAnimation;
	AnimationState* jumpAnimationStart;
	AnimationState* jumpAnimationLoop;
	AnimationState* jumpAnimationEnd;
	Vector3 keyframePos;
	int movementLength = 80;
	Vector3 src = Vector3(0, 0, 1);
	Vector3 scale;
	float timer = 0.0f;

	PlayerState determineState(float time);
	void handleJumping(const Ogre::FrameEvent& evt);
	//void handleDancing(const Ogre::FrameEvent& evt);
	void handleRunning(const Ogre::FrameEvent& evt);
	//void handleFighting(const Ogre::FrameEvent& evt);
	void resetToIdle();
};

