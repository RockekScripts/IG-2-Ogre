#include "sinbad.h"


sinbad::sinbad(Ogre::SceneNode* scnMgr_) :ObjectMan(scnMgr_)
{
	ent = node->getCreator()->createEntity("nSinbad","Sinbad.mesh");
	 ent->setQueryFlags(MY_QUERY_MASK);
	setObjMan(ent);
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

