#include <GL/glut.h>

void drawArc(int h, int k, int x, int y) {
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex2f(x + h, y + k);
	glVertex2f(-x + h, y + k);
	glVertex2f(x + h, -y + k);
	glVertex2f(-x + h, -y + k);
	glVertex2f(y + h, x + k);
	glVertex2f(-y + h, x + k);
	glVertex2f(y + h, -x + k);
	glVertex2f(-y + h, -x + k);
	glEnd();
}

void drawCircle(int h, int k, int r) {
	int d = 1 - r, x = 0, y = r;
	while (y >= x) {
		drawArc(h, k, x, y);
		if (d < 0) {
			d += 2 * x + 3;
		} else {
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
}

void drawCylinder() {
	int xc = 100, yc = 100, r = 50;
	int n = 200;

	for (int i = 0; i < n; i += 3)
		drawCircle(xc, yc + i, r);
}

void drawRectangle(int x1, int x2, int y1, int y2) {
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1, y1);
	glVertex2i(x2, y1);
	glVertex2i(x2, y2);
	glVertex2i(x1, y2);
	glEnd();
}

void drawParallelepiped() {
	int x1 = 200, x2 = 400, y1 = 100, y2 = 300;
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

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	int id1 = glutCreateWindow("Cylinder");
	glutDisplayFunc(display1);
	myInit();

	int id2 = glutCreateWindow("Parallelepiped");
	glutDisplayFunc(display2);
	myInit();

	glutMainLoop();
}
