#include "Helices.h"

Helices::Helices(Vector3 pos, SceneNode* node, SceneManager* sceneManager, int numPalas, Vector3 escala, int n, int n_villano)
    : IG2Object(pos, node->createChildSceneNode("helice"+ to_string(n_villano)+to_string(n)), sceneManager) {
   /* mNode->scale(escala);*/
    
    float anguloEntrePalas = 360.0f / numPalas;
    for (int i = 0; i < numPalas; ++i) {
        // Crear nodo para la pala
        /*SceneNode* nodoPala = mNode->createChildSceneNode(to_string(n) + "pala" + std::to_string(i));*/
        float radio = 10.0f;
        Vector3 posePala = { radio * Ogre::Math::Sin(Ogre::Degree(i * anguloEntrePalas)),
            0, radio * Ogre::Math::Cos(Ogre::Degree(i * anguloEntrePalas)) };
        Pala* nuevaPala = new Pala(posePala, mNode, sceneManager, Vector3(0.5, 0.05, 0.2),n,i,n_villano);
        nuevaPala->getNode()->yaw(Ogre::Degree(i * anguloEntrePalas + 90));
        palas.push_back(nuevaPala);
    }
    mNode->roll(Ogre::Degree(90));
    setScale(escala);
}

void Helices::frameRendered(const Ogre::FrameEvent& evt) {
    mNode->yaw(Ogre::Degree(-1));
}