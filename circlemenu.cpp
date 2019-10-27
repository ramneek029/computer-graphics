#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;
int x_radius, y_radius;
int x_end, y_end, c = 0;
float r=0;

int width, height;
static int window;
static int menu_id;
static int submenu_id;
static int submenu_id1;
static int submenu_id2;
static int value = 0;
int choice;
void plot(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void put_pixel(int x_r, int y_r, int x, int y)
{
    plot(x_r + x, y_r + y);
    plot(x_r + x, y_r - y);
    plot(x_r - x, y_r + y);
    plot(x_r - x, y_r - y);
    plot(x_r + y, y_r + x);
    plot(x_r - y, y_r + x);
    plot(x_r + y, y_r - x);
    plot(x_r - y, y_r - x);
}

void circle(int x_r, int y_r, int x_c, int y_c, float r, int patt_code)
{
    int x = 0;
    int y = r;

    float decision = 5 / 4 - r;
    put_pixel(x_r,y_r,x, y);

    while (y > x)
    {
        if (decision < 0)
        {
            x++;
            decision += 2 * x + 1;
        }
        else
        {
            y--;
            x++;
            decision += 2 * (x - y) + 1;
        }
        if (patt_code == 1)
        {
            put_pixel(x_r, y_r, x, y);
        }

        else if (patt_code == 2)
        {
            if (x % 3 == 0)
            {
                put_pixel(x_r, y_r, x, y);
            }
        }

        else if (patt_code == 3)
        {
            if (x % 16 <= 8)
            {
                put_pixel(x_r, y_r, x, y);
            }
        }
        else if (patt_code == 4)
        {
            if (x % 16 <= 8 || x % 16 == 12)
            {
                put_pixel(x_r, y_r, x, y);
            }
        }

        glEnd();
    }
}
void make_circle(float r, int choice)
{
    circle(x_radius - width / 2, height / 2 - y_radius, x_end - width / 2, height / 2 - y_end, r, choice);
}

void mouse(GLint button, GLint action, GLint xM, GLint yM)
{
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        if (c == 0)
        {
            x_radius = xM;
            y_radius = yM;
            cout << "center point: (" << x_radius - width / 2 << "," << height / 2 - y_radius << ")\n";
            plot(x_radius - width / 2, height / 2 - y_radius);
            c++;
        }
        else if (c == 1)
        {
            x_end = xM;
            y_end = yM;
            cout << "Ending point: (" << x_end - width / 2 << "," << height / 2 - y_end << ")\n";
            plot(x_end - width / 2, height / 2 - y_end);
            //cout << x_radius-width/2 << " " << height/2-y_radius << " " << x_end - width/2 << " " << height/2 -y_end << endl;
            r = sqrt(pow((x_end - x_radius), 2) + pow((y_end - y_radius), 2));
            cout << "radius = " << r << endl;
            make_circle(r, 1);
            c--;
        }
    }
    glFlush();
}
void menu(int num)
{
    if (num == 0)
    {
        glutDestroyWindow(window);
        exit(0);
    }
    else
    {
        value = num;
    }
    glutPostRedisplay();
}

void createMenu(void)
{
    submenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Solid", 11);
    glutAddMenuEntry("Dotted", 2);
    glutAddMenuEntry("Dashed", 3);
    glutAddMenuEntry("Dashed-Dotted", 4);
    submenu_id1 = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 5);
    glutAddMenuEntry("Green", 6);
    glutAddMenuEntry("Blue", 7);
    submenu_id2 = glutCreateMenu(menu);
    glutAddMenuEntry("1-size", 8);
    glutAddMenuEntry("3-size", 9);
    glutAddMenuEntry("5-size", 10);
    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 1);
    glutAddSubMenu("Properties", submenu_id);
    glutAddSubMenu("Color", submenu_id1);
    glutAddSubMenu("Thickness", submenu_id2);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(-width / 2, 0);
    glVertex2f(width / 2, 0);
    glVertex2f(0, -height / 2);
    glVertex2f(0, height / 2);
    glEnd();

    if (value == 1)
    {
        glClearColor(1.0, 1.0, 1.0, 0.0);
        return; //glutPostRedisplay();
    }
    else if (value == 11)
    {
        glPushMatrix();
        choice = 1;
        make_circle(r, choice);
        glPopMatrix();
    }

    else if (value == 2)
    {
        glPushMatrix();
        choice = 2;
        make_circle(r, choice);
        glPopMatrix();
    }
    else if (value == 3)
    {
        glPushMatrix();
        choice = 3;
        make_circle(r, choice);
        glPopMatrix();
    }
    else if (value == 4)
    {
        glPushMatrix();
        choice = 4;
        make_circle(r, choice);
        glPopMatrix();
    }
    else if (value == 5)
    {
        glPushMatrix();
        glColor3d(1.0, 0.0, 0.0);
        make_circle(r, choice);
        glPopMatrix();
    }
    else if (value == 6)
    {
        glPushMatrix();
        glColor3d(0.0, 1.0, 0.0);
        make_circle(r, 1);
        glPopMatrix();
    }
    else if (value == 7)
    {
        glPushMatrix();
        glColor3d(0.0, 0.0, 1.0);
        make_circle(r, choice);
        glPopMatrix();
    }
    else if (value == 8)
    {
        glPushMatrix();
        make_circle(r, choice);
        glPopMatrix();
    }
    else if (value == 9)
    {
        glPushMatrix();
        make_circle(r, choice);
        make_circle(r + 1, choice);
        make_circle(r - 1, choice);
        glPopMatrix();
    }
    else if (value == 10)
    {
        glPushMatrix();
        make_circle(r, choice);
        make_circle(r + 1, choice);
        make_circle(r - 1, choice);
        make_circle(r + 2, choice);
        make_circle(r - 2, choice);
        glPopMatrix();
    }
    glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("DropDown");
    width = glutGet(GLUT_WINDOW_WIDTH);
    height = glutGet(GLUT_WINDOW_HEIGHT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);

    glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1.0, 1.0);
    glutDisplayFunc(display);
    createMenu();
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
