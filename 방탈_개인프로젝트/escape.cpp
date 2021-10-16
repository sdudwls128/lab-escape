#include "escape.h"

Escape::Escape() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	startMenu = Scene::create("", "Images/startMenu.png");
	labExplain = Scene::create("", "Images/menu1.png");

	labButton = Object::create("Images/labButton.png", startMenu, 145, 80);
	labPlayButton = Object::create("Images/playButton.png", labExplain, 170, 220);
	labBackButton = Object::create("Images/backButton.png", labExplain, 170, 120);

	labButton->setOnMouseCallback([&](ObjectPtr obj, int x, int y, MouseAction action)->bool {
		labExplain->enter();
		return true;
	});

	labPlayButton->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		labGame.labStart();
		return true;
	});

	labBackButton->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		startMenu->enter();
		return true;
	});
}

bool Escape::gameStart() {
	startGame(startMenu);
	return true;
}