#pragma once
#include "Pala.h"
#include "IG2Object.h"
class Helices: public IG2Object
{
private: 
	std::vector<Pala*> palas;
	
public:
	Helices(Vector3 pos, SceneNode* node, SceneManager* sceneManager, int numPalas, Vector3 escala): 
		IG2Object(pos, node, sceneManager) {
        mNode->scale(escala);
        SceneNode* nodoHelice = mNode->createChildSceneNode();

        float anguloEntrePalas = 360.0f / numPalas;

        for (int i = 0; i < numPalas; ++i) {
            SceneNode* nodoPala = nodoHelice->createChildSceneNode();

            Pala* nuevaPala = new Pala(mNode->getPosition(), nodoPala, sceneManager, Vector3(1.5, 0.1, 0.5));

            nodoPala->yaw(Ogre::Degree(i * anguloEntrePalas));

            palas.push_back(nuevaPala);
        }
	}
    ~Helices() {
        for (auto& e : palas) {
            delete e;
        }
        palas.clear();
    }
    virtual void init() {};
};

