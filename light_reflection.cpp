#include <Windows.h>
#include <gl\GL.h>
#include <gl\glut.h>
#include <gl\GLU.h> 


void MyLightInit( ){
	GLfloat global_ambient[ ] = {0.1, 0.1, 0.1, 1.0};	// 전역 주변반사
	// 0번과 1번 조명만 씀, 총 7번까지 있음
	GLfloat light0_ambient[ ] = {0.5, 0.4, 0.3, 1.0}; 	// 0번 광원 특성 
	GLfloat light0_diffuse[ ] = {0.5, 0.4, 0.3, 1.0};   // 확산반사를 줌
	GLfloat light0_specular[ ] = {1.0, 1.0, 1.0, 1.0};	// 경면광을 줌( 흰색을 부여함 )

	GLfloat light1_ambient[ ] =  {0.0, 0.0, 0.0, 1.0};	// 1번 광원 특성
	GLfloat light1_diffuse[ ] =  {0.5, 0.2, 0.3, 1.0};	// 확산반사를 줌 (붉은 조명)
	GLfloat light1_specular[ ] = {0.0, 0.0, 0.0, 1.0};	// 경면광을 주지 않음

	GLfloat material_ambient[ ] = {0.3, 0.3, 0.3, 1.0};		//	물체 특성
	GLfloat material_diffuse[ ] =  {0.8, 0.8, 0.8, 1.0};
	GLfloat material_specular[ ] =  {0.0, 0.0, 1.0, 1.0};	// 물체의 반사개수 : 블루만 해당	 
	GLfloat material_shininess[ ] = {25.0};		// 조명모델을 세울때 제곱값을 25로 줌 (R과 V의 내적값을 제곱)

	glShadeModel(GL_SMOOTH);		// 구로 셰이딩
	glEnable(GL_DEPTH_TEST);		// 깊이 버퍼 활성화
	glEnable(GL_LIGHTING);		// 조명 활성화

	glEnable(GL_LIGHT0);		// 0번 광원 활성화
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);	// 0번 광원 특성할당
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);	// 0번 확산반사를 할당
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);	// 0번 경면광 할당

	glEnable(GL_LIGHT1);		// 1번 광원 활성화
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);	// 1번 광원 특성할당
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);	// 1번 확산반사를 할당
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);	// 1번 경면광 할당

	// 물체의 정면에서 적용시키겠다.후면은 FRONTBACK
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);	// 물체 특성할당
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);	 
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);	// 전역주변반사 
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);	// 근접시점

	// glEnable(GL_COLOR_MATERIAL);			// glColor 로 정의된 색상을 추적하게 허용
	// glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  // 색상이 영향을 미치는 반사의 면 및 종류 지정
}

void MyDisplay( ){
	GLfloat LightPosition0[ ] = {0.0, 0.0, 2.0, 1.0};	// 0번 광원위치
	GLfloat LightPosition1[ ] = {1.0, 1.0, 1.0, 1.0};	// 1번 광원위치
	GLfloat LightDirection1[ ]  = {-0.5, -1.0, -1.0};	// 1번 광원 방향
	GLfloat SpotAngle1[ ] = {20.0};						// 1번 광원 각도
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);							// 모델뷰 행렬
	glLoadIdentity( );									// 항등행렬 로드
	gluLookAt(0.5, 0.5, 0.5, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);	// 시점변환
	glTranslatef(0.3, 0.3, 0.0);						// 모델변환
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);	// 위치성 광원
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);	// 스포트라이트
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDirection1);	// 방향
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, SpotAngle1);	// 각도
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);			// 코사인 승수
	glutSolidTorus(0.3, 0.6, 800, 800);					// 원환체 정의
	glFlush( );
}

void MyReshape (int w, int h){
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);				//	투상행렬
	glLoadIdentity( );							//	항등행렬 로드
	glOrtho (-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);	//	평행투상
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("openGL Sample Drawing");
	MyLightInit( );
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop( );
	return 0;
}

