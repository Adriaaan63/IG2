#include "Personaje.h"
#include <OgreAxisAlignedBox.h>
#include <OgreTrays.h>
#include <OgreOverlaySystem.h>
#include <OgreAnimation.h>
#include <OgreAnimationTrack.h>
#include <OgreKeyFrame.h> 

class VillanoAnimation : public Personaje
{
private:
    AnimationState* moveAnimation;
    int movementLength = 50; 
    Real duration = 16.0;
    Vector3 keyframePos;
    Real durStep = duration / 4.0;
public:
    VillanoAnimation(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh) :
        Personaje(pos, node, sceneManager, mesh) {
        /*setScale(Vector3(4, 4, 4));*/
        keyframePos = pos;
    }

    ~VillanoAnimation() {}

    void init() override {}

    void createAnimationVillanoWalk() {
        Animation* animation = mSM->createAnimation("villanoWalking", duration);
        animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
        NodeAnimationTrack* track = animation->createNodeTrack(0); 
        track->setAssociatedNode(mNode); 
        TransformKeyFrame* kf;
        //Keyframe 0 (Init state) 
        kf = track->createNodeKeyFrame(durStep * 0); 
        kf->setTranslate(keyframePos); 
        // Keyframe 1: Go to the right 
        kf = track-> createNodeKeyFrame(durStep * 1); 
        keyframePos += Ogre::Vector3::UNIT_X * movementLength; 
        kf->setTranslate(keyframePos); 
        // Keyframe 2: Go to the initial position 
        kf = track-> createNodeKeyFrame(durStep * 2);
        keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength;
        kf->setTranslate(keyframePos);
        // Keyframe 3: Go to the left
        kf = track-> createNodeKeyFrame(durStep * 3); 
        keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength; 
        kf->setTranslate(keyframePos); 
        // Keyframe 4: Go to the right (initital position) 
        kf = track-> createNodeKeyFrame(durStep * 4);
        keyframePos += Ogre::Vector3::UNIT_X * movementLength; 
        kf->setTranslate(keyframePos);

        moveAnimation = mSM->createAnimationState("villanoWalking");
        moveAnimation->setLoop(true);
        moveAnimation->setEnabled(true);
    }

    virtual void frameRendered(const Ogre::FrameEvent& evt);

   
    
};
