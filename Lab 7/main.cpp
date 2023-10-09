#include "canvas.h"
#include <GL/glut.h>
#include <math.h>

Canvas cvs(640, 480, "Test Canvas");
float Canvas::getWindowAspectRatio(void) {
    // Calculate and return the aspect ratio of the window
    float windowWidth = window.getr() - window.getl();
    float windowHeight = window.gett() - window.getb();
    return windowWidth / windowHeight;
}

float Canvas::getCP_X(void) {
    // Return the x-coordinate of the current position (CP)
    return CP.getX();
}

float Canvas::getCP_Y(void) {
    // Return the y-coordinate of the current position (CP)
    return CP.getY();
}

void Canvas::moveTo(float x, float y) {
    // Set the current position (CP) to the specified coordinates
    CP.set(x, y);
}

void Canvas::moveTo(Point2 p) {
    // Set the current position (CP) to the coordinates of the given Point2 object
    CP.set(p.getX(), p.getY());
}

void Canvas::lineTo(float x, float y) {
    // Draw a line from the current position (CP) to the specified coordinates
    glBegin(GL_LINES);
    glVertex2f(CP.getX(), CP.getY());
    glVertex2f(x, y);
    glEnd();
    CP.set(x, y); // Update the current position (CP)
}

void Canvas::lineTo(Point2 p) {
    // Draw a line from the current position (CP) to the coordinates of the given Point2 object
    glBegin(GL_LINES);
    glVertex2f(CP.getX(), CP.getY());
    glVertex2f(p.getX(), p.getY());
    glEnd();
    CP.set(p.getX(), p.getY()); // Update the current position (CP)
}


void display(void) {
    cvs.setBackgroundColor(1.0, 1.0, 1.0); // Background color is white
    cvs.clearScreen(); // Clear the screen

    cvs.setColor(1.0, 0.0, 0.0); // Drawing color is red
    cvs.setWindow(-10.0, 10.0, -10.0, 10.0);
    cvs.setViewport(10, 460, 10, 460);

    // Draw a filled pentagon
    cvs.moveTo(0.0, 0.0);

    // Calculate the coordinates of the five vertices of the pentagon
    float angle = 0.0;
    float centerX = 0.0;
    float centerY = 0.0;
    float radius = 5.0;
    float vertices[5][2];

    for (int i = 0; i < 5; ++i) {
        vertices[i][0] = centerX + radius * cos(angle);
        vertices[i][1] = centerY + radius * sin(angle);
        angle += 0.4 * M_PI; // 0.4 * PI radians (72 degrees) between vertices
    }

    // Draw the filled pentagon
    glBegin(GL_POLYGON);
    for (int i = 0; i < 5; ++i) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();

    glFlush();
}


int main(int argc, char **argv) {
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
