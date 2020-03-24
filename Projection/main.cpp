#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/*
    A 3D projection or graphical projection maps points in
    three-dimensions onto a two-dimensional plane.
    As graphics are usually displayed on two-dimensional
    media such as paper and computer monitors,
    these projections are widely used, especially
    in engineering drawing, drafting, and computer graphics.
*/

void display();
void reshape(int, int);
void timer(int);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 400);
    glutCreateWindow("Screen");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}

float jump = 0;

/*
    there are the perspective projection and orthographic projection
*/

void display() {
    // reset buffer color
    glClear(GL_COLOR_BUFFER_BIT);
    // reset any transformations
    glLoadIdentity();
    glPointSize(20.0);
    // glTranslatef(jump, jump, 0);
    glTranslatef(0.0, 0.0, jump+-5.0);
    // Creating 3D object (QUADS makes the four following coordinate a single square)
    // if I use a GL_POLYGON, all vertex are going to be treated as one polygon
    glBegin(GL_QUADS);
        // set of vertex that form a cube
        //front
        glColor3f(1.0,0.0,0.0);
        glVertex3f(-1.0,1.0,1.0);
        glVertex3f(-1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,1.0);
        glVertex3f(1.0,1.0,1.0);
        //back
        glColor3f(0.0,1.0,0.0);
        glVertex3f(1.0,1.0,-1.0);
        glVertex3f(1.0,-1.0,-1.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glVertex3f(-1.0,1.0,-1.0);
        //right
        glColor3f(0.0,0.0,1.0);
        glVertex3f(1.0,1.0,1.0);
        glVertex3f(1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,-1.0);
        glVertex3f(1.0,1.0,-1.0);
        //left
        glColor3f(1.0,1.0,0.0);
        glVertex3f(-1.0,1.0,-1.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glVertex3f(-1.0,-1.0,1.0);
        glVertex3f(-1.0,1.0,1.0);
        //top
        glColor3f(0.0,1.0,1.0);
        glVertex3f(-1.0,1.0,-1.0);
        glVertex3f(-1.0,1.0,1.0);
        glVertex3f(1.0,1.0,1.0);
        glVertex3f(1.0,1.0,-1.0);
        //bottom
        glColor3f(1.0,1.0,1.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glVertex3f(-1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,-1.0);
    glEnd();

    // show it
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    // set a perspective projection (checkout info of projections)
    gluPerspective(60, 1, 2.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

bool up = true;
void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);

    if (jump < -2 && up)
        jump+=0.15;
    else
        up = false;

    if (jump > -25 && !up)
        jump-=0.15;
    else
        up = true;
}
