#ifndef __HolaApp_H__
#define __HolaApp_H__

#include "MyApplicationContext.h"
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "sinbad.h"
#include "OgreRenderTargetListener.h"

class HolaApp :
	public MyApplicationContext, public OgreBites::InputListener, public Ogre::RenderTargetListener
{
public:
  explicit HolaApp() : MyApplicationContext("HolaApp") { };
  virtual ~HolaApp(){ };   // delete ... los elementos creado con m�todos factoria (create...) se destruyen autom�ticamente 
  
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupInput();
  virtual void setupScene();
  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
  virtual bool mousePressed(const OgreBites::MouseButtonEvent &  evt);
  virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt);
  virtual void frameRendered(const Ogre::FrameEvent &  evt);
  virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
  virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);

  Ogre::SceneManager* scnMgr = nullptr;
  OgreBites::TrayManager* trayMgr = nullptr;
  OgreBites::CameraMan* cameraMgr = nullptr;
  Ogre::SceneNode* lightNode = nullptr;
  Ogre::SceneNode* camNode = nullptr;
};


#endif
