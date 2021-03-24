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
void myMouse(GLint button,GLint action,GLint x, GLint y);
void showText(int x, int y,char text[]);
void showMenu();
void playGame();
void exitGame();
void setupRectangle();
int checkRectangle(int x,int y);
void countTime(int value);
void moveRec(int value);
void drawShape(Rectangle r);
void Timeout();
void won();
void specialKey (int key, int x, int y);
void showText1(int x,int y,char text[]);

#define SPACE 32

const int MAX_RECTANGLE = 10;
Rectangle rec[MAX_RECTANGLE];

const int ScreenWidth = 800;
const int ScreenHeight = 600;
int Status = 0;
int Score = 0;
int Time = 0;
char strScore[15];
char strTime[15];

void main(int argc,char** argv){
	srand(time(0));
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(ScreenWidth,ScreenHeight);
	glutCreateWindow("Game");
	init();
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(specialKey);
	glutMouseFunc(myMouse);
	glutMainLoop();
}

void init(){
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,ScreenWidth,0.0,ScreenHeight);
}
void myDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT);
	if(Status==0)showMenu();
	else if(Status==1)playGame();
	else if(Status==2)exitGame();
	glFlush();
}
void showMenu(){
	glColor3f(0.0,0.0,0.0);
	showText(300,350,"F1 - Play Game");
	showText(300,300,"F2 - Stop Game");
	showText(300,250,"F10 - Exit Game");
}
void playGame(){
	for(int n=0;n<MAX_RECTANGLE;n++){
		if(rec[n].show)
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
	sprintf(strScore,"Score : %d",Score);
	sprintf(strTime,"Time : %d",Time);
	showText1(0,ScreenHeight-20,strTime);
	showText1(ScreenWidth-90,ScreenHeight-20,strScore);
	if(Score==MAX_RECTANGLE)won();
	if(Time>=30)Timeout();
}
void exitGame(){
	cout<<"Exit Game\n";
	exit(0);
}
void showText(int x,int y,char text[]){
	glRasterPos2i(x,y);
	for(int n=0;text[n]!='\0';n++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text[n]);
}
void myKeyboard(GLubyte key,GLint x,GLint Y){
	if(key == SPACE)Status=0;showMenu();
	glutPostRedisplay();
}
void myMouse(GLint button,GLint action,GLint x, GLint y){
	if(Status==1){
		if(button==GLUT_LEFT_BUTTON &&action==GLUT_DOWN){
			y=ScreenHeight-y;
			cout<<"Point of Click : "<<x<<", "<<y<<endl;
			int pos =checkRectangle(x,y);
			if(pos >-1){
				rec[pos].show=!rec[pos].show;
				Score++;
			}
			glutPostRedisplay();
		}
	}
}
void setupRectangle(){
	for(int n =0;n<MAX_RECTANGLE;n++){
		rec[n].x=rand()%700+50;
		rec[n].y=rand()%500+50;
		rec[n].size=rand()%30+30;
		rec[n].show=true;
		rec[n].speedX=1+rand()%5;
		rec[n].speedY=1+rand()%5;
		rec[n].color=1+rand()%4;
	}
}
int checkRectangle(int x,int y){
	for(int n=0;n<MAX_RECTANGLE;n++){
		if(rec[n].show)
			if(x>=rec[n].x&&x<=rec[n].x+rec[n].size)
				if(y>=rec[n].y&&y<=rec[n].y+rec[n].size){
					return n;
			}
	}
	return -1;
}
void countTime(int value){
	Time++;
	glutPostRedisplay();
	if(Status==1)glutTimerFunc(value,countTime,value);
}
void moveRec(int value){
	for(int n=0;n<MAX_RECTANGLE;n++){
		if(rec[n].show){
			rec[n].x+=rec[n].speedX;
			if(rec[n].x<=0 || rec[n].x>ScreenWidth-rec[n].size)rec[n].speedX=-rec[n].speedX;
			rec[n].y+=rec[n].speedY;
			if(rec[n].y<=0 || rec[n].y>ScreenHeight-rec[n].size)rec[n].speedY=-rec[n].speedY;
		}
	}
	glutPostRedisplay();
	if(Status==1)glutTimerFunc(value,moveRec,value);
}
void Timeout(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,1.0);
	showText(300,350,"Time out!");
	showText(200,300,"You Lose,press space key to menu");
}
void won(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,1.0);
	showText(300,350,strScore);
	showText(200,300,"You Win,press space key to menu");
}
void specialKey (int key, int x, int y){
if (key == GLUT_KEY_F10 &&Status==0)Status=2;
else if (key == GLUT_KEY_F1 &&Status==0){
	Status =1;
	setupRectangle();
	glutTimerFunc(1000,countTime,1000);
	glutTimerFunc(30,moveRec,30);
}
else if (key == GLUT_KEY_F2 &&Status==1)Status=0;Score=0,Time=0;
glutPostRedisplay();

}
void showText1(int x,int y,char text[]){
	glRasterPos2i(x,y);
	for(int n=0;text[n]!='\0';n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,text[n]);
}