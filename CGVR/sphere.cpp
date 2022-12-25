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
