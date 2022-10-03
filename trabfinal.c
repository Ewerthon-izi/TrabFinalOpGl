#include<GL/glut.h>

#include<GL/freeglut.h>

#include<stdlib.h>

#include<stdio.h>


static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat xPer = 0.0f;
static GLfloat yPer = 0.0f;
//static GLfloat spin=15.0;
//static GLfloat scale=0.0f;


GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat light_position1[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat light_position2[] = { -1.0, -1.0, -1.0, 0.0 };

GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat yellow_light[] = {1,1,0,0};
GLfloat blue_light[] = {1, 1, 0.5, 1.0};
GLfloat white_ambient[] = { 0.1, 0.1, 0.1, 1.0 };


void init(void)
{

 glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, yellow_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, blue_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
}

void Display(void){   
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


 	glMatrixMode(GL_MODELVIEW);



    	glPushMatrix();
   	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// parte de baixo do carro
    	glBegin(GL_POLYGON);
          glColor3f(1, 0, 1);
          glVertex3f(-40.0f,-50.0f,-15.0f);
          glVertex3f(40.0f,-50.0f,15.0f);
          glVertex3f(40.0f,-75.0f,15.0f);
          glVertex3f(-40.0f,-75.0f,-15.0f);
    	glEnd();
    	
    	glBegin(GL_POLYGON);
          glColor3f(1, 0, 1);
          glVertex3f(-40.0f,-50.0f,15.0f);
          glVertex3f(40.0f,-50.0f,-15.0f);
          glVertex3f(40.0f,-75.0f,-15.0f);
          glVertex3f(-40.0f,-75.0f,15.0f);
    	glEnd();
     	
	// teto do carro  
    	glBegin(GL_POLYGON);
          glVertex3f(-20.0f,-50.0f,-15);
          glVertex3f(-10.0f,-30.0f,-15);
          glVertex3f(20.0f,-30.0f,15);
          glVertex3f(25.0f,-50.0f,15);
    	glEnd();
    	
    	glBegin(GL_POLYGON);
          glVertex3f(-20.0f,-50.0f,15);
          glVertex3f(-10.0f,-30.0f,15);
          glVertex3f(20.0f,-30.0f,-15);
          glVertex3f(25.0f,-50.0f,-15);
    	glEnd();
    	 	
    	// rodas
    	glBegin(GL_3D);
    	  glColor3f(0.5, 0.5, 0.5);
    	  glTranslated(-20.0f,-75.0f,15.0f);
    	  glutSolidTorus(2,5,5,10);
    	  glTranslated(0.0f,0.0f,-30.0f);
    	  glutSolidTorus(2,5,5,10);
    	  glTranslated(45.0f,0.0f,0.0f);
    	  glutSolidTorus(2,5,5,10);
    	  glTranslated(0.0f,0.0f,30.0f);
    	  glutSolidTorus(2,5,5,10);
    	glEnd();	
		
	glPushMatrix();

    	glPopMatrix();
    	
    	glPushMatrix();
    	//glRotatef(45,0,0,1);
    	glScalef(10,0.3,3);

    	glPopMatrix();

    	glPopMatrix();
    	  	
	//sol
    	glPushMatrix();

    	glTranslatef(60, 70, 0);
    	
    	glColor3f(1, 1, 0);
    
    	glutSolidSphere(30, 300, 300);
    
    	glPopMatrix();
    	
    	//começo boneco
    	
    	glPushMatrix();

    	glTranslatef(-60, -30, 0);
    	
    	glColor3f(1, 0.95, 0.75);
    
	//cabeça    
    	glutSolidSphere(10, 300, 300);
    	
    	//tronco
    	glBegin(GL_POLYGON);
    	glColor3f(1, 0.95, 0.75);
          glVertex3f(2.5, 0,0);
          glVertex3f(-2.5,0,0);
          glVertex3f(-2.5,-30,0);
          glVertex3f(2.5,-30,0);
    	glEnd();
    	
    	//perna esquerdo
    	glBegin(GL_POLYGON);
          glVertex3f(2.5, -10,0);
          glVertex3f(3.5,-10,0);
          glVertex3f(-10,-40,0);
          glVertex3f(-5,-40,0);
    	glEnd();
    	
    	//perna direito
    	glBegin(GL_POLYGON);
          glVertex3f(-2.5, -10,0);
          glVertex3f(-3.5,-10,0);
          glVertex3f(10,-40,0);
          glVertex3f(5,-40,0);
    	glEnd();
    	
    	//braço esquerda
    	glBegin(GL_POLYGON);
          glVertex3f(2.5, 0,0);
          glVertex3f(3.5,0,0);
          glVertex3f(-10,-20,0);
          glVertex3f(-5,-20,0);
    	glEnd();
    	
    	//braço direita
    	glBegin(GL_POLYGON);
          glVertex3f(-2.5, 0,0);
          glVertex3f(-3.5,0,0);
          glVertex3f(10,-20,0);
          glVertex3f(5,-20,0);
    	glEnd();
    	
    	glPopMatrix();
   	//fim boneco
   	//começo arvore
   	glPushMatrix();
   	glTranslatef(60, -25, 0);
   	//tronco
    	glBegin(GL_POLYGON);
    	  glColor3f(0.21,0.18,0.14);
          glVertex3f(8, 0,0);
          glVertex3f(-2.5,0,0);
          glVertex3f(-2.5,-60,0);
          glVertex3f(8,-60,0);
    	glEnd();
  	glPopMatrix();
   	
   	//"Folhas"
   	glPushMatrix();
   	glColor3f(0, 1, 0);
   	glTranslatef(55, -38, 0);
    	glutSolidSphere(15, 300, 300);
    	glPopMatrix();
    	
    	glPushMatrix();
    	glTranslatef(75, -33, 0);
    	glutSolidSphere(15, 300, 300);
    	glPopMatrix();
    	
    	glPushMatrix();
    	glTranslatef(55, -28, 0);
    	glutSolidSphere(15, 300, 300);
    	glPopMatrix();
    	
    	glPushMatrix();
    	glTranslatef(75, -24, 0);
    	glutSolidSphere(15, 300, 300);
    	glPopMatrix();
    	
   	glutSwapBuffers();

     	glFlush();

}






void SpecialKeys(unsigned char key, int x, int y)
{
    switch(key)

    {
     case 'a':
          glTranslatef(-10,0.0,0.0);
          //glRotatef(spin,0,0,0);

                   //toot--;

            //Display();
            //glutIdleFunc(spinDisplay);

             glutPostRedisplay();

            break;
     case 'd':
          glTranslatef(+10,0.0,0.0);
            //toot++;
            //Display();

             glutPostRedisplay();

            break;
     case 't':
         xRot-= 10.0f;
          glutPostRedisplay();
     case 'y':
         yRot+=10.0f;
          glutPostRedisplay();

    }

}



int main(int argc, char* argv[])
{   glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("oto");
     init();
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glOrtho (-100, 100, -100, 100,-100, 100);

    glutKeyboardFunc(SpecialKeys);
    glutDisplayFunc(Display);


    //gluLookAt(0., 0., 0., 1., -1., 1., 0., 1., 0.);

    glutMainLoop();
    return 0;
}

