#pragma once
#include "MyApplicationContext.h"
class ObjectMan;

class
	UserControl
{  // clase recubridora
public:
	ObjectMan* getControl() { return object; };
	friend class ObjectMan;
protected:
	UserControl(ObjectMan * obj) : object(obj) {};
	~UserControl() { };
	ObjectMan* object;  // ObjectMan: clase raíz de una jerarquía

};

class
	ObjectMan
{
public:
	static const Ogre::uint32 MY_QUERY_MASK = 1; // << 0;
	ObjectMan(){};
	
		virtual bool mousePicking(const OgreBites::MouseButtonEvent& evt)
	{
		return true;
	};
	virtual void frameRendered(const Ogre::FrameEvent &  evt) { };
	virtual void setObjMan(Ogre::MovableObject* mObj);
	virtual ~ObjectMan();
protected:
	ObjectMan(Ogre::SceneNode* scnNode);
	Ogre::SceneNode* node = nullptr;
	UserControl* control = nullptr;
	Ogre::Entity * ent = nullptr;
};
