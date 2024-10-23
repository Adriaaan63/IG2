#include "Laberinto.h"

void Laberinto::createFloor(SceneManager* sceneManager) {
    Plane plane(Vector3::UNIT_Y, -50);
    MeshManager::getSingleton().createPlane("ground", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, (columnas - 1) * 100, (filas - 1) * 100, 20, 20, true, 1, 5, 5, Vector3::UNIT_Z);
    Entity* entSuelo = sceneManager->createEntity("ground");
    SceneNode* nodeSuelo = sceneManager->getRootSceneNode()->createChildSceneNode();
    nodeSuelo->setPosition(columnas * 100 / 2, 0, filas * 100 / 2);
    entSuelo->setMaterialName(materialSuelo);
    nodeSuelo->attachObject(entSuelo);
}