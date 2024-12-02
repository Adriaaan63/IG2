#pragma once
#include "Bloque.h"
#include <iostream>
#include <fstream> 
#include <vector>
#include "IG2ApplicationContext.h"
#include "HeroeAnimation.h"
#include "VillanoAnimation.h"
#include "EmisoresParticulas.h"

class Cinematica
{
private:
    HeroeAnimation* heroe;
    VillanoAnimation* villanos;
    string materialSuelo;
    int typeLight;
    Light* light;
    std::vector<EmisoresParticulas*> particle_system_fire;
    
    SceneNode* nodeSuelo;

public:
    Cinematica(SceneManager* sceneManager, SceneNode* parentNode, SceneNode* camNode)
    {
        createFloor(sceneManager, camNode);
        ajustarCamara(camNode);
        createPersonajes(sceneManager, parentNode);
        createFire(sceneManager, parentNode);
        createSphere(sceneManager, parentNode);
        /*createLightHeroe(sceneManager);*/
    }
    ~Cinematica() {}
    void setVisibleCinematica(bool visible);
    void createFloor(SceneManager* sceneManager, SceneNode* camNode);
    void createLightCinematica(SceneManager* sceneManager);
    void createFire(SceneManager* sceneManager, SceneNode* parentNode);
    void createSphere(SceneManager* sceneManager, SceneNode* parentNode);
   
    HeroeAnimation* getHeroe() const {
        return heroe;
    };
    VillanoAnimation* getVillanos()const { return villanos; };
    void createPersonajes(SceneManager* sceneManager, SceneNode* parentNode) {
        heroe = new HeroeAnimation(Vector3(nodeSuelo->getPosition().x,
            nodeSuelo->getPosition().y - 30, nodeSuelo->getPosition().z), parentNode->createChildSceneNode(), sceneManager, "Sinbad.mesh");
        villanos = new VillanoAnimation(Vector3(nodeSuelo->getPosition().x - WIDTH_FLOOR / 2 ,
            nodeSuelo->getPosition().y - 30, nodeSuelo->getPosition().z), parentNode->createChildSceneNode(), sceneManager, "ogrehead.mesh");
        
    }

    Light* getLightHeroe() const {
        return light;
    };
    void ajustarCamara(SceneNode* camNode) {
        float alturaCamara = 0;
        float centroX = 0;
        float centroZ = 170;

        camNode->setPosition(centroX, alturaCamara, centroZ);

        camNode->lookAt(Vector3(0, -10, 0), Node::TS_WORLD);
    }

};


