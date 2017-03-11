// CG01.cpp : Defines the entry point for the console application.
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

	//按照A->C->E->B->D->A的顺序一笔画出五角星
	glBegin(GL_LINE_LOOP);
	glVertex2fv(pointA);
	glVertex2fv(pointC);
	glVertex2fv(pointE);
	glVertex2fv(pointB);
	glVertex2fv(pointD);
	glVertex2fv(pointA);
	glEnd();
	glFlush();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("OpenGL画五角星");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;
}

/*
#include<GL\glew.h>
#include<GL\glut.h>
#include<time.h>
#include<math.h>
double green_color = 0;
bool sign = true;
float PI = 3.141592654;
void init()
{
	glClearColor(0, 0, 0, 1);
	glShadeModel(GL_FLAT);
}
void display()
{
	float d = 30;
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_LINE_LOOP);
	glColor4f(0, green_color, 0, 1);
	glVertex3f(0, d, 0);//1
	glVertex3f(0.5*d*cos(0.3*PI), 0.5*d*sin(0.3*PI), 0);
	glVertex3f(d*cos(PI/18), d*sin(PI/18), 0);//2
	glVertex3f(0.5*d*cos(PI / 18), -0.5*d*sin(PI / 18), 0);
	glVertex3f(d*cos(0.3*PI), -d*sin(0.3*PI), 0);//3
	glVertex3f(0, -0.5*d, 0);
	glVertex3f(-d*cos(0.3*PI), -d*sin(0.3*PI), 0);//4
	glVertex3f(-0.5*d*cos(PI / 18), -0.5*d*sin(PI / 18), 0);
	glVertex3f(-d*cos(PI / 18), d*sin(PI / 18), 0);//5
	glVertex3f(-0.5*d*cos(0.3*PI), 0.5*d*sin(0.3*PI), 0);
	glEnd();
	
	glutSwapBuffers();
	glFlush();
}
void mydisplay(int value)
{
	glClearColor(1.0, 1.0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glColor4f(0, green_color, 0, 1);
	glVertex3f(-30, -30, 0);
	glVertex3f(-30, 30, 0);
	glVertex3f(30, 30, 0);
	glVertex3f(30, -30, 0);
	glEnd();
	
	glutSwapBuffers();

	//glFinish();
	glFlush();
}
void timer(int value)
{
	if (green_color >= 1)
		sign = false;
	else if (green_color <= 0)
		sign = true;
	if (sign)
		green_color += 0.1;
	else
		green_color -= 0.1;
	glutPostRedisplay();
	glutTimerFunc(50, timer, 0);
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	//glutIdleFunc(mydisplay);空闲调用
	glutTimerFunc(50, timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
*/