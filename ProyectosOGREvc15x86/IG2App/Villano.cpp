#include "Villano.h"
#include "Laberinto.h"
void Villano::createVillano() {
    SceneNode* nodeCuerpo = mSM->getRootSceneNode()->createChildSceneNode("cuerpo");
    IG2Object* cuerpo = new IG2Object(Vector3(0, 0, 0), nodeCuerpo, mSM, "Barrel.mesh");
    cuerpo->setScale(Vector3(20, 20, 20));
    bodyVillano.push_back(cuerpo);

    SceneNode* nodeHelice1 = mSM->getRootSceneNode()->createChildSceneNode("helice1");
    Helices* helice1 = new Helices(Vector3(cuerpo->getPosition().x + 55, 0, 0), nodeHelice1, mSM, 8, Vector3(0.5, 0.5, 0.5),1);
    bodyVillano.push_back(helice1);

    SceneNode* nodeHelice2 = mSM->getRootSceneNode()->createChildSceneNode("helice2");
    Helices* helice2 = new Helices(Vector3(cuerpo->getPosition().x - 55, 0, 0), nodeHelice2, mSM, 8, Vector3(0.5, 0.5, 0.5),2);
    bodyVillano.push_back(helice2);

    SceneNode* nodePingu = mSM->getRootSceneNode()->createChildSceneNode("pingu");
    IG2Object* pingu = new IG2Object(Vector3(0, 85, 0), nodePingu, mSM, "penguin.mesh");
    pingu->setScale(Vector3(1, 1, 1));
    bodyVillano.push_back(pingu);
}

void Villano::frameRendered(const Ogre::FrameEvent& evt) {
    if (mNode == nullptr || lab == nullptr) {
        return;
    }
    if (fmod(getPosition().x, TILE_WIDTH) == 0 && fmod(getPosition().z, TILE_HEIGHT) == 0) {
        next_dir= nuevaDireccion();
        giro();
    }
    for (auto& e : bodyVillano) {
        e->frameRendered(evt);
    }
    move(dir);
}
Vector3 Villano::nuevaDireccion() {
    std::vector<Vector3> posiblesDirecciones = lab->getDireccionesTraspasables(getPosition());
    Vector3 posicionHeroe = lab->getHeroe()->getPosition();
    float distanciaMinima = std::numeric_limits<float>::max();
    Vector3 mejorDireccion;
    for (const auto& dir : posiblesDirecciones) {
        // Evitar giros de 180 grados
        if (dir != -this->dir || posiblesDirecciones.size() == 1) {
            Vector3 siguientePosicion = Vector3(dir.x * TILE_WIDTH + getPosition().x, 0, dir.z * TILE_HEIGHT + getPosition().z);
            // Calcular la distancia al héroe
            float distancia = hypot(posicionHeroe.x - siguientePosicion.x, posicionHeroe.z - siguientePosicion.z);
            if (distancia < distanciaMinima) {
                distanciaMinima = distancia;
                mejorDireccion = dir;
            }
        }
    }
    return mejorDireccion;
}