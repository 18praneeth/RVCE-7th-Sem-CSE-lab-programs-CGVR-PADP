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
	if (scanline > y1 && scanline < y2)
		intx[count++] = x1 + (scanline - y1) * (x2 - x1) / (y2 - y1);
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
