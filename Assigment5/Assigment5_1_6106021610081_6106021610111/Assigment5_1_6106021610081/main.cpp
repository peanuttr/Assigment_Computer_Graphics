#include <iostream>
using namespace std;

#include<GL\glut.h>

void init(void);
void myDisplay(void);
void myMouse(GLint button,GLint action,GLint x,GLint y);
void myKeyboard(GLubyte key,GLint x,GLint y);
void defineLight();
void define3dView();
void drawShape(int type);
void drawSphere();
void drawTorus();
void drawCube();
void Rotate(int value);

#define ESCAPE 27

int Type = 1 ;
GLfloat light_color[] = {1.0,1.0,1.0};
GLfloat light_position[] = {30.0,30.0,30.0,0.0};
int angle = 0,vX = 0,vY = 0,vZ = 1;
bool Play = false;

void main(int argc,char** argv){
	//Function Main ใช้เรียก การสร้างหน้าต่าง GUI และเรียกใช้ Function สำหรับ glut ในการทำงาน
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(1024,768);
	glutCreateWindow("Assignment 05_1 ");
	init();
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	glutPostRedisplay();
	glutMainLoop();
}

void init(void){
	//Function สำหรับเชื่อมต่อ display และ หน้าต่าง GUI
	glClearColor(1.0,1.0,1.0,0);
	define3dView();
	defineLight();
}

void define3dView(){
	//Function จัดมุมมอง 3D ในการวาดภาพ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-30,30,-30,30,-30,30);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void defineLight(){
	//Function สำหรับการจัดแสง
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_color);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_color);

	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void myDisplay(void){
	//Function ที่ใช้สำหรับวาดขึ้น GUI
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	drawShape(Type);

	glutSwapBuffers();
	glFlush();
}

void myKeyboard(GLubyte key,GLint x,GLint y){
	//Function รับค่าจาก keyboard เพื่อทำการ เซ็ทสีของแสงและเซ็ท Type ของรูปทรง
	key = toupper(key);
	if(key == 'R'){

		light_color[0] = 1.0;
		light_color[1] = 0.0;
		light_color[2] = 0.0;

		glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color);
		glLightfv(GL_LIGHT0,GL_AMBIENT,light_color);
	}
	else if(key == 'G'){

		light_color[0] = 0.0;
		light_color[1] = 1.0;
		light_color[2] = 0.0;

		glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color);
		glLightfv(GL_LIGHT0,GL_AMBIENT,light_color);
	}
	else if(key == 'B'){

		light_color[0] = 0.0;
		light_color[1] = 0.0;
		light_color[2] = 1.0;

		glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color);
		glLightfv(GL_LIGHT0,GL_AMBIENT,light_color);
	}
	else if(key == 'W'){

		light_color[0] = 1.0;
		light_color[1] = 1.0;
		light_color[2] = 1.0;

		glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color);
		glLightfv(GL_LIGHT0,GL_AMBIENT,light_color);
	}
	else if(key == ESCAPE){

		exit(0);
	}
	else if(key == 'S'){

		Type = 1;
	}
	else if(key == 'C'){

		Type = 2;
	}
	else if(key == 'T'){

		Type = 3;
	}

	
	glutPostRedisplay();
}

void myMouse(GLint button,GLint action,GLint x,GLint y){
	//Function รับค่าจาก Mouse เมื่อคลิ๊กซ้ายให้ทำการหมุน และ เมื่อคลิกขวาให้ทำการหยุด
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
		if(!Play){

				Play = true;
				glutTimerFunc(30,Rotate,30);
			}
		}
	else if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN){
			
			Play = false;
		}
	glutPostRedisplay();
}

void Rotate(int value){
	//Function ใช้สำหรับการหมุนวัตถุโดยหมุน 360 องศา
	angle +=1;
	if(angle == 360){
		angle = 0;
	}
	glutPostRedisplay();
	if(Play) glutTimerFunc(value,Rotate,value);
	
}
void drawTorus(){
	//Function สำหรับวาดรูป โดนัท
	glPushMatrix();
	glRotatef(angle,vX,vY,vZ);
		glPushMatrix();
			glTranslatef(0.0f,10.0f,0.0f);
			glutSolidTorus( 1, 3, 10, 15);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-10.0f,0.0f,0.0f);
			glutSolidTorus( 1, 3, 10, 15);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(10.0f,0.0f,0.0f);
			glutSolidTorus( 1, 3, 10, 15);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f,-10.0f,0.0f);
			glutSolidTorus( 1, 3, 10, 15);
		glPopMatrix();
	glPopMatrix();
}

void drawCube(){
	//Function สำหรับวาดรูป ลูกบาศก์
	glPushMatrix();
		glRotatef(angle,vX,vY,vZ);
		glPushMatrix();
			glTranslatef(0.0f,10.f,0.0f);
			glutSolidCube( 5);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-10.0f,0.0f,0.0f);
			glutSolidCube( 5);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(10.0f,0.0f,0.0f);
			glutSolidCube( 5);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f,-10.0f,0.0f);
			glutSolidCube( 5);
		glPopMatrix();
	glPopMatrix();
}

void drawSphere(){
	//Function สำหรับวาดรูป วงกลม
	glPushMatrix();
		glRotatef(angle,vX,vY,vZ);
		glPushMatrix();
			glTranslatef(0.0f,10.0f,0.0f);
			glutSolidSphere(3,20,20);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-10.0f,0.0f,0.0f);
			glutSolidSphere(3,20,20);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(10.0f,0.0f,0.0f);
			glutSolidSphere(3,20,20);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f,-10.0f,0.0f);
			glutSolidSphere(3,20,20);
		glPopMatrix();
	glPopMatrix();
}
void drawShape(int Type){
	//Function สำหรับเช็คค่า ในการวาดวัตถุ
	switch(Type){
	case 1:drawSphere();
		break;
	case 2 :drawCube();
		break;
	case 3 :drawTorus();
		break;
	}
}