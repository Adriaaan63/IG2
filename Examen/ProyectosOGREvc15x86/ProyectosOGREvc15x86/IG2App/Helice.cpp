#include "Helice.h"

Helice::Helice(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int helice, int numPalas) :
    IG2Object(initPos, node->createChildSceneNode("helice" + std::to_string(helice)), sceneMng)
{
    float anguloEntrePalas = 360.0f / numPalas;
    for (int i = 0; i < numPalas; ++i) {
        // Crear nodo para la pala
        float radio = 40.0f;
        Vector3 posePala = { radio * Ogre::Math::Sin(Ogre::Degree(i * anguloEntrePalas)),
            0, radio * Ogre::Math::Cos(Ogre::Degree(i * anguloEntrePalas)) };
        Pala* nuevaPala = new Pala(posePala, mNode, sceneMng, Vector3(0.5, 0.05, 0.2), i, helice);
        nuevaPala->getMNode()->yaw(Ogre::Degree(i * anguloEntrePalas + 90));
        palas.push_back(nuevaPala);
    }
   mNode->pitch(Ogre::Degree(90));
   setScale({ 2,2,2 });
}
void Helice::frameRendered(const Ogre::FrameEvent& evt) {
    mNode->yaw(Ogre::Degree(-1));
}
