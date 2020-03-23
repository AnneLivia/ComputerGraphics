/*
     First thing include all the libraries needed
     glut provides function to make openGL easier.
     The OpenGL Utility Toolkit (GLUT) is a library
     of utilities for OpenGL programs, which primarily
     perform system-level I/O with the host operating
     system. Functions performed include window definition,
     window control, and monitoring of keyboard and mouse input.


     The GL Library in OpenGL is the core library,
     GLU is a utility library, glut is a utility library,
     GL is the core, GLU is part of the package for GL,
     glut is OpenGL"s cross-platform tool Library,
     GL contains the most basic 3D functions,
     and GLU seems to support GL, if the arithmetic
     is good, The same effect can be done without
     the GLU of the case. Glut is the basic window
     interface, is independent of GL and GLU,
     if you do not like to use glut can use MFC and Win32 window,
     etc., but glut is cross-platform,
     which ensures that our program is a cross-platform,
     If you use MFC or WIN32 only on Windows operating systems.
     One of the big reasons for choosing OpenGL is that it's
     cross-platform, so we can use the glut library as much
     as possible.

    OpenGL is a graphic API that allow to create images through objects
    definitions (2D and 3D), using a set of primitives geometric shapes
    and functions for manipulation.

    OpenGL is a graphics API. GLUT is a library that makes using OpenGL a little easier.
*/

#include <GL/gl.h> // -> already included in glut library (some versions of glut does not include it)
#include <GL/glu.h> // -> already include in glut library (some versions of glut does not include it)
#include <GL/glut.h>

void display();
void reshape(int,int);
void timer(int);

void init() {
    // change background color
    // Specify the red, green, blue, and alpha values used when the color buffers are cleared.
    // The initial values are all 0. (0.0 to 1.0)
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // change the color of the objects
    // one state variable is a color
    // in this way all primitives are red
    // to solve this, place this function bellow in the place we draw the primitive
    // glColor3f(0.0, 0.0, 1.0);
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
    // double buffer to avoid error of rendering
    // in double there are two frame buffers
    // front buffer -> show the draws on the screen right now
    // back buffer -> used to drawn and it's not display on the screen
    // then, when finish the draw, back become first buffer and first becomes back
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    // initialize the windows position when it first display (pixels)
    glutInitWindowPosition(200, 100);

    // initialize the windows size when it first display (pixels)
    glutInitWindowSize(500, 500);

    // create the window, gets one argument which is the tittle
    glutCreateWindow("Graphic Window");

    /*
        To display the window we must use a callback function.
        A callback function is a function that is passed as an
        argument to another function, to be "called back" at a
        later time. A function that accepts other functions
        as arguments is called a higher-order function,
        which contains the logic for when the callback
        function gets executed.

        It's in this function that we are going to place what we're
        going to display on the created window.



        glutDisplayFunc is called whenever your window must be redrawn

        When does a window need to be redrawn?

        When its size changes
        when it becomes visible
        when some parts of it become visible
        when it is moved
        etc

        But what if your display function paints a triangle
        at position x;y where x;y; are determined by
        the mouse position? In this case you must ask
        the system to redraw the window whenever the mouse
        is moved right? That's why you'll call glutPostRedisplay
        from MouseFunc(). Actually when you call glutPostRedisplay,
        the redraw event is queued along with other window-events,
        like mouse click etc. Essentially what your mainLoop does
        it pick events from that queue and call their handlers
    */

    glutDisplayFunc(display);

    /*
        The reshape function defines what to do when
        the window is resized. It must have a void return type,
        and takes two int parameters (the new width and height
        of the window).

        glutReshapeFunc is similar to glutDisplayFunc in that it sets up a callback - this time, the callback
        is the function to call when the window is reshaped (i.e. resized).
    */

    glutReshapeFunc(reshape);

    /*
        to display frame, we draw, clear then redraw in another position
        each time we call the display function, it will be a different frame
        to call it more than once we use the glutTimerFunc();
        where we need to specify the time in milliseconds
        callback timer
        and another integer that we can pass to the callback function
    */
    glutTimerFunc(0, timer, 0);

    // change background color of the window
    init();

    // after create the window if there's no task it closes the window.
    // the function glutMainLoop will let the window appearing while this loop
    // is running, this loop can get all interaction with the program.
    // this function is similar to the OpenCV function waitKey;
    glutMainLoop();
    return 0;
}

// this function is going to be used when call function each frame the x changes
// only the x changes here because we are doing a horizontally movement
float x_pos = -10;
float y_pos_triangle = 0;
// this is the callback function
void display() {
    // clear - reset - drawn and then display
    // GLClear clear any type of buffer, for this time we are going to clear the color buffer
    // before drawn on window, must clear it, it must have draws from the previous frame
    //  GL_COLOR_BUFFER_BIT means to clear the information about pixel colors.
    glClear(GL_COLOR_BUFFER_BIT);

    // reset the matrix (any transformation, translation, etc.)
    // essentially resets the matrix back to its default state.
    glLoadIdentity();

    // size of the point
    glPointSize(10.0);

    glShadeModel(GL_SMOOTH);

    // draw comes here. GL Begin initiates the drawn of the vertexes
     glBegin(GL_TRIANGLES);
    // GL_POINTS, GL_POLYGON, and many other types of thing I can drawn
    // to create a triangle need to specify 3 points
       glColor3f(0.0, 0.0, 1.0); // change color of the primitive (this color is assign to all following vertexes)
       glVertex2f(0.0, y_pos_triangle+2.0);
       glVertex2f(3.0, y_pos_triangle+-2.0);
       glVertex2f(-3.0, y_pos_triangle-2.0);

     glEnd(); // GL End specify that the drawn of the vertexes has finished.


    glBegin(GL_POLYGON);
       // drawing a square
       glColor3f(1.0, 1.0, 0.0);
       glVertex2f(x_pos, 1.0);
       glVertex2f(x_pos, -1.0);
       glVertex2f(x_pos+2.0, -1.0);
       glVertex2f(x_pos+2.0, 1.0);
    glEnd();

    // then display the frame buffer on the screen
    // OpenGL caches drawing commands for efficiency,
    // so nothing will actually appear on the screen until
    // you call GLFlush. This should generally be the last
    // thing done by a display callback.
    // glFlush(); -> when using double buffer, need to use other function
    // if we have finish the draw in the back buffer and the time to do the swap
    // has come, when keep the first buffer and continue drawing until it finishes
    glutSwapBuffers();
}

// reshape the window function
void reshape(int w, int h) {
    // if the user has reshape the window, this function is going
    // to be called to respecify some area to work, etc.. Avoid distortion
    // the ViewPort is going to specify here.
    // viewPort is a rectangle area where the shapes can be drawn. anything outside
    // the viewPort is not going to be shown (this function takes x and y coordinates and also width and height
    // x, y is the bottom left corner of the viewPort(rectangle).
    // to use the whole window, must do 0,0 and width and height must be the width of the window and height of the window
    // this function returns new width and height when this window is reshaped
    glViewport(0, 0, w, h);

    // GLMATRIXMode sets the current matrix mode. mode can assume one of four values
    // GL_MODELVIEW: Applies subsequent matrix operations to the model view matrix stack.
    // GL_PROJECTION: Applies subsequent matrix operations to the projection matrix stack.
    // GL_TEXTURE: Applies subsequent matrix operations to the texture matrix stack.
    // GL_COLOR: Applies subsequent matrix operations to the color matrix stack.
    // only change the matrix model to this when we need to change the projection
    glMatrixMode(GL_PROJECTION);

    // reset the matrix (any transformation, translation, etc.)
    // essentially resets the matrix back to its default state.
    glLoadIdentity();

    /*
        It is the process of converting a 3D object into a 2D object.
        It is also defined as mapping or transformation of the object
        in projection plane or view plane. The view plane is displayed surface.
        There are two type parallel and perspective

        Orthographic is a method of projection in which an object is depicted
        or a surface mapped using parallel lines to project
        its shape onto a plane.
    */
    // this function is used to specify the orthogonality
    // it takes 4 values as a parameter: left and right of the x coordinate
    // up and down of the right coordinate
    gluOrtho2D(-10, 10, -10, 10);
    // return back to model view mode
    glMatrixMode(GL_MODELVIEW);
}

bool foward = true;

// recursive, it's going to call itself periodically after 1000/60 times
void timer(int) {
    // openGL is going to call display function
    glutPostRedisplay();
    // 1000 / 60 is the frame rate
    glutTimerFunc(1000/60, timer, 0);

    // need to change the x position to create the animation
    // goes right
    if (x_pos < 8 && foward) {
        x_pos+=0.15; // change the speed of the object here, 0.30, etc.
    } else {
        foward = false;
    }

    // goes left
    if (!foward && x_pos > -10)
        x_pos-=0.15;
    else
        foward = true;

    // checking if the square is near the triangle
    if (x_pos >= -5.0 && x_pos <= 4.0)
        y_pos_triangle = 4;
    else
        y_pos_triangle = 0;

}
