#include<iostream>
using namespace std;
#include <GL\glut.h>

void init (void);
void display (void);
void putPixel(int x, int y);
void ellipseMidpoint(int xc,int yc,float rx,float ry);
void plot(int xc,int yc,int x,int y);
void getvalue();


int xc,yc,rx,ry;
void getvalue(){
	cout<<"Enter Center Point (Xc,Yc) : ";
	cin>>xc>>yc;
	cout<<"Enter Radius x : ";
	cin>>rx;
	cout<<"Enter Radius y : ";
	cin>>ry;
}
void main(int argc, char **argv)
{
	getvalue();
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 150);
	glutInitWindowSize (800,600);
	glutCreateWindow (" OpenGL Program Assignment #2 : Ellipse ");
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
    ellipseMidpoint(xc,yc,rx,ry);//face
	glColor3f (1.0, 0.0, 0.0);
	glPointSize(1);
    ellipseMidpoint(xc+(rx/2),yc+(2/3)+(ry/3),ry/6,rx/6);//right eye
	glColor3f (1.0, 0.0, 0.0);
	glPointSize(1);
    ellipseMidpoint(xc-(rx/2),yc+(2/3)+(ry/3),ry/6,rx/6);//left eye
	glColor3f (1.0, 0.0, 0.0);
	glPointSize(1);
    ellipseMidpoint(xc,yc+(2/3)-(ry/2),rx/4,ry/4);//mouth
	glFlush ( );
}
void putPixel(int x, int y) 
{
	glBegin( GL_POINTS);
		glVertex2i( x, y );
	glEnd();
}
void ellipseMidpoint(int xc,int yc,float rx,float ry)
{
	int x,y;
	float p1,p2;
	x=0;
	y=ry;
	plot(xc,yc,x,y);
	p1 = ry*ry-rx*rx*ry+1/4*rx*rx;
	//region 1
	while(2*ry*ry*x<=2*rx*rx*y){
		x++;
		if(p1<0){
			p1=p1+2*ry*ry*x+ry*ry;
		}
		else{
			y--;
			p1=p1+2*ry*ry*x-2*rx*rx*y-ry*ry;
		}
		plot(xc,yc,x,y);
	}
	//region 2
	p2 = ry*ry*(x+1/2)*(x+1/2)+rx*rx*(y-1)*(y-1)-rx*rx*ry*ry;
	while(y>0){
		y--;
		if(p2>0){
			p2 = p2-2*rx*rx*y+rx*rx;
		}
		else{
			x++;
			p2 = p2+2*ry*ry*x-2*rx*rx*y+rx*rx;
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
}