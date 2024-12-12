#ifndef CPYRAMID_H
#define CPYRAMID_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"

class Pyramid : public Shape {
protected:
    GLfloat vertex[5][3];  /* 2D array to store pyramid vertices */
    GLint face[5][4];      /* 2D array to store faces */
    GLfloat r, g, b;       /* color pyramid */
    GLfloat x, y, z;



public:
    Pyramid();
    void draw();
    void drawFace(int);
    void setPosition(float x, float y, float z);
    float getX() const;
    float getY() const;
    float getZ() const;
    void erase();
};

#endif
