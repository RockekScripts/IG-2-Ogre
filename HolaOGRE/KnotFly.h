#pragma once
#include "OgreInput.h"
#include <Ogre.h>
#include "ObjectMan.h"
class KnotFly : public ObjectMan
{
public:
	KnotFly(Ogre::SceneNode* scnMgr);
	~KnotFly();
	virtual void frameRendered(const Ogre::FrameEvent & evt);
	
	Ogre::Entity* ent = nullptr;
	Ogre::Node* sinbad = nullptr;
};

