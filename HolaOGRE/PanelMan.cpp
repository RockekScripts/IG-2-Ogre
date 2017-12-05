#include "PanelMan.h"

using namespace Ogre;

PanelMan::PanelMan(SceneNode * scnMgr) : ObjectMan(scnMgr)
{

	MeshPtr plane = MeshManager::getSingleton().createPlane("mFondo",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Z, 0),
		(Real)scnMgr->getCreator()->getCamera("Cam")->getViewport()->getActualWidth(),
		(Real)scnMgr->getCreator()->getCamera("Cam")->getViewport()->getActualHeight(),
		10, 10, true, 1, 1.0, 1.0, Vector3::UNIT_Y);
	Entity* entPlano = scnMgr->getCreator()->createEntity("entFondo", "mFondo");

	entPlano->getSubEntity(0)->getMaterial()->
		getTechnique(0)->getPass(0) ->
		createTextureUnitState("RustedMetal.jpg");
	Ogre::SceneNode* nodee = scnMgr->getCreator()->getRootSceneNode()->createChildSceneNode("nodoPlano");
	nodee->attachObject(entPlano);

	Camera* camRef = scnMgr->getCreator()->createCamera("RefCam");
	camRef->setNearClipDistance(cam->getNearClipDistance());
	camRef->setFarClipDistance(cam->getFarClipDistance());
	camRef->setAutoAspectRatio(true);


	camRef->enableReflection(Plane(Vector3::UNIT_Z, 0));
	camRef->enableCustomNearClipPlane(Plane(Vector3::UNIT_Z, 0));

	scnMgr->getCreator()->getSceneNode("CamNode")->attachObject(camRef);
	TexturePtr rttTex = TextureManager::getSingleton().createManual(
		"texRtt",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		TEX_TYPE_2D,
		(Real)scnMgr->getCreator()->getCamera("Cam")->getViewport()->getActualWidth(),
		(Real)scnMgr->getCreator()->getCamera("Cam")->getViewport()->getActualHeight(),
		0, PF_R8G8B8, TU_RENDERTARGET);

	RenderTexture* renderTexture = rttTex->getBuffer()->getRenderTarget();
	Viewport * v = renderTexture->addViewport(camRef);
	v->setClearEveryFrame(true);
	v->setBackgroundColour(ColourValue::Black);

	TextureUnitState* t = entPlano->getSubEntity(0)->getMaterial()->
		getTechnique(0)->getPass(0)->
		createTextureUnitState("texRtt");
	t->setColourOperation(LBO_ADD); // backgroundColour -> black
	// LBO_MODULATE / LBO_REPLACE / LBO_ALPHA_BLEND;
	t->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
	t->setProjectiveTexturing(true, camRef);
	renderTexture->addListener(this);

	rayScnQuery = scnMgr->getCreator()->createRayQuery(Ray());
	rayScnQuery->setSortByDistance(true); 
}


PanelMan::~PanelMan()
{
}
