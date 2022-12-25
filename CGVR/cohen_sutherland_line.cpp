#include<GL/glut.h>

typedef int outcode;

float xmin=-100, ymin=-100, xmax=100, ymax=100;

const int LEFT = 8;
const int RIGHT = 4;
const int BOTTOM = 2;
const int TOP = 1;

outcode computeOutcode(float x, float y) {
	outcode code = 0;
	if(y > ymax)
		code |= TOP;
	else if(y < ymin) 
		code |= BOTTOM;
	if(x > xmax)
		code |= RIGHT;
	else if(x < xmin)
		code |= LEFT;
	return code;
}

void cohenSutherland(float x0, float y0, float x1, float y1) {
	outcode out0 = computeOutcode(x0,y0);
	outcode out1 = computeOutcode(x1,y1);

	bool accept = false;
	do {
		if(!(out0 | out1)) {
			accept = true;
			break;
		} else if(out0 & out1) {
			break;
		} else {
			float x, y;
			float m = (y1-y0) / (x1-x0);
			outcode o = out0 ? out0 : out1;
			if(o & TOP) {
				x = x0 + (ymax-y0) / m;
				y = ymax;
			} else if(o & BOTTOM) {
				x = x0 + (ymin-y0) / m;
				y = ymin;
			} else if(o & RIGHT) {
				y = y0 + (xmax-x0) * m;
				x = xmax;
			} else if(o & LEFT) {
				y = y0 + (xmin-x0) * m;
				x = xmin;
			}

			if(o == out0) {
				x0 = x;
				y0 = y;
				out0 = computeOutcode(x0, y0);
			} else {
				x1 = x;
				y1 = y;
				out1 = computeOutcode(x1, y1);
			}
		}
	} while(true);

	if(accept) {
		glColor3f(0, 0, 1);
		glPointSize(2);
		glBegin(GL_LINES);
		glVertex2f(x0, y0);
		glVertex2f(x1, y1);
		glEnd();
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	float x0 = -120, y0 = -120, x1 = 160, y1 = 80;
	float x2 = 60, y2 = 30, x3 = 90, y3 = 120;
	
	glColor3f(1, 0, 0);
	glPointSize(2);
	glBegin(GL_LINES);
	glVertex2f(x0, y0);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEnd();

	glColor3f(0, 1, 0);
	glPointSize(1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glVertex2f(xmin, ymax);
	glEnd();

	cohenSutherland(x0, y0, x1, y1);
	cohenSutherland(x2, y2, x3, y3);

	glFlush();
}

void myInit() {
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Cohen Sutherland Line Clipping");

	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
}
