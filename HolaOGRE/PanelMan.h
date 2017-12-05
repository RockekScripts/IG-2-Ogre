#pragma once
#include "MyApplicationContext.h"
#include "OgreRenderTargetListener.h"
#include "ObjectMan.h"
class PanelMan :public Ogre::RenderTargetListener, public ObjectMan
{
public:
	PanelMan(Ogre::SceneNode * scnMgr);
	~PanelMan();
	Ogre::Camera* cam;
	Ogre::RaySceneQuery * rayScnQuery = nullptr;
};

