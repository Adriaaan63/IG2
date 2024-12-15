#include "Avion.h"

Avion::Avion(Vector3 initPos, SceneNode* node, SceneManager* sceneMng):
	IG2Object(initPos, node->createChildSceneNode("avion"), sceneMng)
{
	createAvion(sceneMng);
	
}

void Avion::createAvion(SceneManager* sceneMng)
{
	IG2Object* cuerpo = new IG2Object(getPosition(), mNode->createChildSceneNode("cuerpo"), sceneMng, "uv_sphere.mesh");
	cuerpo->setScale({ 2.0f, 2.0f, 7.0f });
	cuerpo->setMaterialName("cuerpoAvion");
	composicion.push_back(cuerpo);

	IG2Object* alas = new IG2Object(getPosition(), mNode->createChildSceneNode("alas"), sceneMng, "cube.mesh");
	alas->setScale({ 12.0f, 0.2f, 2.0f });
	alas->setMaterialName("alasAvion");
	composicion.push_back(alas);

	Vector3 posHelice = { getPosition().x - 400, getPosition().y, getPosition().z + 105};
	Helice* helice1 = new Helice(posHelice, mNode, sceneMng, 1, 7);
	composicion.push_back(helice1);

	posHelice = { getPosition().x + 400, getPosition().y, getPosition().z + 105 };
	Helice* helice2 = new Helice(posHelice, mNode, sceneMng, 2, 7);
	composicion.push_back(helice2);

	posHelice = { getPosition().x, getPosition().y + 80, getPosition().z + 370 };
	IG2Object* player = new IG2Object(posHelice, mNode->createChildSceneNode("player"), sceneMng, "ninja.mesh");
	player->yaw(Degree(180));
	composicion.push_back(player);

	posHelice = { getPosition().x, getPosition().y + 150, getPosition().z - 530 };
	IG2Object* cola = new IG2Object(posHelice, mNode->createChildSceneNode("cola"), sceneMng, "cube.mesh");
	cola->setScale({ 0.2f,1.3f,1.0f });
	cola->pitch(Degree(-15));
	composicion.push_back(cola);

	emisoresPart.push_back(new EmisorParticulas(cola->getPosition(), mNode, sceneMng, 1, "example/smokeParticle"));
}

void Avion::frameRendered(const Ogre::FrameEvent& evt) {
	for (auto& e : composicion) {
		e->frameRendered(evt);
	}
}

