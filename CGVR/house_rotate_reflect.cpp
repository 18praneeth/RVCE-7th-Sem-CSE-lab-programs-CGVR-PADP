#include <iostream>
#include <cmath>
#include <GL/glut.h>

using namespace std;

float m, c, t, xr, yr;

float house[11][2] = {
	{100, 100},
	{140, 100},
	{140, 150},
	{160, 150},
	{160, 100},
	{200, 100},
	{200, 200},
	{220, 200},
	{150, 300},
	{80, 200},
	{100, 200},
};
int n = 11;

void drawHouse() {
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < n; i++)
		glVertex2fv(house[i]);
	glEnd();
	glFlush();
}

void displayRot() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 0, 0);
	drawHouse();

	glPushMatrix();
	glTranslatef(xr, yr, 0);
	glRotatef(t, 0, 0, 1);
	glTranslatef(-xr, -yr, 0);

	glColor3f(0, 0, 1);
	drawHouse();
	glPopMatrix();

	glFlush();
}

void displayRef() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 0, 0);
	drawHouse();

	int x0 = 0, x1 = 400;
	int y0 = m * x0 + c, y1 = m * x1 + c;

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex2f(x0,y0);
	glVertex2f(x1,y1);
	glEnd();

	float r = atan(m) * (180/3.1415);
	glPushMatrix();
	glTranslatef(0, c, 0);
	glRotatef(r, 0, 0, 1);
	glScalef(1, -1, 1);
	glRotatef(-r, 0, 0, 1);
	glTranslatef(0, -c, 0);

	glColor3f(0, 0, 1);
	drawHouse();
	glPopMatrix();

	glFlush();
}

void myInit() {
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv) {
	int opt;
	cout << "Enter 1 for rotation and 2 for reflection\n";
	cin >> opt;
	if(opt == 1){
		cout << "Enter t, xr, yr\n";
		cin >> t >> xr >> yr;
	}
	if(opt == 2){
		cout << "Enter m, c\n";
		cin >> m >> c;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("House");

	if(opt == 1)
		glutDisplayFunc(displayRot);
	if(opt == 2)
		glutDisplayFunc(displayRef);
	myInit();
	glutMainLoop();
}
