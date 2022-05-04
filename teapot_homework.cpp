#include "teapot_homework.hpp"
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

void Object(){
    glColor3f(0,0.2,0.8);
    glTranslatef (-0.1, -0.1, 0.0);
    glutWireTeapot(0.3);
    glTranslatef (1.0, 0.0, 0.0);
    glColor3f(1,0,0);
    glutSolidCube(0.5);
}


void MyDisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
//    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 100.0); //경사투영
    glFrustum(-2.0, 2.0, -2.0, 1.5, 0.1, 100.0); //원근투영
    Object();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow(" glutWireTeapot ");
    glClearColor(0.0,0.0,0.0,1.0);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
    
}

