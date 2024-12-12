#include "Cube.hpp"

Cube::Cube()
{
	// set set cordinate values for all vertices
    vertex[0][0] = -1; vertex[0][1] = -1; vertex[0][2] = -1;
    vertex[1][0] = -1; vertex[1][1] = 1;  vertex[1][2] = -1;
    vertex[2][0] = 1;  vertex[2][1] = 1;  vertex[2][2] = -1;
    vertex[3][0] = 1;  vertex[3][1] = -1; vertex[3][2] = -1;
    vertex[4][0] = -1; vertex[4][1] = -1; vertex[4][2] = 1;
    vertex[5][0] = -1; vertex[5][1] = 1;  vertex[5][2] = 1;
    vertex[6][0] = 1;  vertex[6][1] = 1;  vertex[6][2] = 1;
    vertex[7][0] = 1;  vertex[7][1] = -1; vertex[7][2] = 1;
    // other faces
    face[0][0] = 0; face[0][1] = 1; face[0][2] = 2; face[0][3] = 3;
    face[1][0] = 7; face[1][1] = 6; face[1][2] = 5; face[1][3] = 4;
    face[2][0] = 0; face[2][1] = 4; face[2][2] = 5; face[2][3] = 1;
    face[3][0] = 2; face[3][1] = 1; face[3][2] = 5; face[3][3] = 6;
    face[4][0] = 3; face[4][1] = 2; face[4][2] = 6; face[4][3] = 7;
    face[5][0] = 0; face[5][1] = 3; face[5][2] = 7; face[5][3] = 4;
    // setting color
    r = 1.0;
    g = 0.0;
    b = 0.0;
}

void Cube::drawFace(int i)
{
// draw face i
    glBegin(GL_LINE_LOOP);
    glVertex3fv(vertex[face[i][0]]);
    glVertex3fv(vertex[face[i][1]]);
    glVertex3fv(vertex[face[i][2]]);
    glVertex3fv(vertex[face[i][3]]);
    glEnd();
}

void Cube::draw()
{
    glPushMatrix();
    this->ctmMultiply();
    // setting color
    glColor3f(r, g, b);
    // drawing all faces
     for (int i = 0; i < 6; i++) {
        drawFace(i);
    }
    glPopMatrix();
}

