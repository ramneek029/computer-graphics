#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

#include <cmath>
int num;
int xa, xb, ya, yb;
int height = 500;
int width = 500;
void bresenham(void);
void disp(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-250, 0);
    glVertex2f(250, 0);
    glVertex2f(0, 250);
    glVertex2f(0, -250);
    glEnd();

    glFlush();

    //bresenham();
}
void input(void)
{
    printf("Enter the points\n(X1,Y1,X2,Y2):-\n");
    scanf("%d %d %d %d", &xa, &ya, &xb, &yb);
}
void bresenham(int xa,int ya,int xb,int yb)
{

    int dx = xb - xa;
    int dy = yb - ya;

    int x = xa, y = ya;

    glBegin(GL_POINTS);
    glVertex2i(x, y);

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
                    glVertex2i(x, y);
                    p = p + 2 * dx - 2 * dy;
                }

                else
                {
                    y = y;
                    x = x + 1;
                    glVertex2i(x, y);
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
                    glVertex2i(x, y);
                    p = p - 2 * dy;
                }

                else
                {
                    y = y - 1;
                    x = x - 1;
                    glVertex2i(x, y);
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

                    glVertex2i(x, y);
                    p = p - 2 * dx - 2 * dy;
                }

                else
                {
                    y = y;
                    x = x - 1;

                    glVertex2i(x, y);
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
                    glVertex2i(x, y);
                    p = p - 2 * dy;
                }

                else
                {
                    y = y - 1;
                    x = x + 1;
                    glVertex2i(x, y);
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
                    glVertex2i(x, y);
                    p = p + 2 * dx;
                }

                else
                {
                    y = y + 1;
                    x = x + 1;
                    glVertex2i(x, y);
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
                    glVertex2i(x, y);
                    p = p + 2 * dx + 2 * dy;
                }

                else
                {
                    y = y + 1;
                    x = x;
                    glVertex2i(x, y);
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
                    glVertex2i(x, y);
                    p = p - 2 * dx;
                }

                else
                {
                    y = y - 1;
                    x = x - 1;
                    glVertex2i(x, y);
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
                    glVertex2i(x, y);
                    p = p - 2 * dx - 2 * dy;
                }

                else
                {
                    y = y - 1;
                    x = x;
                    glVertex2i(x, y);
                    p = p - 2 * dx;
                }
            }
        }
    }

    glEnd();
    glFlush();
}

void mouse(GLint button, GLint action, GLint xM, GLint yM)
{  int x_start, y_start, x_end, y_end;
int c;
cout<<"in mouse"<<endl;
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        if(c==0)
        {
            x_start=xM;
            y_start=yM;
            cout<<"Starting point: ("<<x_start-width/2<<","<<height/2-y_start<<")\n";
            glBegin(GL_POINTS);
            glVertex2i(x_start-width/2,height/2-y_start);
            glEnd();
            c++;
        }
        else if(c==1)
        {
            x_end=xM;
            y_end=yM;
            cout<<"Ending point: ("<<x_end-width/2<<","<<height/2-y_end<<")\n";
            glBegin(GL_POINTS);
            glVertex2i(x_end-width/2,height/2-y_end);
            glEnd();
            bresenham(x_start, y_start,x_end,y_end);
            c--;
        }
    }
    glFlush();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2 ,width/2, -height/2, height/2, -1.0, 1.0);
}

int main(int argc, char **argv)
{
    //input();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Breshanman Line Algorithm ");
    init();
    glutDisplayFunc(disp);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
