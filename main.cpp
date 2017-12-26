#include <iostream>
#include <GL/glut.h>
#include <GLKit/GLKMatrix4.h>

struct RGBColor {
    float R, G, B;
};

void setPixel(GLint x, GLint y, RGBColor color) {
    glBegin(GL_POINTS);
    glColor3f(color.R, color.G, color.B);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

void bresenham(int x1, int y1, int x2, int y2, RGBColor xc, RGBColor yc)
{
    int m_new = 2 * abs(y2 - y1);
    int slope_error_new = m_new - abs(x2 - x1);
    float color_f = 0.0f;
    for (int x = x1, y = y1; x <= x2; x++)
    {
        RGBColor color = {xc.R * (1.0f - color_f) + yc.R * color_f, xc.G * (1.0f - color_f) + yc.G * color_f, xc.B * (1.0f - color_f) + yc.B * color_f};
        setPixel(x, y, color);

        // Add slope to increment angle formed
        slope_error_new += m_new;

        // Slope error reached limit, time to
        // increment y and update slope error.
        if (slope_error_new >= 0)
        {
            y++;
            slope_error_new  -= 2 * abs(x2 - x1);
        }
        color_f += 0.01f;
    }
}

void draw() {
    RGBColor x = {0.0f, 0.0f, 0.0f};
    RGBColor y = {1.0f, 1.0f, 1.0f};
    bresenham(0, 0, 155, 80, x, y);
    bresenham(20, 40, 150, 40, x, y);
    bresenham(100, 100, 400, 120, x, y);
    bresenham(30, 30, 155, 80, x, y);
}

void init() {
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham");
    glClearColor(0.0,0.0,0.0,0);
    GLKMatrix4 orthoMat = GLKMatrix4MakeOrtho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
    glLoadMatrixf(orthoMat.m);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}