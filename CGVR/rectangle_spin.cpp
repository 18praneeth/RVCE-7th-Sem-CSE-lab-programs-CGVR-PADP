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