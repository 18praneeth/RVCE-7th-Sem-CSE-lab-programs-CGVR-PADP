#include <iostream>
#include <cmath>
#include <GL/glut.h>

using namespace std;

int xc, yc, r;

void draw8Pixel(int xc, int yc, int x, int y) {
	glColor3f(0, 1, 0);
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2f(xc + x, yc + y);
	glVertex2f(xc - x, yc + y);
	glVertex2f(xc + x, yc - y);
	glVertex2f(xc - x, yc - y);
	glVertex2f(xc + y, yc + x);
	glVertex2f(xc - y, yc + x);
	glVertex2f(xc + y, yc - x);
	glVertex2f(xc - y, yc - x);
	glEnd();
}

void drawCircle() {
	int d = 3 - 2 * r;
	int x = 0, y = r;
	while (x <= y) {
		draw8Pixel(xc, yc, x, y);
		x++;
		if (d < 0) {
			d += 4 * x + 6;
		} else {
			y--;
			d += 4 * (x - y) + 10;
		}
	}
	glFlush();
}
void mouse(int button, int state, int x, int y) {
	static bool flag = false;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (!flag) {
			xc = x - 250;
			yc = 250 - y;
			cout << "xc, yc : " << xc << " " << yc << " \n";
		} else {
			int xb = x - 250;
			int yb = 250 - y;
			r = hypot(xb - xc, yb - yc);
			cout << "xb, yb : " << xb << " " << yb << " \n";
			drawCircle();
		}
		flag = !flag;
	}
}

void display(){}

void myInit() {
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv) {
	int choice;
	cout << "Enter 1 for keyboard and 2 for mouse\n";
	cin >> choice;
	if (choice == 1) {
		cout << "Enter xc : ";
		cin >> xc;
		cout << "Enter yc : ";
		cin >> yc;
		cout << "Enter r : ";
		cin >> r;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Circle Drawing");

	if (choice == 2) {
		glutMouseFunc(mouse);
		glutDisplayFunc(display);
	} else {
		glutDisplayFunc(drawCircle);
	}
	myInit();
	glutMainLoop();
}
