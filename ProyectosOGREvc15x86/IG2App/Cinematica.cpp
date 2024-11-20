#include "Cinematica.h"

void Cinematica::createFloor(SceneManager* sceneManager, SceneNode* camNode) {
    Plane plane(Vector3::UNIT_Y, -50);
    MeshManager::getSingleton().createPlane("ground1", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 300, 150, 20, 20, true, 1, 5, 5, Vector3::UNIT_Z);
    Entity* entSuelo = sceneManager->createEntity("ground1");
    nodeSuelo = sceneManager->getRootSceneNode()->createChildSceneNode();
    nodeSuelo->setPosition(camNode->getPosition().x, camNode->getPosition().y - 50, camNode->getPosition().z - 40);
    nodeSuelo->pitch(Degree(-20));
    entSuelo->setMaterialName("materialMuro");
    nodeSuelo->attachObject(entSuelo);

}
void Cinematica::createLightCinematica(SceneManager* sceneManager) {
    light = sceneManager->createLight("Luz Foco");
   
    light->setType(Ogre::Light::LT_DIRECTIONAL);  // Luz direccional
    light->setDiffuseColour(0.5, 0.5, 0.5);
        
    

}
void Cinematica::setVisibleCinematica(bool visible) {
    villanos->setVisible(visible);
    heroe->setVisible(visible);
    nodeSuelo->setVisible(visible);
}