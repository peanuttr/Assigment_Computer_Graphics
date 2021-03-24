#include<iostream>
#include<time.h>
using namespace std;
#include<GL/glut.h>

class Rectangle{
public:
	int x,y,size,speedX,speedY,color;
	bool show;
};

void init(void);
void myDisplay(void);
void myKeyboard(GLubyte key,GLint x,GLint Y);
void showText(int x, int y,char text[]);
void playAnimate();
void setupRectangle();
void moveRec(int value);
void showText1(int x,int y,char text[]);


const int MAX_RECTANGLE = 5;
Rectangle rec[MAX_RECTANGLE];

const int ScreenWidth = 800;
const int ScreenHeight = 600;
int Status = 0;

void main(int argc,char** argv){
	setupRectangle();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(ScreenWidth,ScreenHeight);
	glutCreateWindow("Animation");
	init();
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutMainLoop();
}

void init(){
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,ScreenWidth,0.0,ScreenHeight);
}
void myDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT);
	if(Status==0){
		playAnimate();
		glColor3f(0.0,0.0,0.0);
		showText(300,0,"Stop Animation");
	}
	else if(Status==1){
		playAnimate();
		glColor3f(0.0,0.0,0.0);
		showText(300,0,"Play Animation");
	}
	glFlush();
}
void playAnimate(){
	for(int n=0;n<MAX_RECTANGLE;n++){
			if(rec[n].color==1){
				glColor3f(1.0,0.0,0.0);
				glRecti(rec[n].x,rec[n].y,rec[n].x+rec[n].size,rec[n].y+rec[n].size);
			}
			else if(rec[n].color==2){
				glColor3f(0.0,1.0,0.0);
				glRecti(rec[n].x,rec[n].y,rec[n].x+rec[n].size,rec[n].y+rec[n].size);
			}
			else if(rec[n].color==3){
				glColor3f(0.0,0.0,1.0);
				glRecti(rec[n].x,rec[n].y,rec[n].x+rec[n].size,rec[n].y+rec[n].size);
			}
			else if(rec[n].color==4){
				glColor3f(0.0,0.0,0.0);
				glRecti(rec[n].x,rec[n].y,rec[n].x+rec[n].size,rec[n].y+rec[n].size);
			}
			
	}
}
void showText(int x,int y,char text[]){
	glRasterPos2i(x,y);
	for(int n=0;text[n]!='\0';n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,text[n]);
}
void myKeyboard(GLubyte key,GLint x,GLint Y){
	key = toupper(key);
	if(key == 'P' &&Status==0){
		Status =1;
		glutTimerFunc(30,moveRec,30);
	}
	else if(key =='S'&&Status==1)Status=0;
	glutPostRedisplay();
}
void setupRectangle(){
	for(int n =0;n<MAX_RECTANGLE;n++){
		rec[n].x=rand()%700+50;
		rec[n].y=rand()%500+50;
		rec[n].size=rand()%30+30;
		rec[n].speedX=1+rand()%5;
		rec[n].speedY=1+rand()%5;
		rec[n].color=1+rand()%4;
	}
}
void moveRec(int value){
	for(int n=0;n<MAX_RECTANGLE;n++){
			rec[n].x+=rec[n].speedX;
			if(rec[n].x<=0 || rec[n].x>ScreenWidth-rec[n].size)rec[n].speedX=-rec[n].speedX;
			rec[n].y+=rec[n].speedY;
			if(rec[n].y<=0 || rec[n].y>ScreenHeight-rec[n].size)rec[n].speedY=-rec[n].speedY;
	}
	glutPostRedisplay();
	if(Status==1)glutTimerFunc(value,moveRec,value);
}