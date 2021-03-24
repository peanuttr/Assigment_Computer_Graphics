#include<iostream>
using namespace std;
#include <GL/glut.h>

GLint X1, Y1, X2, Y2;
const int screenWidth = 800;
const int screenHeight = 600;
char StrType[][10]={"Lines","Rectangle","Triangle"};
char StrColor[][10]={"Red","Green","Blue"};
char StrXY[20];
int Type;
int Color;
int lwidth;

void init (void);
void setPixel(int x, int y);
void myDisplay (void);
void myKeyboard (GLubyte key, GLint x, GLint y);
void myMouse(GLint button, GLint action, GLint x, int y);
void showText(int x,int y,char text[]);
void setColor(int Color);
void mySpKeyboard (GLint key, GLint x, GLint y);
void drawShape(int Type);
void myMotion (GLint x, GLint y);
void setLineWidth(int lwidth);
void myMouseMotion(GLint x, GLint y);

void main (int argc, char** argv){
	Type=1;
	Color=1;
	lwidth=1;
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 50);
	glutInitWindowSize (screenWidth, screenHeight);
	glutCreateWindow (
	"Example use mouse : left to draw point, right to clear");
	init( );
	glutDisplayFunc (myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpKeyboard);
	glutMouseFunc(myMouse);
	glutMotionFunc (myMotion);
	glutPassiveMotionFunc(myMouseMotion);
	glutMainLoop ( );
}
void init (void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glColor3f (0.0, 0.0, 1.0);

	glPointSize(4.0);

	glLineWidth(lwidth);

	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, screenWidth, 0.0, screenHeight);

}
void myDisplay (void) {
	glClear (GL_COLOR_BUFFER_BIT);
	setColor(Color);
	setLineWidth(lwidth);
	drawShape(Type);
	showText(0,screenHeight-20,"Type :");
	showText(40,screenHeight-20,StrType[Type-1]);
	showText(screenWidth-100,screenHeight-20,"Color :");
	showText(screenWidth-60,screenHeight-20,StrColor[Color-1]);
	showText(screenWidth-60,0,StrXY);
	glFlush ( );
}
void myMotion (GLint x, GLint y)
{
	X2 = x; Y2 = screenHeight - y;
	setPixel(X2, Y2);
	y = screenHeight - y;
	glutPostRedisplay();
}
void setPixel(int x, int y)
{
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}
void myKeyboard (GLubyte key, GLint x, GLint y){
	switch ( key )
	{

		case 'r': Color=1; // red color

		break;

		case 'g': Color=2;  // green color

		break;

		case 'b': Color=3;  // blue color

		break;
		case '1': lwidth=1;
		break;
	case '2':lwidth=2;
		break;
	case '3':  lwidth=3;
		break;
	}
	glutPostRedisplay();
}
void mySpKeyboard (GLint key, GLint x, GLint y){
	switch ( key ){

		case GLUT_KEY_F1: Type=1; // red color

		break;

		case GLUT_KEY_F2: Type=2; // green color

		break;

		case GLUT_KEY_F3: Type=3; // blue color

		break;

	}
	glutPostRedisplay();
}
void setColor(int Color){
	switch(Color){
	case 1: glColor3f(1.0,0.0,0.0);
		break;
	case  2:glColor3f(0.0,1.0,0.0);
		break;
	case 3:glColor3f(0.0,0.0,1.0);
		break;
	}
}
void drawShape(int Type){
	switch(Type){
	case 1:glBegin (GL_POINTS);
			glVertex2i ( X1, Y1);
			glVertex2i ( X2, Y2);
		glEnd ( );
		glBegin(GL_LINES);
				 glVertex2i(X1,Y1);
				 glVertex2i(X2,Y2);
				 glEnd();
				 glColor3f(0.0,0.0,0.0);
		setPixel( X1, Y1); 
		setPixel( X2, Y2);
		break;
	case 2:glBegin (GL_POINTS);
			glVertex2i ( X1, Y1);
			glVertex2i ( X1, Y2);
			glVertex2i ( X2, Y2);
			glVertex2i ( X2, Y1);
		glEnd ( );
		glBegin (GL_LINE_LOOP);
			glVertex2i ( X1, Y1);
			glVertex2i ( X1, Y2);
			glVertex2i ( X2, Y2);
			glVertex2i ( X2, Y1);
		glEnd();
		glColor3f(0.0,0.0,0.0);
		setPixel( X1, Y1); setPixel( X2, Y2);
		setPixel( X2, Y2); setPixel( X2, Y1);
		break;
	case 3:glBegin (GL_POINTS);
			glVertex2i ( X1, Y1);
			glVertex2i ( X2, Y2);
			glVertex2i ( X2, Y1);
		glEnd ( );
		glBegin (GL_LINE_LOOP);
			glVertex2i ( X1, Y1);
			glVertex2i ( X2, Y2);
			glVertex2i ( X2, Y1);
		glEnd();
		glColor3f(0.0,0.0,0.0);
		setPixel( X1, Y1); setPixel( X2, Y2);
		setPixel( X2, Y1);
		break;
	}
}
void showText(int x,int y,char text[]){
	glColor3f(0.0,0.0,0.0);
	glRasterPos2i(x,y);
	for(int n=0;text[n]!='\0';n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,text[n]);
}
void myMouse(GLint button, GLint action, GLint x, int y){
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		X1 = x; Y1 = screenHeight - y;
	}
}
void setLineWidth(int lwidth){
	switch(lwidth){
	case 1: glLineWidth(1.0);
		break;
	case 2: glLineWidth(2.0);
		break;
	case 3:  glLineWidth(3.0);
		break;
	}
}
void myMouseMotion(GLint x, GLint y){
	sprintf(StrXY, "(%d,%d)",x,y);
	glutPostRedisplay();
}