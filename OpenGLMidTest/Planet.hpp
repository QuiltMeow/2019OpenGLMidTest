#pragma once

#include <GL/glut.h>

#include "Star.hpp"

class Planet : public Star {
public:
	Planet(GLfloat radius, GLfloat distance, GLfloat speed, GLfloat selfSpeed, Star* parent, GLfloat RGBColor[3]) : Star(radius, distance, speed, selfSpeed, parent) {
		this->RGBAColor[0] = RGBColor[0];
		this->RGBAColor[1] = RGBColor[1];
		this->RGBAColor[2] = RGBColor[2];
		this->RGBAColor[3] = 1;
	}

	// 行星光照
	void drawPlanet() {
		GLfloat ambientMat[] = { 0, 0, 0.5F, 1 };
		GLfloat diffuseMat[] = { 0, 0, 0.5F, 1 };
		GLfloat specularMat[] = { 0, 0, 1, 1 };
		GLfloat emissionMat[] = { RGBAColor[0], RGBAColor[1], RGBAColor[2], RGBAColor[3] };
		GLfloat shininessMat = 90;

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMat);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularMat);
		glMaterialfv(GL_FRONT, GL_EMISSION, emissionMat);
		glMaterialf(GL_FRONT, GL_SHININESS, shininessMat);
	}

	virtual void draw() {
		drawPlanet();
		drawStar();
	}
};