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
