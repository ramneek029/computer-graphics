#include <math.h>
//#include <gl/glut.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <iostream>
using namespace std;
int x_radius, y_radius;
int x_end, y_end, c = 0, a = 0;
float r = 0;
int n;

int angle = 0;
float pi = 3.14;
int width, height;

struct Point
{
    GLint x;
    GLint y;
};

struct Color
{
    float r;
    float g;
    float b;
};
Color newColor = {1.0, 0.0, 0.0};
Color oldColor = {1.0, 1.0, 1.0};
Color backgrd = {0.0,0.0,0.0};
void plot(GLint x, GLint y)
{
    //glPointSize(3.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

Color getPixelColor(GLint x, GLint y)
{
    Color color;
    glReadPixels(x+width/2,height/2+ y, 1, 1, GL_RGB, GL_FLOAT, &color);
    
    return color;
}

void setPixelColor(GLint x, GLint y, Color color)
{
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void floodFill(GLint x, GLint y, Color oldColor, Color newColor)
{
    Color color;
    color = getPixelColor(x, y);
  
if (color.r == backgrd.r && (color.g == backgrd.g && color.b == backgrd.b) )
    {        
        setPixelColor(x, y, newColor);
        floodFill(x + 1, y, oldColor, newColor);
        floodFill(x, y + 1, oldColor, newColor);
        floodFill(x - 1, y, oldColor, newColor);
        floodFill(x, y - 1, oldColor, newColor);
        floodFill(x + 1, y+1, oldColor, newColor);
        floodFill(x-1, y + 1, oldColor, newColor);
        floodFill(x - 1, y-1, oldColor, newColor);
        floodFill(x+1, y - 1, oldColor, newColor);       
    }   
    return;    
}

void polygon(int x_r, int y_r, int x_c, int y_c, float r)
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= n; i++)
    {
        glVertex2f(x_r + r * cos((angle + i * 360 / n) * pi / 180), y_r + r * sin((angle + i * 360 / n) * pi / 180));
    }
    glEnd();
 
    
   // floodFill(x_r + 3, y_r + 3, oldColor, newColor);
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
            //plot(x_radius - width / 2, height / 2 - y_radius);
            c++;
        }
        else if (c == 1)
        {
            x_end = xM;
            y_end = yM;
            cout << "Ending point: (" << x_end - width / 2 << "," << height / 2 - y_end << ")\n";
            r = sqrt(pow((x_end - x_radius), 2) + pow((y_end - y_radius), 2));
            cout << "radius = " << r << endl;
            polygon(x_radius - width / 2, height / 2 - y_radius, x_end - width / 2, height / 2 - y_end, r);

            c++;
        }
        else if(c==2)
        {   x_radius = xM;
            y_radius = yM;
            floodFill(x_radius - width / 2, height / 2 - y_radius, oldColor, newColor);
            c=0;
        }
    }
    glFlush();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    cout << "Enter the number of sides : ";
    cin >> n;
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Polygon");
    width = glutGet(GLUT_WINDOW_WIDTH);
    height = glutGet(GLUT_WINDOW_HEIGHT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    
    glMatrixMode(GL_PROJECTION);
    glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1.0, 1.0);
    glutDisplayFunc(display);
    static int p = 0;
    
        glutMouseFunc(mouse);
        p++;
    
    glutMainLoop();
    return 0;
}
