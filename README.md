# Triangle Invasion

## Introduction

Triangle Invasion is an interactive 3D endless runner built using OpenGL. In this game, players control a cube which can move horizontally within a pre-defined plane. The objective of this game is to get the highest score possible by avoiding the pesky incoming Triangles!

This project explores core computer graphics concepts, such as rendering 3D objects, animations, and user interactions, while also delving into algorithms for efficient collision detection and game mechanics. 
 
## Problem Solving and Algorithms

Following are some expected problems and their potential solutions:

**1. Collision Detection:** Implementing an efficient method to detect when the cube collides with a pyramid.

  **Solution:** We will use Axis-Aligned Bounding Box (AABB) for collision detection between cube and pyramids.

**2. Dynamic Scoring:** Designing a scoring system that increments the player's score when pyramids safely despawn without collision.

  **Solution:** Each pyramid will be monitored for its 'z position'. If a pyramid moves out of the viewing area (z > 25.0f) without colliding with the cube, the score will be incremented.

**3. Object Management:** Dealing with pyramids once they have been dodged successffuly.

  **Solution:** Dynamic object spawning and removal will be handled efficiently using a vector. When a pyramid will move out of bounds it will be removed from memory to optimize performance.


## Design Consideration 

### System Design

The game will consist of the following core components:

**1. Game Objects:** The cube and pyramids will be the primary objects rendered in 3D space.

**2. Game Logic:** Collision detection, scoring, and pyramid spawning/despawning define the game logic.

**3. User Interaction:** Players will use arrow keys to control the cube's movement along the x-axis within the specified plane.

**4. Visual Elements:** A wireframe plane will define the playable area.

**5. Audio Elements:** A sound effect will be played whenever a collision occurs. Additionally, background music will also be added to enhance immersion.

### Architecture

This project follows a modular design for clarity and scalability, based on the Model-View-Controller pattern.

**1. Model:** The Model component defines the cube and pyramid objects, detailing their properties such as position and size. It also implements algorithms for collision detection and scoring.

**2. View:** The View component focuses on rendering the game world, objects, and the score overlay, utilizing OpenGL for real-time 3D rendering and providing visual feedback to the user.

**3. Control:** The Control component manages user input through keyboard controls and oversees the game loop, ensuring proper updates to objects, performing collision checks, and executing rendering calls.
 
