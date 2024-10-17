#pragma once
#include "Pala.h"
#include "IG2Object.h"
#include <OgreVector3.h>

class Helices : public IG2Object {
private:
    std::vector<Pala*> palas;

public:
    Helices(Vector3 pos, SceneNode* node, SceneManager* sceneManager, int numPalas, Vector3 escala, int n)
        : IG2Object(pos, node, sceneManager)
    {
        mNode->scale(escala);
        float anguloEntrePalas = 360.0f / numPalas;
        for (int i = 0; i < numPalas; ++i) {
            // Crear nodo para la pala
            SceneNode* nodoPala = mNode->createChildSceneNode(to_string(n) + "pala" + std::to_string(i));
            Pala* nuevaPala = new Pala(Vector3(0, 0, 0), nodoPala, sceneManager, Vector3(1.5, 0.1, 0.5));

            float radio = 50.0f; 
            nodoPala->setPosition(radio * Ogre::Math::Sin(Ogre::Degree(i * anguloEntrePalas)),
                0, radio * Ogre::Math::Cos(Ogre::Degree(i * anguloEntrePalas)));
            nodoPala->yaw(Ogre::Degree(i * anguloEntrePalas + 90));
            palas.push_back(nuevaPala);
        }
        mNode->roll(Ogre::Degree(90));
    }

    ~Helices() {
        for (auto& e : palas) {
            delete e;
        }
        palas.clear();
    }

    virtual void init() {}
};
