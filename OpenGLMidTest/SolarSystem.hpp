#pragma once

#include <GL/glut.h>

#include "StarEnumeration.hpp"
#include "Operation.hpp"
#include "DataType.hpp"
#include "Planet.hpp"
#include "LightPlanet.hpp"

// 星星數量
#define STAR_COUNT 10

// 按鍵單次變化量
#define OFFSET 20

// 攝影機位置
#define CAMERA 700
#define CAMERA_Z (CAMERA)
#define CAMERA_Y (-CAMERA)

// 更新時間差 (單位 : 天)
#define TIME_PAST 1

// 自轉速度
#define SELF_ROTATE 3

// 公轉半徑
#define SUN_RADIUS 48.74
#define MERCURY_RADIUS 7.32
#define VENUS_RADIUS 18.15
#define EARTH_RADIUS 19.13
#define MOON_RADIUS 6.15
#define MARS_RADIUS 10.19
#define JUPITER_RADIUS 42.9
#define SATURN_RADIUS 36.16
#define URANUS_RADIUS 25.56
#define NEPTUNE_RADIUS 24.78

// 與太陽距離
#define MERCURY_DISTANCE 62.06
#define VENUS_DISTANCE 115.56
#define EARTH_DISTANCE 168.0
#define MOON_DISTANCE 26.01
#define MARS_DISTANCE 228.0
#define JUPITER_DISTANCE 333.4
#define SATURN_DISTANCE 428.1
#define URANUS_DISTANCE 848.0
#define NEPTUNE_DISTANCE 949.1

// 運動速度
#define MERCURY_SPEED 87.0
#define VENUS_SPEED 225.0
#define EARTH_SPEED 365.0
#define MOON_SPEED 30.0
#define MARS_SPEED 687.0
#define JUPITER_SPEED 1298.4
#define SATURN_SPEED 3225.6
#define URANUS_SPEED 3066.4
#define NEPTUNE_SPEED 6014.8

template <typename T, typename U>
void setValue3(T * target, U left, U middle, U right) {
	target[0] = left;
	target[1] = middle;
	target[2] = right;
}

class SolarSystem {
public:
	SolarSystem() {
		viewX = 0;
		viewY = CAMERA_Y;
		viewZ = CAMERA_Z;

		centerX = centerY = centerZ = 0;

		upX = upY = 0;
		upZ = 1;

		// 定義行星與顏色
		GLfloat RGBColor[3] = { 1, 0, 0 };
		solarSystemStar[SUN] = new LightPlanet(SUN_RADIUS, 0, 0, SELF_ROTATE, NULL, RGBColor);

		setValue3(RGBColor, 0.2F, 0.2F, 0.5F);
		solarSystemStar[MERCURY] = new Planet(MERCURY_RADIUS, MERCURY_DISTANCE, MERCURY_SPEED, SELF_ROTATE, solarSystemStar[SUN], RGBColor);

		setValue3(RGBColor, 1.0F, 0.3F, 0.0F);
		solarSystemStar[VENUS] = new Planet(VENUS_RADIUS, VENUS_DISTANCE, VENUS_SPEED, SELF_ROTATE, solarSystemStar[SUN], RGBColor);

		setValue3(RGBColor, 0, 1, 0);
		solarSystemStar[EARTH] = new Planet(EARTH_RADIUS, EARTH_DISTANCE, EARTH_SPEED, SELF_ROTATE, solarSystemStar[SUN], RGBColor);

		setValue3(RGBColor, 1, 1, 0);
		solarSystemStar[MOON] = new Planet(MOON_RADIUS, MOON_DISTANCE, MOON_SPEED, SELF_ROTATE, solarSystemStar[EARTH], RGBColor);

		setValue3(RGBColor, 1.0F, 0.5F, 0.5F);
		solarSystemStar[MARS] = new Planet(MARS_RADIUS, MARS_DISTANCE, MARS_SPEED, SELF_ROTATE, solarSystemStar[SUN], RGBColor);

		setValue3(RGBColor, 1.0F, 1.0F, 0.5F);
		solarSystemStar[JUPITER] = new Planet(JUPITER_RADIUS, JUPITER_DISTANCE, JUPITER_SPEED, SELF_ROTATE, solarSystemStar[SUN], RGBColor);

		setValue3(RGBColor, 0.5F, 1.0F, 0.5F);
		solarSystemStar[SATURN] = new Planet(SATURN_RADIUS, SATURN_DISTANCE, SATURN_SPEED, SELF_ROTATE, solarSystemStar[SUN], RGBColor);

		setValue3(RGBColor, 0.4F, 0.4F, 0.4F);
		solarSystemStar[URANUS] = new Planet(URANUS_RADIUS, URANUS_DISTANCE, URANUS_SPEED, SELF_ROTATE, solarSystemStar[SUN], RGBColor);

		setValue3(RGBColor, 0.5F, 0.5F, 1.0F);
		solarSystemStar[NEPTUNE] = new Planet(NEPTUNE_RADIUS, NEPTUNE_DISTANCE, NEPTUNE_SPEED, SELF_ROTATE, solarSystemStar[SUN], RGBColor);
	}

	~SolarSystem() {
		for (int i = 0; i < STAR_COUNT; ++i) {
			delete solarSystemStar[i];
		}
	}

	void onDisplay() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.7F, 0.7F, 0.7F, 0.1F);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// 投影矩陣
		gluPerspective(75, 1, 1, 40000000);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		// 攝影機矩陣
		gluLookAt(viewX, viewY, viewZ, centerX, centerY, centerZ, upX, upY, upZ);

		// 光源
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);

		// 遮擋隱藏
		glEnable(GL_DEPTH_TEST);

		// 畫星球
		for (int i = 0; i < STAR_COUNT; ++i) {
			solarSystemStar[i]->draw();
		}

		glutSwapBuffers();
	}

	// 更新位置並顯示
	void onUpdate() {
		for (int i = 0; i < STAR_COUNT; ++i) {
			solarSystemStar[i]->update(TIME_PAST);
		}
		onDisplay();
	}

	void processOperation(Operation operation) {
		switch (operation) {
		case SUB_X_OFFSET: {
			viewX -= OFFSET;
			break;
		}
		case ADD_X_OFFSET: {
			viewX += OFFSET;
			break;
		}

		case SUB_Y_OFFSET: {
			viewY -= OFFSET;
			break;
		}
		case ADD_Y_OFFSET: {
			viewY += OFFSET;
			break;
		}

		case SUB_Z_OFFSET: {
			viewZ -= OFFSET;
			break;
		}
		case ADD_Z_OFFSET: {
			viewZ += OFFSET;
			break;
		}

		case RESET: {
			viewX = 0;
			viewY = CAMERA_Y;
			viewZ = CAMERA_Z;
			centerX = centerY = centerZ = 0;
			upX = upY = 0;
			upZ = 1;
			break;
		}

		case EXIT: {
			exit(EXIT_SUCCESS);
			break;
		}
		default: {
			break;
		}
		}
	}

	// 選單處理
	void onMenu(int item) {
		Operation operation = (Operation)item;
		processOperation(operation);
	}

	// 按鍵處理
	void onKeyboard(byte key, int x, int y) {
		switch (key) {
		case 'q': {
			processOperation(ADD_X_OFFSET);
			break;
		}
		case 'a': {
			processOperation(SUB_X_OFFSET);
			break;
		}
		case 'w': {
			processOperation(ADD_Y_OFFSET);
			break;
		}
		case 's': {
			processOperation(SUB_Y_OFFSET);
			break;
		}
		case 'e': {
			processOperation(ADD_Z_OFFSET);
			break;
		}
		case 'd': {
			processOperation(SUB_Z_OFFSET);
			break;
		}
		case 'r': {
			processOperation(RESET);
			break;
		}

		case 27: {
			processOperation(EXIT);
			break;
		}
		default: {
			break;
		}
		}
	}
private:
	// 星球資料
	Star* solarSystemStar[STAR_COUNT];

	// 攝影機參數
	GLdouble viewX, viewY, viewZ;
	GLdouble centerX, centerY, centerZ;
	GLdouble upX, upY, upZ;
};