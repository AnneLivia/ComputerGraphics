/*
     first thing include all the libraries needed
     glut provides function to make openGL easier.
     The OpenGL Utility Toolkit (GLUT) is a library
     of utilities for OpenGL programs, which primarily
     perform system-level I/O with the host operating
     system. Functions performed include window definition,
     window control, and monitoring of keyboard and mouse input.
*/

/*
    OpenGL is a graphic API that allow to create images through objects
    definitions (2D and 3D), using a set of primitives geometric shapes
    and functions for manipulation.
*/

#include <GL/gl.h> // -> already included in glut library (some versions of glut does not include it)
#include <GL/glu.h> // -> already include in glut library (some versions of glut does not include it)
#include <GL/glut.h>

void display();

void init() {
    // change background color
    glClearColor(1.0, 1.0, 0.0, 1.0);
}

int main(int argc, char **argv) {
    // all function in glut, GLU or GL library initialize with glut, GLU or GL
    /*
        glutInit is used to initialize the GLUT library.
        void glutInit(int *argcp, char **argv);
        since it receives a pointer in both parameter and the argc in main function
        is not a pointer, we need to pass its address using &.

        Those arguments are used so that GLUT can process command line
        arguments. It has a number of arguments that it always uses.
    */

    glutInit(&argc, argv);

    /*
        need to initialize the display mode too
        id glutInitDisplayMode(unsigned int mode);

        To specify more flags we can use the | (or) operator.
    */

    glutInitDisplayMode(GLUT_RGB);
    // initialize the windows position when it first display (pixels)
    glutInitWindowPosition(200, 100);
    // initialize the windows size when it first display (pixels)
    glutInitWindowSize(500, 500);

    // create the window, gets one argument which is the tittle
    glutCreateWindow("Window 1");

    glutDisplayFunc(display);
    init();
    // after create the window if there's no task it closes the window.
    // the function glutMainLoop will let the window appearing while this loop
    // is running, this loop can get all interaction with the program.
    // this function is similar to the OpenCV function waitKey;
    glutMainLoop();
    return 0;
}

void display() {
    // clear - reset - drawn and then display
    // before drawn on window, must clear it, it must have draws from the previous frame
    glClear(GL_COLOR_BUFFER_BIT);
    // reset the matrix (any transformation, translation, etc.)
    glLoadIdentity();
    // draw comes here.

    // then display on the screen
    glFlush();
}
