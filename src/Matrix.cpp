
#include "Matrix.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

Matrix::Matrix() {
	loadIdentity();
}

// mat <- identity matrix
void Matrix::loadIdentity() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
		}
	}
}

// multiplication  mat <- m * mat
void Matrix::matrixPreMultiply(Matrix* m) {
	// add code here
	    GLfloat temp[4][4];
    
    // Performing matrix multiplication
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                temp[i][j] += m->mat[i][k] * mat[k][j];
            }
        }
    }

    // Copying results
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat[i][j] = temp[i][j];
        }
    }
}

// transpose  mat <- mat'
void Matrix::transpose() {
	// add code here
	    GLfloat temp[4][4];

    // Getting transpose matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = mat[j][i];
        }
    }

    // Copying  results
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat[i][j] = temp[i][j];
        }
    }
}

// normalize MC
void Matrix::normalize() {
	// add code here

    // Normalizing rotation vectors
    GLfloat lengthX = sqrt(mat[0][0] * mat[0][0] + mat[1][0] * mat[1][0] + mat[2][0] * mat[2][0]);
    GLfloat lengthY = sqrt(mat[0][1] * mat[0][1] + mat[1][1] * mat[1][1] + mat[2][1] * mat[2][1]);
    GLfloat lengthZ = sqrt(mat[0][2] * mat[0][2] + mat[1][2] * mat[1][2] + mat[2][2] * mat[2][2]);

    for (int i = 0; i < 3; i++) {
        mat[i][0] /= lengthX;
        mat[i][1] /= lengthY;
        mat[i][2] /= lengthZ;
    }
}


// v  <- mat * v
void Matrix::multiplyVector(GLfloat* v) {
	// add code here
	    GLfloat result[4] = {0, 0, 0, 0};

    // Performing multiplication
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i] += mat[i][j] * v[j];
        }
    }

    // Copying results
    for (int i = 0; i < 4; i++) {
        v[i] = result[i];
    }
}

void Matrix::rotateMatrix(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
// add code here
    GLfloat rad = angle * 3.1415926 / 180.0; 
    GLfloat cosA = cos(rad);
    GLfloat sinA = sin(rad);
    GLfloat length = sqrt(rx * rx + ry * ry + rz * rz);

    // Normalizing rotation vector
    if (length != 0) {
        rx /= length;
        ry /= length;
        rz /= length;
    }

    // Defining rotation matrix
    GLfloat rotation[4][4];
    
    rotation[0][0] = cosA + (1 - cosA) * rx * rx;
    rotation[0][1] = (1 - cosA) * rx * ry - sinA * rz;
    rotation[0][2] = (1 - cosA) * rx * rz + sinA * ry;
    rotation[0][3] = 0;

    rotation[1][0] = (1 - cosA) * ry * rx + sinA * rz;
    rotation[1][1] = cosA + (1 - cosA) * ry * ry;
    rotation[1][2] = (1 - cosA) * ry * rz - sinA * rx;
    rotation[1][3] = 0;

    rotation[2][0] = (1 - cosA) * rz * rx - sinA * ry;
    rotation[2][1] = (1 - cosA) * rz * ry + sinA * rx;
    rotation[2][2] = cosA + (1 - cosA) * rz * rz;
    rotation[2][3] = 0;

    rotation[3][0] = 0;
    rotation[3][1] = 0;
    rotation[3][2] = 0;
    rotation[3][3] = 1;

    // Multiplying matrix by rotation matrix
    Matrix rotationMatrix;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            rotationMatrix.mat[i][j] = rotation[i][j];
        }
    }

    matrixPreMultiply(&rotationMatrix);
}



