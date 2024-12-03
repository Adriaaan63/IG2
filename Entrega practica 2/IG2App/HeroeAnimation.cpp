#include "HeroeAnimation.h"
void HeroeAnimation::frameRendered(const Ogre::FrameEvent& evt) {
	if (!visible) return;

	HeroState currentState = determineState(timer);

	switch (currentState) {
	case HeroState::Dancing:
		handleDancing(evt);
		break;
	case HeroState::Running:
		handleRunning(evt);
		break;
	case HeroState::Fighting:
		handleFighting(evt);
		break;
	case HeroState::Idle:
		resetToIdle();
		timer = 0.0f; // Reset the timer
		break;
	}

	timer += evt.timeSinceLastFrame;
}

HeroState HeroeAnimation::determineState(float time) {
	if (time >= 0.0f && time < 4.0f) {
		return HeroState::Dancing;
	}
	else if (time >= 4.0f && time < 8.0f) {
		return HeroState::Running;
	}
	else if (time >= 8.0f && time < 21.0f) {
		return HeroState::Fighting;
	}
	else {
		return HeroState::Idle;
	}
}
void HeroeAnimation::handleDancing(const Ogre::FrameEvent& evt) {
	if (!danceAnimation->getEnabled()) {
		activeAnimation(true, true, danceAnimation);
	}
	danceAnimation->addTime(evt.timeSinceLastFrame);
}

void HeroeAnimation::handleRunning(const Ogre::FrameEvent& evt) {
	if (danceAnimation->getEnabled()) {
		activeAnimation(false, false, danceAnimation);
	}
	if (!runAnimation->getEnabled() && !armsAnimation->getEnabled()) {
		activeAnimation(true, true, runAnimation);
		activeAnimation(true, true, armsAnimation);
	}
	if (!moveAnimation->getEnabled()) {
		activeAnimation(true, true, moveAnimation);
	}
	moveAnimation->addTime(evt.timeSinceLastFrame);
	runAnimation->addTime(evt.timeSinceLastFrame);
	armsAnimation->addTime(evt.timeSinceLastFrame);
}

void HeroeAnimation::handleFighting(const Ogre::FrameEvent& evt) {
	if (!swordAnimation->getEnabled()) {
		activeAnimation(false, true, swordAnimation);
		sword1->setVisible(true);
		sword2->setVisible(true);
	}
	moveAnimation->addTime(evt.timeSinceLastFrame);
	swordAnimation->addTime(evt.timeSinceLastFrame);
	runAnimation->addTime(evt.timeSinceLastFrame);
	armsAnimation->addTime(evt.timeSinceLastFrame);
}

void HeroeAnimation::resetToIdle() {
	activeAnimation(false, false, runAnimation);
	activeAnimation(false, false, armsAnimation);
	activeAnimation(false, false, swordAnimation);
	activeAnimation(true, true, danceAnimation);
	activeAnimation(false, false, moveAnimation);
	sword1->setVisible(false);
	sword2->setVisible(false);
}
