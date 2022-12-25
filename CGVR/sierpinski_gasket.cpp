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
