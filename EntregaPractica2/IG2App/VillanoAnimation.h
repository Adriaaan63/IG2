#include "Personaje.h"
#include <OgreParticleSystem.h>


class VillanoAnimation : public Personaje
{
private:
    AnimationState* moveAnimation;
    int movementLength = WIDTH_FLOOR -120 ; 
    int movementLength2 = WIDTH_FLOOR /2 ; 
    Real duration = 21.0;
    Vector3 keyframePos;
    Real durStep = 5;
    Vector3 src = Vector3(0, 0, 1);
public:
    VillanoAnimation(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh);
    ~VillanoAnimation() {}

    void init() override {}
    
    void createAnimationVillanoWalk() {
        Animation* animation = mSM->createAnimation("villanoWalking", duration);
        animation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
        NodeAnimationTrack* track = animation->createNodeTrack(0); 
        track->setAssociatedNode(mNode); 
        TransformKeyFrame* kf;
        //Keyframe 1 (Init state) 
        
        kf = track->createNodeKeyFrame(0); 
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)));
        
        // Keyframe 2: Go to the right 

        kf = track-> createNodeKeyFrame(8 ); 
        keyframePos += Ogre::Vector3::UNIT_X * movementLength; 
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)));

        //KeyFrame 3: rotate

        kf = track->createNodeKeyFrame(9);
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(-1, 0, 0)));

         //Keyframe 4: Go to the initial position 
        kf = track-> createNodeKeyFrame(16);
        keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength;
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(-1, 0, 0)));

        //KeyFrame 5: rotate
        kf = track->createNodeKeyFrame(17);
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)));

        // Keyframe 6: Go to the right 
        kf = track->createNodeKeyFrame(21);
        keyframePos += Ogre::Vector3::UNIT_X * movementLength2;
        addkeyFrame(track, kf, keyframePos, src.getRotationTo(Vector3(1, 0, 0)), kf->getScale() / 5.0);

        moveAnimation = mSM->createAnimationState("villanoWalking");
        moveAnimation->setLoop(true);
        moveAnimation->setEnabled(true);
    }

    virtual void frameRendered(const Ogre::FrameEvent& evt);

   
    
};
