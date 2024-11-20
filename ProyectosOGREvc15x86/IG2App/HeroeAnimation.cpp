#include "HeroeAnimation.h"
void HeroeAnimation::frameRendered(const Ogre::FrameEvent& evt) {
	if(visible)
		danceAnimation->addTime(evt.timeSinceLastFrame);

}