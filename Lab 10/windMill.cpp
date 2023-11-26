#include <gl/glut.h>
#include <cstdlib>
#include <cmath>

#define PI 3.141592

// Define variables for airplane animation
float planeY = 230.0;  // Initial Y-coordinate of the airplane
bool planeCrashed = false;  // Flag to indicate if the airplane has crashed

// Variables for windmill animation
float windmillAngle = 0.0;  // Angle for animating windmill rotation

void display(void); // draw everything
void drawWind(void);  // draw single blade 
void drawwindmill(void); // complete this to complete windmill i.e. call drawWind() in it
void drawplane();  // work in this function
//  for crash landing of plane i.e. animate and collision with land 

void drawlandscape();// do nothing with it 
void Timer(int value); // update varible for animation here

void keyboard(unsigned char key, int x, int y);
void init(void);
void reshape(GLsizei w, GLsizei h);

void drawWind() // single Triangle
{
    glBegin(GL_TRIANGLES);
    glColor3f(0.8, 0.8, 0.8);
    glVertex2f(125.0, 90.0);
    glVertex2f(140.0, 120.0);
    glVertex2f(160.0, 120.0);
    glEnd();
}

void drawwindmill()   // complete windmill in this body
{
    /* Draw a windmill */

    // Draw the windmill blades with animation
    glPushMatrix();
    glTranslatef(130.0, 100.0, 0.0);  // Translate to the center of the windmill
    glRotatef(windmillAngle, 0.0, 0.0, 1.0);  // Rotate the windmill
    glTranslatef(-130.0, -100.0, 0.0);  // Translate back to the original position
    for (int i = 0; i < 4; ++i) {
        glPushMatrix();
        glRotatef(i * 90.0, 0.0, 0.0, 1.0);  // Rotate each blade by 90 degrees
        drawWind();
        glPopMatrix();
    }
    glPopMatrix();

    // Draw the windmill body
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.0);
    glVertex2f(145.0, 50.0);
    glVertex2f(135.0, 100.0);
    glVertex2f(115.0, 100.0);
    glVertex2f(105.0, 50.0);
    glEnd();
}

void Timer(int value)
{
    if (!planeCrashed) {
        // Update airplane's Y-coordinate for animation
        planeY -= 1.0;  // Adjust the descent speed as needed

        // Check if the airplane has hit the ground
        if (planeY <= 50.0) {
            planeY = 50.0;  // Limit the Y-coordinate to the ground level
            planeCrashed = true;
        }

        // Update windmill animation angle
        windmillAngle += 1.0;  // Adjust the rotation speed as needed
        if (windmillAngle >= 360.0) {
            windmillAngle -= 360.0;
        }
    }

    display();
    glutTimerFunc(30, Timer, 1);
}

void drawplane()
{
    /* Draw a plane */
    glBegin(GL_TRIANGLES);

    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(245.0, planeY + 10.0);
    glVertex2f(245.0, planeY + 20.0);
    glVertex2f(215.0, planeY + 10.0);

    glColor3f(0.2, 0.2, 0.2);
    glVertex2f(244.0, planeY + 8.0);
    glVertex2f(244.0, planeY + 15.0);
    glVertex2f(228.0, planeY + 15.0);

    glEnd();

    // If the airplane has crashed
    if (planeCrashed) {
        
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawlandscape();
    drawplane();
    drawwindmill();

    glutSwapBuffers();
}

void drawlandscape()
{
    /* Draw a box of grass */
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(250.0, 0.0);
    glColor3f(0.0, 0.9, 0.0);
    glVertex2f(250.0, 50.0);
    glColor3f(0.0, 0.8, 0.0);
    glVertex2f(0.0, 50.0);
    glColor3f(0.0, 0.7, 0.0);
    glVertex2f(0.0, 0.0);
    glEnd();

    /* An attempt at a few snow-covered mountains */

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 0.6);
    glVertex2f(250.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(200.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(150.0, 50.0);

    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(200.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(150.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(100.0, 50.0);

    glColor3f(0.0, 0.0, 0.7);
    glVertex2f(150.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(100.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(50.0, 50.0);

    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(100.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(50.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(0.0, 50.0);

    glEnd();

    /* Draw the body of a windmill */
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.0);
    glVertex2f(145.0, 50.0);
    glVertex2f(135.0, 100.0);
    glVertex2f(115.0, 100.0);
    glVertex2f(105.0, 50.0);
    glEnd();
}

void init()
{
    glClearColor(0.8f, 0.8f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 250.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 250.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Wind Mill");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(30, Timer, 1);
    glutMainLoop();
}
