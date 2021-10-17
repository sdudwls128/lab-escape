#include "escape.h"

Escape::Escape() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	startScene = Scene::create("", "Images/start-scene.png");
	labExplain = Scene::create("", "Images/lab-explain-scene.png");
	labButton = Object::create("Images/labButton.png", startScene, 825, 370);
	labPlayButton = Object::create("Images/playButton.png", labExplain, 180, 220);

	labButton->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		labExplain->enter();
		return true;
	});
	labPlayButton->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		labGame.labStart();
		return true;
	});
}

bool Escape::gameStart() {
	startGame(startScene);
	return true;
}