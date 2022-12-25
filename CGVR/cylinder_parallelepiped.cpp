#include<cmath>
#include<GL/glut.h>

void drawCircle(int xc, int yc, int r){
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	for (float t = 0; t < 2*M_PI; t += .01) {
		int x = xc + r * cos(t);
		int y = yc + r * sin(t);
		glVertex2f(x, y);
	}
	glEnd();
}

void drawCylinder(){
	int xc = 200, yc = 200, r = 50;
	int n = 200;
	for(int i = 0; i < n; i += 3)
		drawCircle(xc, yc + i, r);
}

void drawRectangle(int x1, int x2, int y1, int y2) {
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
}

void drawParallelepiped() {
	int x1 = 100, x2 = 300, y1 = 100, y2 = 300;
	int n = 100;
	for (int i = 0; i < n; i += 2)
		drawRectangle(x1 + i, x2 + i, y1 + i, y2 + i);
}

void display1() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawCylinder();
	glFlush();
}

void display2() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawParallelepiped();
	glFlush();
}

void myInit() {
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 500, 0, 500);
}

int main(int argc,char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Cylinder");
	glutDisplayFunc(display1);
	myInit();

	glutCreateWindow("Parallelepiped");
	glutDisplayFunc(display2);
	myInit();

	glutMainLoop();
}