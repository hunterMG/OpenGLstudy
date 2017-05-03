// CG01.cpp : Defines the entry point for the console application.
//http://www.tuicool.com/articles/VRRVV3j hide the console window
#include <GL\glew.h>
#include <GL\glut.h>
#include <GL/glaux.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "tgaload.h"
GLfloat angle = 0.0; //set the angle of rotation 

#define MAX_NO_TEXTURES 1

#define CUBE_TEXTURE 0

GLuint texture_id[MAX_NO_TEXTURES];

float ratio;

void init()
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glEnable(GL_COLOR_MATERIAL);//���ò���
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);//���ò���
	//������ͼ
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, texture_id);
	image_t   temp_image;
	glBindTexture(GL_TEXTURE_2D, texture_id[CUBE_TEXTURE]);
	tgaLoad("chuyin2.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);//����ͼƬ
	glEnable(GL_CULL_FACE);
	//��Դ0 �� 1��1�Ǿ۹��Դ�� 
	GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 }; GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; GLfloat mat_shininess[] = { 50.0 };
	GLfloat light0_diffuse[] = { 0.0, 0.0, 1.0, 1.0 }; GLfloat light0_position[] = { 3.0, 3.0, 1.0, 0.0 };
	GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 }; GLfloat light1_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 0.6, 0.6, 1.0 }; GLfloat light1_position[] = { -3.0, -3.0, 1.0, 1.0 };
	GLfloat spot_direction[] = { 1.0,1.0,-1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);//����--����ʲô��--����������ֵ���ɫ
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//���ʵľ���ָ��
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);//RGBAģʽ���������
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);//��Դλ���������
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);//RGBAģʽ�»�����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);//RGBAģʽ�¾����
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);//���Դ�۹��ֹ��
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);//���Դ�۹ⷽ��ʸ��
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
}

GLfloat vertices[][3] = { { -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },{ -1.0,-1.0,1.0 },{ 1.0,-1.0,1.0 },{ 1.0,1.0,1.0 },{ -1.0,1.0,1.0 } ,{0.0, 1.0, 0.0} };
GLfloat colors[][3] = { { 0.0,0.0,0.0 },{ 1.0,0.0,0.0 },{ 1.0,1.0,0.0 },{ 0.0,1.0,0.0 },{ 0.0,0.0,1.0 },{ 1.0,0.0,1.0 },{ 1.0,1.0,1.0 },{ 0.0,1.0,1.0 } };
GLfloat point[][3] = { {0,1,0},{-1,-1,1},{1,-1,1},{0,-1,-1} };

void triangle(int a, int b, int c, int color)
{
	glBegin(GL_POLYGON); glColor3fv(colors[color]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(point[a]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(point[b]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(point[c]);
	glEnd();
}

void colorPyramid() {
	triangle(0, 1, 2, 6); //6Ϊ��ɫ��ʹ������ΪͼƬ��ɫ����Ӧ������ɫ 
	triangle(0, 3, 1, 6); //ǰ��������˳�򲻿ɴ����򿴲���ͼƬ
	triangle(0, 2, 3, 6); 
	triangle(1, 3, 2, 6); 
}
GLfloat m_viewer[3] = { 0,0,6 };
GLfloat m_theta[3] = { 0,0,0 };
void display1()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0, 0, -5);
	gluLookAt(m_viewer[0], m_viewer[1], m_viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//        �۾���λ��                              �۲췽��        ͷ���ϵķ���
	/*
	glTranslatef()����ģ�ͱ任----�ƶ�����
	gluLookAt()������ͼ�任-------�ƶ���������۾���
	-----Ч��һ��
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);//��Ȳ������������� 
	
	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	
	glPushMatrix();
	//glLoadIdentity();
	glTranslated(-3.0, -3.0, 1.0);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 0.0);
	glutWireCube(0.1);//��ע��Դ1λ��--��
	glEnable(GL_LIGHTING);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(3.0, 3.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glutWireCube(0.1);//��ע��Դ0λ��--��
	glPopMatrix();

	glRotatef(m_theta[0], 1.0, 0.0, 0.0);
	glRotatef(m_theta[1], 0.0, 1.0, 0.0); // ��ת 
	glRotatef(m_theta[2], 0.0, 0.0, 1.0);

	colorPyramid();
	glutSwapBuffers();
	m_theta[0] += 1.0f;
	m_theta[1] += 1.0f;
	m_theta[2] += 1.0f;
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

void reshape(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you can't make a window of zero width).
	if (h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the clipping volume
	gluPerspective(80, ratio, 1, 200);//͸��ͶӰ
	//glOrtho(-width / 2, width / 2, -height / 2, height / 2, 0, 10);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0, 0, 10, 	0, 0, 10,    0.0f, 1.0f, 0.0f);
	gluLookAt(m_viewer[0], m_viewer[1], m_viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
void timer(int value)
{
	//glutPostRedisplay();
	display1();

	glutTimerFunc(10, timer, 0);
}
int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("OpenGLʵ��5");
	//glewInit();
	init();
	glutDisplayFunc(display1);//������ʾ�����,WM_PAINT  
	//glutIdleFunc(display1);//����ʱ����
	glutTimerFunc(50, timer, 0);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);
	glutMainLoop();
	return 0;
}
