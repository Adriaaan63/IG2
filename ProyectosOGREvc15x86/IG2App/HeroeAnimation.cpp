#include "HeroeAnimation.h"
void HeroeAnimation::frameRendered(const Ogre::FrameEvent& evt) {
	if (visible) {
		if (timer >= 0.0f && timer < 4.0f) {
			if (!danceAnimation->getEnabled())
				activeAnimation(true, true, danceAnimation);
			danceAnimation->addTime(evt.timeSinceLastFrame);
		}
		else if (timer >= 3.0f && timer < 8.0f) {
			if(danceAnimation->getEnabled())
				activeAnimation(false, false, danceAnimation);
			if (!runAnimation->getEnabled() && !armsAnimation->getEnabled()) {
				activeAnimation(true, true, runAnimation);
				activeAnimation(true, true, armsAnimation);
			}
			if (!moveAnimation->getEnabled())
				activeAnimation(true, true, moveAnimation);
			moveAnimation->addTime(evt.timeSinceLastFrame);
			runAnimation->addTime(evt.timeSinceLastFrame);
			armsAnimation->addTime(evt.timeSinceLastFrame);
		}
		else if (timer >= 8.0f && timer < 21) {
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
		else {
			activeAnimation(false, false, runAnimation);
			activeAnimation(false, false, armsAnimation);
			activeAnimation(false, false, swordAnimation);
			activeAnimation(true, true, danceAnimation);
			activeAnimation(false,false, moveAnimation);
			sword1->setVisible(false);
			sword2->setVisible(false);
			timer = 0.0f;
		}	
		timer += evt.timeSinceLastFrame;
	}
		

}