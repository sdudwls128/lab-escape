#pragma once
#include <iostream>
#include <bangtal>
using namespace std;
using namespace bangtal;

class Lab {
	TimerPtr timer;

	char path[40];

	//Aisle
	ScenePtr aisleScene;
	ObjectPtr aisleDoor;
	
	//Door
	ScenePtr doorScene;
	ObjectPtr doorIn;
	int doorInIsOpen;

	//Front
	ScenePtr frontScene;
	ObjectPtr frontBack;
	ObjectPtr frontLeft;
	ObjectPtr frontMiddle;
	ObjectPtr frontRight;
	ObjectPtr frontProps[6];

	//Exit
	ScenePtr exitScene;
	ObjectPtr exitDoor;
	ObjectPtr exitBack;
	int isComplete;
	int exitDoorIsOpen;

	//Left
	ScenePtr leftScene;
	ObjectPtr leftBack;
	ObjectPtr leftBookshelf;
	ObjectPtr leftProps[6];
	ObjectPtr key;
	
	//Middle
	ScenePtr middleScene;
	ObjectPtr middleBack;

	//Right
	ScenePtr rightScene;
	ObjectPtr rightBack;
	ObjectPtr drawerSet;
	ObjectPtr computer;

	//Computer
	ScenePtr computerScene;
	ObjectPtr computerBack;
	ObjectPtr password[4];
	ObjectPtr keypad[26];
	ObjectPtr enter;
	ObjectPtr clear;


	//Drawer
	ScenePtr drawerScene;
	ObjectPtr drawerBack;
	ObjectPtr drawers[3];
	ObjectPtr drawer3Lock[6];
	ObjectPtr box;
	ObjectPtr hints[3];

public:
	Lab();
	void labStart();
	void setAisleScene();
	void setDoorScene();
	void setFrontScene();
	void setExitScene();
	void setLeftScene();
	void setMiddleScene();
	void setRightScene();
	void setComputerScene();
	void setDrawerScene();
};