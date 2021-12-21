#include <iostream>
#include <GL/glut.h>

#include "Operation.hpp"
#include "DataType.hpp"
#include "SolarSystem.hpp"

// 視窗位置與大小
#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WIDTH 700
#define HEIGHT 600

using namespace std;

SolarSystem solarSystem;

void onDisplay() {
	solarSystem.onDisplay();
}

void onUpdate() {
	solarSystem.onUpdate();
}

void onKeyboard(byte key, int x, int y) {
	solarSystem.onKeyboard(key, x, y);
}

void onMenu(int item) {
	solarSystem.onMenu(item);
}

int main() {
	system("title 喵嗚");
	system("color 3f");

	cout << "Open GL 載入中 ..." << endl;
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(WINDOW_X_POS, WINDOW_Y_POS);
	glutInitWindowSize(WIDTH, HEIGHT);

	glutCreateWindow("Open GL 期中程式實作");
	// 顯示函式
	glutDisplayFunc(onDisplay);

	// 空閒時更新函式
	glutIdleFunc(onUpdate);

	// 按鍵註冊函式
	glutKeyboardFunc(onKeyboard);

	// 選單註冊函式
	glutCreateMenu(onMenu);
	glutAddMenuEntry("攝影機 +X 移動", ADD_X_OFFSET);
	glutAddMenuEntry("攝影機 -X 移動", SUB_X_OFFSET);
	glutAddMenuEntry("攝影機 +Y 移動", ADD_Y_OFFSET);
	glutAddMenuEntry("攝影機 -Y 移動", SUB_Y_OFFSET);
	glutAddMenuEntry("攝影機 +Z 移動", ADD_Z_OFFSET);
	glutAddMenuEntry("攝影機 -Z 移動", SUB_Z_OFFSET);
	glutAddMenuEntry("重置攝影機", RESET);
	glutAddMenuEntry("結束", EXIT);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return EXIT_SUCCESS;
}