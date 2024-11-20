#include "VillanoAnimation.h"
VillanoAnimation::VillanoAnimation(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh) :
    Personaje(pos, node, sceneManager, mesh), keyframePos(pos){
    setScale(Vector3(0.8, 0.8, 0.8));
    
    createAnimationVillanoWalk();
}
void VillanoAnimation::frameRendered(const Ogre::FrameEvent& evt) {
	if (visible)
	{
		moveAnimation->addTime(evt.timeSinceLastFrame);
	}

}