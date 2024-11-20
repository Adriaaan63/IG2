#pragma once
#include "Bloque.h"
#include <iostream>
#include <fstream> 
#include <vector>
#include "Villano.h"
#include "IG2ApplicationContext.h"
#include "HeroeAnimation.h"
#include "VillanoAnimation.h"
using namespace std;

class Cinematica
{
private:
    HeroeAnimation* heroe;
    VillanoAnimation* villanos;
    string materialSuelo;
    int typeLight;
    Light* light;
    
    SceneNode* nodeSuelo;

public:
    Cinematica(SceneManager* sceneManager, SceneNode* parentNode, SceneNode* camNode)
    {
        createFloor(sceneManager, camNode);
        createPersonajes(sceneManager, parentNode);
        /*createLightHeroe(sceneManager);*/
    }
    ~Cinematica() {}
    void setVisibleCinematica(bool visible);
    void createFloor(SceneManager* sceneManager, SceneNode* camNode);
    void createLightCinematica(SceneManager* sceneManager);
   
    HeroeAnimation* getHeroe() const {
        return heroe;
    };
    VillanoAnimation* getVillanos()const { return villanos; };
    void createPersonajes(SceneManager* sceneManager, SceneNode* parentNode) {
        heroe = new HeroeAnimation(Vector3(nodeSuelo->getPosition().x + nodeSuelo->getScale().x / 2,
            nodeSuelo->getPosition().y - 10, nodeSuelo->getPosition().z + nodeSuelo->getScale().z / 2 - 20), parentNode->createChildSceneNode(), sceneManager, "Sinbad.mesh");
        villanos = new VillanoAnimation(Vector3(nodeSuelo->getPosition().x + nodeSuelo->getScale().x / 2,
            nodeSuelo->getPosition().y - 10, nodeSuelo->getPosition().z), parentNode->createChildSceneNode(), sceneManager, "ogrehead.mesh");
        
    }

    Light* getLightHeroe() const {
        return light;
    };


};


