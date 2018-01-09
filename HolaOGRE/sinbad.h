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
	virtual void interactua(const Ogre::String name);
	enum estados {
		quieto,corriendo, atacando, muerto
	};
private:
	estados estadoAct = corriendo;
	Ogre::SceneNode* scnMgr = nullptr;
	Ogre::Entity* ent;
	Ogre::AnimationState* top;
	Ogre::AnimationState* base;
	Ogre::AnimationState* handle;
	Ogre::AnimationState* dance;
	Ogre::AnimationState* ataca;
	Ogre::AnimationState* espadas;

	Ogre::MovableObject* espadaL;
	Ogre::MovableObject* espadaR;
	Ogre::NodeAnimationTrack * track;
	Ogre::TransformKeyFrame * kf;
	Ogre::AnimationState * animationState;
	Ogre::Vector3 keyframePos;
	
};

