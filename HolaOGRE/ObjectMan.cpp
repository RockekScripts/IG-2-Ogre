#include "ObjectMan.h"
#include <string>
#include <iostream>
using namespace Ogre;
ObjectMan::ObjectMan
(Ogre::SceneNode* scnNode) : node(scnNode) {
	control = new
		UserControl
		(this);
}
ObjectMan::~ObjectMan() {
	
}
void ObjectMan:: setObjMan (MovableObject* mObj) {
   // comprobar que es primer objeto que se adjunta al nodo

		node->attachObject(mObj);
		node->getAttachedObject(0)->getUserObjectBindings().setUserAny(Ogre::Any(control));
}