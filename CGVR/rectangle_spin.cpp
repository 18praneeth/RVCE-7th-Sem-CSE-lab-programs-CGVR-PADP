#include <GL/glut.h>

int id1,id2;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(100, 100);
	glColor3f(0, 1, 0);
	glVertex2f(100, 400);
	glColor3f(0, 0, 1);
	glVertex2f(400, 400);
	glColor3f(1, 1, 0);
	glVertex2f(400, 100);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void idle() {
	glutSetWindow(id2);
	glTranslatef(250, 250, 0);
	glRotatef(.10, 0, 0, 1);
	glTranslatef(-250, -250, 0);
	glutPostRedisplay();
}

void myInit() {
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	id1 = glutCreateWindow("Rect 1");
	glutDisplayFunc(display);
	myInit();

	id2 = glutCreateWindow("Rect 2");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	myInit();

	glutMainLoop();
}
