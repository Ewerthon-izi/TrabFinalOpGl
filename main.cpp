#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#define SENS_ROT 5.0
#define SENS_OBS 10.0
#define SENS_TRANSL 10.0

GLint b = 300;
float counter = 600.0;

GLfloat distance = 50;
GLfloat azimuth = 0;
GLfloat incidence = 0;
GLfloat twist = 0;
GLfloat angle, fAspect;

GLfloat rotX, rotY, rotX_ini, rotY_ini, mov, jump, movDog, rotateDogY, rotateDogX;

GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;

int x_ini, y_ini, mouse_button;

void polarView() {
	glTranslatef(0.0, 0.0, -distance);
	glRotatef(-twist, 0.0, 0.0, 1.0);
	glRotatef(-incidence, 1.0, 0.0, 0.0);
	glRotatef(-azimuth, 0.0, 0.0, 1.0);
}

void DefineIluminacao() {
	GLfloat luzAmbiente[4] = {0.2, 0.2, 0.2, 1.0};
	GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0}; // "cor"
	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho"
	GLfloat posicaoLuz[4] = {20.0, 150.0, 50.0, 1.0};

	GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};
	GLint especMaterial = 60;

	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
}

void PosicionaObservador() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DefineIluminacao();
	glTranslatef(-obsX, -obsY, -obsZ);
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
}

void EspecificaParametrosVisualizacao() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, fAspect, 0.5, 500);
	PosicionaObservador();
}

void TeclasEspeciais(int tecla, int x, int y) {
	switch (tecla) {

	case GLUT_KEY_HOME:
		if (angle >= 10) angle -= 5;
		break;

	case GLUT_KEY_END:
		if (angle <= 150) angle += 5;
		break;
	
	case GLUT_KEY_LEFT:
		mov += 1;
		break;
	case GLUT_KEY_RIGHT:
		mov -= 1;
		break;
		
	case GLUT_KEY_UP:	
		if(jump <= 10)
			jump += 10;	
		break;
	case GLUT_KEY_DOWN:	
		if(jump >= 1.5)
			jump -= 10;
		break;
	case GLUT_KEY_F2:
		movDog += 1;
		break;

	case GLUT_KEY_F1:
		movDog -= 1;
		break;
	case GLUT_KEY_F3:
		rotateDogY += 10;
		break;
	case GLUT_KEY_F4:
		rotateDogX += 10;
		break;
	}
	
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void myKeyboard(unsigned char c, int x, int y) {
	switch (c) {
	case 27: // ESC em ASCII
		exit(0);
		break;
	case 'w':
		incidence += 2;
		break;
	case 's':
		incidence -= 2;
		break;
	case 'z':
		distance++;
		break;
	case 'x':
		distance--;
		break;
	case 'd':
		azimuth += 5;
		break;
	case 'a':
		azimuth -= 5;
		break;
	case 65:
		rotateDogY += 180;
		break;
	case 71:
		rotateDogY -= 180;
		break;
	case 'p':
		exit(0);
		break;
	}
}

void GerenciaMouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		mouse_button = button;
	}

	else mouse_button = -1;
}

void GerenciaMovim(int x, int y) {
	if (mouse_button == GLUT_LEFT_BUTTON) {
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		rotY = rotY_ini - deltax / SENS_ROT;
		rotX = rotX_ini - deltay / SENS_ROT;
	} else if (mouse_button == GLUT_RIGHT_BUTTON) {
		int deltaz = y_ini - y;
		obsZ = obsZ_ini + deltaz / SENS_OBS;
	} else if (mouse_button == GLUT_MIDDLE_BUTTON) {
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		obsX = obsX_ini + deltax / SENS_TRANSL;
		obsY = obsY_ini - deltay / SENS_TRANSL;
	}

	PosicionaObservador();
	glutPostRedisplay();
}

void Reshape(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	EspecificaParametrosVisualizacao();
}

void display() {
	const double a = glutGet(GLUT_ELAPSED_TIME) / 10;
	GLfloat yellow[4] = {1, 1, 0, 1};

	/* Limpa todos os pixels da tela */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DefineIluminacao();

	glPushMatrix(); // ground
		glTranslatef(0, -510, 0);
		glColor3d(0, 0.5, 0);
		glutSolidCube(1000);
	glPopMatrix(); // end of ground

	glPushMatrix(); // sun
		glTranslatef(120, 120,mov + (-50));
		glColor3d(1, 1, 0.2);
		glutSolidSphere(25, 100, 100);
	glPopMatrix(); // end of sun
	
	glPushMatrix(); // cloud
		glTranslatef(60, 120, 0);
		glColor3d(1, 1, 1);
		glutSolidSphere(15, 50, 100);
		glTranslatef(10, 0, 10);
		glutSolidSphere(15, 50, 100);
		glTranslatef(0, 10, -5);
		glutSolidSphere(15, 50, 100);
		glTranslatef(-20, 0, -20);
		glutSolidSphere(15, 50, 100);
		glTranslatef(0, 10, 5);
		glutSolidSphere(15, 50, 100);
	glPopMatrix(); // end cloud
	
	//colocar uma imagem dps
	glPushMatrix(); // street sign
		glTranslatef(40, -15, 20);
		glRotatef(90, -1, 0, 0);
		glColor3d(0.5, 0.5, 0.5);
		glutSolidCylinder(3, 23, 100, 20);
		glRotatef(-90, 1, 0, 0);
		glBegin(GL_POLYGON);
        	glColor3f(1, 1, 0);
        	glVertex3f(-5,-35.0f,-25);
        	glVertex3f(-5,-35.0f,25);  
       		glVertex3f(5,-20.0f,25);
			glVertex3f(5,-20.0f,-25);
		
    	glEnd();

	glPopMatrix(); // end of street sign 
	//garbage truck
	glPushMatrix();
		glTranslatef(120, 0.5, mov +0);
		//truck cabin
		glColor3f(1, 1, 1);
		glutSolidCube(20);
		glTranslatef(0, 2, 20);
		glColor3f(0, 1, 0);
		//garbage cabin
		glutSolidCube(30);
		glBegin(GL_POLYGON);
        	glColor3f(0, 1, 0);
        	glVertex3f(-15.0f,15.0f,15.0f);
        	glVertex3f(15.0f,15.0f,15.0f);  
       	glVertex3f(15,-15.0f,30.0f);
		glVertex3f(-15,-15.0f,30.0f);
		glVertex3f(-15,15.0f,15.0f);
	glEnd();
	//wheels
	glPushMatrix();	
    		glColor3f(0,0,0);
		glRotatef(90,0,90,0);
		glTranslatef(25,-8,13);
		glutSolidTorus(3,3,10,30);
    	glPopMatrix();
    	glPushMatrix();	
    		glColor3f(1,1,1);
		glRotatef(3, 0,30,0);
		glTranslatef(17,-8,0);
		glutSolidCylinder(1.5,10,8,10);
    	glPopMatrix();
    	glPushMatrix();
    		glColor3f(0,0,0);	
		glTranslatef(-12,-8,-26);
		glRotatef(90,0,90,0);
		glutSolidTorus(3,3,10,30);
    	glPopMatrix();
    	glPushMatrix();	
    		glColor3f(1,1,1);
		glTranslatef(-14,-8,-31);
		glutSolidCylinder(1.5,10,8,10);
    	glPopMatrix();
    	glPushMatrix();
    		glColor3f(0,0,0);	
		glRotatef(90,0,90,0);
		glTranslatef(-5,-8,15);
		glutSolidTorus(3,3,10,30);
    	glPopMatrix();
    	glPushMatrix();	
    		glColor3f(1,1,1);
		glRotatef(90,0,0,0);
		glTranslatef(-17,-8,0);
		glutSolidCylinder(1.5,10,8,10);
    	glPopMatrix();
    	glPushMatrix();	
    		glColor3f(0,0,0);
		glRotatef(90,0,90,0);
		glTranslatef(-5,-8,-15);
		glutSolidTorus(3,3,10,30);
    	glPopMatrix();
    	glPushMatrix();	
    		glColor3f(1,1,1);
		glRotatef(90,0,0,0);
		glTranslatef(15,-8,-30);
		glutSolidCylinder(1.5,10,8,10);
    	glPopMatrix();
    	//End wheels		
		glBegin(GL_POLYGON);
         	glColor3f(0, 1, 0);
          	glVertex3f(-15.0f,15.0f,15.0f);
          	glVertex3f(-15.0f,-15.0f,15.0f);  
          	glVertex3f(-15,-15.0f,30.0f);
    	glEnd();
		glBegin(GL_POLYGON);
          	glColor3f(0, 1, 0);
          	glVertex3f( 15.0f,15.0f,15.0f);
          	glVertex3f( 15.0f,-15.0f,15.0f);  
          	glVertex3f(15,-15.0f,30.0f);
    	glEnd();
	glPopMatrix();
	//end garbage cabin
	//start dog/capybara
	glPushMatrix();
		glColor3f(0.45, 0.20, 0);
		glTranslatef(72, jump + (-1.5), movDog + 55);
		glRotated(40,0,0,40);
		glRotated(40+rotateDogY,1,0,0);
		glRotated(40+rotateDogX,1,1,0);
		glRotated(40,-2,0,0);
		//body
		glutSolidCylinder(5,30,4,10);
		glRotated(-140,0,200,-140);
		//legs
		glutSolidCylinder(1.5,10,8,10);
		glTranslatef(3, 0, 0);
		glRotatef(-10,30,0,0);
		glutSolidCylinder(1.5,10,8,10);
		glTranslatef(13, -20, -10);
		glutSolidCylinder(1.5,10,8,10);
		glTranslatef(-5, 0, 0);
		glutSolidCylinder(1.5,10,8,10);
		//end legs
		glRotated(75,0,20,0);
		glRotated(35,30,0,0);
		glRotated(35,0,0,90);
		//neck
		glutSolidCylinder(1.5,12,8,10);
		glTranslatef(2,-6,12);
		//head
		glutSolidSphere(5,20,25);
	glPopMatrix();
	//end dog/capybara
	glutSwapBuffers();
}

void myReshape(int winWidth, int winHeight) {
	int tam = winWidth < winHeight ? winWidth : winHeight;
	glViewport(0, 0, tam, tam); // reset the viewport
}


// imprimir as coordenadas com o clique do mouse
void myMouse(int b, int s, int x, int y) {
	switch (b) {
	case GLUT_LEFT_BUTTON:
		printf("(%d, %d)\n", x, y);
	}
}

// fun????o detecta movimento do mouse e salva coordenadas
void myMotion(int x, int y) {
	printf("Motion: (%d, %d)\n", x, y);
}

void init() {
	// background color
	glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	angle = 45;
	rotX = 10;
	rotY = -110;
	obsX = -50;
	obsY = 0;
	obsZ = 400;
	mov = 0;
	jump = 0;
	rotateDogY = 0;
	rotateDogX = 0;
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(5, 5);
	glutInitWindowSize(450, 450);
	glutCreateWindow("Trabalho CG");
	glutDisplayFunc(display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(TeclasEspeciais);
	glutMouseFunc(GerenciaMouse);
	glutMotionFunc(GerenciaMovim);
	init();
	glutMainLoop();

	return 0;
}
