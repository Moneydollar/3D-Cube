#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>

#include <GL/glew.h>
#define FREEGLUT_STATIC
#include <GL/freeglut.h>

using namespace std;

int g_iWindowWidth = 1000, g_iWindowHeight = 800, g_hWindowHandle = 0;
clock_t g_PreviousTicks, g_CurrentTicks;
float g_fRotationRate = 50.0; // degree per second
float g_fRotate1 = 0.0f;

// Camera variables
float g_fCameraAngleX = 0.0f; // Camera angle around the X axis
float g_fCameraAngleY = 0.0f; // Camera angle around the Y axis
float g_fCameraDistance = 6.0f; // Distance from the cube

// Mouse state variables
bool g_bMouseDragging = false;
int g_iLastMouseX = 0, g_iLastMouseY = 0;

void InitGLUT(int argc, char* argv[]);
void DisplayGL();
void IdleGL();
void KeyboardGL(unsigned char c, int x, int y);
void MouseGL(int button, int state, int x, int y);
void MotionGL(int x, int y);
void ReshapeGL(int w, int h);

int main(int argc, char* argv[])
{
    InitGLUT(argc, argv);

    g_PreviousTicks = clock();
    glutMainLoop();
}

void InitGLUT(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    int iScreenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int iScreenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition((iScreenWidth - g_iWindowWidth) / 2, (iScreenHeight - g_iWindowHeight) / 2);
    glutInitWindowSize(g_iWindowWidth, g_iWindowHeight);

    g_hWindowHandle = glutCreateWindow("OpenGL Template");

    glutDisplayFunc(DisplayGL);
    glutIdleFunc(IdleGL);
    glutKeyboardFunc(KeyboardGL);
    glutMouseFunc(MouseGL);
    glutMotionFunc(MotionGL);
    glutReshapeFunc(ReshapeGL);

    glEnable(GL_DEPTH_TEST);
}

void DisplayGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set camera position
    glTranslatef(0.0f, 0.0f, -g_fCameraDistance);
    glRotatef(g_fCameraAngleX, 1.0f, 0.0f, 0.0f); // Rotate around X axis
    glRotatef(g_fCameraAngleY, 0.0f, 1.0f, 0.0f); // Rotate around Y axis

    glRotatef(g_fRotate1, 0.0f, 1.0f, 0.0f);

    // Render the cube
    glBegin(GL_QUADS);
    // Top face
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    // Bottom face
    glColor3f(1.0f, 0.5f, 0.0f); // Orange
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    // Front face
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    // Back face
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    // Left face
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    // Right face
    glColor3f(1.0f, 0.0f, 1.0f); // Violet
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glEnd();

    glutSwapBuffers();
    glutPostRedisplay();
}

void IdleGL()
{
    g_CurrentTicks = clock();
    float deltaTicks = (float)(g_CurrentTicks - g_PreviousTicks);
    g_PreviousTicks = g_CurrentTicks;

    float fDetaTime = deltaTicks / (float)CLOCKS_PER_SEC;

    g_fRotate1 += (10 * g_fRotationRate * fDetaTime);
    g_fRotate1 = fmodf(g_fRotate1, 360.0f);
}

void KeyboardGL(unsigned char c, int x, int y)
{
    cout << "Key Pressed " << (int)c << endl;

    switch (c)
    {
        case 'w':
            g_fCameraDistance -= 0.1f;
            break;
        case 's':
            g_fCameraDistance += 0.1f;
            break;
        case 'a':
            g_fCameraAngleY -= 2.0f;
            break;
        case 'd':
            g_fCameraAngleY += 2.0f;
            break;
        case 'q':
            g_fCameraAngleX -= 2.0f;
            break;
        case 'e':
            g_fCameraAngleX += 2.0f;
            break;
        case 27: // Escape key
            glutLeaveMainLoop();
            break;
    }
}

void MouseGL(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            g_bMouseDragging = true;
            g_iLastMouseX = x;
            g_iLastMouseY = y;
        }
        else if (state == GLUT_UP)
        {
            g_bMouseDragging = false;
        }
    }
}

void MotionGL(int x, int y)
{
    if (g_bMouseDragging)
    {
        int dx = x - g_iLastMouseX;
        int dy = y - g_iLastMouseY;

        // Update camera angles based on mouse movement
        g_fCameraAngleY += dx * 0.1f;
        g_fCameraAngleX -= dy * 0.1f;

        // Update last mouse position
        g_iLastMouseX = x;
        g_iLastMouseY = y;

        glutPostRedisplay();
    }
}

void ReshapeGL(int w, int h)
{
    if (h == 0)
        h = 1;

    g_iWindowWidth = w;
    g_iWindowHeight = h;

    glViewport(0, 0, g_iWindowWidth, g_iWindowHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, g_iWindowWidth / (GLdouble)g_iWindowHeight, 0.1, 100.0);

    glutPostRedisplay();
}
