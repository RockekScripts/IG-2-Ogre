#include "HolaApp.h"
#include "ObjectMan.h"
#include "PanelMan.h"
#include "BombMan.h"
#include "KnotFly.h"
using namespace Ogre;
enum QueryFlags {
	MY_QUERY_IGNORE = 1 << 1,
	MY_QUERY_INTERACT = 1 << 0
};
void HolaApp::frameRendered(const FrameEvent &  evt)
{
 // trayMgr->frameRendered(evt);

	for (int i = 0; i < vecObjMan.size(); ++i){
		vecObjMan[i]->frameRendered(evt);
	}
}

bool HolaApp::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    mRoot->queueEndRendering();
  }
  else if (evt.keysym.sym == SDLK_t) {
	  if(cameraMgr->getTarget() == scnMgr->getRootSceneNode())

		  cameraMgr->setTarget(scnMgr->getSceneNode("nSinbad"));
	  else
	 
	  cameraMgr->setTarget(scnMgr->getRootSceneNode());
  }
 
 
  return true;
}

bool HolaApp::mousePressed(const OgreBites::MouseButtonEvent &  evt)
{
	rayScnQuery->setRay(cam->getCameraToViewportRay(
		evt.x / (Real)scnMgr->getCamera("Cam")->getViewport()->getActualWidth(),
		evt.y / (Real)scnMgr->getCamera("Cam")->getViewport()->getActualHeight()));
	
	rayScnQuery->setSortByDistance(true);
	
//rayScnQuery->setQueryMask(MY_QUERY_INTERACT);
	
	RaySceneQueryResult& qryResult = rayScnQuery->execute();
	RaySceneQueryResult::iterator it = qryResult.begin();
	
	while (it != qryResult.end()) {
		
		for each (ObjectMan* var in vecObjMan)
		{
			var->interactua(it->movable->getName());
		}
		
		++it;

	}
	return true;
	}

bool HolaApp::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
 // trayMgr->mouseMoved(evt);
  
  return true;
}

void HolaApp::setupInput()
{
  // do not forget to call the base first
  MyApplicationContext::setupInput(); 
  // register for input events
  addInputListener(this);
}

void HolaApp::shutdown()
{
  scnMgr->removeRenderQueueListener(mOverlaySystem);
  delete trayMgr;  trayMgr = nullptr;
  for (int i = 0; i< vecObjMan.size(); ++i) {
	  delete vecObjMan[i];
  }

  // do not forget to call the base 
  MyApplicationContext::shutdown();
}

void HolaApp::setup(void)
{
  // do not forget to call the base first
  MyApplicationContext::setup();

  scnMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(scnMgr);

  scnMgr->addRenderQueueListener(mOverlaySystem);
  
  trayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow);
  trayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(trayMgr);
  
  setupScene();
}
void HolaApp::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt){

	scnMgr->getEntity("entFondo")->setVisible(false);
	scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
}
void HolaApp::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt){
	scnMgr->getEntity("entFondo")->setVisible(true);
	scnMgr->setAmbientLight(ColourValue(0, 0, 0));
}
void HolaApp::setupScene(void)
{
  // without light we would just get a black screen    
  Light* light = scnMgr->createLight("Light");
  light->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y); // !!! opngl <-> dirección a la fuente de luz
  lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  lightNode->setPosition(0, 10, 0);
  lightNode->attachObject(light);

  Light* directionalLight = scnMgr->createLight("DirectionalLight");
  directionalLight->setDiffuseColour(1.0, 1.0, 1.0);
  directionalLight->setSpecularColour(1.0, 1.0, 1.0);
  directionalLight->setType(Light::LT_DIRECTIONAL);
  directionalLight->setDirection(Vector3::NEGATIVE_UNIT_Z);
  SceneNode* directionalLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  directionalLightNode->attachObject(directionalLight);
  directionalLightNode->setDirection(0, -1, 0);
  directionalLightNode->setPosition(Vector3(20, 30, -20));
  
  // also need to tell where we are
  camNode = scnMgr->getRootSceneNode()->createChildSceneNode("CamNode");
  camNode->setPosition(0, 0, 20);
  camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);


  // create the camera
   cam = scnMgr->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME);  // en material
  camNode->attachObject(cam);

  cameraMgr = new OgreBites::CameraMan(camNode);
  cameraMgr->setStyle(OgreBites::CS_ORBIT);

  addInputListener(cameraMgr);

  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  vp->setBackgroundColour(ColourValue::Black);

 
  rayScnQuery = scnMgr->createRayQuery(Ray());
  rayScnQuery->setSortByDistance(true);

  Ogre::SceneNode*  node = scnMgr->getRootSceneNode()->createChildSceneNode("nSinbad");
  sinbad * aux = new sinbad (node);
  vecObjMan.push_back(aux);
  addInputListener(aux);	

  Ogre::SceneNode* nodee = scnMgr->getRootSceneNode()->createChildSceneNode("Panel");
  PanelMan * panel = new PanelMan(nodee);
  vecObjMan.push_back(panel);

  Ogre::SceneNode* nodeBomb = scnMgr->getRootSceneNode()->createChildSceneNode("Bomba");
  BombMan * bomba = new BombMan(nodeBomb);
  vecObjMan.push_back(bomba);

  Ogre::SceneNode* nodeKnot = node->createChildSceneNode("Knot");
  KnotFly * knot = new KnotFly(nodeKnot);
  vecObjMan.push_back(knot);

  rayScnQuery = scnMgr->createRayQuery(Ray(), MY_QUERY_INTERACT);
 scnMgr -> setSkyPlane (true, Plane(Vector3::UNIT_Z, -20), "Mandelbrot1", 1, 1, true, 1.0 , 100, 100);
}



