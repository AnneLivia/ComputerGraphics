#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void display();
void reshape(int, int);
void timer(int);

int main(int argc, char **argv) {
    srand(time(nullptr));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Screen");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    init();
    glutMainLoop();
}

int open_mouth = 0, appear_food = 1;

float x_pos = -10, food_color_r = 1.0, food_color_g = 0.0, food_color_b = 1.0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPointSize(10.0);

    // body of the object
    glTranslatef(7.8, 0, 0);
    glBegin(GL_POLYGON);
       glColor3f(1.0, 1.0, 0.0);
       glVertex2f(-2.0, 2.0);
       glVertex2f(-2.0, -2.0);
       glVertex2f(2.0, -2.0);
       glVertex2f(2.0, 2.0);
    glEnd();

    // eye of the object
    glBegin(GL_POLYGON);
       glColor3f(0.0, 0.0, 0.0);
       glVertex2f(1.2+-0.3f, 1.2+0.3f); // top left
       glVertex2f(1.2+0.3f, 1.2+0.3f); // top right
       glVertex2f(1.2+0.3f, 1.2+-0.3f); // bottom right
       glVertex2f(1.2+-0.3f, 1.2+-0.3f); // bottom left
    glEnd();

    // it's going to be the mouth (open and close)
    glBegin(GL_TRIANGLES);
       glColor3f(0.0, 0.0, 0.0);
       glVertex2f(open_mouth * -2.0, 2.0);
       glVertex2f(open_mouth * 0.0, 0.0);
       glVertex2f(open_mouth * -2.0, -2.0);
    glEnd();

    // mouth line
    glBegin(GL_LINES);
       glColor3f(0.0, 0.0, 0.0);
        glVertex2f(-2, 0);
        glVertex2f(-0.1, 0);
    glEnd();

    // Floor (first layer)
    glBegin(GL_POLYGON);
       glColor3f(0.0, 1.0, 0.0);
       glVertex2f(-20, -2);
       glVertex2f(-20, -4);
       glVertex2f(10, -4);
       glVertex2f(10, -2);
    glEnd();

    // Floor (second layer)
    glBegin(GL_POLYGON);
       glColor3f(0.0, 0.8, 0.0);
       glVertex2f(10, -4);
       glVertex2f(10, -10);
       glVertex2f(-50, -10);
       glVertex2f(-50, -4);
    glEnd();

    // object to eat
    glTranslatef(-10, 0, 0);
    glBegin(GL_POLYGON);
       glColor3f(food_color_r, food_color_g, food_color_b);
       glVertex2f(appear_food * x_pos, 1.0);
       glVertex2f(appear_food * x_pos, -1.0);
       glVertex2f(appear_food * (x_pos+2.0), -1.0);
       glVertex2f(appear_food * (x_pos+2.0), 1.0);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    glutPostRedisplay();
    // 60 frames
    glutTimerFunc(1000/60, timer, 0);

    // moving object forward
    if (x_pos < 8)
        x_pos+=0.15;
    else {
        x_pos = -10;

        // change color of food randomly
        int r = 1 + rand() % 100;
        int g = 1 + rand() % 100;
        int b = 1 + rand() % 100;

        food_color_r = r / 100.0;
        food_color_g = g / 100.0;
        food_color_b = b / 100.0;
    }

    // open mouth or not, it depends if the object is coming closer
    if (x_pos >= 3.0 && x_pos <= 8.4) {
        open_mouth = 1;
        if (x_pos >= 7.0) {
            appear_food = 0;
        }
    } else {
        open_mouth = 0;
        appear_food = 1;
    }
}
