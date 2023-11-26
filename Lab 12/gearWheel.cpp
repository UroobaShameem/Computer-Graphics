#include <GL/glut.h>
#include <cmath>

float deg = 0.0;  // Global variable to store the rotation angle
int numTeeth = 12;  // Number of teeth in the gear

void tooth0() {
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.2, 0.2);
    glVertex2f(0.6, 0.2);
    glVertex2f(0.6, 0.8);
    glVertex2f(0.2, 0.8);
    glVertex2f(0.0, 1.0);
    glEnd();
}

void tooth1(double r, double angle) {
    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);  // Rotate each tooth by the specified angle
    double rad = 6.0 * 3.1416 / 180.0;
    double cos6 = r * cos(rad);
    double sin6 = r * sin(rad);

    glTranslatef(cos6, -sin6, 0.0);
    tooth0();
    glPopMatrix();
}

void gear(double r) {
    glPushMatrix();
    for (int i = 0; i < numTeeth; ++i) {
        double angle = i * 360.0 / numTeeth;
        tooth1(r, angle);
    }
    glPopMatrix();
}

void move(int value) {
    deg += 0.5;  // Adjust the rotation speed as needed
    glutPostRedisplay();
    glutTimerFunc(16, move, 0);  // Call move function again after 16ms (about 60 FPS)
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Call the gear function to draw the gear shape
    glColor3f(1.0, 1.0, 1.0);  // Set color to white
    glLoadIdentity();
    glRotatef(deg, 0.0, 0.0, 1.0);  // Rotate the gear
    gear(0.2);

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Gear Shape");

    glClearColor(0.0, 0.0, 0.0, 1.0);  // Set clear color to black

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutTimerFunc(0, move, 0);  // Start the timer function

    glutMainLoop();

    return 0;
}
