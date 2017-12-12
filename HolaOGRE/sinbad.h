#pragma once
#include <OgreInput.h>
#include <Ogre.h>
#include <vector>
#include "ObjectMan.h"
class sinbad : public OgreBites::InputListener,public ObjectMan
{
public:  
	sinbad(Ogre::SceneNode* scnMgr_);
	~sinbad();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	//virtual bool mousePressed(const OgreBites::MouseButtonEvent &  evt);
	virtual void frameRendered(const Ogre::FrameEvent & evt);
	
private:
	Ogre::SceneNode* scnMgr = nullptr;
	Ogre::Entity* ent;
	Ogre::AnimationState* top;
	Ogre::AnimationState* base;
	Ogre::AnimationState* handle;
	Ogre::MovableObject* espada;
};

