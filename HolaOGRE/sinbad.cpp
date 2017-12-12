#include "sinbad.h"


sinbad::sinbad(Ogre::SceneNode* scnMgr_) :ObjectMan(scnMgr_)
{
	ent = node->getCreator()->createEntity("nSinbad","Sinbad.mesh");
	 ent->setQueryFlags(MY_QUERY_MASK);
	setObjMan(ent);
	base = ent->getAnimationState("RunBase");
	base->setLoop(true);
	base->setEnabled(true);

	top = ent->getAnimationState("RunTop");
	top->setLoop(true);
	top->setEnabled(true);


	espada = node->getCreator()->createEntity("espada","Sword.mesh");

	ent->attachObjectToBone("Handle.L", espada);
}


sinbad::~sinbad()
{
}
bool sinbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	int avance = 1;
	switch (evt.keysym.sym){
	case SDLK_a:	scnMgr->setPosition(Ogre::Vector3(scnMgr->getPosition().x - avance, scnMgr->getPosition().y, scnMgr->getPosition().z)); break;
	case SDLK_w:	scnMgr->setPosition(Ogre::Vector3(scnMgr->getPosition().x, scnMgr->getPosition().y, scnMgr->getPosition().z + avance)); break;
	case SDLK_s:	scnMgr->setPosition(Ogre::Vector3(scnMgr->getPosition().x , scnMgr->getPosition().y, scnMgr->getPosition().z - avance)); break;
	case SDLK_d:	scnMgr->setPosition(Ogre::Vector3(scnMgr->getPosition().x + avance, scnMgr->getPosition().y, scnMgr->getPosition().z)); break;
	}
	

	return true;
}
void sinbad::frameRendered(const Ogre::FrameEvent &  evt)
{
	float avance = 0.1f;

	//node->yaw(Ogre::Degree(10 *evt.timeSinceLastFrame));
	base->addTime(evt.timeSinceLastFrame);
	node->setPosition(Ogre::Vector3(node->getPosition().x, node->getPosition().y, node->getPosition().z + avance));
	top->addTime(evt.timeSinceLastFrame);
	
}

