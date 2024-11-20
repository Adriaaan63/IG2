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
public:
    HeroeAnimation(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh) :
        Personaje(pos, node, sceneManager, mesh),
        TextInfoPlayer(nullptr) {
        setScale(Vector3(4, 4, 4));
        danceAnimation = entity->getAnimationState("Dance");
        danceAnimation->setLoop(true);
        danceAnimation->setEnabled(true);
    }

    ~HeroeAnimation() {}

    void init() override {}


    virtual void frameRendered(const Ogre::FrameEvent& evt);

    void setInfoText(OgreBites::TextBox* TextInfoPlayer_) {
        TextInfoPlayer = TextInfoPlayer_;
    }
    void updateText();
    ;
};
