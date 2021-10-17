#include "lab.h"

Lab::Lab() {
	setAisleScene();
	setDoorScene();
	setFrontScene();
	setExitScene();
	setLeftScene();
	setMiddleScene();
	setRightScene();
	setComputerScene();
	setDrawerScene();
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

/** set the door scene **/
void Lab::setDoorScene(){
	doorInIsOpen = 0;
	doorScene = Scene::create("", "Images/door-background.png");
	doorIn = Object::create("Images/door-caution-close.png", doorScene, 150, 0);
	doorIn->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (doorInIsOpen == 0) {
			doorIn->setImage("Images/door-caution-open.png");
			doorInIsOpen = 1;
		}
		else  frontScene->enter();
		return true;
	});
}

/** set the front scene **/
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

	// 장면 이동 동작 설정
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

/** set the exit scene **/
void Lab::setExitScene() {
	exitScene = Scene::create("", "Images/Front/lab-front.png");
	exitBack = Object::create("Images/back.png", exitScene, 600, 50);
	exitDoor = Object::create("Images/door-close.png", exitScene, 400, 220);
	exitDoor->setScale(0.45);
	
	// 탈출할 수 있는지 확인하는 동작
	exitDoor->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (isComplete == 0) 
			showMessage("코드를 풀지 못했습니다.\n정확한 코드를 입력하기 전까지 문을 열 수 없습니다.");
		else {
			if (exitDoorIsOpen == 0) {
				exitDoor->setImage("Images/door-open.png");
				exitDoorIsOpen = 1;
				showMessage("축하합니다. 탈출에 성공했습니다!");
			}
			else endGame();
		}
		return true;
	});	
	
	// 이전 장면으로 돌아가는 동작 설정
	exitBack->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		frontScene->enter();
		return true;
	});
}

/** set the left scene **/
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
	}

	// 소품들을 내려놓는 동작 설정
	leftProps[0]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		obj->locate(leftScene, 700, 100);
		frontProps[0]->locate(frontScene, 530, 200);
		return true;
	});
	leftProps[1]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		obj->locate(leftScene, 720, 80);
		frontProps[1]->locate(frontScene, 530, 200);
		return true;
	});
	leftProps[2]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		obj->locate(leftScene, 800, 100);
		frontProps[2]->locate(frontScene, 530, 200);
		return true;
	});
	leftProps[3]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		obj->locate(leftScene, 770, 80);
		frontProps[3]->locate(frontScene, 530, 200);
		return true;
	});
	leftProps[4]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		obj->locate(leftScene, 750, 120);
		frontProps[4]->locate(frontScene, 530, 200);
		return true;
	});
	leftProps[5]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		obj->locate(leftScene, 740, 100);
		frontProps[5]->locate(frontScene, 500, 200);
		return true;
	});

	key->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		obj->pick();
		return true;
	});
	leftBack->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		frontScene->enter();
		return true;
	});
}

/** set the middle scene **/
void Lab::setMiddleScene() {
	middleScene = Scene::create("", "Images/Middle/lab-middle.png");
	middleBack = Object::create("Images/back.png", middleScene, 600, 50);
	middleBack->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		frontScene->enter();
		return true;
	});
}

/** set the right scene **/
void Lab::setRightScene() {
	// 필요한 Scene과 Object 설정
	rightScene = Scene::create("", "Images/Right/lab-right.png");
	rightBack = Object::create("Images/back.png", rightScene, 600, 50);
	computer = Object::create("Images/Right/monitor.png", rightScene, 650, 460);
	computer->setScale(1.6);
	drawerSet = Object::create("Images/Right/drawers.png", rightScene, 490, 135);
	drawerSet->setScale(0.6);
	
	// 하위 장면으로 이동하는 동작 설정
	computer->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		computerScene->enter();
		return true;
	});
	drawerSet->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		drawerScene->enter();
		return true;
	});

	// 이전 장면으로 돌아가는 동작 설정
	rightBack->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		frontScene->enter();
		return true;
	});
}

/** set the computer scene **/
void Lab::setComputerScene() {
	computerScene = Scene::create("", "Images/Right/computer-scene.png");
	computerBack = Object::create("Images/back.png", computerScene, 600, 50);
	int index = 0;
	int input[4] = { 0, 0, 0, 0 };

	for (int i = 0; i < 10; i++) {
		sprintf_s(path, "Images/Right/a%d.png", i + 1);
		keypad[i] = Object::create(path, computerScene, 400 + 57 * i, 360);
		keypad[i]->setScale(0.8);
	}
	for (int i = 10; i < 19; i++) {
		sprintf_s(path, "Images/Right/a%d.png", i + 1);
		keypad[i] = Object::create(path, computerScene, 430 + 57 * (i - 10), 300);
		keypad[i]->setScale(0.8);
	}
	for (int i = 19; i < 26; i++) {
		sprintf_s(path, "Images/Right/a%d.png", i + 1);
		keypad[i] = Object::create(path, computerScene, 493 + 57 * (i - 19), 240);
		keypad[i]->setScale(0.8);
	}
	for (int i = 0; i < 4; i++) {
		password[i] = Object::create("Images/Right/password.png", computerScene, 460 + i * 100, 470, false);
		password[i]->setScale(1.2);
	}
	clear = Object::create("Images/Right/clear.png", computerScene, 346, 240);
	clear->setScale(0.8);
	enter = Object::create("Images/Right/enter.png", computerScene, 893, 240);
	enter->setScale(0.8);

	clear->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		index = 0;
		for (int i = 0; i < 4; i++) {
			input[i] = 0;
			password[i]->hide();
		}
		return true;
	});
	
	// keypad를 입력하고, 입력한 값을 저장하는 동작
	keypad[0]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 0;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[1]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 1;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[2]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 2;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[3]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 3;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[4]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 4;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[5]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 5;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[6]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 6;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[7]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 7;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[8]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 8;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[9]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 9;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[10]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 10;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[11]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 11;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[12]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 12;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[13]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 13;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[14]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 14;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[15]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 15;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[16]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 16;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[17]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 17;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[18]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 18;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[19]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 19;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[20]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 20;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[21]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 21;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[22]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 22;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[23]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 23;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[24]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 24;
			password[index]->show();
			index++;
		}
		return true;
	});
	keypad[25]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (index < 4) {
			input[index] = 25;
			password[index]->show();
			index++;
		}
		return true;
	});

	// 코드를 입력하고 맞는지 확인하는 동작
	enter->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		for (int i = 0; i < 4; i++)
			printf_s("%d  ", input[i]);
		if (input[0] == 3 && input[1] == 10 && input[2] == 7 && input[3] == 24) {
			showMessage("코드가 입력되었습니다. 로봇이 모두 중단됩니다.\n이제 밖으로 나갈 수 있습니다.");
			isComplete = 1;
		}
		else {
			showMessage("잘못된 코드입니다. 다시 시도해보세요.");
			index = 0;
			for (int i = 0; i < 4; i++) {
				input[i] = 0;
				password[i]->hide();
			}
		}
		return true;
	});

	// 이전 장면으로 이동하는 동작 설정
	computerBack->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		rightScene->enter();
		return true;
	});
}

/** Set the drawer scene **/
void Lab::setDrawerScene() {
	drawerScene = Scene::create("", "Images/Right/drawer-background.png");
	drawerBack = Object::create("Images/back.png", drawerScene, 600, 50);

	// 서랍에 관련된 동작을 하는 데 필요한 변수 선언 및 초기화
	int drawer3Index[6] = { 0, };
	int drawerIsOpen[3] = { 0, };
	int drawer3IsSolve = 0;
	int boxIsOpen = 0;
	
	// 3개의 서랍과 힌트 설정
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

	// 세번째 서랍의 비밀번호를 입력하는 Object 설정
	for (int i = 0; i < 6; i++) {
		drawer3Lock[i] = Object::create("Images/Right/0.png", drawerScene, 475 + 30 * i, 315);
		drawer3Lock[i]->setScale(0.7);
	}

	// 세 번째 서랍의 비밀번호를 맞추는 동작 설정
	drawer3Lock[0]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		drawer3Index[0]++;
		sprintf_s(path, "Images/Right/%d.png", drawer3Index[0] % 10);
		obj->setImage(path);
		if (drawer3Index[0] % 10 == 1 && drawer3Index[1] % 10 == 2 && drawer3Index[2] % 10 == 0
			&& drawer3Index[3] % 10 == 8 && drawer3Index[4] % 10 == 0 && drawer3Index[5] % 10 == 4) {
			drawer3IsSolve = 1;
		}
		return true;
	});
	drawer3Lock[1]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		drawer3Index[1]++;
		sprintf_s(path, "Images/Right/%d.png", drawer3Index[1] % 10);
		obj->setImage(path);
		if (drawer3Index[0] % 10 == 1 && drawer3Index[1] % 10 == 2 && drawer3Index[2] % 10 == 0
			&& drawer3Index[3] % 10 == 8 && drawer3Index[4] % 10 == 0 && drawer3Index[5] % 10 == 4) {
			drawer3IsSolve = 1;
		}
		return true;
	});
	drawer3Lock[2]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		drawer3Index[2]++;
		sprintf_s(path, "Images/Right/%d.png", drawer3Index[2] % 10);
		obj->setImage(path);
		if (drawer3Index[0] % 10 == 1 && drawer3Index[1] % 10 == 2 && drawer3Index[2] % 10 == 0
			&& drawer3Index[3] % 10 == 8 && drawer3Index[4] % 10 == 0 && drawer3Index[5] % 10 == 4) {
			drawer3IsSolve = 1;
		}
		return true;
	});
	drawer3Lock[3]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		drawer3Index[3]++;
		sprintf_s(path, "Images/Right/%d.png", drawer3Index[3] % 10);
		obj->setImage(path);
		if (drawer3Index[0] % 10 == 1 && drawer3Index[1] % 10 == 2 && drawer3Index[2] % 10 == 0
			&& drawer3Index[3] % 10 == 8 && drawer3Index[4] % 10 == 0 && drawer3Index[5] % 10 == 4) {
			drawer3IsSolve = 1;
		}
		return true;
	});
	drawer3Lock[4]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		drawer3Index[4]++;
		sprintf_s(path, "Images/Right/%d.png", drawer3Index[4] % 10);
		obj->setImage(path);
		if (drawer3Index[0] % 10 == 1 && drawer3Index[1] % 10 == 2 && drawer3Index[2] % 10 == 0
			&& drawer3Index[3] % 10 == 8 && drawer3Index[4] % 10 == 0 && drawer3Index[5] % 10 == 4) {
			drawer3IsSolve = 1;
		}
		return true;
	});
	drawer3Lock[5]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		drawer3Index[5]++;
		sprintf_s(path, "Images/Right/%d.png", drawer3Index[5] % 10);
		obj->setImage(path);
		if (drawer3Index[0] % 10 == 1 && drawer3Index[1] % 10 == 2 && drawer3Index[2] % 10 == 0
			&& drawer3Index[3] % 10 == 8 && drawer3Index[4] % 10 == 0 && drawer3Index[5] % 10 == 4) {
			drawer3IsSolve = 1;
		}
		return true;
	});

	// 세번째 서랍에 들어있는 힌트 박스 설정
	box = Object::create("Images/Right/box-close.png", drawerScene, 470, 200, false);
	box->setScale(0.15);
	
	// 각 서랍을 열고 닫는 동작 설정
	drawers[0]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (drawerIsOpen[0] == 0) {
			for (int i = 0; i < 6; i++)
				drawer3Lock[i]->hide();
			obj->setImage("Images/Right/drawer1-open.png");
			obj->locate(drawerScene, 350, 270);
			drawerIsOpen[0] = 1;
			hints[0]->show();
		}
		else {
			for (int i = 0; i < 6; i++)
				drawer3Lock[i]->show();
			obj->setImage("Images/Right/drawer1-close.png");
			obj->locate(drawerScene, 453, 550);
			drawerIsOpen[0] = 0;
			hints[0]->hide();
		}
		return true;
	});
	drawers[1]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (drawerIsOpen[1] == 0) {
			for (int i = 0; i < 6; i++)
				drawer3Lock[i]->hide();
			obj->setImage("Images/Right/drawer2-open.png");
			obj->locate(drawerScene, 360, 150);
			drawerIsOpen[1] = 1;
			hints[1]->show();
		}
		else {
			for (int i = 0; i < 6; i++)
				drawer3Lock[i]->show();
			obj->setImage("Images/Right/drawer2-close.png");
			obj->locate(drawerScene, 453, 412);
			drawerIsOpen[1] = 0;
			hints[1]->hide();
		}
		return true;
	});
	drawers[2]->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		if (drawer3IsSolve == 1) {
			if (drawerIsOpen[2] == 0) {
				for (int i = 0; i < 6; i++)
					drawer3Lock[i]->hide();
				obj->setImage("Images/Right/drawer3-open.png");
				obj->locate(drawerScene, 365, 15);
				drawerIsOpen[2] = 1;
				box->show();
				if (boxIsOpen == 1)
					hints[2]->show();
			}
			else {
				for (int i = 0; i < 6; i++)
					drawer3Lock[i]->show();
				obj->setImage("Images/Right/drawer3-close.png");
				obj->locate(drawerScene, 455, 280);
				drawerIsOpen[2] = 0;
				box->hide();
				if (boxIsOpen == 1)
					hints[2]->hide();
			}
		}
		else showMessage("비밀번호가 틀립니다.");
		return true;
	});

	// 힌트 박스를 여는 동작 설정
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

	// 이전 장면으로 돌아가는 동작 설정
	drawerBack->setOnMouseCallback([&](auto obj, auto x, auto y, auto action)->bool {
		rightScene->enter();
		return true;
	});
}
