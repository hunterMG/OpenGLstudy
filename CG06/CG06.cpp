// CG01.cpp : Defines the entry point for the console application.
//http://www.tuicool.com/articles/VRRVV3j hide the console window
#include<GL\glew.h>
#include<GL\glut.h>
#include<time.h>
#include<math.h>
void init()
{
	glClearColor(0, 0, 0, 1);
	glShadeModel(GL_FLAT);
}
GLsizei winWidth = 600, winHeight = 600;
class wcPt3D {
public:
	GLfloat x, y, z;
};
GLfloat ctrlPts[4][3] = { { -50.0, 40.0, 0.0 },{ -10.0, 70.0, 0.0 },{ 10.0, -70.0, 0.0 },{ 80.0, 40.0, 0.0 } };
void Bezier3() {
	//glTranslated(100, 0, 0);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, *ctrlPts);//定义Bezier曲线参数
	glEnable(GL_MAP1_VERTEX_3);
	GLint k;
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP); //绘制 3次 Bezier 曲线
	for (k = 0; k <= 50; k++)
		glEvalCoord1f(GLfloat(k) / 50.0);
	glEnd();

	glColor3f(1.0, 0.0, 0.0); glPointSize(5.0); //绘制控制点
	glBegin(GL_POINTS);
	for (k = 0; k < 4; k++)
		glVertex3fv(ctrlPts[k]);
	glEnd();
	//绘制控制多边形
	glColor3f(0.0, 1.0, 0.0); glLineWidth(2.0);
	glBegin(GL_LINE_STRIP);
	for (k = 0; k < 4; k++)
		glVertex3fv(&ctrlPts[k][0]);
	glEnd();
}
GLfloat ctrlPts4[5][3] = { { -50.0, 40.0, 0.0 },{ -10.0, 70.0, 0.0 },{ 10.0, -70.0, 0.0 },{ 80.0, 40.0, 0.0 },{40.0, 200.0, 0.0} };
void Bezier4() {
	//glTranslated(100, 0, 0);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 5, *ctrlPts4);//定义Bezier曲线参数
	glEnable(GL_MAP1_VERTEX_3);
	GLint k;
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP); //绘制 4次 Bezier 曲线
	for (k = 0; k <= 50; k++)
		glEvalCoord1f(GLfloat(k) / 50.0);
	glEnd();

	glColor3f(1.0, 0.0, 0.0); glPointSize(5.0); //绘制控制点
	glBegin(GL_POINTS);
	for (k = 0; k < 5; k++)
		glVertex3fv(ctrlPts4[k]);
	glEnd();
	//绘制控制多边形
	glColor3f(0.0, 1.0, 0.0); glLineWidth(2.0);
	glBegin(GL_LINE_STRIP);
	for (k = 0; k < 5; k++)
		glVertex3fv(&ctrlPts4[k][0]);
	glEnd();
}
GLfloat ctrlPts5[6][3] = { { -50.0, 40.0, 0.0 },{ -10.0, 70.0, 0.0 },{ 10.0, -70.0, 0.0 },{ 80.0, 40.0, 0.0 },{ 40.0, 200.0, 0.0 },{-100.0, 150.0, 0.0} };
void Bezier5() {
	//glTranslated(100, 0, 0);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 6, *ctrlPts5);//定义Bezier曲线参数
	glEnable(GL_MAP1_VERTEX_3);
	GLint k;
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP); //绘制 5次 Bezier 曲线
	for (k = 0; k <= 50; k++)
		glEvalCoord1f(GLfloat(k) / 50.0);
	glEnd();

	glColor3f(1.0, 0.0, 0.0); glPointSize(5.0); //绘制控制点
	glBegin(GL_POINTS);
	for (k = 0; k < 6; k++)
		glVertex3fv(ctrlPts5[k]);
	glEnd();
	//绘制控制多边形
	glColor3f(0.0, 1.0, 0.0); glLineWidth(2.0);
	glBegin(GL_LINE_STRIP);
	for (k = 0; k < 6; k++)
		glVertex3fv(&ctrlPts5[k][0]);
	glEnd();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	Bezier3();
	Bezier4();
	Bezier5();
	glutSwapBuffers();
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}
void arrow_keys(int a_keys, int x, int y)  // Create Special Function (required for arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
		glutFullScreen(); // Go Into Full Screen Mode
		break;
	case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
		glutReshapeWindow(500, 500); // Go Into A 500 By 500 Window
		break;
	default:
		break;
	}
}

float ratio;
void reshape(int width, int height)
{
	if (height == 0)
		height = 1;
	ratio = 1.0f * width / height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width / 2, width / 2, -height / 2, height / 2, 0, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("OpenGL Bezier 曲线");
	init();
	glutDisplayFunc(display);
	//glutIdleFunc(change);//空闲调用
	//glutTimerFunc(50, timer, 0);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);
	glutMainLoop();
	return 0;
}
