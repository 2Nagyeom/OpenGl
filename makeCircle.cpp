//
//  makeCircle.cpp
//  openGL
//
//  Created by 이나겸 on 2022/05/25.
//

#include "makeCircle.hpp"
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>
#define PI 3.141592

void drawCircle(float radius){
    glPointSize(5.0);
    glColor3f(0.6, 1.0, 0.1);
    glBegin(GL_LINE_LOOP);
        for (float angle=0; angle <2*PI; angle += 0.4)
            glVertex3f(radius * cos(angle), radius*sin(angle), 0);
    glEnd();
    glFlush();
}
void MyDisplay(){
    unsigned short stipple = 0xFF00;
    //직선의 패턴을 만들어줌(16비트짜리로), 1은 색깔을 찍어주고 0은 색깔을 찍어주지 않음, 더 조밀하게 할려면 F0
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(7.0);
    glLineWidth(4.0);
    glEnable(GL_LINE_STIPPLE); // 라인의 대한 패턴을 사용한다는 것을 의미 사용하지 않으면 disable
    glLineStipple(1, stipple); // 점선에 해당되는 패턴을 스케일링 해준다. (정수가 클수록 막대의 길이가 길어짐)
    
    glEnable(GL_BLEND);
    // 에일리어싱은 엣지의 색을 바탕색과 혼합시켜주어야하기 때문에 블랜딩을 해주어야함
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // 블랜딩을 해주는 방법은 투영도를 이용한다.(알파, 1-알파) 점과 직선 폴리곤까지 가능함. (단 폴리곤은 엣지부분만)
    // 점에 대한 엔티에얼리싱
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH, GL_NICEST); // 좀 더 이쁘게 에얼리싱 해주는 nicest, 빠르게 할려면 fastset
    // 라인에 대한 엔티에얼리싱
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    
    glBegin(GL_LINE_LOOP);
        glColor3f(1,0,0);  glVertex3f(-0.5, -0.5, 0);
        glColor3f(0,1,0);  glVertex3f(-0.5, 0.5, 0);
        glColor3f(0,0,1);  glVertex3f(0.5, 0.5, 0);
        glColor3f(1,1,1);  glVertex3f(0.5, -0.5, 0);
    glEnd();
    
    glDisable(GL_LINE_STIPPLE);
    glLineWidth(1.0);
    drawCircle(0.85);
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_LINE_SMOOTH);
    drawCircle(0.8);
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
