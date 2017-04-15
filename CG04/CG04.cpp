// CG01.cpp : Defines the entry point for the console application.
//http://www.tuicool.com/articles/VRRVV3j hide the console window
#include<GL\glew.h>
#include<GL\glut.h>
#include<time.h>
#include<math.h>
GLdouble PI = 3.141592654;
GLfloat x = -200, y = 0, angle = 90;
GLfloat d = 30, d1 = 30;
unsigned int r = 0, g = 123, b = 0;
GLfloat preX;
int roundX, roundY, dx, dy;//round centre ,round move
enum direction
{
	up,
	down,
	left,
	right
}starDirect;
bool bigger;
void init()
{
	glClearColor(0, 0, 0, 1);
	glShadeModel(GL_FLAT);
}
void SetPixel(int x, int y, float r, float g, float b)
{
	glColor3f(r, g, b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
//圆弧的中点算法
void midpointRound(int x0, int y0, GLfloat rr, GLfloat r, GLfloat g, GLfloat b) {
	int H = 5 - 4 * rr,
		E = 12,
		SE = 20 - 8 * rr;
	GLfloat y = rr;
	for (int x = 0; x <= rr / pow(2, 0.5); x++) {
		SetPixel(x0+x, y0+y, r, g, b);
		SetPixel(x0-x, y0-y, r, g, b);
		SetPixel(x0+x, y0-y, r, g, b);
		SetPixel(x0-x, y0+y, r, g, b);
		SetPixel(x0+y, y0+x, r, g, b);
		SetPixel(x0+y, y0-x, r, g, b);
		SetPixel(x0-y, y0+x, r, g, b);
		SetPixel(x0-y, y0-x, r, g, b);
		if (H <= 0) {
			H += E;	E += 8;	SE += 8;
		}
		else {
			--y;
			H += SE; E += 8;	SE += 16;
		}
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(255, 255, 0);
	glBegin(GL_LINE_LOOP);//外围方框
		glVertex2d(-100, 100);
		glVertex2d(100, 100);
		glVertex2d(100, -100);
		glVertex2d(-100, -100);
	glEnd();
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 5; i++)//滚动的五角星
	{
		glColor3ub(0, 255, 115);
		glVertex2d(x, y);
		glVertex2d(x + d*cos((angle - i * 72)*PI / 180), y + d*sin((angle - i * 72)*PI / 180));
		glVertex2d(x + 0.5*d*cos((angle - 36 - i * 72)*PI / 180), y + 0.5*d*sin((angle - 36 - i * 72)*PI / 180));

		glColor3ub(136, 201, 140);
		glVertex2d(0, 0);
		glVertex2d(x + d*cos((angle - i * 72)*PI / 180), y + d*sin((angle - i * 72)*PI / 180));
		glVertex2d(x + 0.5*d*cos((angle + 36 - i * 72)*PI / 180), y + 0.5*d*sin((angle + 36 - i * 72)*PI / 180));
	}
	glEnd();
	glColor3ub(255, 0, 0);
	glBegin(GL_LINE_LOOP);//放缩的五角星
		for (int i = 0; i < 5; i++)
		{
			glVertex3f(x + d1*cos((angle - i * 72)*PI / 180), y + d1*sin((angle - i * 72)*PI / 180), 0);
			glVertex3f(x + 0.5*d1*cos((angle - 36 - i * 72)*PI / 180), y + 0.5*d1*sin((angle - 36 - i * 72)*PI / 180), 0);
		}
	glEnd();
	midpointRound(roundX, roundY, 20, 0, 0, 1);//任意方向运动的圆
	glutSwapBuffers();
}
void change()
{	//滚动的五角星
	if (starDirect == right) {
		--angle;//旋转
		if (x<70) ++x;
		else    { --x; starDirect = left; }
	}
	else{
		++angle;//旋转
		if (x > -70) --x;
		else       { ++x; starDirect = right; }
	}
	//放缩的五角星
	if (bigger){
		if (d1 < 70) ++d1;
		else { --d1; bigger = false; }
	}
	else
	{
		if (d1 > 0) --d1;
		else { ++d1; bigger = true; }
	}
	//任意方向运动的圆
	srand(time(NULL));
	if (roundX>75 && roundX < 80) {//用范围判断，防止加大于1的数时跳过
		dx = rand() % 3 - 4;
		dy = rand() % 6 - 3;
	}
	else if (roundX > -80 && roundX < -75) {
		dx = rand() % 3 + 1;
		dy = rand() % 6 - 3;
	}
	else if (roundY < 80 && roundY > 75) {
		dx = rand() % 6 - 3;
		dy = rand() % 3 - 4;
	}
	else if (roundY > -80 && roundY < -75) {
		dx = rand() % 6 - 3;
		dy = rand() % 3 + 1;
	}
	roundX += dx;
	roundY += dy;
	display();
}
void timer(int value)
{
	//glutPostRedisplay();
	change();
	glutTimerFunc(50, timer, 0);
}
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width/2, width / 2, -height/2, height/2, 0, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char**argv)
{
	starDirect = right;
	bigger = true;
	roundX = 0, roundY = 0;
	dx = 1, dy = 0;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL图形几何变换");
	init();
	glutDisplayFunc(display);
	//glutIdleFunc(change);//空闲调用
	glutTimerFunc(50, timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
