// CG01.cpp : Defines the entry point for the console application.
//http://www.tuicool.com/articles/VRRVV3j hide the console window
#include<GL\glew.h>
#include<GL\glut.h>
#include<time.h>
#include<math.h>

const double PI = 3.141592654;

void init()
{
	glClearColor(0, 0, 0, 1);
	glShadeModel(GL_FLAT);
	glPointSize(1.0f);
}
void SetPixel(int x, int y, float r, float g, float b){
	glColor3f(r, g, b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
float* getPixel(int x, int y, float r, float g, float b) {
	float *rgb = new float[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, rgb);
	return rgb;
}
void seedFill(int x,int y) {
	glColor4f(163.0 / 255, 219.0 / 255, 183.0 / 255, 1);
	
}
void display()
{
	int x = 0, y = 0, angle = 0, d = 200;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(230.0/255, 95.0/255, 127.0/255, 1);
	glBegin(GL_TRIANGLES);
		for (int i = 0; i < 5; i++)
		{
			glColor4f(230.0 / 255, 95.0 / 255, 127.0 / 255, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(x + d*cos((angle - i * 72)*PI / 180), y + d*sin((angle - i * 72)*PI / 180), 0);
			glVertex3f(x + 0.5*d*cos((angle - 36 - i * 72)*PI / 180), y + 0.5*d*sin((angle - 36 - i * 72)*PI / 180), 0);

			glColor4f(169.0 / 255, 99.0 / 255, 127.0 / 255, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(x + d*cos((angle - i * 72)*PI / 180), y + d*sin((angle - i * 72)*PI / 180), 0);
			glVertex3f(x + 0.5*d*cos((angle + 36 - i * 72)*PI / 180), y + 0.5*d*sin((angle + 36 - i * 72)*PI / 180), 0);
		}
	glEnd();
	seedFill(10, 2);
	glutSwapBuffers();
}
void reshape(int width, int height)
{
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
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGLÉ¨Ãè×ª»»");
	init();
	glutDisplayFunc(display);
	//glutIdleFunc(change);//¿ÕÏÐµ÷ÓÃ
	//glutTimerFunc(50, timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
