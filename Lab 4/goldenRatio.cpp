#include <GL/glut.h>

// Function to draw a rectangle with a specified color
void drawRectangle(float centerX, float centerY, float rectWidth, float rectHeight, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(centerX - rectWidth / 2, centerY - rectHeight / 2);
    glVertex2f(centerX + rectWidth / 2, centerY - rectHeight / 2);
    glVertex2f(centerX - rectWidth / 2, centerY + rectHeight / 2);
    glVertex2f(centerX + rectWidth / 2, centerY + rectHeight / 2);
    glEnd();
}

// Display callback function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Calculate the initial size of the outer rectangle based on the golden ratio
    float outerWidth = 1.0f;
    float outerHeight = 1.0f / 1.618f; // Golden ratio is approximately 1.618

    // Number of rectangles to draw
    int numRectangles = 10;

    // Draw rectangles within the outer rectangle
    for (int i = 0; i < numRectangles; ++i)
    {
        float r = i / static_cast<float>(numRectangles); // Varies from 0.0 to 1.0
        float g = 1.0f - r; // Varies from 1.0 to 0.0
        float b = 0.5f + r / 2; // Varies from 0.5 to 1.0

        // Calculate the position of the rectangle
        float centerX = 0.0f;
        float centerY = 0.0f;

        // Draw the rectangle
        drawRectangle(centerX, centerY, outerWidth, outerHeight, r, g, b);

        // Update the size of the outer rectangle based on the golden ratio for the next iteration
        float temp = outerWidth;
        outerWidth = outerHeight;
        outerHeight = temp / 1.618f;
    }

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Rectangles Within Rectangle (Golden Ratio)");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
