#include "Shape.hpp"
#include <stdio.h>

using namespace std;

Shape::Shape() {
	reset();
}

Shape::~Shape() { };

Matrix Shape::getMC() {
	return  mc;
};


void Shape::setParentMC(Matrix *pm)
{
   pmc = pm;
}


void Shape::reset(){
	mc.loadIdentity();
	pmc = NULL;
	s = 1;
}

void Shape::translate(GLfloat tx, GLfloat ty, GLfloat tz) {
	mc.mat[0][3] += tx;
	mc.mat[1][3] += ty;
	mc.mat[2][3] += tz;
	mc.mat[3][3] = 1;
}

void Shape::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	Matrix m;
	m.rotateMatrix(rx, ry, rz, angle);
	mc.matrixPreMultiply(&m);
}


void Shape::rotate(GLfloat x0, GLfloat  y0, GLfloat  z0, GLfloat  rx, GLfloat  ry, GLfloat rz,  GLfloat  angle) {
	// your implementation

	// Translating object
    translate(-x0, -y0, -z0);
    
    // Creating rotation matrix
    Matrix rotationMatrix;
    rotationMatrix.rotateMatrix(rx, ry, rz, angle);
    mc.matrixPreMultiply(&rotationMatrix);
    
    // Translating object back
    translate(x0, y0, z0);
}


void Shape::rotateOrigin(GLfloat x0, GLfloat  y0, GLfloat  z0, GLfloat  rx, GLfloat  ry, GLfloat rz,  GLfloat  angle) {
	Matrix m;
	m.rotateMatrix(rx, ry, rz, angle);
	GLfloat v[4];
	v[0] = mc.mat[0][3] - x0;
	v[1] = mc.mat[1][3] - y0;
	v[2] = mc.mat[2][3] - z0;
	v[3] = mc.mat[3][3];
	m.multiplyVector(v);
	mc.mat[0][3] = v[0] + x0;
	mc.mat[1][3] = v[1] + y0;
	mc.mat[2][3] = v[2] + z0;
	mc.mat[3][3] = v[3];
}


void Shape::setScale(GLfloat x) {
	s = x;
}

void Shape::scaleChange(GLfloat x) {
	// s += x;
	// Changed Default scaleChange
	Matrix scalingMatrix;
    scalingMatrix.loadIdentity();

    // Scaling x-axis
    scalingMatrix.mat[0][0] = 1 + x;
    scalingMatrix.mat[1][0] = 0;
    scalingMatrix.mat[2][0] = 0;
	// Scaling y-axis
    scalingMatrix.mat[0][1] = 0;
    scalingMatrix.mat[1][1] = 1 + x;
    scalingMatrix.mat[2][1] = 0;
	// Scaling z-axis
    scalingMatrix.mat[0][2] = 0;
    scalingMatrix.mat[1][2] = 0;
    scalingMatrix.mat[2][2] = 1 + x;

    mc.matrixPreMultiply(&scalingMatrix);
}

void Shape::setId(GLint i) {
	id = i;
}

GLint Shape::getId() {
	return id;
}

void Shape::ctmMultiply() {
	GLfloat M[16];
	M[0] = mc.mat[0][0];
	M[1] = mc.mat[1][0];
	M[2] = mc.mat[2][0];
	M[3] = 0;
	M[4] = mc.mat[0][1];
	M[5] = mc.mat[1][1];
	M[6] = mc.mat[2][1];
	M[7] = 0;
	M[8] = mc.mat[0][2];
	M[9] = mc.mat[1][2];
	M[10] = mc.mat[2][2];
	M[11] = 0;
	M[12] = mc.mat[0][3];
	M[13] = mc.mat[1][3];
	M[14] = mc.mat[2][3];
	M[15] = 1;
	glMultMatrixf(M);
}

