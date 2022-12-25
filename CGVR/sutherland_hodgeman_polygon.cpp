#include<algorithm>
#include<GL/glut.h>

using namespace std;

float xmin=-100, ymin=-100, xmax=100, ymax=100;

struct Point {
	float x, y;
};

void drawPoly(Point p[], int n){
	glLineWidth(3);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	for(int i = 0; i < n; i++)
		glVertex2f(p[i].x, p[i].y);   
	glEnd();
}

enum Edge { LEFT, TOP, RIGHT, BOTTOM };

bool insideVer(Point p, int edge) {
	switch (Edge(edge)) {
	case LEFT:
		return p.x >= xmin;
	case RIGHT:
		return p.x <= xmax;
	case BOTTOM:
		return p.y >= ymin;
	case TOP:
		return p.y <= ymax;
	}
	return false;
}

Point getInterSect(Point s, Point p, int edge){
	float m = (p.y-s.y) / (p.x-s.x);
	switch (Edge(edge)) {
	case LEFT:
		return { xmin, (xmin-s.x) * m + s.y };
	case RIGHT:
		return { xmax, (xmax-s.x) * m + s.y };
	case BOTTOM:
		return { (ymin-s.y) / m + s.x, ymin };
	case TOP:
		return { (ymax-s.y) / m + s.x, ymax };
	}
	return {};
}

void sutherlandHodgman(Point pts[], int n){
	Point inp[10], outp[10];
	int inn, outn;

	copy(pts, pts + n, inp);
	inn = n;
	for(int i = 0; i < 4; i++) {
		outn = 0;
		Point s = inp[inn-1];

		for(int j = 0; j < inn; j++) {		   
			Point p = inp[j];

			if(insideVer(p, i)) {
				if(insideVer(s, i)) {
					outp[outn++] = p;
				} else {
					outp[outn++] = getInterSect(s, p, i);
					outp[outn++] = p;
				}
			} else {
				if(insideVer(s, i)) {
					outp[outn++] = getInterSect(s, p, i);
				}
			}
			s = p;
		}
		copy(outp, outp + outn, inp);
		inn = outn;
	}

	glColor3f(0, 0, 1);
	glPointSize(2);
	drawPoly(outp, outn);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	Point inp[] = {
		{ -120, -120 }, { 160, 80 },
		{ 60, 30 }, { 90, 120 },
	};

	glColor3f(1, 0, 0);
	glPointSize(2);
	drawPoly(inp, 4);

	glColor3f(0, 1, 0);
	glPointSize(1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glVertex2f(xmin, ymax);
	glEnd();

	sutherlandHodgman(inp, 4);

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
	glutCreateWindow("Sutherland Hodgman Polygon Clipping");

	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
}
