//
//  windowSize.cpp
//  openGL
//
//  Created by 이나겸 on 2022/05/25.
//

#include "points_lines.hpp"
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>

void MyDisplay(){
    unsigned short stipple = 0xFF00;
    //직선의 패턴을 만들어줌(16비트짜리로), 1은 색깔을 찍어주고 0은 색깔을 찍어주지 않음, 더 조밀하게 할려면 F0
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(7.0);
    glLineWidth(4.0);
    glEnable(GL_LINE_STIPPLE); // 라인의 대한 패턴을 사용한다는 것을 의미 사용하지 않으면 disenable
    glLineStipple(1, stipple); // 점선에 해당되는 패턴을 스케일링 해준다. (정수가 클수록 막대의 길이가 길어짐)
    
    glBegin(GL_LINE_LOOP);
        glColor3f(1,0,0);  glVertex3f(-0.5, -0.5, 0);
        glColor3f(0,1,0);  glVertex3f(-0.5, 0.5, 0);
        glColor3f(0,0,1);  glVertex3f(0.5, 0.5, 0);
        glColor3f(1,1,1);  glVertex3f(0.5, -0.5, 0);
    glEnd();
    glFlush();
}

void MyReShape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH );
    glutInitWindowSize(600, 600);
//    glutInitWindowPosition(100, 100);
    glutCreateWindow("test opengl program");
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReShape);
    glutMainLoop();
    return 0;
}
