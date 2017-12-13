#include "sinbad.h"

using namespace Ogre;
sinbad::sinbad(SceneNode* scnMgr_) :ObjectMan(scnMgr_)
{
	float duracion = 10.0f;
	keyframePos = Vector3(0, 0, 0);
	ent = node->getCreator()->createEntity("nSinbad","Sinbad.mesh");
		 ent->setQueryFlags(MY_QUERY_MASK);
		 node->getCreator()->getSceneNode("nSinbad")->scale(Vector3(4.0, 4.0, 4.0));
	setObjMan(ent);
	
	base = ent->getAnimationState("RunBase");
	
	base->setLoop(true);
	base->setEnabled(true);

	top = ent->getAnimationState("RunTop");
	top->setLoop(true);
	top->setEnabled(true);

	/*
	espada = node->getCreator()->createEntity("espada","Sword.mesh");

	ent->attachObjectToBone("Handle.L", espada);

	*/
	/*SceneNode * nodeKnot = node->getCreator()->getRootSceneNode()->createChildSceneNode("nKnot");
	Entity * entKnot = node->getCreator()->createEntity("entKnot", "knot.mesh");
	nodeKnot->attachObject(entKnot); // Examples.material -> "2 – Default " -> MtlPlat2.jpg	


	 */
	Animation * animation = node->getCreator()->createAnimation("animSinbad", duracion);
	 track = animation->createNodeTrack(0);
	track->setAssociatedNode(node->getCreator()->getSceneNode("nSinbad"));	Real longitudPaso = duracion / 4.0;
	Real tamDesplazamiento = 10.0;
	 // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)
	kf = track->createNodeKeyFrame(longitudPaso * 0); // Keyframe 0: origen.
	kf->setTranslate(keyframePos); // Origen: Vector3	kf->setScale(Vector3(4.0, 4.0, 4.0));	kf = track->createNodeKeyFrame(longitudPaso * 1); // Keyframe 1: arriba.
	keyframePos += Vector3::UNIT_Y * tamDesplazamiento;
	kf->setTranslate(keyframePos); // Arriba
	kf->setScale(Vector3(4.0, 4.0, 4.0));
	// Keyframe 2: origen. ….
	kf = track->createNodeKeyFrame(longitudPaso * 2); 
	keyframePos += Vector3::UNIT_Y * tamDesplazamiento;
	kf->setTranslate(keyframePos); // Arriba
	kf->setScale(Vector3(4.0, 4.0, 4.0));


	kf = track->createNodeKeyFrame(longitudPaso * 3); // Keyframe 3: abajo.
	keyframePos += Vector3::UNIT_Y * tamDesplazamiento * -2;
	kf->setTranslate(keyframePos); // Abajo
	kf->setScale(Vector3(4.0, 4.0, 4.0));

	kf = track->createNodeKeyFrame(longitudPaso * 4); // Keyframe 4: origen.
	keyframePos += Vector3::UNIT_Y * tamDesplazamiento;
	kf->setTranslate(keyframePos); // Origen.	kf->setScale(Vector3(4.0, 4.0, 4.0));	animationState = node->getCreator()->createAnimationState("animSinbad");
	animationState->setLoop(true);
	animationState->setEnabled(true);	
}


sinbad::~sinbad()
{
}
bool sinbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	int avance = 1;
	switch (evt.keysym.sym){
	case SDLK_a:	scnMgr->setPosition(Ogre::Vector3(scnMgr->getPosition().x - avance, scnMgr->getPosition().y, scnMgr->getPosition().z)); break;
	case SDLK_w:	scnMgr->setPosition(Ogre::Vector3(scnMgr->getPosition().x, scnMgr->getPosition().y, scnMgr->getPosition().z + avance)); break;
	case SDLK_s:	scnMgr->setPosition(Ogre::Vector3(scnMgr->getPosition().x , scnMgr->getPosition().y, scnMgr->getPosition().z - avance)); break;
	case SDLK_d:	scnMgr->setPosition(Ogre::Vector3(scnMgr->getPosition().x + avance, scnMgr->getPosition().y, scnMgr->getPosition().z)); break;
	}
	

	return true;
}
void sinbad::frameRendered(const Ogre::FrameEvent &  evt)
{
	
	//node->yaw(Ogre::Degree(10 *evt.timeSinceLastFrame));
	base->addTime(evt.timeSinceLastFrame);
	top->addTime(evt.timeSinceLastFrame);
	animationState->addTime(evt.timeSinceLastFrame);
	
	
}

