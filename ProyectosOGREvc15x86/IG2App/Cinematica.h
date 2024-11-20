#pragma once
#include "Bloque.h"
#include <iostream>
#include <fstream> 
#include <vector>
#include "Villano.h"
#include "IG2ApplicationContext.h"
#include "Heroe.h"
using namespace std;

class Cinematica
{
private:
    IG2Object* heroe;
    IG2Object* villanos;
    string materialSuelo;
    int typeLight;
    Light* light;
    
    SceneNode* nodeSuelo;

public:
    Cinematica(SceneManager* sceneManager, SceneNode* parentNode, SceneNode* camNode)
    {
        createFloor(sceneManager, camNode);
        
        /*createLightHeroe(sceneManager);*/
    }
    ~Cinematica() {}
    void setVisibleCinematica(bool visible);
    void createFloor(SceneManager* sceneManager, SceneNode* camNode);
    void createLightCinematica(SceneManager* sceneManager);
   
    IG2Object* getHeroe() const {
        return heroe;
    };
    IG2Object* getVillanos()const { return villanos; };
   

    Light* getLightHeroe() const {
        return light;
    };


};


