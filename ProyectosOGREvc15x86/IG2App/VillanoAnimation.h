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
    int movementLength = WIDTH_FLOOR -100 ; 
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
        //Keyframe 0 (Init state) 
        kf = track->createNodeKeyFrame(0); 
        kf->setTranslate(keyframePos); 
       /* Quaternion q1 = Quaternion(Degree(90.0), Vector3(0, 1, 0));
        kf->setRotation(q1);*/
        Quaternion q1 = src.getRotationTo(Vector3(1, 0, 0));
        kf->setRotation(q1);
        // Keyframe 2: Go to the right 
        kf = track-> createNodeKeyFrame(7 ); 
        keyframePos += Ogre::Vector3::UNIT_X * movementLength; 
        kf->setTranslate(keyframePos); 
        kf->setRotation(q1);
        //KeyFrame 3: rotate
        kf = track->createNodeKeyFrame(8);
        // Mantén la posición actual
        kf->setTranslate(keyframePos);
        // Configura la rotación de 90 grados en el eje Y
        Quaternion q2 = src.getRotationTo(Vector3(-1, 0, 0));
        kf->setRotation(q2);
         //Keyframe 4: Go to the initial position 
        kf = track-> createNodeKeyFrame(15);
        keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength;
        kf->setTranslate(keyframePos);
        kf->setRotation(q2);
        //KeyFrame 5: rotate
        kf = track->createNodeKeyFrame(16);
        // Mantén la posición actual
        kf->setTranslate(keyframePos);
        // Configura la rotación de 90 grados en el eje Y
        Quaternion q3 = src.getRotationTo(Vector3(1, 0, 0));
        kf->setRotation(q3);
        // Keyframe 6: Go to the right 
        kf = track->createNodeKeyFrame(21);
        keyframePos += Ogre::Vector3::UNIT_X * movementLength2;
        kf->setTranslate(keyframePos);
        kf->setRotation(q3);
        kf->setScale(kf->getScale() / 5.0);
        

        moveAnimation = mSM->createAnimationState("villanoWalking");
        moveAnimation->setLoop(true);
        moveAnimation->setEnabled(true);
    }

    virtual void frameRendered(const Ogre::FrameEvent& evt);

   
    
};
