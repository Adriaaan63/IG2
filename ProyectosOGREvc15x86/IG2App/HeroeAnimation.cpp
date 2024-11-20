#include "HeroeAnimation.h"
void HeroeAnimation::frameRendered(const Ogre::FrameEvent& evt) {
	if(visible)
		moveAnimation->addTime(evt.timeSinceLastFrame);

}