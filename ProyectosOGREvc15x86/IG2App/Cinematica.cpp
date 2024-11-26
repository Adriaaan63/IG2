#include "Cinematica.h"

void Cinematica::createFloor(SceneManager* sceneManager, SceneNode* camNode) {
    Plane plane(Vector3::UNIT_Y, -50);
    MeshManager::getSingleton().createPlane("ground1", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, WIDTH_FLOOR, HEIGHT_FLOOR, 20, 20, true, 1, 5, 5, Vector3::UNIT_Z);
    Entity* entSuelo = sceneManager->createEntity("ground1");
    nodeSuelo = sceneManager->getRootSceneNode()->createChildSceneNode();
    nodeSuelo->setPosition(0, 0, 0);
    
    entSuelo->setMaterialName("materialMuro");
    nodeSuelo->attachObject(entSuelo);

}
void Cinematica::createLightCinematica(SceneManager* sceneManager) {
    light = sceneManager->createLight("Luz Foco");
    light->setType(Ogre::Light::LT_DIRECTIONAL);  // Luz direccional
    light->setDiffuseColour(0.5, 0.5, 0.5);
        
    

}
void Cinematica::setVisibleCinematica(bool visible) {
    villanos->setVisiblePersonaje(visible);
    heroe->setVisiblePersonaje(visible);
    nodeSuelo->setVisible(visible);
}
void Cinematica::createFire(SceneManager* sceneManager, SceneNode* parentNode) {
    int n_particle_system_fire = 0;
    for (int i = 0; i < 1; i++) {
        particle_system_fire.push_back(new EmisoresParticulas(Vector3(0,0,0), parentNode, sceneManager, n_particle_system_fire, 1));
        n_particle_system_fire++;
    }
}