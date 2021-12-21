#pragma once

#include <GL/glut.h>

#include "Planet.hpp"

class LightPlanet : public Planet {
public:
	LightPlanet(GLfloat radius, GLfloat distance, GLfloat speed, GLfloat selfSpeed, Star* parent, GLfloat RGBColor[3]) : Planet(radius, distance, speed, selfSpeed, parent, RGBColor) {
	}

	// ��P����
	void drawLight() {
		GLfloat lightPosition[] = { 0, 0, 0, 1 };
		GLfloat lightAmbient[] = { 0, 0, 0.5F, 1 };
		GLfloat lightDiffuse[] = { 0, 0, 0.5F, 1 };
		GLfloat lightSpecular[] = { 0, 0, 1, 1 };

		glMaterialfv(GL_LIGHT0, GL_EMISSION, lightPosition); // ������m
		glMaterialfv(GL_LIGHT0, GL_AMBIENT, lightAmbient); // �Ϯg����u�j��
		glMaterialfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse); // ���Ϯg���u�j��
		glMaterialfv(GL_LIGHT0, GL_SPECULAR, lightSpecular); // �譱�Ϯg���u�j��
	}

	virtual void draw() {
		drawLight();
		drawPlanet();
		drawStar();
	}
};