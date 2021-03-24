#include<iostream>
using namespace std;
#include<GL\glut.h>
int round(const float a){
	return (int(a+0.5));
}
void putPixel(int x , int y)
{
	glBegin(GL_POINTS);
	     glVertex2i(x , y);
	glEnd();
}

void lineSimple (int X1 , int Y1 , int X2 , int Y2)
{
	int dx = X2 - X1;
	int dy = Y2 - Y1;
	float m = (float) dy / dx;
	if(m <= 1)
	{
	float y = Y1;
	float x = X1;
	for(int i = 0 ; i < dx ; i++)
	{
		float b = Y1 - (m * X1);
		x++;
		y = (m * x) + b;
		putPixel(x,round(y));
	}
	}
	else if(m>1)
	{
		float b = X1 - (Y1/m);
	float y = Y1;
	float x = X1;
	for(int i = 0 ; i < dy ; i++)
	{
		y++;
		x = (y / m) + b;
		putPixel(round(x),y);
	}
	}
}
void lineDDA (int X1 , int Y1 , int X2 , int Y2)
{
	int dx = X2 - X1,dy = Y2 - Y1, steps, k;
	float xIncrement, yIncrement, x = X1 , y = Y1;

	(abs(dx) > abs(dy))? steps = abs(dx):steps = abs(dy);
	xIncrement = (float)dx/(float)steps;
	yIncrement = (float)dy/(float)steps;
	putPixel(round(x),round(y));
	for(k = 0;k < steps ; k++)
	{
		x+= xIncrement;
		y+= yIncrement;
		putPixel(round(x),round(y));
	}
}

void lineBres(int X1 , int Y1 , int X2 , int Y2)
{
	int x3 = abs(X2 - X1),y3 = abs(Y2 - Y1);
	int p = 2 * y3 - x3;
	int twoDy = 2 * y3, twoDyMinusDx = 2 * (y3 - x3);
	int x,y;
	if (X1 > X2){x = X2;y = Y2;X2 = X1;}
	else{x = X1;y = Y1;}
	putPixel(x,y);
	while (x < X2)
	{
		x++;
		if (p < 0)p+=twoDy;
		else {y++; p += twoDyMinusDx;}
		putPixel(x,y);
	}
}
