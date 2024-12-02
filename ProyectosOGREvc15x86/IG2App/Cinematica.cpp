#include "Cinematica.h"

void Cinematica::createFloor(SceneManager* sceneManager, SceneNode* camNode) {
    Plane plane(Vector3::UNIT_Y, -50);
    MeshManager::getSingleton().createPlane("ground1", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, WIDTH_FLOOR, HEIGHT_FLOOR, 20, 20, true, 1, 5, 5, Vector3::UNIT_Z);
    Entity* entSuelo = sceneManager->createEntity("ground1");
    nodeSuelo = sceneManager->getRootSceneNode()->createChildSceneNode();
    nodeSuelo->setPosition(0, 0, 0);
    
    entSuelo->setMaterialName("example/textureTest");
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
    for (size_t i = 0; i < particle_system_fire.size(); i++)
    {
        particle_system_fire[i]->setVisible(visible);
    }
}
void Cinematica::createFire(SceneManager* sceneManager, SceneNode* parentNode) {
    float posIniX = nodeSuelo->getPosition().x - WIDTH_FLOOR/2;
    float posIniZ = nodeSuelo->getPosition().x - HEIGHT_FLOOR/2;
    float posIniY = nodeSuelo->getPosition().y - 45;
    float space = WIDTH_FLOOR / PS_FIRE;
    for (int i = 1; i < PS_FIRE; i++) {
        particle_system_fire.push_back(new EmisoresParticulas(Vector3( posIniX + i* space,posIniY,posIniZ), parentNode->createChildSceneNode(), sceneManager, i, 1));
    }    
}

void Cinematica::createSphere(SceneManager* sceneManager, SceneNode* parentNode) {
    Entity* entity = sceneManager->createEntity("sphere", "uv_sphere.mesh");
    SceneNode* esfera = parentNode->createChildSceneNode("esfera");
    esfera->attachObject(entity);
    esfera->setPosition(Vector3(0, 5, -25));
    esfera->setScale(Vector3(0.3, 0.3, 0.3));
    esfera->setVisible(true);
    entity->setMaterialName("practica2/SphereHoles");
}
