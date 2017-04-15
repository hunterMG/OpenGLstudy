// CG01.cpp : Defines the entry point for the console application.
//http://www.tuicool.com/articles/VRRVV3j hide the console window
#pragma comment(linker, "/STACK:1024000000,1024000000")//to fix the stack full
#include <GL\glew.h>
#include <GL\glut.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <iostream>

using namespace std;
const double PI = 3.141592654;
unsigned int counter = 0;
int width, height;
void init()
{
	glClearColor(0, 0, 0, 1);
	glShadeModel(GL_FLAT);
	glPointSize(1.0f);
}
void SetPixel(int x, int y, GLfloat r, GLfloat g, GLfloat b){
	
	glColor3f(r, g, b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
float* getPixel(int x, int y) {
	float *rgb = new float[3];
	glReadPixels(x+width/2, y+height/2, 1, 1, GL_RGB, GL_FLOAT, rgb);
	//glReadPixels() 参数中坐标是以窗口左下角为（0，0），投影（glOrtho）时如不是，需加上相应的值
	return rgb;
}
bool colorSame(GLfloat *c1, GLfloat *c2) {
	GLfloat ex = 0.001;
	if (c1[0] == c2[0] && c1[1] == c2[1] && c1[2] == c2[2]) {
		return true;
	}
	else {
		return false;
	}
	// fabs(c1[0] - c2[0]) < ex && fabs(c1[1] - c2[1]) < ex && fabs(c1[2] - c2[2]) < ex
}
//种子填充算法
void seedFill4(int x,int y, GLfloat *oldColor, GLfloat *newColor) {
	GLfloat *color = new GLfloat[3];
	color = getPixel(x, y);
	if (colorSame(color, oldColor) && !colorSame(color, newColor)){
		SetPixel(x, y, newColor[0], newColor[1], newColor[2]);
		seedFill4(x+1, y, oldColor, newColor);
		seedFill4(x-1, y, oldColor, newColor);
		seedFill4(x, y+1, oldColor, newColor);
		seedFill4(x, y-1, oldColor, newColor);
	}
}
void display()
{
	int x = 0, y = 0, angle = 0, d = 100;//star's centre ,angle to begin ,size
	GLfloat oldColor[3] = { 1, 0, 0};//red
	GLfloat newColor[3] = { 0, 0, 1};//blue
	glClear(GL_COLOR_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(oldColor[0], oldColor[1], oldColor[2]);
	glBegin(GL_TRIANGLES);
		for (int i = 0; i < 5; i++)
		{
			glColor3f(oldColor[0], oldColor[1], oldColor[2]);
			glVertex2d(0, 0);
			glVertex2d(x + d*cos((angle - i * 72)*PI / 180), y + d*sin((angle - i * 72)*PI / 180) );
			glVertex2d(x + 0.5*d*cos((angle - 36 - i * 72)*PI / 180), y + 0.5*d*sin((angle - 36 - i * 72)*PI / 180) );

			glColor3ub(169, 99, 127);
			glVertex2d(0, 0);
			glVertex2d(x + d*cos((angle - i * 72)*PI / 180), y + d*sin((angle - i * 72)*PI / 180) );
			glVertex2d(x + 0.5*d*cos((angle + 36 - i * 72)*PI / 180), y + 0.5*d*sin((angle + 36 - i * 72)*PI / 180) );
		}
	glEnd();

	seedFill4(0, 0, oldColor, newColor);//种子填充
	glutSwapBuffers();
}
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width / 2, width / 2, -height / 2, height / 2, 0, 10);//(0,0)在窗口中心
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char**argv)
{
	width = 400, height = 400;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("OpenGL SeedFill4");
	init();
	glutDisplayFunc(display);
	//glutIdleFunc(change);//空闲调用
	//glutTimerFunc(50, timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
