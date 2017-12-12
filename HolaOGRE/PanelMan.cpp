#include "PanelMan.h"

using namespace Ogre;

PanelMan::PanelMan(SceneNode * scnNode) : ObjectMan(scnNode)
{
	
	MeshPtr plane = MeshManager::getSingleton().createPlane("mFondo",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Z, 0),
		(Real)node->getCreator()->getCamera("Cam")->getViewport()->getActualWidth(),
		(Real)node->getCreator()->getCamera("Cam")->getViewport()->getActualHeight(),
		10, 10, true, 1, 1.0, 1.0, Vector3::UNIT_Y);
	Entity* entPlano = node->getCreator()->createEntity("entFondo", "mFondo");

	entPlano->getSubEntity(0)->getMaterial()->
		getTechnique(0)->getPass(0) ->
		createTextureUnitState("RustedMetal.jpg");
	Ogre::SceneNode* nodee = node->getCreator()->getRootSceneNode()->createChildSceneNode("nodoPlano");
	node->attachObject(entPlano);

	Camera* camRef = node->getCreator()->createCamera("RefCam");
	camRef->setNearClipDistance(node->getCreator()->getCamera("Cam")->getNearClipDistance());
	camRef->setFarClipDistance(node->getCreator()->getCamera("Cam")->getFarClipDistance());
	camRef->setAutoAspectRatio(true);


	camRef->enableReflection(Plane(Vector3::UNIT_Z, 0));
	camRef->enableCustomNearClipPlane(Plane(Vector3::UNIT_Z, 0));

	node->getCreator()->getSceneNode("CamNode")->attachObject(camRef);
	TexturePtr rttTex = TextureManager::getSingleton().createManual(
		"texRtt",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		TEX_TYPE_2D,
		(Real)node->getCreator()->getCamera("Cam")->getViewport()->getActualWidth(),
		(Real)node->getCreator()->getCamera("Cam")->getViewport()->getActualHeight(),
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

	rayScnQuery = node->getCreator()->createRayQuery(Ray());
	rayScnQuery->setSortByDistance(true); 
}


PanelMan::~PanelMan()
{
}
