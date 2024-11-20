#pragma once
#include "Personaje.h"
#include "OgreAxisAlignedBox.h"
#include <OgreTrays.h>       
#include <OgreOverlaySystem.h> 


class HeroeAnimation : public Personaje
{
private:
    OgreBites::TextBox* TextInfoPlayer;
    AnimationState* danceAnimation;
    AnimationState* moveAnimation;
    AnimationState* swordAnimation;
    AnimationState* runAnimation;
    int movementLength = 70;
    int movementLength2 = WIDTH_FLOOR / 2;
    Real duration = 17.0;
    Vector3 keyframePos;
    Real durStep = 5;
    Vector3 src = Vector3(0, 0, 1);
    Vector3 scale;
public:
    HeroeAnimation(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh) :
        Personaje(pos, node, sceneManager, mesh),
        TextInfoPlayer(nullptr),scale(Vector3(4, 4, 4)), keyframePos(pos) {
        
        setScale(scale);
        createAnimationHeroeWalk();
    }

    ~HeroeAnimation() {}

    void init() override {}


    virtual void frameRendered(const Ogre::FrameEvent& evt);

    void setInfoText(OgreBites::TextBox* TextInfoPlayer_) {
        TextInfoPlayer = TextInfoPlayer_;
    }
    void updateText();
    ;
    void createAnimationHeroe(bool loop, bool enable, string animation) {
        danceAnimation = entity->getAnimationState(animation);
        danceAnimation->setLoop(loop);
        danceAnimation->setEnabled(enable);
    }
    void createAnimationHeroeWalk() {
        Animation* animation = mSM->createAnimation("HeroeWalking", duration);
        animation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
        NodeAnimationTrack* track = animation->createNodeTrack(0);
        track->setAssociatedNode(mNode);
        TransformKeyFrame* kf;
        //Keyframe 1 (Init state) 

        kf = track->createNodeKeyFrame(0);
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)),scale);

        // Keyframe 2: Go to the right 

        kf = track->createNodeKeyFrame(3);
        keyframePos += Ogre::Vector3::UNIT_X * movementLength;
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)),scale);

        //KeyFrame 3: rotate

        kf = track->createNodeKeyFrame(4);
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(-1, 0, 0)),scale);

        //Keyframe 4: Go to the initial position 
        kf = track->createNodeKeyFrame(11);
        keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength * 2;
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(-1, 0, 0)),scale);

        //KeyFrame 5: rotate
        kf = track->createNodeKeyFrame(12);
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)),scale);

        // Keyframe 6: Go to the right 
        kf = track->createNodeKeyFrame(17);
        keyframePos += Ogre::Vector3::UNIT_X * movementLength;
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)),scale);

        moveAnimation = mSM->createAnimationState("HeroeWalking");
        moveAnimation->setLoop(true);
        moveAnimation->setEnabled(true);
    }
};
