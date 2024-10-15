#pragma once
#include "Personaje.h"
#include "OgreAxisAlignedBox.h"
#include <OgreTrays.h>       
#include <OgreOverlaySystem.h> 


class Heroe : public Personaje
{
private:
    int puntos;
    OgreBites::Label* InfoTextBox;  
public:
    Heroe(Vector3 pos, SceneNode* node, SceneManager* sceneManager, String mesh, Laberinto* lab) :
        Personaje(pos, node, sceneManager, mesh, lab, Vector3(0, 0, 1), Vector3(0, 0, 1)),
        puntos(0), InfoTextBox(nullptr) {}

    ~Heroe() {}

    void init() override {}

    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

    virtual void frameRendered(const Ogre::FrameEvent& evt);

    void setInfoLabel(OgreBites::Label* infoLabel) {
        InfoTextBox = infoLabel;
    }
};
