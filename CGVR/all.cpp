// Bresenham line
#include<iostream>
#include<cmath>
#include<GL/glut.h>

using namespace std;

int xc1, xc2, yc1, yc2;

void drawPixel(int x, int y) {
	glColor3f(0, 0, 1);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void drawLine() {
	int dx = abs(xc2 - xc1), dy = abs(yc2 - yc1);

	int incx = xc1 <= xc2 ? 1 : -1;
	int incy = yc1 <= yc2 ? 1 : -1;

	int x = xc1, y = yc1;
	if (dx > dy) {
		int p = 2 * dy - dx;
		int inc1 = 2 * (dy - dx);
		int inc2 = 2 * dy;
		for (int i = 0; i <= dx; i++) {
			drawPixel(x, y);
			if (p > 0) {
				y += incy;
				p += inc1;
			} else {
				p += inc2;
			}
			x += incx;
		}
	} else {
		int p = 2 * dx - dy;
		int inc1 = 2 * (dx - dy);
		int inc2 = 2 * dx;
		for (int i = 0; i <= dy; i++) {
			drawPixel(x, y);
			if (p > 0) {
				x += incx;
				p += inc1;
			} else {
				p += inc2;
			}
			y += incy;
		}
	}
	glFlush();
}

void mouse(int button, int state, int x, int y) {
	static bool flag = false;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (!flag) {
			xc1 = x - 250;
			yc1 = 250 - y;
			cout << "x1, y1 : " << xc1 << " " << yc1 << " \n";
		} else {
			xc2 = x - 250;
			yc2 = 250 - y;
			cout << "x2, y2 : " << xc2 << " " << yc2 << " \n";
			drawLine();
		}
		flag = !flag;
	}
}

void display() {}

void myInit() {
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv) {
	int choice;
	cout << "Enter 1 for keyboard and 2 for mouse \n";
	cin >> choice;
	if (choice == 1) {
		cout << "Enter x1 : ";
		cin >> xc1;
		cout << "Enter y1 : ";
		cin >> yc1;
		cout << "Enter x2 : ";
		cin >> xc2;
		cout << "Enter y2 : ";
		cin >> yc2;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Line Drawing");

	if (choice == 2) {
		glutMouseFunc(mouse);
		glutDisplayFunc(display);
	} else {
		glutDisplayFunc(drawLine);
	}
	myInit();
	glutMainLoop();
}


/// -----------------------------------
// bresenhman circle

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
		if (d < 0) {
			d += 4 * x + 6;
		} else {
			d += 4 * (x - y) + 10;
			y--;
		}
		x++;
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


// -------------------------------------------------------------

// cohen_sutherland_line
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

// ==================================================================================

// color_cube_spin
#include <GL/glut.h>

float vertices[8][3] = {
	-1, -1, -1,
	1, -1, -1,
	1, 1, -1,
	-1, 1, -1,
	-1, 1, 1,
	1, 1, 1,
	1, -1, 1,
	-1, -1, 1
};

float colors[8][3] = {
	0, 0, 0,
	0, 0, 1,
	0, 1, 0,
	0, 1, 1,
	1, 0, 0,
	1, 0, 1,
	1, 1, 0,
	1, 1, 1,
};

GLubyte elementIndices[24] = {
	0, 1, 2, 3,
	0, 3, 4, 7,
	0, 7, 6, 1,
	3, 4, 5, 2,
	2, 5, 6, 1,
	7, 4, 5, 6,
};

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, elementIndices);

	glFlush();
	glutSwapBuffers();
}

void idle() {
	glRotatef(.1, 1, 0, 0);
	glRotatef(.2, 0, 1, 0);
	glRotatef(.3, 0, 0, 1);
	glutPostRedisplay();
}

void reshape(int w, int h){
	glViewport(0, 0, w, h);
}

void myInit() {
	glEnable(GL_DEPTH_TEST);
	gluPerspective(80, 1, .1, 10);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0, 0, -6);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Cube Spin");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 3*sizeof(float), vertices);
	glColorPointer(3, GL_FLOAT, 3*sizeof(float), colors);

	myInit();
	glutMainLoop();
}

/// =========================================================================------------------------------------------==-=
// cylinder_parallelpiped

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

/// house_rotate
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

//---------------------------------------------------------------------
// liang_barsky_line


#include<algorithm>
#include<GL/glut.h>

using namespace std;

float xmin=-100, ymin=-100, xmax=100, ymax=100;

bool cliptest(float p, float q, float &t1, float &t2) {
	if(p == 0.0) {
		if(q < 0.0)
			return false;
	} else {
		float r = q / p;
 		if(p < 0.0) {
			t1 = max(t1, r);
			if(r > t2)
				return false;
		} else {
			t2 = min(t2, r);
			if(r < t1)
				return false;
		}
	}
	return true;
}

void liangBarsky(float x0, float y0, float x1, float y1) {
	float dx = x1-x0, dy = y1-y0, t1 = 0.0, t2 = 1.0;

	if(cliptest(-dx, x0-xmin, t1, t2) &&
		cliptest(dx, xmax-x0, t1, t2) &&
		cliptest(-dy, y0-ymin, t1, t2) &&
    	cliptest(dy, ymax-y0, t1, t2)) {
		
		if(t2 < 1.0) {
			x1 = x0 + t2 * dx;
			y1 = y0 + t2 * dy;
		}
		if(t1 > 0.0) {
			x0 = x0 + t1 * dx;
			y0 = y0 + t1 * dy;
		}

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

	liangBarsky(x0, y0, x1, y1);
	liangBarsky(x2, y2, x3, y3);

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
	glutCreateWindow("Liang Barsky Line Clipping");

	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
}


// -------------------------------------------------------------------------------
// rectangle_spin

#include <GL/glut.h>

int spinWin;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(-150, -150);
	glColor3f(0, 1, 0);
	glVertex2f(-150, 150);
	glColor3f(0, 0, 1);
	glVertex2f(150, 150);
	glColor3f(1, 1, 0);
	glVertex2f(150, -150);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void idle() {
	glutSetWindow(spinWin);
	glRotatef(.10, 0, 0, 1);
	glutPostRedisplay();
}

void myInit() {
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);

	glutInitWindowPosition(100, 100);
	glutCreateWindow("Rect 1");
	glutDisplayFunc(display);
	myInit();

	glutInitWindowPosition(600, 100);
	spinWin = glutCreateWindow("Rect 2");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	myInit();

	glutMainLoop();
}

/// ------------------------------------------------------------------------------------------------------
// scanline areafil

#include <iostream>
#include <algorithm>
// #include <unistd.h>
// #include <windows.h>
#include <GL/glut.h>

using namespace std;

int n;
float x[100], y[100];

void drawLine(float x1, float y1, float x2, float y2) {
	// sleep(1); // uni
	// Sleep(1000); // win
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glFlush();
}

void edgeDetect(float x1, float y1, float x2, float y2, int scanline, int intx[], int &count) {
	if (y2 < y1) {
		swap(x1, x2);
		swap(y1, y2);
	}
	if (scanline > y1 && scanline < y2) {
		float m = (y2-y1) / (x2-x1);
		intx[count++] = x1 + (scanline - y1) / m;
	}
}

void scanFill(float x[], float y[]) {
	for (int s = 0; s <= 500; s++) {
		int intx[10], count = 0;
		for (int i = 0; i < n; i++) {
			int j = (i + 1) % n;
			edgeDetect(x[i], y[i], x[j], y[j], s, intx, count);
		}
		sort(intx, intx + count);
		for (int i = 0; i < count; i += 2)
			drawLine(intx[i], s, intx[i + 1], s);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 1, 0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
		glVertex2f(x[i], y[i]);
	glEnd();
	glFlush();
	scanFill(x, y);
}

void myInit() {
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv) {
	cout << "Enter the number of sides : ";
	cin >> n;
	cout << "Enter the coordinates of vertices : \n";
	for (int i = 0; i < n; i++)
		cin >> x[i] >> y[i];
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Scanline Areafill");

	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
}

// ---------------------------------------
// sierpinski gasket

#include<iostream>
#include<GL/glut.h>

using namespace std;

typedef GLfloat point[3];

int iter;
point tetra[4]={{0,0,250},{0,250,-250},{250,-250,-250},{-250,-250,-250}};

void drawTriangle(point a, point b, point c){
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}

void drawTetrahedron(point a, point b, point c, point d){
	glColor3f(1, 0, 0);
	drawTriangle(a, b, c);
	glColor3f(0, 1, 0);
	drawTriangle(a, b, d);
	glColor3f(0, 0, 1);
	drawTriangle(a, c, d);
	glColor3f(1, 1, 0);
	drawTriangle(b, c, d);
}

void divideTetrahedron(point a, point b, point c, point d, int iter){
	if (iter > 0){
		point ab, ac, ad, bc, bd, cd;
		for(int j = 0; j < 3; j++){
			ab[j] = (a[j] + b[j]) / 2;
			ac[j] = (a[j] + c[j]) / 2;
			ad[j] = (a[j] + d[j]) / 2;
			bc[j] = (b[j] + c[j]) / 2;
			bd[j] = (b[j] + d[j]) / 2;
			cd[j] = (c[j] + d[j]) / 2;

		}
		divideTetrahedron(a, ab, ac, ad, iter-1);
		divideTetrahedron(ab, b, bc, bd, iter-1);
		divideTetrahedron(ac, bc, c, cd, iter-1);
		divideTetrahedron(ad, bd, cd, d, iter-1);
	} else {
		drawTetrahedron(a,b,c,d);
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	divideTetrahedron(tetra[0], tetra[1], tetra[2], tetra[3], iter);
	glEnd();
	glFlush();
}

void myInit(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);
	glOrtho(-250, 250, -250, 250, -250, 250);
}

int main(int argc, char **argv){
	cout << "Ënter the number of subdivisions:";
	cin >> iter;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sierpenski Gasket");

	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
}


///-----------------------------------------------------------
// sphere.cpp

#include<cmath>
#include<GL/glut.h>

using namespace std;

void sphere() {
	double c = 3.142 / 180;
	float x, y, z;

	glColor3f(0, 0, 1);
	for (int phi = -80; phi < 80; phi += 10) {
		float phir = c * phi;
		float phir2 = c * (phi + 10);

		glBegin(GL_QUAD_STRIP);
		for (int theta = -180; theta <= 180; theta += 10) {
			float thetar = c * theta;

			x = sin(thetar) * cos(phir);
			y = cos(thetar) * cos(phir);
			z = sin(phir);
			glVertex3f(x, y, z);

			x = sin(thetar) * cos(phir2);
			y = cos(thetar) * cos(phir2);
			z = sin(phir2);
			glVertex3f(x, y, z);
		}
		glEnd();
	}

	glColor3f(1, 0, 0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 1);
	float c80 = c * 80;
	for (int theta = -180; theta <= 180; theta += 10) {
		float thetar = c * theta;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		z = sin(c80);
		glVertex3d(x, y, z);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0, 0, -1);
	for (int theta = -180.0; theta <= 180.0; theta += 10.0) {
		float thetar = c * theta;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		z = -sin(c80);
		glVertex3d(x, y, z);
	}
	glEnd();

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -1);
	glRotatef(60.0, 1.0, 1.0, 0.0);

	sphere();

	glFlush();
}

void myInit() {
	glClearColor(1, 1, 1, 1);
	glOrtho(-1, 1, -1, 1, -1, 1);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sphere Display");

	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
}


// suther polygon cliping
//-----------------------------------------------

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
