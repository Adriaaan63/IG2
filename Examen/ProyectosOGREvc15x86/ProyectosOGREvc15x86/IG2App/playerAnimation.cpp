#include "playerAnimation.h"

playerAnimation::playerAnimation(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) :
	IG2Object(initPos, node->createChildSceneNode("playerAnim"), sceneMng, "Sinbad.mesh"), scale({ 4,5,4 })
{
	setScale(scale);
	keyframePos = getPosition();
	createMoveAnimation();
	createAnimation("JumpStart", jumpAnimationStart);
	createAnimation("JumpLoop", jumpAnimationLoop);
	createAnimation("JumpEnd", jumpAnimationEnd);
	
	
}

void playerAnimation::createMoveAnimation()
{
	Animation* animation = mSM->createAnimation("playerWalking", 14.7);
	animation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);
	TransformKeyFrame* kf;
	// Keyframe 0 (Init state) 
	kf = track->createNodeKeyFrame(0); 
	addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)));
	// Keyframe: rotate 
	kf = track->createNodeKeyFrame(0.5);
	addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(-1, 0, 0)));
	// Keyframe 1: Go to the left 
	kf = track-> createNodeKeyFrame(2); 
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength;
	addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(-1, 0, 0)));
	// Keyframe 2: rotate 
	kf = track->createNodeKeyFrame(2.5);
	addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)));
	//Keyframe 3: got to right
	kf = track->createNodeKeyFrame(6);
	keyframePos += Ogre::Vector3::UNIT_X * movementLength * 2;
	addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)));
	//Keyframe 3: static
	kf = track->createNodeKeyFrame(6.2);
	addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)));
	//Keyframe 3: jump
	kf = track->createNodeKeyFrame(7.6);
	keyframePos += Vector3(250, 400, 0);
	/*keyframePos += Ogre::Vector3::UNIT_X * movementLength;
	keyframePos += Ogre::Vector3::UNIT_Y * movementLength;*/
	addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)));
	//Keyframe 3: jump
	kf = track->createNodeKeyFrame(9);
	keyframePos += Vector3(300, -400, 0);
	/*keyframePos += Ogre::Vector3::UNIT_X * movementLength;
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * movementLength;*/
	addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)));
	//Keyframe 3: static
	kf = track->createNodeKeyFrame(9.2);
	addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)));
	//Keyframe 3: got to right
	kf = track->createNodeKeyFrame(12.7);
	keyframePos += Ogre::Vector3::UNIT_X * movementLength * 2;
	addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)));
	// Keyframe 2: rotate 
	kf = track->createNodeKeyFrame(13.2);
	addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(-1, 0, 0)));
	// Keyframe 1: Go to the left 
	kf = track->createNodeKeyFrame(14.7);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength;
	addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(-1, 0, 0)));
	
	moveAnimation = mSM->createAnimationState("playerWalking"); 
}

void playerAnimation::frameRendered(const Ogre::FrameEvent& evt) {
	PlayerState currentState = determineState(timer);

	switch (currentState) {
	case PlayerState::Jumping:
		handleJumping(evt);
		break;
	case PlayerState::Running:
		handleRunning(evt);
		break;
	case PlayerState::Idle:
		resetToIdle();
		timer = 0.0f; // Reset the timer
		break;
	}

	timer += evt.timeSinceLastFrame;
}

PlayerState playerAnimation::determineState(float time) {
	if (time >= 6.0f && time < 9.2f) {
		return PlayerState::Jumping;
	}
	else if ((time >= 0.0f && time < 6.0f) || (time >= 9.2f && time < 14.7f)) {
		return PlayerState::Running;
	}
	else {
		return PlayerState::Idle;
	}
}

void playerAnimation::handleJumping(const Ogre::FrameEvent& evt) {
	if (timer >= 6.0f && timer < 6.2f) {
		activeAnimation(true, true, jumpAnimationStart);
		jumpAnimationStart->addTime(evt.timeSinceLastFrame);
	}
	else if (timer >= 6.2f && timer < 9.0f) {
		activeAnimation(false, false, jumpAnimationStart);
		activeAnimation(true, true, jumpAnimationLoop);
		jumpAnimationLoop->addTime(evt.timeSinceLastFrame);
	}
	else if (timer >= 9.0f) {
		activeAnimation(false, false, jumpAnimationLoop);
		activeAnimation(true, true, jumpAnimationEnd);
		jumpAnimationEnd->addTime(evt.timeSinceLastFrame);
	}
	moveAnimation->addTime(evt.timeSinceLastFrame);
	
}

void playerAnimation::handleRunning(const Ogre::FrameEvent& evt) {
	if (jumpAnimationEnd->getEnabled()) {
		activeAnimation(false, false, jumpAnimationEnd);
	}
	if (!moveAnimation->getEnabled()) {
		activeAnimation(true, true, moveAnimation);
	}
	moveAnimation->addTime(evt.timeSinceLastFrame);
}


void playerAnimation::resetToIdle() {
	activeAnimation(false, false, moveAnimation);
}
