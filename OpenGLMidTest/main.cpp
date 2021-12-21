#include <iostream>
#include <GL/glut.h>

#include "Operation.hpp"
#include "DataType.hpp"
#include "SolarSystem.hpp"

// ������m�P�j�p
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
	system("title �p��");
	system("color 3f");

	cout << "Open GL ���J�� ..." << endl;
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(WINDOW_X_POS, WINDOW_Y_POS);
	glutInitWindowSize(WIDTH, HEIGHT);

	glutCreateWindow("Open GL �����{����@");
	// ��ܨ禡
	glutDisplayFunc(onDisplay);

	// �Ŷ��ɧ�s�禡
	glutIdleFunc(onUpdate);

	// ������U�禡
	glutKeyboardFunc(onKeyboard);

	// �����U�禡
	glutCreateMenu(onMenu);
	glutAddMenuEntry("��v�� +X ����", ADD_X_OFFSET);
	glutAddMenuEntry("��v�� -X ����", SUB_X_OFFSET);
	glutAddMenuEntry("��v�� +Y ����", ADD_Y_OFFSET);
	glutAddMenuEntry("��v�� -Y ����", SUB_Y_OFFSET);
	glutAddMenuEntry("��v�� +Z ����", ADD_Z_OFFSET);
	glutAddMenuEntry("��v�� -Z ����", SUB_Z_OFFSET);
	glutAddMenuEntry("���m��v��", RESET);
	glutAddMenuEntry("����", EXIT);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return EXIT_SUCCESS;
}