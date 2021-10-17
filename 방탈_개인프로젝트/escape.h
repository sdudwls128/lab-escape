#pragma once
#include "lab.h"

class Escape {
	ScenePtr startScene;
	ScenePtr labExplain;

	ObjectPtr labButton;
	ObjectPtr labPlayButton;

	Lab labGame;

public:
	Escape();
	bool gameStart();
};