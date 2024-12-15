#include "Pala.h"

Pala::Pala(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Vector3 tam, int i, int helice):
	IG2Object(initPos,node->createChildSceneNode("pala" + std::to_string(i) + std::to_string(helice)),sceneMng,"cube.mesh")
{
	mNode->scale(tam);
    // Crear nodo independiente para la cabeza
    SceneNode* cabezaNode = mNode->createChildSceneNode("cabeza" + std::to_string(i) + std::to_string(helice));
    Vector3 cabezaPos = { -35.0f, 70.0f, 0.0f };  // Posición relativa a la pala
    cabezaNode->setPosition(cabezaPos);

    // Crear la cabeza y asignar su malla
    cabeza = new IG2Object(cabezaPos, cabezaNode, sceneMng, "ogrehead.mesh");

    // Escalar y rotar la cabeza
    cabeza->setScale({ 0.3f, 0.8f, 1.0f });
    cabeza->yaw(Degree(90));

	
}
