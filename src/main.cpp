/*
 * Description: Triangle Invasion
 * Author: Hamza Tariq
 */

#include <vector>
#include <cstdlib>
#include <GL/glut.h>
#include <string>
#include <sstream>
#include <windows.h>
#include <mmsystem.h>
#include "Cube.hpp"
#include "Pyramid.hpp"

// Game States
enum GameState { TITLE_SCREEN, GAMEPLAY, GAME_OVER };
GameState currentState = TITLE_SCREEN;

// Cube and Pyramid objects
Cube cube;
std::vector<Pyramid> pyramids;

// Global Variables
float cubeX = 0.0f;
const float minX = -4.0f;
const float maxX = 4.0f;
const float minZ = -25.0f;
const float maxZ = 25.0f;
const float minXPlane = -5.0f;
const float maxXPlane = 5.0f;
const float pyramidSpeed = 0.25f; // Speed of pyramid movement
const int spawnInterval = 440;   // Milliseconds between spawns
bool isSoundPlaying = false;
int erasedPyramidCount = 0;


// Initializing the OpenGL environment
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glEnable(GL_DEPTH_TEST);          // Enable depth testing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 100.0); // Perspective projection
    glMatrixMode(GL_MODELVIEW);

    // Initialize pyramid
    Pyramid initialPyramid;
    initialPyramid.setPosition(0.0f, 0.0f, -20.0f); // Start from z = -20.0f
    pyramids.push_back(initialPyramid);
}


// Play sound during gameplay
void playGameplaySound() {
    if (!isSoundPlaying) {
    	PlaySound((LPCSTR) "steel_samurai.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);
        isSoundPlaying = true;
    }
}


// Stop sound when the game is over
void stopGameplaySound() {
    PlaySound(NULL, 0, 0);
    isSoundPlaying = false;
}


// Draw the plane with a white wireframe border
void drawPlane() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(minXPlane, 0.0, -25.0); glVertex3f(maxXPlane, 0.0, -25.0); // Bottom border
    glVertex3f(maxXPlane, 0.0, -25.0); glVertex3f(maxXPlane, 0.0, 25.0);  // Right border
    glVertex3f(maxXPlane, 0.0, 25.0);  glVertex3f(minXPlane, 0.0, 25.0);  // Top border
    glVertex3f(minXPlane, 0.0, 25.0);  glVertex3f(minXPlane, 0.0, -25.0); // Left border
    glEnd();
}


// Update the pyramids' positions and manage despawning
void updatePyramids() {

    for (std::vector<Pyramid>::iterator it = pyramids.begin(); it != pyramids.end(); ++it) {
        // Move pyramid to the opposite end of the screen
        it->setPosition(it->getX(), it->getY(), it->getZ() + pyramidSpeed);
    }

    // Removing pyramids that are out of view
    for (std::vector<Pyramid>::iterator it = pyramids.begin(); it != pyramids.end(); ) {
        if (it->getZ() > 25.0f) {
            it = pyramids.erase(it);
            erasedPyramidCount++;
        } else {
            ++it;
        }
    }
}


// Spawn new pyramids at random X positions within the plane's bounds
void spawnPyramid() {
    Pyramid newPyramid;
    int randomX = (std::rand() % 9) - 4;
    newPyramid.setPosition(randomX, 0.0f, -25.0f); // Start new pyramid at z = -25.0f (bottom of the plane)
    pyramids.push_back(newPyramid);
}

// Rendering Text
void renderStrokeText(const std::string& text, float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, scale);
    glColor3f(1.0, 1.0, 1.0);

    for (size_t i = 0; i < text.length(); ++i) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }


    glPopMatrix();
}


// Rendering Counter
void renderCounter() {

	std::ostringstream oss;
	oss << "Score: " << erasedPyramidCount;
	std::string text = oss.str();

    glPushMatrix();
    glLoadIdentity();

    // Switching to orthographic projection for 2D text rendering
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    // Render text at the top-left corner
    glMatrixMode(GL_MODELVIEW);
    renderStrokeText(text, -0.95f, 0.9f, 0.0005f);

    // Restoring projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}


// Collision Detector
bool checkCollision(float cubeMinX, float cubeMaxX, float cubeMinZ, float pyramidMinX, float pyramidMaxX, float pyramidMinZ) {

    // Check if cube's x bounds overlap with pyramid's x bounds
    bool xOverlap = (cubeMinX >= pyramidMinX && cubeMinX <= pyramidMaxX) ||
                    (cubeMaxX >= pyramidMinX && cubeMaxX <= pyramidMaxX);

    // Check if the sum of cubeMinZ and pyramidMinZ equals -2.5
    bool zCondition = (cubeMinZ + pyramidMinZ == -2.5f);

    // Return true if both conditions are met
    return xOverlap && zCondition;
}

void detectCollisions() {
    float cubeMinX = cubeX - 1.0f;
    float cubeMaxX = cubeX + 1.0f;
    float cubeMinZ = -1.0f;

    for (std::vector<Pyramid>::iterator it = pyramids.begin(); it != pyramids.end(); ++it) {
        float pyramidMinX = it->getX() - 1.0f;
        float pyramidMaxX = it->getX() + 1.0f;
        float pyramidMinZ = it->getZ() - 1.0f;

        if (checkCollision(cubeMinX, cubeMaxX, cubeMinZ, pyramidMinX, pyramidMaxX, pyramidMinZ)) {
        	PlaySound((LPCSTR)"collision.wav", NULL, SND_FILENAME | SND_SYNC);
            // Print positions for debugging
//            std::cout << "Collision detected!" << std::endl;
//            std::cout << "Cube Position: X = " << cubeX
//                      << ", MinX = " << cubeMinX << ", MaxX = " << cubeMaxX
//                      << ", MinZ = " << cubeMinZ << std::endl;
//            std::cout << "Pyramid Position: X = " << it->getX()
//                      << ", MinX = " << pyramidMinX << ", MaxX = " << pyramidMaxX
//                      << ", MinZ = " << pyramidMinZ << std::endl;

        	// Resetting
            currentState = GAME_OVER;
            pyramids.clear();
            cubeX = 0.0f;
            break;
        }
    }

}



// Timer function for game loop
void timer(int value) {
    if (currentState == GAMEPLAY) {
        updatePyramids();
        detectCollisions();

        // Spawning pyramids at regular intervals
        if (value % spawnInterval == 0) {
            spawnPyramid();
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, value + 16); // around 60 FPS
}



// Displaying Title Screen
void displayTitleScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Switch to orthographic projection
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Rendering text
    std::string text1 = "Triangle Invasion!";
    std::string text2= "Press Enter to Start";
    renderStrokeText(text1, -0.52f, 0.2f, 0.001f);
    renderStrokeText(text2, -0.325f, 0.005f, 0.0005f);

    // Restoring projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}


// Displaying Game Over
void displayGameOver() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Switch to orthographic projection
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Render text
    std::string text1 = "Game Over!";
    std::string text2= "Press Enter to retry";
	std::ostringstream oss;
	oss << "Score: " << erasedPyramidCount;
	std::string text3 = oss.str();
    renderStrokeText(text1, -0.35f, 0.15f, 0.001f);
    renderStrokeText(text3, -0.11f, 0.05f, 0.0005f);
    renderStrokeText(text2, -0.315f, -0.05f, 0.0005f);

    // Restore projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}


// Display function
void display() {

    if (currentState == TITLE_SCREEN) {
        displayTitleScreen();
    } else if (currentState == GAMEPLAY) {
    	playGameplaySound();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        gluLookAt(
            0.0, 15.0, 10.0,  // Camera position
            0.0, 0.0, 0.0,   // Look at point
            0.0, 1.0, 0.0    // Up vector
        );

        // Draw plane and border
        drawPlane();

        // Drawing cube
        glPushMatrix();
        glTranslatef(cubeX, 0.0, 0.0);
        cube.draw();
        glPopMatrix();

        // Drawing all pyramids
        for (std::vector<Pyramid>::iterator it = pyramids.begin(); it != pyramids.end(); ++it) {
            glPushMatrix();
            glTranslatef(it->getX(), it->getY(), it->getZ());
            it->draw();
            glPopMatrix();
        }

        // Rendering the counter
        renderCounter();

        glutSwapBuffers();

    } else if (currentState == GAME_OVER) {
    	stopGameplaySound();
//    	PlaySound((LPCSTR)"collision.wav", NULL, SND_FILENAME | SND_ASYNC);
    	displayGameOver();

    }
}

// Handle window resizing
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Handling arrow key input
void specialKeys(int key, int x, int y) {
    if (currentState == GAMEPLAY) {
        if (key == GLUT_KEY_LEFT) {
            cubeX -= 0.5f;
            if (cubeX < minX) cubeX = minX;
        }
        if (key == GLUT_KEY_RIGHT) {
            cubeX += 0.5f;
            if (cubeX > maxX) cubeX = maxX;
        }
        glutPostRedisplay();
    }
}

// Handling Enter Key Input
void keyboard(unsigned char key, int x, int y) {
    if (currentState == TITLE_SCREEN && key == 13) { // Enter key
        currentState = GAMEPLAY;
        glutPostRedisplay();
    } else if (currentState == GAME_OVER && key == 13) {
    	erasedPyramidCount = 0;
    	currentState = GAMEPLAY;
    	glutPostRedisplay();
    }
}


// Main Function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Triangle Invasion");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, timer, 0); // Starting the timer
    glutMainLoop();

    return 0;
}
