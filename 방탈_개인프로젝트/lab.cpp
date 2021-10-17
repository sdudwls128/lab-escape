#include "lab.h"

Lab::Lab() {
	setAisleScene();
	setDoorScene();
	setFrontScene();
	setExitScene();
	setLeftScene();
	setRightScene();
	setComputerScene();
	setDrawerScene();
	setMiddleScene();

}

/** lab.h를 참조하는 다른 소스코드에서 게임을 시작할 수 있도록 함 **/
void Lab::labStart() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, true);
	aisleScene->enter();
}


void Lab::setAisleScene() {
	aisleScene = Scene::create("", "Images/aisle.png");
	aisleDoor = Object::create("Images/door-caution-close.png", aisleScene, 580, 330);
	aisleDoor->setScale(0.12);
	aisleDoor->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		doorScene->enter();
		return true;
	});
}


void Lab::setDoorScene(){
	doorInIsOpen = 0;
	doorScene = Scene::create("", "Images/door-background.png");
	doorIn = Object::create("Images/door-caution-close.png", doorScene, 150, 0);
	doorIn->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (doorInIsOpen == 0) {
			doorIn->setImage("Images/door-caution-open.png");
			doorInIsOpen = 1;
		}
		else if (doorInIsOpen == 1) 
			frontScene->enter();
		return true;
	});
}


void Lab::setFrontScene() {
	frontScene = Scene::create("", "Images/Front/lab-front.png");
	frontBack = Object::create("Images/back.png", frontScene, 600, 50);
	frontLeft = Object::create("Images/Left/bookshelf.png", frontScene, 220, 200);
	frontLeft->setScale(0.5);
	frontMiddle = Object::create("Images/Middle/clock.png", frontScene, 640, 460);
	frontRight = Object::create("Images/Right/desk-set.png", frontScene, 780, 155);

	int x[6] = { 235, 333, 350, 425, 240, 325 };
	int y[6] = { 425, 425, 345, 345, 280, 225 };

	for (int i = 0; i < 6; i++) {
		sprintf_s(path, "Images/Left/prop%d.png", i + 1);
		frontProps[i] = Object::create(path, frontScene, x[i], y[i]);
		frontProps[i]->setScale(0.5);
	}

	frontBack->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		exitScene->enter();
		return true;
	});
	frontLeft->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		leftScene->enter();
		return true;
	});
	frontMiddle->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		middleScene->enter();
		return true;
	});
	frontRight->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		rightScene->enter();
		return true;
	});
}


void Lab::setExitScene() {
	exitScene = Scene::create("", "Images/Front/lab-front.png");
	exitBack = Object::create("Images/back.png", exitScene, 600, 50);
	exitDoor = Object::create("Images/door-close.png", exitScene, 400, 220);
	exitDoor->setScale(0.45);
	
	exitBack->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		frontScene->enter();
		return true;
	});

	exitDoor->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (isComplete == 0) 
			showMessage("코드를 풀지 못했습니다.\n코드를 입력하기 전까지 문을 열 수 없습니다.");
		else if (isComplete == 1) {
			if (exitDoorIsOpen == 0) {
				exitDoor->setImage("Images/door-open.png");
				exitDoorIsOpen = 1;
				showMessage("축하합니다. 탈출에 성공했습니다!");
			}
			else if (exitDoorIsOpen == 1) {
				endGame();
			}
		}

		return true;
	});
}


void Lab::setLeftScene() {
	leftScene = Scene::create("", "Images/Left/lab-left.png");
	leftBack = Object::create("Images/back.png", leftScene, 600, 50);
	leftBookshelf = Object::create("Images/Left/bookshelf.png", leftScene, 101, 80);
	key = Object::create("Images/Left/key.png", leftScene, 560, 372);
	key->setScale(0.15);

	int originX[6] = { 123, 325, 355, 507, 136, 310 };
	int originY[6] = { 525, 525, 372, 372, 230, 115 };

	for (int i = 0; i < 6; i++) {
		sprintf_s(path, "Images/Left/prop%d.png", i + 1);
		leftProps[i] = Object::create(path, leftScene, originX[i], originY[i]);
		leftProps[i]->setScale(1.1);

		leftProps[i]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
			obj->locate(leftScene, 780, 100);
			return true;
		});
	}

	key->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		obj->pick();
		return true;
	});
	leftBack->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		frontScene->enter();
		return true;
	});
}


void Lab::setRightScene() {
	rightScene = Scene::create("", "Images/Right/lab-right.png");
	rightBack = Object::create("Images/back.png", rightScene, 600, 50);
	computer = Object::create("Images/Right/monitor.png", rightScene, 650, 460);
	computer->setScale(1.6);
	drawerSet = Object::create("Images/Right/drawers.png", rightScene, 490, 135);
	drawerSet->setScale(0.6);

	rightBack->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		frontScene->enter();
		return true;
	});
	computer->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		computerScene->enter();
		return true;
	});
	drawerSet->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		drawerScene->enter();
		return true;
	});
}

void Lab::setComputerScene() {
	computerScene = Scene::create("", "Images/Right/computer-scene.png");
	computerBack = Object::create("Images/back.png", computerScene, 600, 50);

	computerBack->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		rightScene->enter();
		return true;
	});
	
}

void Lab::setDrawerScene() {
	drawerScene = Scene::create("", "Images/Right/drawer-background.png");
	drawerBack = Object::create("Images/back.png", drawerScene, 600, 50);

	boxIsOpen = 0;
	for (int i = 0; i < 3; i++) {
		drawerIsOpen[i] = 0;
		drawerIsSolve[i] = 0;
	}

	for (int i = 2; i > -1; i--) {
		sprintf_s(path, "Images/Right/drawer%d-close.png", i + 1);
		drawers[i] = Object::create(path, drawerScene, 453, 550 - i * 138);
		sprintf_s(path, "Images/Right/hint%d.png", i + 1);
		hints[i] = Object::create(path, drawerScene, 475, 460 - i * 110);
		hints[i]->setScale(0.15);
		hints[i]->hide();

		hints[i]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
			obj->pick();
			return true;
		});
		
		hints[i]->setOnDropCallback([&](auto obj)->bool {
			showMessage("힌트는 버릴 수 없습니다!");
			obj->pick();
			return true;
		});
	}

	box = Object::create("Images/Right/box-close.png", drawerScene, 470, 200, false);
	box->setScale(0.15);
	
	drawers[0]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (drawerIsOpen[0] == 0) {
			obj->setImage("Images/Right/drawer1-open.png");
			obj->locate(drawerScene, 350, 270);
			drawerIsOpen[0] = 1;
			hints[0]->show();
		}
		else {
			obj->setImage("Images/Right/drawer1-close.png");
			obj->locate(drawerScene, 453, 550);
			drawerIsOpen[0] = 0;
			hints[0]->hide();
		}
		return true;
	});
	
	drawers[1]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (drawerIsOpen[1] == 0) {
			obj->setImage("Images/Right/drawer2-open.png");
			obj->locate(drawerScene, 360, 150);
			drawerIsOpen[1] = 1;
			hints[1]->show();
		}
		else {
			obj->setImage("Images/Right/drawer2-close.png");
			obj->locate(drawerScene, 453, 412);
			drawerIsOpen[1] = 0;
			hints[1]->hide();
		}
		return true;
	});

	drawers[2]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (drawerIsOpen[2] == 0) {
			obj->setImage("Images/Right/drawer3-open.png");
			obj->locate(drawerScene, 365, 15);
			drawerIsOpen[2] = 1;
			box->show();
			if (boxIsOpen == 1)
				hints[2]->show();
		}
		else {
			obj->setImage("Images/Right/drawer3-close.png");
			obj->locate(drawerScene, 455, 280);
			drawerIsOpen[2] = 0;
			box->hide();
			if (boxIsOpen == 1)
				hints[2]->hide();
		}
		return true;
	});

	box->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (boxIsOpen == 0) {
			if (key->isHanded()) {
				box->setImage("Images/Right/box-open.png");
				box->setScale(0.18);
				box->locate(drawerScene, 470, 185);
				boxIsOpen = 1;
				hints[2]->locate(drawerScene, 510, 320);
				hints[2]->show();
			}
			else {
				showMessage("상자가 잠겨있네. 열쇠가 필요하겠군!");
			}
		}
		return true;
	});
	drawerBack->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		rightScene->enter();
		return true;
	});
}


void Lab::setMiddleScene() {
	middleScene = Scene::create("", "Images/Middle/lab-middle.png");
	middleBack = Object::create("Images/back.png", middleScene, 600, 50);
	middleBack->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		frontScene->enter();
		return true;
	});
}