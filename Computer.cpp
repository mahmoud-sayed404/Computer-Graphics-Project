#include <GL/glut.h>
#include <iostream>
#include <string>
using namespace std;

float carX = 0.0f;
float carSpeed = 0.02f;

float carScale = 1.0f;
float defaultScale = 1.0f;

float minScale = 0.2f;
float maxScale = 2.0f;

float wheelAngle = 0.0f;

bool isPaused = false;

float houseSpeed = 0.01f;
float houseX1 = -0.8f;
float houseX2 = 0.0f;
float houseX3 = 0.8f;

void drawRect(float x, float y, float w, float h)
{
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }
}

void drawHouse(float x, float y)
{
    glColor3f(0.8f, 0.6f, 0.3f);
    drawRect(x, y, 0.2f, 0.2f);

    glColor3f(0.5f, 0.1f, 0.1f);
    drawTriangle(x, y + 0.2f, x + 0.1f, y + 0.3f, x + 0.2f, y + 0.2f);

    glColor3f(0.3f, 0.2f, 0.1f);
    drawRect(x + 0.08f, y, 0.04f, 0.1f);

    glColor3f(0.7f, 0.9f, 1.0f);
    drawRect(x + 0.03f, y + 0.1f, 0.05f, 0.05f);
    drawRect(x + 0.12f, y + 0.1f, 0.05f, 0.05f);
}

void drawCar()
{
    glPushMatrix();

    glTranslatef(carX, -0.3f, 0.0f);
    glScalef(carScale, carScale, 1.0f);

    glColor3f(0.9f, 0.1f, 0.1f);
    drawRect(-0.3f, 0.0f, 0.6f, 0.15f);

    glColor3f(0.7f, 0.0f, 0.0f);
    drawRect(-0.18f, 0.15f, 0.36f, 0.12f);

    glColor3f(0.85f, 0.85f, 0.9f);
    drawRect(-0.14f, 0.18f, 0.12f, 0.07f);
    drawRect(0.02f, 0.18f, 0.12f, 0.07f);

    glColor3f(0.1f, 0.1f, 0.1f);

    glPushMatrix();
    glTranslatef(-0.18f, -0.02f, 0.0f);
    glRotatef(wheelAngle, 0, 0, 1);
    drawRect(-0.05f, -0.05f, 0.1f, 0.1f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.18f, -0.02f, 0.0f);
    glRotatef(wheelAngle, 0, 0, 1);
    drawRect(-0.05f, -0.05f, 0.1f, 0.1f);
    glPopMatrix();

    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.1f, 0.6f, 0.1f);
    drawRect(-1.0f, -1.0f, 2.0f, 2.0f);

    glColor3f(0.2f, 0.2f, 0.2f);
    drawRect(-1.0f, -0.5f, 2.0f, 0.4f);

    glColor3f(1.0f, 1.0f, 1.0f);
    for (float i = -1.0f; i < 1.0f; i += 0.4f)
    {
        drawRect(i + 0.1f, -0.32f, 0.2f, 0.02f);
    }

    drawHouse(houseX1, -0.1f);
    drawHouse(houseX2, -0.1f);
    drawHouse(houseX3, -0.1f);

    glColor3f(1, 1, 1);
    drawText(-0.95f, 0.85f, "Controls:");
    drawText(-0.95f, 0.78f, "+ / - : Scale");
    drawText(-0.95f, 0.71f, "Arrows : Move");
    drawText(-0.95f, 0.64f, "S : Pause/Resume");
    drawText(-0.95f, 0.57f, "R : Reset");
    drawText(-0.95f, 0.50f, "ESC : Exit");


    drawText(-0.95f, 0.43f, "Car Position X = " + to_string(carX));
    drawText(-0.95f, 0.36f, "Car Scale = " + to_string(carScale));

    drawCar();

    glutSwapBuffers();
}

void update(int value)
{
    if (!isPaused)
    {
        wheelAngle -= 5.0f;
        if (wheelAngle <= -360)
            wheelAngle = 0;

        houseX1 -= houseSpeed; 
        houseX2 -= houseSpeed;
        houseX3 -= houseSpeed;

        if (houseX1 < -1.2f) houseX1 = 1.2f;
        if (houseX2 < -1.2f) houseX2 = 1.2f;
        if (houseX3 < -1.2f) houseX3 = 1.2f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == '+')
    {
        carScale += 0.1f;
        if (carScale > maxScale) carScale = maxScale;
    }
    else if (key == '-')
    {
        carScale -= 0.1f;
        if (carScale < minScale) carScale = minScale;
    }
    else if (key == 's' || key == 'S')
    {
        isPaused = !isPaused; // ?? Toggle
    }
    else if (key == 'r' || key == 'R')
    {
        carX = 0.0f;
        carScale = defaultScale;
        wheelAngle = 0.0f;

        houseX1 = -0.8f;
        houseX2 = 0.0f;
        houseX3 = 0.8f;

        isPaused = false;
    }
    else if (key == 27)
    {
        exit(0);
    }
}
void specialKeys(int key, int x, int y)
{
    if (isPaused) return;

    float halfWidth = 0.3f * carScale;

    if (key == GLUT_KEY_RIGHT)
    {
        carX += carSpeed;
        if (carX > 1.0f - halfWidth)
            carX = 1.0f - halfWidth;
    }
    else if (key == GLUT_KEY_LEFT)
    {
        carX -= carSpeed;
        if (carX < -1.0f + halfWidth)
            carX = -1.0f + halfWidth;
    }
}

void init()
{
    glClearColor(0.05f, 0.05f, 0.15f, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 500);
    glutCreateWindow("Car Game");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}

