#include "Villano.h"
#include "Laberinto.h"
void Villano::createVillano() {
    IG2Object* cuerpo = new IG2Object(getPosition() , mNode, mSM, "Barrel.mesh");
    cuerpo->setScale(Vector3(20, 20, 20));
    bodyVillano.push_back(cuerpo);

   /* SceneNode* nodeHelice1 = mNode->createChildSceneNode("helice1");*/
    Helices* helice1 = new Helices(Vector3(2.5, 0, 0), mNode, mSM, 8, Vector3(0.1, 0.1, 0.1), 1, n);
    bodyVillano.push_back(helice1);

    
    Helices* helice2 = new Helices(Vector3(-2.5, 0, 0), mNode, mSM, 8, Vector3(0.1, 0.1, 0.1), 2, n);
    bodyVillano.push_back(helice2);

  
    Pinguino* pingu = new Pinguino(Vector3(0, 5, 0), mNode, mSM, Vector3(0.1, 0.1, 0.1), n);
    
    bodyVillano.push_back(pingu);

   
    Rueda* rueda1 = new Rueda(Vector3( - 2, -4, 0), mNode, mSM, Vector3(0.02, 0.02, 0.02),1, n);
    bodyVillano.push_back(rueda1);
   
    Rueda* rueda2 = new Rueda(Vector3(2,- 4,0), mNode, mSM, Vector3(0.02, 0.02, 0.02),2, n);
    bodyVillano.push_back(rueda2);

}

void Villano::frameRendered(const Ogre::FrameEvent& evt) {
    if (!visible) {
        return;
    }
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
            // Calcular la distancia al h�roe
            float distancia = hypot(posicionHeroe.x - siguientePosicion.x, posicionHeroe.z - siguientePosicion.z);
            if (distancia < distanciaMinima) {
                distanciaMinima = distancia;
                mejorDireccion = dir;
            }
        }
    }
    return mejorDireccion;
}