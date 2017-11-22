#pragma once
#include <OgreInput.h>
#include <Ogre.h>
#include <vector>
class sinbad : public OgreBites::InputListener
{
public:  
	sinbad(Ogre::SceneNode* scnMgr_);
	~sinbad();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	
private:
	Ogre::SceneNode* scnMgr = nullptr;
	
};

