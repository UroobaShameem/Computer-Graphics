#include <GL/glut.h>
#include <iostream>

class Point {
public:
    float x, y;
    void set(float x, float y) {
        this->x = x;
        this->y = y;
    }
};

class Canvas {
private:
    Point CP;

public:
    void moveRel(float dx, float dy) {
        CP.set(CP.x + dx, CP.y + dy);
    }

    void lineRel(float dx, float dy) {
        float x = CP.x + dx, y = CP.y + dy;
        glBegin(GL_LINES);
        glVertex2f(CP.x, CP.y);
        glVertex2f(x, y);
        glEnd();
        CP.set(x, y);
    }
};

Canvas canvas;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white

    // Example drawing using the Canvas class
    canvas.moveRel(10.0f, 10.0f);
    canvas.lineRel(50.0f, 50.0f);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Canvas Example");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -300, 300); // Set up a 2D coordinate system

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}