#include <GL/glut.h>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const float SCALE_FACTOR = 13.0;

// Function to draw a single motif of the snowflake
void drawFlakeMotif() {
    glBegin(GL_LINE_STRIP);
    glVertex2f(3 * SCALE_FACTOR, 3 * SCALE_FACTOR);
    glVertex2f(0 * SCALE_FACTOR, 8 * SCALE_FACTOR);
    glVertex2f(-3 * SCALE_FACTOR, 0 * SCALE_FACTOR);
    glVertex2f(-2 * SCALE_FACTOR, -1 * SCALE_FACTOR);
    glVertex2f(0 * SCALE_FACTOR, 5 * SCALE_FACTOR);
    glVertex2f(2 * SCALE_FACTOR, 3 * SCALE_FACTOR);
    glVertex2f(3 * SCALE_FACTOR, 3 * SCALE_FACTOR);
    glEnd();
}

// Function to display the snowflake
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glColor3f(1.0, 1.0, 1.0); // Set the drawing color to white

    glPushMatrix(); // Save the current matrix
    glTranslatef(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0, 0.0); // Center the snowflake

    for (int count = 0; count < 5; count++) {
        drawFlakeMotif(); // Draw one motif of the snowflake
        glRotatef(72.2, 0.0, 0.0, 1.0); // Rotate for the next spoke
    }

    glPopMatrix(); // Restore the original matrix

    glFlush(); // Flush the drawing commands
}

// Function to initialize OpenGL settings
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set the clear color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT); // Set the orthographic projection
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set the display mode
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Set the window size
    glutInitWindowPosition(100, 100); // Set the window position
    glutCreateWindow("Star"); // Create a window with the title "Star"

    init(); // Initialize OpenGL settings

    glutDisplayFunc(display); // Set the display function
    glutMainLoop(); // Enter the GLUT main loop

    return 0;
}
