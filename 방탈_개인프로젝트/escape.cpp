#include "escape.h"

Escape::Escape() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	labExplain = Scene::create("", "Images/menu1.png");
	labPlayButton = Object::create("Images/playButton.png", labExplain, 170, 220);

	labPlayButton->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		labGame.labStart();
		return true;
	});

}

bool Escape::gameStart() {
	startGame(labExplain);
	return true;
}