#include<iostream>
using namespace std;

#include<GL\glut.h>

void init(void);
void myDisplay(void);
void drawShape();
void myKeyboard(GLubyte key,GLint x,GLint y);
void defineLight();
void definePerspective();
void defineRightPerspective();
void defineFontPerspective();
void Rotate(int Value);
void anif(int option);
void camf(int option);
void mainMenu(int option);

#define ESCAPE 27

GLfloat light_color[] = {1.0,1.0,1.0};
GLfloat light_position[] = {40.0,40.0,40.0,0.0};
int angle = 0,vX = 0,vY = 0,vZ = 1;
bool Play = false;

void main(int argc,char** argv){
	//Function Main ใช้เรียก การสร้างหน้าต่าง GUI และเรียกใช้ Function สำหรับ glut ในการทำงาน
	GLint ani, cam;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(1024,768);
	glutCreateWindow("Assignment 05_2 ");
	init();
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	ani = glutCreateMenu (anif);
	glutAddMenuEntry ("Play Animation", 1);
	glutAddMenuEntry ("Stop Animation", 2);

	cam = glutCreateMenu(camf);
	glutAddMenuEntry ("Font View", 1);
	glutAddMenuEntry ("Right View", 2);
	glutAddMenuEntry ("Perspective View", 3);

	glutCreateMenu (mainMenu);
	glutAddSubMenu ("Animation", ani);
	glutAddSubMenu ("Camera View", cam);
	glutAddMenuEntry ("Exit Program", 3);

	glutAttachMenu (GLUT_RIGHT_BUTTON);

	glutPostRedisplay();
	glutMainLoop();
}

void init(void){
	//Function สำหรับเชื่อมต่อ display และ หน้าต่าง GUI
	glClearColor(1.0,1.0,1.0,0);
	defineFontPerspective();
	defineLight();
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
	//Function สำหรับการวาดบน GUI
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	drawShape();

	glutSwapBuffers();
	glFlush();
}

void drawShape(){
	//Function สำหรับการ วาดวัตถุลงบน หน้าต่างของ GUI
	GLfloat no_mat[]={0.0,0.0,0.0,1.0};

	GLfloat G_ambient[]={0,0,0,1.0};
	GLfloat G_diffuse[]={0,0.7,0.7};
	GLfloat G_specular[]={0,0,0};

	GLfloat Y_ambient[]={0,0,0,1.0};
	GLfloat Y_diffuse[]={0.6,0.6,0};
	GLfloat Y_specular[]={0,0,0};

	GLfloat shininess[]={12};

	glPushMatrix();
			glRotatef(angle,0,1,0);

			glPushMatrix();
				glScalef( 0.8, 1.2, 0.6);
				glMaterialfv(GL_FRONT,GL_AMBIENT,G_ambient);
				glMaterialfv(GL_FRONT,GL_DIFFUSE,G_diffuse);
				glMaterialfv(GL_FRONT,GL_SPECULAR,G_specular);
				glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
				glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
				glutSolidCube(2.5);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,2.2,0.0);
				glScalef(1,1,0.6);
				glMaterialfv(GL_FRONT,GL_AMBIENT,Y_ambient);
				glMaterialfv(GL_FRONT,GL_DIFFUSE,Y_diffuse);
				glMaterialfv(GL_FRONT,GL_SPECULAR,Y_specular);
				glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
				glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
				glutSolidSphere(1.0,20,20);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-1.5,0.9,0.0);
				glScalef(3,0.8,0.8);
				glMaterialfv(GL_FRONT,GL_AMBIENT,Y_ambient);
				glMaterialfv(GL_FRONT,GL_DIFFUSE,Y_diffuse);
				glMaterialfv(GL_FRONT,GL_SPECULAR,Y_specular);
				glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
				glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(1.5,0.9,0.0);
				glScalef(3,0.8,0.8);
				glMaterialfv(GL_FRONT,GL_AMBIENT,Y_ambient);
				glMaterialfv(GL_FRONT,GL_DIFFUSE,Y_diffuse);
				glMaterialfv(GL_FRONT,GL_SPECULAR,Y_specular);
				glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
				glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);;
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.5,-2,0.0);
				glScalef(0.6,5,0.6);
				glMaterialfv(GL_FRONT,GL_AMBIENT,Y_ambient);
				glMaterialfv(GL_FRONT,GL_DIFFUSE,Y_diffuse);
				glMaterialfv(GL_FRONT,GL_SPECULAR,Y_specular);
				glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
				glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.5,-2,0.0);
				glScalef(0.6,5,0.6);
				glMaterialfv(GL_FRONT,GL_AMBIENT,Y_ambient);
				glMaterialfv(GL_FRONT,GL_DIFFUSE,Y_diffuse);
				glMaterialfv(GL_FRONT,GL_SPECULAR,Y_specular);
				glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
				glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
				glutSolidCube(1);
			glPopMatrix();
		glPopMatrix();
}

void Rotate(int value){
	//Function สำหรับทำการหมุนรูปวัตถุที่ 360 องศา
	angle +=1;
	if(angle == 360){
		angle = 0;
	}
	glutPostRedisplay();
	if(Play) glutTimerFunc(value,Rotate,value);
	
}
void myKeyboard(GLubyte key,GLint x,GLint y){
	//Function การรับค่าจาก Keyboard เพื่อทำการเปลี่ยนสี พื้นหลัง
	key = toupper(key);
	if(key == 'K') glClearColor(0.0,0.0,0.0,0.0);
	else if(key == 'W') glClearColor(1.0,1.0,1.0,0);
	else if(key == ESCAPE) exit(0);
	glutPostRedisplay();
}

void definePerspective(){
	//Function การจัดมุมมองแบบ perspective
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30,1,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(20,20,20,0,0,0,0,1,0);
}

void defineRightPerspective(){
	//Function สำหรับการจัดมุมมองทางขวา
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30,1,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(20,00,00,0,0,0,0,1,0);
}

void defineFontPerspective(){
	//Function สำหรับการจัดมุมมองข้างหน้า
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30,1,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(00,00,20,0,0,0,0,1,0);
}

void anif(int option){
	//Function สำหรับการรับค่าจาก pop-up menu ของการหมุน
	switch(option){
		case 1:Play = true; glutTimerFunc(30,Rotate,30); break;
		case 2:Play = false; angle = 0; break;
	}
	glutPostRedisplay ( );

}

void camf(int option){
	//Function สำหรับการรับค่าจาก pop-up menu ของมุมมอง
	switch(option){
		case 1: defineFontPerspective(); break;
		case 2: defineRightPerspective(); break;
		case 3: definePerspective(); break;
	}
	glutPostRedisplay ( );

}

void mainMenu(int option){
	//Function สำหรับการรับค่าจาก pop-up menu หลัก
	switch (option){
		case 3: exit(0); break;
	}
	glutPostRedisplay ( );

}