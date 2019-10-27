#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;
int x_start, y_start;
int x_end, y_end, c = 0;
int width, height;
static int window;
static int menu_id;
static int submenu_id;
static int submenu_id1;
static int submenu_id2;
static int value = 0;
#define drawOneLine(x1, y1, x2, y2) \
    glBegin(GL_LINES);                 \
    glLineWidth(8.0);                 \
    glVertex2f((x1), (y1));            \
    glVertex2f((x2), (y2));            \
    glEnd();
void plotpoint(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
void bresenham(int xa, int ya, int xb, int yb)
{

    int dx = xb - xa;
    int dy = yb - ya;

    int x = xa, y = ya;

    glBegin(GL_POINTS);
    plotpoint(x - width / 2, height / 2 - y);

    int k;
    if (abs(dx) >= abs(dy))
    {
        int p0 = dx - 2 * dy;
        int p = p0;
        if (xb > xa && yb > ya) // quadrant 1
        {
            for (k = 0; k < abs(dx); k++)
            {
                if (p < 0)
                {
                    x = x + 1;
                    y = y + 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p + 2 * dx - 2 * dy;
                }

                else
                {
                    y = y;
                    x = x + 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dy;
                }
            }
        }

        else if (xb < xa && yb < ya) // quadrant 3
        {
            for (k = 0; k < abs(dx); k++)
            {
                if (p < 0)
                {
                    x = x - 1;
                    y = y;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dy;
                }

                else
                {
                    y = y - 1;
                    x = x - 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dy + 2 * dx;
                }
            }
        }
        else if (xa > xb && yb > ya) // quadrant 2
        {
            p = -dx - 2 * dy;
            for (k = 0; k < abs(dx); k++)
            {
                if (p < 0)
                {
                    x = x - 1;
                    y = y + 1;

                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dx - 2 * dy;
                }

                else
                {
                    y = y;
                    x = x - 1;

                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dy;
                }
            }
        }

        else if (xa < xb && yb < ya) // quadrant 4
        {
            for (k = 0; k < abs(dx); k++)
            {
                if (p < 0)
                {
                    x = x + 1;
                    y = y;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dy;
                }

                else
                {
                    y = y - 1;
                    x = x + 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dx - 2 * dy;
                }
            }
        }
    }

    else if (abs(dy) > abs(dx))
    {
        int p0 = dy - 2 * dx; ///     /////
        int p = p0;
        if (xb > xa && yb > ya) // first quadrant
        {
            for (k = 0; k < abs(dy); k++)
            {
                if (p < 0)
                {
                    x = x;
                    y = y + 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p + 2 * dx;
                }

                else
                {
                    y = y + 1;
                    x = x + 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p + 2 * dx - 2 * dy;
                }
            }
        }

        else if (xa > xb && yb > ya) // second quadrant
        {
            p = 2 * dx + dy;
            for (k = 0; k < abs(dy); k++)
            {
                if (p < 0)
                {
                    x = x - 1;
                    y = y + 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p + 2 * dx + 2 * dy;
                }

                else
                {
                    y = y + 1;
                    x = x;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p + 2 * dx;
                }
            }
        }
        else if (xa > xb && ya > yb) // third quadrant
        {
            for (k = 0; k < abs(dy); k++)
            {
                if (p < 0)
                {
                    x = x;
                    y = y - 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dx;
                }

                else
                {
                    y = y - 1;
                    x = x - 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dx + 2 * dy;
                }
            }
        }

        else if (xb > xa && yb < ya) // fourth quadrant
        {
            p = -2 * dx - dy;
            for (k = 0; k < abs(dy); k++)
            {
                if (p < 0)
                {
                    x = x + 1;
                    y = y - 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dx - 2 * dy;
                }

                else
                {
                    y = y - 1;
                    x = x;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dx;
                }
            }
        }
    }

    glEnd();
    glFlush();
}

void mouse(GLint button, GLint action, GLint xM, GLint yM)
{
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        if (c == 0)
        {
            x_start = xM;
            y_start = yM;
            cout << "Starting point: (" << x_start - width / 2 << "," << height / 2 - y_start << ")\n";
            plotpoint(x_start - width / 2, height / 2 - y_start);
            c++;
        }
        else if (c == 1)
        {
            x_end = xM;
            y_end = yM;
            cout << "Ending point: (" << x_end - width / 2 << "," << height / 2 - y_end << ")\n";
            plotpoint(x_end - width / 2, height / 2 - y_end);
            bresenham(x_start, y_start, x_end, y_end);
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
    glEnable(GL_LINE_STIPPLE);
    if (value == 1)
    {
        glClearColor(1.0, 1.0, 1.0, 0.0);
        return; //glutPostRedisplay();
    }
    else if (value == 2)
    {
        glPushMatrix();
        glLineStipple(1, 0x1010); /*  dash/dot/dash  */
        drawOneLine(x_start - width / 2, height / 2 - y_start, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        drawOneLine(x_end - width / 2, height / 2 - y_end, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        glPopMatrix();
    }
    else if (value == 3)
    {
        glPushMatrix();
        glLineStipple(1, 0xFF00);
        drawOneLine(x_start - width / 2, height / 2 - y_start, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        drawOneLine(x_end - width / 2, height / 2 - y_end, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        glPopMatrix();
    }
    else if (value == 4)
    {
        glPushMatrix();
        // plotline("dashdot");
        glLineStipple(1, 0xF820); /*  dash/dot/dash  */
        drawOneLine(x_start - width / 2, height / 2 - y_start, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        drawOneLine(x_end - width / 2, height / 2 - y_end, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        glPopMatrix();
    }
    else if (value == 5)
    {
        glPushMatrix();
        glColor3d(1.0, 0.0, 0.0);
        drawOneLine(x_start - width / 2, height / 2 - y_start, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        drawOneLine(x_end - width / 2, height / 2 - y_end, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        glPopMatrix();
    }
    else if (value == 6)
    {
        glPushMatrix();
        glColor3d(0.0, 1.0, 0.0);
        drawOneLine(x_start - width / 2, height / 2 - y_start, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        drawOneLine(x_end - width / 2, height / 2 - y_end, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        glPopMatrix();
    }
    else if (value == 7)
    {
        glPushMatrix();
        glColor3d(0.0, 0.0, 1.0);
        drawOneLine(x_start - width / 2, height / 2 - y_start, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        drawOneLine(x_end - width / 2, height / 2 - y_end, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        glPopMatrix();
    }
    else if (value == 8)
    {
        glPushMatrix();
        glLineWidth(1.0);
        drawOneLine(x_start - width / 2, height / 2 - y_start, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        drawOneLine(x_end - width / 2, height / 2 - y_end, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        glPopMatrix();
    }
    else if (value == 9)
    {
        glPushMatrix();
        
        drawOneLine(x_start - width / 2, height / 2 - y_start, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        drawOneLine(x_start - width / 2, height / 2 - y_start + 1, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2) + 1);
        drawOneLine(x_start - width / 2, height / 2 - y_start - 1, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2) - 1);
        drawOneLine(x_end - width / 2, height / 2 - y_end, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        drawOneLine(x_end - width / 2, height / 2 - y_end +1, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2) +1);
        drawOneLine(x_end - width / 2, height / 2 - y_end - 1, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2) - 1);
        glPopMatrix();
    }
    else if (value == 10)
    {
        glPushMatrix();
        
        drawOneLine(x_start - width / 2, height / 2 - y_start, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));

        drawOneLine(x_start - width / 2, height / 2 - y_start + 1, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2) +1);
        drawOneLine(x_start - width / 2, height / 2 - y_start - 1, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2) - 1);
        drawOneLine(x_start - width / 2, height / 2 - y_start + 2, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2) +2);
        drawOneLine(x_start - width / 2, height / 2 - y_start - 2, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2) - 2);

        drawOneLine(x_end - width / 2, height / 2 - y_end, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));

        drawOneLine(x_end - width / 2 + 1, height / 2 - y_end +1, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2) + 1);
        drawOneLine(x_end - width / 2, height / 2 - y_end -1, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2) - 1);
        drawOneLine(x_end - width / 2+2, height / 2 - y_end +2, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2) +2);
        drawOneLine(x_end - width / 2, height / 2 - y_end - 2, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2) - 2);
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
    createMenu();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
