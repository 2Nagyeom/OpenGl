#include "visibilityTest.hpp"
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

float trans = 0;

void MyDisplay(){
    trans = trans - 0.005;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glEnable(GL_CULL_FACE); //후면제거 : 법선벡터 => glEnable(GL_CULL_FACE); 정면과 후면중 어떤것을 cullface 할 것인가?
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST); //은면제거 : z-buffer를 써라 (이걸 안쓰면 그림순서를 바꿨을때 그림이 가려져보임)
    
//    glScalef(3, 3, 3);
    glColor3f(1, 1, 0);
    glFrontFace(GL_CW);
    glRotatef(30, 10.0f, 0.0f, 0.0f);
    glRotatef(30, 0.0f, 0.0f, 1.0f);

    glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
           glVertex3f(-0.5, 0.5, -0.5 );
           glVertex3f(0.5, 0.5, -0.5);
           glVertex3f(0.5, 0.5, 0.5);
           glVertex3f(-0.5, 0.5, 0.5);
        glColor3f(0, 1, 0);
           glVertex3f(-0.5, 0.5, 0.5);
           glVertex3f(0.5, 0.5, 0.5);
           glVertex3f( 0.5, -0.5, 0.5 );
           glVertex3f(-0.5, -0.5, 0.5);
        glColor3f(0, 0, 1);
           glVertex3f(0.5, 0.5, -0.5);
           glVertex3f( 0.5, -0.5, -0.5 );
           glVertex3f( 0.5, -0.5, 0.5 );
           glVertex3f(0.5, 0.5, 0.5);
        glColor3f(1, 1, 0);
           glVertex3f(-0.5, 0.5, -0.5 );
           glVertex3f( 0.5, 0.5, -0.5);
           glVertex3f( 0.5, -0.5, -0.5 );
           glVertex3f(-0.5, -0.5, -0.5 );
        glColor3f(0, 1, 1);
           glVertex3f( 0.5, -0.5, -0.5 );
           glVertex3f(-0.5, -0.5, -0.5 );
           glVertex3f(-0.5, -0.5, 0.5);
           glVertex3f( 0.5, -0.5, 0.5 );
        glColor3f(1, 0, 1);
           glVertex3f(-0.5, -0.5, -0.5 );
           glVertex3f(-0.5, 0.5, -0.5 );
           glVertex3f(-0.5, 0.5, 0.5);
           glVertex3f(-0.5, -0.5, 0.5);
    glEnd();
//    glRotatef(30, 10.0f, -30.0f, 0.0f);
    glTranslatef(0, 0, trans+0.5);
    glFrontFace(GL_CCW);  //ccw 는 반시계 방향으로 한다는 뜻
    glBegin(GL_POLYGON);
        glColor3f(1, 1, 1); glVertex3f(0.0,1.0,0.0);
        glColor3f(1, 1, 1); glVertex3f(-1.0,0,0.0);
        glColor3f(1, 1, 1); glVertex3f(1.0,0.0,0.0);
    glEnd();
    glutSwapBuffers();
//    glFlush();
}

void MyReShape(int w, int h){ // 절단 : 뷰볼륨 glOrtho, glPerspective
    float ratio;
    ratio = (float)w/(float)h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0*ratio, 1.0*ratio, -1, 1, -1, 1);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow(" test hidden removal");
    glClearColor(0.0,0.0,0.0,1.0);
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReShape);
    glutIdleFunc(MyDisplay);
    glutMainLoop();
    return 0;
    
}
