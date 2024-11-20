#include "VillanoAnimation.h"
void VillanoAnimation::frameRendered(const Ogre::FrameEvent& evt) {
	if (visible)
	{
		moveAnimation->addTime(evt.timeSinceLastFrame);
	}

}