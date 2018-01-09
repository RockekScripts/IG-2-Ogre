#include "KnotFly.h"
using namespace Ogre;

KnotFly::KnotFly(Ogre::SceneNode * scnMgr): ObjectMan(scnMgr)
{
	ent = node->getCreator()->createEntity("Knot", "knot.mesh");
	
	ent->setMaterialName("Knot");
	ent->setQueryFlags(MY_QUERY_IGNORE);
	node->setScale(Vector3(0.01, 0.01, 0.01));
	setObjMan(ent);
	sinbad = node->getCreator()->getSceneNode("nSinbad");
	//node->getCreator()->getSceneNode("nSinbad")->addChild(node);
	//node->setPosition(sinbad->getPosition().x, sinbad->getPosition().y + 10, sinbad->getPosition().z);
	node->setPosition(0, 10, 0);
}

KnotFly::~KnotFly()
{
}

void KnotFly::frameRendered(const Ogre::FrameEvent & evt)
{
	node->rotate(Quaternion(Degree(3), Vector3::UNIT_Y));
	//node->setPosition(sinbad->getPosition().x, sinbad->getPosition().y + 10, sinbad->getPosition().z);
}
