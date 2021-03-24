#include<iostream>
using namespace std;
#include <GL\glut.h>

void init (void);
void display (void);
void putPixel(int x, int y);
void circleMidpoint(int xc,int yc,int r);
void plot(int xc,int yc,int x,int y);
void getvalue();


int xc,yc,r;
void getvalue(){
	cout<<"Enter Center Point (Xc,Yc) : ";
	cin>>xc>>yc;
	cout<<"Enter Radius : ";
	cin>>r;
}
void main(int argc, char **argv)
{
	getvalue();
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 150);
	glutInitWindowSize (800,600);
	glutCreateWindow (" OpenGL Program Assignment #2 : Circle ");
	init ( );
	glutDisplayFunc (display);
	glutMainLoop ( );
}
void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D ( 0.0, 800, 0.0, 600);
}
void display (void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 0.0, 0.0);
	glPointSize(1);
    circleMidpoint(xc,yc,r);//face
	glColor3f (1.0, 0.0, 0.0);
	glPointSize(1);
    circleMidpoint(xc+(r/2),yc*(2/3)+yc+(r/3),r/5);//right eye
	glColor3f (1.0, 0.0, 0.0);
	glPointSize(1);
    circleMidpoint(xc-(r/2),yc*(2/3)+yc+(r/3),r/5);//left eye
	glColor3f (1.0, 0.0, 0.0);
	glPointSize(1);
    circleMidpoint(xc,yc+(2/3)-(r/2),r/4);//mouth
	glFlush ( );
}
void putPixel(int x, int y) 
{
	glBegin( GL_POINTS);
		glVertex2i( x, y );
	glEnd();
}
void circleMidpoint(int xc,int yc,int r)
{
	int x,y,p;
	x=0;
	y=r;
	plot(xc,yc,x,y);
	p=1-r;
	while(x<=y)
	{
		if(p<0)
		{
			x++;
			p=p+(2*x)+1;
		}
		else 
		{
			x++;
			y--;
			p=p+(2*x)+1-(2*y);
		}
			plot(xc,yc,x,y);
	}
}
void plot(int xc,int yc,int x,int y)
{

	putPixel(xc+x,yc+y);
	putPixel(xc-x,yc+y);
	putPixel(xc+x,yc-y);
	putPixel(xc-x,yc-y);

	putPixel(xc+y,yc+x);
	putPixel(xc-y,yc+x);
	putPixel(xc+y,yc-x);
	putPixel(xc-y,yc-x);

}