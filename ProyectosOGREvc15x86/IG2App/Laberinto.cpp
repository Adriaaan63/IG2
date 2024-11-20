#include "Laberinto.h"

void Laberinto::createFloor(SceneManager* sceneManager) {
    Plane plane(Vector3::UNIT_Y, -50);
    MeshManager::getSingleton().createPlane("ground", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, (columnas - 1) * 100, (filas - 1) * 100, 20, 20, true, 1, 5, 5, Vector3::UNIT_Z);
    Entity* entSuelo = sceneManager->createEntity("ground");
    nodeSuelo = sceneManager->getRootSceneNode()->createChildSceneNode();
    nodeSuelo->setPosition(columnas * 100 / 2, 0, filas * 100 / 2);
    entSuelo->setMaterialName(materialSuelo);
    nodeSuelo->attachObject(entSuelo);
    
}
void Laberinto::createLightHeroe(SceneManager* sceneManager) {
    light = sceneManager->createLight("Luz Foco");
    switch (typeLight) {
    case 0:
        light->setType(Ogre::Light::LT_POINT);  // Luz puntual
        break;
    case 1:
        light->setType(Ogre::Light::LT_DIRECTIONAL);  // Luz direccional
        light->setDiffuseColour(0.5, 0.5, 0.5);
        break;
    case 2:
        light->setType(Ogre::Light::LT_SPOTLIGHT);  // Luz tipo foco
        light->setDiffuseColour(Ogre::ColourValue(0.8f, 0.8f, 0.8f));
        light->setCastShadows(true);
        /* luzFoco->setDirection(Ogre::Vector3(1, -1, 0));*/
        light->setSpotlightInnerAngle(Ogre::Degree(90.0f));
        light->setSpotlightOuterAngle(Ogre::Degree(90.0f));
        light->setSpotlightFalloff(5.0f);
        break;
    }
    
}
void Laberinto::setVisibleLaberinto(bool visible) {
    for (size_t i = 0; i < filas; i++)
    {
        for (size_t j = 0; j < columnas; j++)
        {
            bloques[i][j]->setVisible(visible);
        }
    } 
    for (auto e : villanos) {
        e->setVisiblePersonaje(visible);
    }
    heroe->setVisiblePersonaje(visible);
    nodeSuelo->setVisible(visible);
}