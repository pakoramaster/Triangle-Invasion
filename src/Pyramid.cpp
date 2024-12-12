#include "Pyramid.hpp"

Pyramid::Pyramid() {
    // set set cordinate values for all vertices
    vertex[0][0] = -1; vertex[0][1] = -1; vertex[0][2] = 0;
    vertex[1][0] = 1;  vertex[1][1] = -1; vertex[1][2] = 0;
    vertex[2][0] = 1;  vertex[2][1] = 1;  vertex[2][2] = 0;
    vertex[3][0] = -1; vertex[3][1] = 1;  vertex[3][2] = 0;
    vertex[4][0] = 0;  vertex[4][1] = 0;  vertex[4][2] = 2;
    // other faces
    face[0][0] = 0; face[0][1] = 1; face[0][2] = 4; face[0][3] = -1;
    face[1][0] = 1; face[1][1] = 2; face[1][2] = 4; face[1][3] = -1;
    face[2][0] = 2; face[2][1] = 3; face[2][2] = 4; face[2][3] = -1;
    face[3][0] = 3; face[3][1] = 0; face[3][2] = 4; face[3][3] = -1;
    face[4][0] = 0; face[4][1] = 1; face[4][2] = 2; face[4][3] = 3;
    // setting color
    r = 1.0;
    g = 1.0;
    b = 0.0;

    x = 0.0;
    y = 0.0;
    z = 0.0;
}

void Pyramid::drawFace(int i) {
    if (i == 4) {
        // Drawing base
        glBegin(GL_LINE_LOOP);
    } else {
        // Drawing sides
        glBegin(GL_LINE_LOOP);
    }

    for (int j = 0; j < 3; j++) {
        if (face[i][j] != -1) {
            // Ignore invalid vertices
            glVertex3fv(vertex[face[i][j]]);
        }
    }
    if (i == 4) {
        glVertex3fv(vertex[face[i][3]]);
    }

    glEnd();
}

void Pyramid::draw() {
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    this->ctmMultiply();
    // setting color
    glColor3f(r, g, b);
    // drawing all faces
    for (int i = 0; i < 5; i++) {
        drawFace(i);
    }
    glPopMatrix();
}

void Pyramid::setPosition(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

// Erase the pyramid
void Pyramid::erase() {
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    this->ctmMultiply();
    // Set the color to match the background
    glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 5; i++) {
        drawFace(i);
    }
    glPopMatrix();
}

// Getter for the X-coordinate
float Pyramid::getX() const {
    return this->x;
}

// Getter for the Y-coordinate
float Pyramid::getY() const {
    return this->y;
}

// Getter for the Z-coordinate
float Pyramid::getZ() const {
    return this->z;
}
