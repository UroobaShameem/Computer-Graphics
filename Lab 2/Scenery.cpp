#include <GL/glut.h>
#include <cmath>

const int windowWidth = 800;
const int windowHeight = 600;

void drawMountain();

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw sky (light blue color)
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);

    // Draw sun (yellow color)
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float angle_rad = i * 3.14159f / 180.0f;
        float x = 100.0f + 50.0f * cos(angle_rad);
        float y = windowHeight - 100.0f + 50.0f * sin(angle_rad);
        glVertex2f(x, y);
    }
    glEnd();

    // Draw mountains
    glColor3f(0.3f, 0.2f, 0.1f); // Brown color for mountains
    drawMountain();

    // Draw river (blue color)
    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(0, 200);
    glVertex2f(windowWidth, 200);
    glVertex2f(windowWidth, 0);
    glVertex2f(0, 0);
    glEnd();

    glutSwapBuffers();
}

void drawMountain() {
    glBegin(GL_TRIANGLES);
    // First mountain
    glVertex2f(100, 200);
    glVertex2f(280, 200);
    glVertex2f(190, 400);

    // Second mountain
    glVertex2f(350, 200);
    glVertex2f(600, 200);
    glVertex2f(475, 550);

    // Third mountain
    glVertex2f(600, 200);
    glVertex2f(800, 200);
    glVertex2f(700, 480);
    glEnd();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Mountain Scenery");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
