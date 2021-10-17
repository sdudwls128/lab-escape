#pragma once
#include "lab.h"

class Escape {
	ScenePtr labExplain;

	ObjectPtr labButton;
	ObjectPtr labPlayButton;

	Lab labGame;

public:
	Escape();
	bool gameStart();
};