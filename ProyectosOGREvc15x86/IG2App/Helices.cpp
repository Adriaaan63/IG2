#include "Helices.h"

Helices::Helices(Vector3 pos, SceneNode* node, SceneManager* sceneManager, int numPalas, Vector3 escala, int n)
    : IG2Object(pos, node, sceneManager) {
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

void Helices::frameRendered(const Ogre::FrameEvent& evt) {
    mNode->yaw(Ogre::Degree(-1));
}