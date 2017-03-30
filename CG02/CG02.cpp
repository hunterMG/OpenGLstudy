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
	glPointSize(1.0f);
	//glDisable(GL_LINE_STIPPLE);
	//glViewport(0, 0, 100, 100);
}
void SetPixel(int x, int y, float r, float g, float b)
{
	glColor3f(r, g, b);
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
}
int max(int a, int b) { return ((a) > (b)) ? (a) : (b); }
int min(int a, int b) { return ((a) > (b)) ? (b) : (a); }
void ddaLine(int x0, int y0, int x1, int y1, GLfloat r, GLfloat g, GLfloat b) {		//线段DDA算法
	if (x0 > x1) {//保证 x0<=x1
		int xtmp = x0, ytmp = y0;
		x0 = x1, y0 = y1;
		x1 = xtmp, y1 = ytmp;
	}
	GLfloat dx = fabs(x0 - x1), dy = fabs(y0 - y1);
	GLfloat m = (GLfloat)(y1 - y0) / (x1 - x0);
	GLfloat y = (GLfloat)y0;
	if (x0==x1) //斜率正无穷
	{
		int y = min(y0, y1), yy = max(y0, y1);
		for (int i = y; i<=yy; i++)
		{
			SetPixel(x0, i, r, g, b);
		}
	} 
	else
	{
		if (m >= 0 && m <= 1) {
			for (int x = x0; x <= x1; x++) {
				SetPixel(x, (int)(y + 0.5), r, g, b);
				y += m;
			}
		}
		else if(m>1){
			GLfloat x = (GLfloat)x0;
			for (int y = y0; y <= y1; y++) {
				SetPixel((int)(x + 0.5), y, r, g, b);
				x += 1.0/m;
			}
		}
		else if (m >= -1 && m<0) {
			for (int x = x0; x <= x1; x++) {
				SetPixel(x, (int)(y - 0.5), r, g, b);
				y += m;
			}
		}
		else {//m<-1
			GLfloat x = (GLfloat)x0;
			for (int y = y0; y >= y1; y--) {
				SetPixel((int)(x + 0.5), y, r, g, b);
				x -= 1.0 / m;
			}
		}
		
	}

}
void midpointLine(int x0, int y0, int x1, int y1, GLfloat r, GLfloat g, GLfloat bb) {	//线段中点算法
	if (x0 > x1) {//保证 x0<=x1
		int xtmp = x0, ytmp = y0;
		x0 = x1, y0 = y1;
		x1 = xtmp, y1 = ytmp;
	}
	int a, b, d1, d2, d, x, y;
	a = y0 - y1; b = x1 - x0; 
	x = x0; y = y0;
	if (x0 == x1) //斜率正无穷
	{
		int y = min(y0, y1), yy = max(y0, y1);
		for (int i = y; i <= yy; i++)
		{
			SetPixel(x0, i, r, g, bb);
		}
		return;
	}
	float m = float(y1 - y0) / (x1 - x0);
	SetPixel(x, y, r, g, bb);
	if (m >= 0 && m <= 1) {
		d = a + a + b;
		d1 = a + a; 
		d2 = (a + b) + (a + b);
		while (x < x1)
		{
			if (d < 0) { y++; d += d2; }
			else d += d1;
			x++;
			SetPixel(x, y, r, g, bb);
		}
	}else if (m>1){
		d = a + b + b;
		d1 = a + a + b + b;
		d2 = b + b;
		while (x < x1)
		{
			if (d < 0) { d += d2; }
			else { x++; d += d1; }
			y++;
			SetPixel(x, y, r, g, bb);
		}
	}else if (m>=-1 && m<0) {
		d = a + a - b;
		d1 = a + a - b - b;
		d2 = a + a;
		while (x < x1)
		{
			if (d < 0) { d += d2; }
			else { y--; d += d1; }
			x++;
			SetPixel(x, y, r, g, bb);
		}
	}else {//m<-1
		d = a - b - b;
		d1 = - b - b;
		d2 = a + a - b - b;
		while (x < x1)
		{
			if (d < 0) { x++; d += d2; }
			else { d += d1; }
			y--;
			SetPixel(x, y, r, g, bb);
		}
	}

}
void midpointCircle(int x0, int y0, GLfloat rr, GLfloat r, GLfloat g, GLfloat b) {
	int h0 = 5 - 4 * rr,
		E0 = 12,
		SE0 = 20 - 8 * rr;
	for (INT x = x0; x <= rr/pow(2, 0.5); x++) {

	}
}
void drawLine()
{
	int x0, y0, x1, y1;
	//x0 = 0; y0 = 0; x1 = 0; y1 = 400;	//斜率正无穷 
//	x0 = 0; y0 = 0; x1 = 600; y1 = 400;	// 0<=m<1
//	x0 = 0; y0 = 0; x1 = 100; y1 = 150;	// m>1
//	x0 = 0; y0 = 0; x1 = 600; y1 = -400;	//-1<=m<0
	x0 = 0; y0 = 0; x1 = 400; y1 = -600;	//m<-1
	glClear(GL_COLOR_BUFFER_BIT);
	ddaLine(x0 - 50, y0, x1 - 50, y1, 0, 1, 0);
	midpointLine(x0 - 100, y0, x1 - 100, y1, 0, 1, 1);
	//ddaLine(x0, y0, x1, y1, 0, 1, 0);
//	MidpointLine(x0, y0, x1, y1, 0, 1, 1);
	//OpenGL绘制线段
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
		glVertex3i(x0, y0, 0);
		glVertex3i(x1, y1, 0);
	glEnd();

	for (int i = 0; i <= 100; i++) {
		SetPixel(i, 0, 1, 1, 0);
	}
	glutSwapBuffers();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(0, 1, 0, 1);
		glBegin(GL_LINE_LOOP);
		
		glEnd();
	glutSwapBuffers();//双缓存用，单缓存用glFlush()
					  //glFlush();//glFinish();
}
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width/2, width/2, -height/2, height / 2, 0, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL扫描转换");
	init();
	glutDisplayFunc(drawLine);
	//glutIdleFunc(change);//空闲调用
	//glutTimerFunc(50, timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
