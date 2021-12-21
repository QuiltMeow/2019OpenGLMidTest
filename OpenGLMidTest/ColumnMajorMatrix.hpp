#pragma once

#define _USE_MATH_DEFINES

#include <sstream>
#include <math.h>
#include <algorithm>

class ColumnMajorMatrix {
public:
	// Column Major
	// 00 10 20 30
	// 01 11 21 31
	// 02 12 22 32
	// 03 13 23 33

	// ¯Á¤Þ
	// 00 04 08 12
	// 01 05 09 13
	// 02 06 10 14
	// 03 07 11 15
	static int getColumnMajorMat4Index(int row, int column) {
		return 4 * row + column;
	}

	static int translateRowMajorMat4Index(int row, int column) {
		return row + column * 4;
	}

	static std::string showMat4(float* input) {
		std::stringstream ss;
		for (int row = 0; row < 4; ++row) {
			for (int col = 0; col < 4; ++col) {
				ss << input[getColumnMajorMat4Index(col, row)] << " ";
			}
			ss << std::endl;
		}
		return ss.str();
	}

	static std::string show1DMat4(float* input) {
		std::stringstream ss;
		for (int i = 0; i < 16; ++i) {
			ss << input[i] << " ";
		}
		ss << std::endl;
		return ss.str();
	}

	static double degreeToRadian(double degree) {
		return M_PI / (double)180 * degree;
	}

	static float* zeroMat4(float* input) {
		for (int i = 0; i < 16; ++i) {
			input[i] = 0;
		}
		return input;
	}

	static float* createZeroMat4() {
		float* ret = new float[16];
		zeroMat4(ret);

		ret[15] = 1;
		return ret;
	}

	static float* createIdentityMat4() {
		float* ret = new float[16];
		zeroMat4(ret);

		for (int i = 0; i < 4; ++i) {
			ret[getColumnMajorMat4Index(i, i)] = 1;
		}
		return ret;
	}

	static float* multiplyMat4(float* left, float* right) {
		float* ret = new float[16];
		zeroMat4(ret);

		for (int row = 0; row < 4; ++row) {
			for (int column = 0; column < 4; ++column) {
				for (int inner = 0; inner < 4; ++inner) {
					ret[getColumnMajorMat4Index(column, row)] += (left[getColumnMajorMat4Index(inner, row)] * right[getColumnMajorMat4Index(column, inner)]);
				}
			}
		}
		return ret;
	}

	static float* createTranslationMat4(float offsetX, float offsetY, float offsetZ) {
		float* ret = createIdentityMat4();
		ret[getColumnMajorMat4Index(3, 0)] = offsetX;
		ret[getColumnMajorMat4Index(3, 1)] = offsetY;
		ret[getColumnMajorMat4Index(3, 2)] = offsetZ;
		return ret;
	}

	static float* createRotationMat4(double degreeX, double degreeY, double degreeZ) {
		float* ret = createIdentityMat4();
		double radianX = degreeToRadian(degreeX);
		double radianY = degreeToRadian(degreeY);
		double radianZ = degreeToRadian(degreeZ);

		float sinX = sin(radianX);
		float cosX = cos(radianX);
		float sinY = sin(radianY);
		float cosY = cos(radianY);
		float sinZ = sin(radianZ);
		float cosZ = cos(radianZ);

		// X
		ret[getColumnMajorMat4Index(1, 1)] = cosX;
		ret[getColumnMajorMat4Index(1, 2)] = -sinX;
		ret[getColumnMajorMat4Index(2, 1)] = sinX;
		ret[getColumnMajorMat4Index(2, 2)] = cosX;

		// Y
		ret[getColumnMajorMat4Index(0, 0)] = cosY;
		ret[getColumnMajorMat4Index(0, 2)] = sinY;
		ret[getColumnMajorMat4Index(2, 0)] = -sinY;
		ret[getColumnMajorMat4Index(2, 2)] = cosY;

		// Z
		ret[getColumnMajorMat4Index(0, 1)] = cosZ;
		ret[getColumnMajorMat4Index(0, 1)] = sinZ;
		ret[getColumnMajorMat4Index(1, 0)] = -sinZ;
		ret[getColumnMajorMat4Index(1, 1)] = cosZ;
		return ret;
	}

	static float* createScalingMat4(float rateX, float rateY, float rateZ) {
		float* ret = createZeroMat4();
		ret[getColumnMajorMat4Index(0, 0)] = rateX;
		ret[getColumnMajorMat4Index(1, 1)] = rateY;
		ret[getColumnMajorMat4Index(2, 2)] = rateZ;
		return ret;
	}

	static float* normalizeAxis(double x, double y, double z) {
		float minValue = std::min(std::min(x, y), z);
		float maxValue = std::max(std::max(x, y), z);
		return new float[3]{ ((float)x - minValue) / (maxValue - minValue), ((float)y - minValue) / (maxValue - minValue), ((float)z - minValue) / (maxValue - minValue) };
	}

	static float* createRotationMat4(double angle, double x, double y, double z) {
		double radianAngle = angle * (M_PI / 180.0f);

		float cosAngle = cos(radianAngle);
		float sinAngle = sin(radianAngle);
		float complement = 1 - cosAngle;

		float* normalize = normalizeAxis(x, y, z);
		float normalizeX = normalize[0];
		float normalizeY = normalize[1];
		float normalizeZ = normalize[2];
		delete[] normalize;

		return new float[16]{
			cosAngle + normalizeX * normalizeX * complement,
			normalizeY * normalizeX * complement + normalizeZ * sinAngle,
			normalizeZ * normalizeX * complement - normalizeY * sinAngle, 0,

			normalizeX * normalizeY * complement - normalizeZ * sinAngle,
			cosAngle + normalizeY * normalizeY * complement,
			normalizeZ * normalizeY * complement + normalizeX * sinAngle, 0,

			normalizeX * normalizeZ * complement + normalizeY * sinAngle,
			normalizeY * normalizeZ * complement - normalizeX * sinAngle,
			normalizeZ * normalizeZ * complement + cosAngle, 0,

			0, 0, 0, 1
		};
	}
};