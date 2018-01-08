#include "sinbad.h"

using namespace Ogre;
sinbad::sinbad(SceneNode* scnMgr_) :ObjectMan(scnMgr_)
{
	float duracion = 24.0f;
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
/*	dance = ent->getAnimationState("Dance");
	dance->setLoop(true);
	dance->setEnabled(true);
	*/
	espadaL = node->getCreator()->createEntity("espadaL","Sword.mesh");
	ent->attachObjectToBone("Handle.L", espadaL);
	espadaR = node->getCreator()->createEntity("espadaR", "Sword.mesh");
	ent->attachObjectToBone("Sheath.R", espadaR);
	
	//*/
	/*SceneNode * nodeKnot = node->getCreator()->getRootSceneNode()->createChildSceneNode("nKnot");
	Entity * entKnot = node->getCreator()->createEntity("entKnot", "knot.mesh");
	nodeKnot->attachObject(entKnot); // Examples.material -> "2 – Default " -> MtlPlat2.jpg	
	 */
	Animation * animation = node->getCreator()->createAnimation("animSinbad", duracion);
	 track = animation->createNodeTrack(0);
	track->setAssociatedNode(node->getCreator()->getSceneNode("nSinbad"));


	Real longitudPaso = duracion / 4.0;
	Real tamDesplazamiento = 40;

	keyframePos = Vector3(0, 0, 0);
	Quaternion Rotacion = Quaternion(Radian(Degree(0)), Vector3(0, 1, 0));
	 // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)

	kf = track->createNodeKeyFrame(longitudPaso * 0); // Keyframe 0: origen.
	kf->setTranslate(keyframePos); // Origen: Vector3
	kf->setRotation(Quaternion(Radian(Degree(0)), Vector3(0, 1, 0)));
	kf = track->createNodeKeyFrame(longitudPaso * 0+1); // Keyframe 0: origen.
	kf->setTranslate(keyframePos); // Origen: Vector3
	kf->setRotation(Quaternion(Radian(Degree(90)), Vector3(0, 1, 0)));



	kf = track->createNodeKeyFrame(longitudPaso * 1); // Keyframe 1: arriba.
	keyframePos = Vector3(tamDesplazamiento, 0, 0);
	kf->setRotation(Quaternion(Radian(Degree(90)), Vector3(0, 1, 0)));
	kf->setTranslate(keyframePos); // Arriba

	kf = track->createNodeKeyFrame(longitudPaso * 1+1); // Keyframe 1: arriba.
	keyframePos = Vector3(tamDesplazamiento, 0, 0);
	kf->setRotation(Quaternion(Radian(Degree(180)), Vector3(0, 1, 0)));
	kf->setTranslate(keyframePos); // Arriba
	

	kf = track->createNodeKeyFrame(longitudPaso * 2 );
	keyframePos = Vector3(tamDesplazamiento, 0, -tamDesplazamiento);
	kf->setRotation(Quaternion(Radian(Degree(180)), Vector3(0, 1, 0)));
	kf->setTranslate(keyframePos); // Arriba

	// Keyframe 2: origen. ….
	kf = track->createNodeKeyFrame(longitudPaso * 2+1);
	keyframePos = Vector3(tamDesplazamiento, 0, -tamDesplazamiento);
	kf->setRotation(Quaternion(Radian(Degree(270)), Vector3(0, 1, 0)));
	kf->setTranslate(keyframePos); // Arriba
	

	kf = track->createNodeKeyFrame(longitudPaso * 3 ); // Keyframe 3: abajo.
	keyframePos = Vector3(0, 0, -tamDesplazamiento);
	kf->setTranslate(keyframePos); // Abajo
	
	kf->setRotation(Quaternion(Radian(Degree(270)), Vector3(0, 1, 0)));

	kf = track->createNodeKeyFrame(longitudPaso * 3+1); // Keyframe 3: abajo.
	keyframePos = Vector3(0, 0, -tamDesplazamiento);
	kf->setTranslate(keyframePos); // Abajo
	
	kf->setRotation(Quaternion(Radian(Degree(360)), Vector3(0, 1, 0)));

	kf = track->createNodeKeyFrame(longitudPaso * 4); // Keyframe 4: origen.
	keyframePos = Vector3(0, 0, 0);
	kf->setTranslate(keyframePos); // Origen.
	
	

	
	animationState = node->getCreator()->createAnimationState("animSinbad");
	animationState->setLoop(true);
	animationState->setEnabled(true);
//	dance->setEnabled(true);

}


sinbad::~sinbad()
{
}
bool sinbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{


	return true;
}
void sinbad::frameRendered(const Ogre::FrameEvent &  evt)
{
	
	//node->yaw(Ogre::Degree(10 *evt.timeSinceLastFrame));
	if (estadoAct == corriendo) {
		top->addTime(evt.timeSinceLastFrame);
		base->addTime(evt.timeSinceLastFrame);
		animationState->addTime(evt.timeSinceLastFrame);
	}
	else if(estadoAct == atacando) {
		if (!ataca->hasEnded()) {
			base->addTime(evt.timeSinceLastFrame);
			top->addTime(evt.timeSinceLastFrame);
			ataca->addTime(evt.timeSinceLastFrame);
		}
		else {
			base->setEnabled(false);
			top->setEnabled(false);
			ataca->setEnabled(false);
			estadoAct = muerto ;
			node->pitch(Degree(-90));
			node->translate(Vector3(0, -3.5, 0));
		}
	}
	else if (estadoAct == muerto) {
		node->translate(Vector3(0, 0, -0.05));
	}
	
}

void sinbad::interactua(const String name)
{
	if (name == "nSinbad" && estadoAct != atacando && estadoAct != muerto) {
		if (estadoAct == quieto)
			estadoAct = corriendo;
		else estadoAct = quieto;

		 !animationState->getEnabled();
		top->setEnabled(!animationState->getEnabled());
		base->setEnabled(!animationState->getEnabled());
		animationState->setEnabled(!animationState->getEnabled());
	}

	if (name == "eBomba") {
		estadoAct = atacando;
		ent->detachObjectFromBone(espadaR);
		ent->attachObjectToBone("Handle.R", espadaR);
		animationState->setEnabled(false);
		Real duracion = 8;
		Animation * animAtaca = node->getCreator()->createAnimation("animAtack", duracion);
		NodeAnimationTrack * track = animAtaca->createNodeTrack(0);
		track->setAssociatedNode(node->getCreator()->getSceneNode("nSinbad"));

		Vector3 keyframePos(node->getPosition());
		TransformKeyFrame* kf;

		kf = track->createNodeKeyFrame(duracion * 0); // Keyframe 0: origen.
		kf->setTranslate(keyframePos); // Origen: Vector3
		kf->setRotation(node->getOrientation());

		kf = track->createNodeKeyFrame(duracion * 0.5);
		Vector3 diferencia = node->getPosition() - node->getCreator()->getSceneNode("Bomba")->getPosition();
		Real radio = sqrt((diferencia.x * diferencia.x) + (diferencia.z * diferencia.z));
		//Real radio = sqrt(pow(diferencia.x, 2) + pow(diferencia.z, 2));
		float grado = acos(node->getPosition().x / radio);
		grado += 3.14159 / 2;
		kf->setRotation(Quaternion(Radian(grado - node->getOrientation().y), Ogre::Vector3::UNIT_Y));
		kf->setTranslate(node->getPosition()); // Origen: Vector3

		kf = track->createNodeKeyFrame(duracion); // Keyframe 0: origen.
		kf->setTranslate(Vector3(node->getCreator()->getSceneNode("Bomba")->getPosition().x,0, node->getCreator()->getSceneNode("Bomba")->getPosition().z)); // Origen: Vector3
		kf->setRotation(Quaternion(Radian(grado), Ogre::Vector3::UNIT_Y));

		ataca = node->getCreator()->createAnimationState("animAtack");
		ataca->setLoop(false);
		ataca->setEnabled(true);

	}
}

