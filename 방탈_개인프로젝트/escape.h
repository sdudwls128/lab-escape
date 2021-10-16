#pragma once
#include "lab.h"

class Escape {
	ScenePtr startMenu;
	ScenePtr labExplain;

	ObjectPtr labButton;
	ObjectPtr labPlayButton;
	ObjectPtr labBackButton;

	Lab labGame;

public:
	Escape();
	bool gameStart();
};