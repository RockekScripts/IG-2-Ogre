#include "BombMan.h"
using namespace Ogre;
BombMan::BombMan(SceneNode * scnMgr) : ObjectMan(scnMgr)
{
	ent = node->getCreator()->createEntity("eBomba", "uv_sphere.mesh");
	ent->setMaterialName("Bomba");
	node->setScale(Vector3(0.01, 0.01, 0.01));
	ent->setQueryFlags(MY_QUERY_INTERACT);
	setObjMan(ent);

	pSystem = node->getCreator()->createParticleSystem("parSystem", "Smoke");

	node->attachObject(pSystem);
	node->setPosition(Vector3(20, 0, -20));
	pSystem->setEmitting(false);
}

BombMan::~BombMan()
{
}

void BombMan::frameRendered(const Ogre::FrameEvent & evt)
{
	y += 0.06;
	node->setPosition(node->getPosition().x, node->getPosition().y + 0.06*sin(y),node->getPosition().z);
	pSystem->getEmitter(0)->setPosition(node->getPosition());

}

void BombMan::interactua(Ogre::String nombre)
{
	if (nombre == "eBomba" && estadoAct != activa) {
		estadoAct = activa;
		pSystem->setEmitting(true);
		ent->setQueryFlags(MY_QUERY_IGNORE);

	}
}
