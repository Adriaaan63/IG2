#pragma once
#include "Personaje.h"
#include "OgreAxisAlignedBox.h"
#include <OgreTrays.h>       
#include <OgreOverlaySystem.h> 

enum class HeroState {
    Dancing,
    Running,
    Fighting,
    Idle
};

class HeroeAnimation : public Personaje
{
private:
    OgreBites::TextBox* TextInfoPlayer;
    AnimationState* danceAnimation;
    AnimationState* moveAnimation;
    AnimationState* swordAnimation;
    AnimationState* runAnimation;
    AnimationState* armsAnimation;
    int movementLength = 70;
    int movementLength2 = WIDTH_FLOOR / 2;
    Real duration = 17.0;
    Vector3 keyframePos;
    Real durStep = 5;
    Vector3 src = Vector3(0, 0, 1);
    Vector3 scale;
    float timer = 0.0f;
    Ogre::Entity* sword1;
    Ogre::Entity* sword2;
public:
    HeroeAnimation(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh) :
        Personaje(pos, node, sceneManager, mesh),
        TextInfoPlayer(nullptr),scale(Vector3(4, 4, 4)), keyframePos(pos) {
        
        setScale(scale);
        createAnimationHeroe("Dance", danceAnimation);
        sword1 = mSM->createEntity("Sword.mesh");
        sword2 = mSM->createEntity("Sword.mesh");

        // Vincula las espadas a los huesos del esqueleto de Sinbad
        entity->attachObjectToBone("Handle.L", sword1); // La espada izquierda
        entity->attachObjectToBone("Handle.R", sword2); // La espada derecha
        sword1->setVisible(false);
        sword2->setVisible(false);

        createAnimationHeroe("DrawSwords", swordAnimation);
        createAnimationHeroe("RunBase", runAnimation);
        createAnimationHeroe("RunTop", armsAnimation);
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
    void createAnimationHeroe(string animation, AnimationState*& animatioState) {
         animatioState = entity->getAnimationState(animation);
    }
    void activeAnimation(bool loop, bool enable, AnimationState* animatioState) {
        animatioState->setLoop(loop);
        animatioState->setEnabled(enable);
    }
    void createAnimationHeroeWalk() {
        Animation* animation = mSM->createAnimation("HeroeWalking", duration);
        animation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
        NodeAnimationTrack* track = animation->createNodeTrack(0);
        track->setAssociatedNode(mNode);
        TransformKeyFrame* kf;
        //Keyframe 1 (Init state) 
        activeAnimation(true, true, danceAnimation);
        kf = track->createNodeKeyFrame(0);
        addkeyFrame(track, kf, keyframePos,src.getRotationTo(Vector3(0, 0, 1)), scale);

        kf = track->createNodeKeyFrame(0.5);
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)), scale);
        
        // Keyframe 2: Go to the right 

        kf = track->createNodeKeyFrame(4);
        keyframePos += Ogre::Vector3::UNIT_X * movementLength;
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)),scale);

        //KeyFrame 3: rotate

        kf = track->createNodeKeyFrame(5);
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(-1, 0, 0)),scale);

        //Keyframe 4: Go to the initial position 
        kf = track->createNodeKeyFrame(11);
        keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength * 2;
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(-1, 0, 0)),scale);

        //KeyFrame 5: rotate
        kf = track->createNodeKeyFrame(12);
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)),scale);

        // Keyframe 6: Go to the right 
        kf = track->createNodeKeyFrame(16);
        keyframePos += Ogre::Vector3::UNIT_X * movementLength;
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)),scale);

        //KeyFrame 5: rotate
        kf = track->createNodeKeyFrame(17);
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(0, 0, 1)), scale);

        moveAnimation = mSM->createAnimationState("HeroeWalking");
        /*moveAnimation->setLoop(true);
        moveAnimation->setEnabled(true);*/
    }
    HeroState determineState(float time);
    void handleDancing(const Ogre::FrameEvent& evt);
    void handleRunning(const Ogre::FrameEvent& evt);
    void handleFighting(const Ogre::FrameEvent& evt);
    void resetToIdle();
};
