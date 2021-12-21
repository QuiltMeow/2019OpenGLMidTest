#pragma once

#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <math.h>

#include "ColumnMajorMatrix.hpp"

class Star {
public:
	Star(GLfloat radius, GLfloat distance, GLfloat speed, GLfloat selfSpeed, Star* parent) {
		this->radius = radius;
		this->distance = distance;
		this->selfSpeed = selfSpeed;
		this->angleSelf = this->angle = 0;

		for (int i = 0; i < 4; ++i) {
			this->RGBAColor[i] = 1;
		}
		this->parentStar = parent;

		if (speed > 0) {
			this->speed = 360 / speed;
		}
		else {
			this->speed = 0;
		}
	}

	void drawStar() {
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);

		static const int EDGE = 1440;

		glPushMatrix();
		// �ìP
		if (parentStar != NULL && parentStar->distance > 0) {
			float* rotateMat = ColumnMajorMatrix::createRotationMat4(parentStar->angle, 0, 0, 1);
			glMultMatrixf(rotateMat);

			float* translateMat = ColumnMajorMatrix::createTranslationMat4(parentStar->distance, 0, 0);
			glMultMatrixf(translateMat);

			delete[] rotateMat;
			delete[] translateMat;
		}

		// �y�D
		glBegin(GL_LINES);
		for (int i = 0; i < EDGE; ++i) {
			glVertex2f(distance * cos(2 * M_PI * i / EDGE), distance * sin(2 * M_PI * i / EDGE));
		}
		glEnd();

		// ����
		float* rotateMat = ColumnMajorMatrix::createRotationMat4(angle, 0, 0, 1);
		glMultMatrixf(rotateMat);

		float* translateMat = ColumnMajorMatrix::createTranslationMat4(distance, 0, 0);
		glMultMatrixf(translateMat);

		delete[] rotateMat;
		delete[] translateMat;

		// ����
		rotateMat = ColumnMajorMatrix::createRotationMat4(angleSelf, 0, 0, 1);
		glMultMatrixf(rotateMat);
		delete[] rotateMat;

		// �C��
		glColor3f(RGBAColor[0], RGBAColor[1], RGBAColor[2]);

		// �P�y����
		glutSolidSphere(radius, 40, 32);
		glPopMatrix();
	}

	virtual void draw() {
		drawStar();
	}

	virtual void update(int timeSpan) {
		// ���ਤ��
		angle += timeSpan * speed;

		// ���ਤ��
		angleSelf += timeSpan * selfSpeed;
	}
protected:
	GLfloat radius;
	GLfloat speed, selfSpeed;
	GLfloat distance;
	GLfloat RGBAColor[4];
	Star* parentStar;
	GLfloat angleSelf, angle;
};