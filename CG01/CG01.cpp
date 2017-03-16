// CG01.cpp : Defines the entry point for the console application.
//http://www.tuicool.com/articles/VRRVV3j hide the console window
#include<GL\glew.h>
#include<GL\glut.h>
#include<time.h>
#include<math.h>
GLfloat green_color = 0;
bool sign = true;
GLfloat PI = 3.141592654;
GLfloat x = 0, y = 0,angle = 90;
GLfloat d = 30;
GLfloat r = 0, g = 0, b = 0;
void init()
{
	glClearColor(0, 0, 0, 1);
	glShadeModel(GL_FLAT);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	srand(time(NULL));
	for (int j = 0; j < 20; j++) {
		int k;
		
		k = rand() % 60 - 30;//五角星中心坐标（圆心）
		x = float(k);
		k = rand() % 60 - 30;
		y = float(k);

		k = rand() % 200;//颜色
		r = k / 200.0f;
		k = rand() % 200;
		g = k / 200.0f;
		k = rand() % 200;
		b = k / 200.0f;

		k = rand() % 20 + 1;//大小
		d = float(k);
		glColor4f(r, g, b, 1);
		glBegin(GL_LINE_LOOP);
			for (int i = 0; i < 5; i++)
			{
				glVertex3f(x + d*cos((angle - i * 72)*PI / 180), y + d*sin((angle - i * 72)*PI / 180), 0);
				glVertex3f(x + 0.5*d*cos((angle - 36 - i * 72)*PI / 180), y + 0.5*d*sin((angle - 36 - i * 72)*PI / 180), 0);
			}
		glEnd();
	}
	glutSwapBuffers();//双缓存用，单缓存用glFlush()
	//glFlush();//glFinish();
}
void change()
{
	angle += 1;//旋转
	display();
}
void timer(int value)
{
	//glutPostRedisplay();
	change();
	glutTimerFunc(50, timer, 0);//改为1即刻触发鬼畜模式
}
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 50, -50, 50, 0, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL一闪一闪亮晶晶~");
	init();
	glutDisplayFunc(display);
	//glutIdleFunc(change);//空闲调用
	glutTimerFunc(50, timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}



/*
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

const GLfloat PI = 3.14159265357f;
void myDisplay(void) {
GLfloat a = 1 / (2 - 2 * cos(72 * PI / 180));
GLfloat bx = a*cos(18 * PI / 180);
GLfloat by = a*sin(18 * PI / 180);
GLfloat cy = -a*cos(18 * PI / 180);
GLfloat pointB[2] = { bx, by },
pointC[2] = { 0.5, cy },
pointD[2] = { -0.5, cy },
pointE[2] = { -bx, by },
pointA[2] = { 0,a };
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1, 1, 0);
//按照A->C->E->B->D->A的顺序一笔画出五角星
glBegin(GL_LINE_LOOP);
glVertex2fv(pointA);
glVertex2fv(pointC);
glVertex2fv(pointE);
glVertex2fv(pointB);
glVertex2fv(pointD);
glVertex2fv(pointA);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(0, 0);
glVertex2f(100, -200);
glEnd();
glFlush();
}
void display() {
glClear(GL_COLOR_BUFFER_BIT);
glColor4f(1, 1, 0, 0);
glBegin(GL_LINE_LOOP);
glVertex3f(30, 30, 0);
glVertex3f(30, -30, 0);
glVertex3f(-30, -30, 0);
glVertex3f(-30, 30, 0);
glEnd();
glFlush();
}
int main(int argc, char *argv[]) {

glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
glutInitWindowPosition(100, 100);
glutInitWindowSize(500, 500);
glutCreateWindow("OpenGL画五角星");
glutDisplayFunc(display);
glutMainLoop();
return 0;
}

*/