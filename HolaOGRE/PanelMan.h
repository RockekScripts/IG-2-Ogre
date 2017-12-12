#pragma once
#include "MyApplicationContext.h"
#include "OgreRenderTargetListener.h"
#include "ObjectMan.h"
class PanelMan :public Ogre::RenderTargetListener, public ObjectMan
{
public:
	PanelMan(Ogre::SceneNode * scnNode);
	~PanelMan();
	Ogre::Camera* cam;

};

