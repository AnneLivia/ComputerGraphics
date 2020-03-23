#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/*
    Transformations are operations done on matrix, three of them are:
        rotation:  rotate a object a certain degree around a point
        translation: is when we slide a figure in any direction.
        scaling: scaling transformation alters size of an object.
*/

void display();
void reshape(int, int);
void timer(int);

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char **argv) {

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
    return 0;
}

float x_pos = 0.0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPointSize(10.0);
    glShadeModel(GL_SMOOTH);

    glBegin(GL_POLYGON);
       glColor3f(0.0, 1.0, 0.0);
       glVertex2f(-1.0, 1.0);
       glVertex2f(-1.0, -1.0);
       glVertex2f(1.0, -1.0);
       glVertex2f(1.0, 1.0);
    glEnd();

    // in order to do translation (change origin of the orthogonality and then the object)
    // translate before the draw (takes three parameters the point where we want to translate, the z is for 3d objects)
    // z is distance
    // translation change the place where a primitive is drawn
    // must be called outside begin and end
    glTranslatef(x_pos, 5.0, 0.0);

    glBegin(GL_POLYGON);
       glColor3f(1.0, 1.0, 0.0);
       glVertex2f(-1.0, 1.0);
       glVertex2f(-1.0, -1.0);
       glVertex2f(1.0, -1.0);
       glVertex2f(1.0, 1.0);
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

bool foward = true;

void timer(int) {
    glutPostRedisplay();
    // 60 frames per second
    glutTimerFunc(1000/60, timer, 0);

    // goes right
    if (x_pos < 9 && foward) {
        x_pos+=0.15; // change the speed of the object here, 0.30, etc.
    } else {
        foward = false;
    }

    // goes left
    if (!foward && x_pos > -9)
        x_pos-=0.15;
    else
        foward = true;
}
