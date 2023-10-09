#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const float PI = 3.14159265358979323846;
const float BULLET_SPEED = 5.0;
const float SHIP_SPEED = 1.0; // Reduced ship speed

// Define the player's spaceship
struct Ship {
    float x, y; // Position
    float angle; // Rotation angle
    bool thrust; // Is the thrust active?
};

// Define a bullet
struct Bullet {
    float x, y; // Position
    float angle; // Bullet's direction
    bool active; // Is the bullet active?
};

// Define an asteroid
struct Asteroid {
    float x, y; // Position
    float angle; // Rotation angle
    int size; // Size of the asteroid
};

vector<Asteroid> asteroids;
vector<Bullet> bullets;
Ship playerShip;

int score = 0; // Initialize the score

void init() {
    srand(time(nullptr));
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    // Initialize the player's ship
    playerShip.x = WIDTH / 2;
    playerShip.y = HEIGHT / 2;
    playerShip.angle = 0;
    playerShip.thrust = false;

    // Create initial asteroids
    for (int i = 0; i < 5; i++) {
        Asteroid asteroid;
        asteroid.x = rand() % WIDTH;
        asteroid.y = rand() % HEIGHT;
        asteroid.angle = (rand() % 360) * (PI / 180.0);
        asteroid.size = 50;
        asteroids.push_back(asteroid);
    }
}

void drawShip() {
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(playerShip.x, playerShip.y, 0.0);
    glRotatef(playerShip.angle, 0.0, 0.0, 1.0);

    glBegin(GL_POLYGON);
    glVertex2f(0, 15);
    glVertex2f(10, -10);
    glVertex2f(0, 0);
    glVertex2f(-10, -10);
    glEnd();

    if (playerShip.thrust) {
        glBegin(GL_POLYGON);
        glVertex2f(-6, -10);
        glVertex2f(0, -20);
        glVertex2f(6, -10);
        glEnd();
    }

    glPopMatrix();
}

void drawAsteroids() {
    glColor3f(1.0, 1.0, 1.0);

    for (const auto& asteroid : asteroids) {
        glPushMatrix();
        glTranslatef(asteroid.x, asteroid.y, 0.0);
        glRotatef(asteroid.angle, 0.0, 0.0, 1.0);
        glBegin(GL_LINE_LOOP);

        for (int i = 0; i < 12; i++) {
            float angle = 2 * PI * i / 12;
            float x = asteroid.size * cos(angle);
            float y = asteroid.size * sin(angle);
            glVertex2f(x, y);
        }

        glEnd();
        glPopMatrix();
    }
}

void drawBullets() {
    glColor3f(1.0, 1.0, 1.0);

    for (auto& bullet : bullets) {
        if (bullet.active) {
            glPushMatrix();
            glTranslatef(bullet.x, bullet.y, 0.0);
            glRotatef(bullet.angle, 0.0, 0.0, 1.0);
            glBegin(GL_LINES);
            glVertex2f(0, 0);
            glVertex2f(0, 10);
            glEnd();
            glPopMatrix();
        }
    }
}

void drawScore() {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(10, HEIGHT - 20); // Set the position of the score text
    string scoreText = "Score: " + to_string(score);
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); // Display the score
    }
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawShip();
    drawAsteroids();
    drawBullets();
    drawScore(); // Display the score
    glutSwapBuffers();
}

void update(int value) {
    // Initialize a flag to track if a bullet hit an asteroid
    bool bulletHitAsteroid = false;

    // Update bullet positions and check for collisions
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        if (bulletIt->active) {
            // Move the bullet in the direction of its angle
            bulletIt->x += BULLET_SPEED * cos(bulletIt->angle * PI / 180);
            bulletIt->y += BULLET_SPEED * sin(bulletIt->angle * PI / 180);

            // Check if the bullet is out of the screen
            if (bulletIt->x < 0 || bulletIt->x > WIDTH || bulletIt->y < 0 || bulletIt->y > HEIGHT) {
                bulletIt->active = false;
            }
        }

        // Check for collision with asteroids
        for (auto it = asteroids.begin(); it != asteroids.end();) {
            Asteroid& asteroid = *it;
            float dx = bulletIt->x - asteroid.x;
            float dy = bulletIt->y - asteroid.y;
            float distance = sqrt(dx * dx + dy * dy);
            if (distance < asteroid.size) {
                bulletIt->active = false;
                it = asteroids.erase(it); // Remove the asteroid
                bulletHitAsteroid = true; // Set the flag to true
                score += 10; // Increase the score when a bullet hits an asteroid
            } else {
                ++it;
            }
        }

        ++bulletIt;
    }

    // Update player's ship position
    if (playerShip.thrust) {
        // Calculate the new position
        float newX = playerShip.x + SHIP_SPEED * cos(playerShip.angle * PI / 180);
        float newY = playerShip.y + SHIP_SPEED * sin(playerShip.angle * PI / 180);

        // Check if the new position is within the window boundaries
        if (newX >= 0 && newX <= WIDTH && newY >= 0 && newY <= HEIGHT) {
            playerShip.x = newX;
            playerShip.y = newY;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        playerShip.thrust = true;
        break;
    case 's':
        // Calculate the initial position of the bullet at the top of the spaceship
        Bullet bullet;
        bullet.x = playerShip.x + 5.0 * cos(playerShip.angle * PI / 180);
        bullet.y = playerShip.y + 5.0 * sin(playerShip.angle * PI / 180);
        bullet.angle = playerShip.angle;
        bullet.active = true;

        // Add the bullet to the vector
        bullets.push_back(bullet);

        break;
    case 'a':
        playerShip.angle += 5.0;
        break;
    case 'd':
        playerShip.angle -= 5.0;
        break;
    case 27:
        exit(0); // ESC key
        break;
    }
}

void keyboardUp(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        playerShip.thrust = false;
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Asteroids Game");

    init();

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(keyboard);
    glutSpecialUpFunc(keyboardUp);

    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
