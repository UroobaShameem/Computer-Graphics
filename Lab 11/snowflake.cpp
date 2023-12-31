#include <GL/glut.h>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const float SCALE_FACTOR = 5.0;

void drawFlakeMotif() {
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 5);
    glVertex2f(20, 5);
    glVertex2f(30, 25);
    glVertex2f(35, 18);
    glVertex2f(25, 5);
    glVertex2f(30, 5);
    glVertex2f(40, 15);
    glVertex2f(50, 13);
    glVertex2f(35, 5);
    glVertex2f(55, 5);
    glVertex2f(60, 0);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslatef(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0, 0.0);
    for (int count = 0; count < 6; count++) {
        drawFlakeMotif();
        glScalef(1.0, -1.0, 1.0);
        drawFlakeMotif();
        glScalef(1.0, -1.0, 1.0);
        glRotatef(60.0, 0.0, 0.0, 1.0);
    }
    glPopMatrix();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Snowflake");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
