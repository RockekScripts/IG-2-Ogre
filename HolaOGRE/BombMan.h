#pragma once
#include "OgreInput.h"
#include <Ogre.h>
#include "ObjectMan.h"
class BombMan : public ObjectMan
{
public:
	BombMan(Ogre::SceneNode * scnMgr);
	~BombMan();
	enum estado {
		activa, normal
	};
	virtual void frameRendered(const Ogre::FrameEvent & evt);
	virtual void interactua(Ogre::String nombre);
	estado estadoAct = normal;
	Ogre::Entity* ent = nullptr;
	float y = 0;
	Ogre::ParticleSystem* pSystem = nullptr;
};

