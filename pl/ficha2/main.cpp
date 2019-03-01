#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
float x=0.0f;
float y=0.0f;
float z=0.0f;
float angle=0.0f;
float angle2=0.0f;

void changeSize(int w,int h){
	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h==0)
		h=1;
	// compute window's aspect ratio 
	float ratio=w*1.0/h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
    glViewport(0,0,w,h);
	// Set perspective
	gluPerspective(45.0f,ratio,1.0f,1000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void){
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
	glutPostRedisplay();
	// put the geometric transformations here
	glTranslatef(x,y,z);
	glRotatef(angle,0.0f,1.0f,0.0f);
	glRotatef(angle2,1.0f,0.0f,0.0f);
	// put drawing instructions here
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(-1.0f,0.0f,1.0f);
	glVertex3f(-1.0f,0.0f,-1.0f);
	glVertex3f(1.0f,0.0f,1.0f);
	glVertex3f(-1.0f,0.0f,-1.0f);
	glVertex3f(1.0f,0.0f,-1.0f);
	glVertex3f(1.0f,0.0f,1.0f);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(1.0f,0.0f,1.0f);
	glVertex3f(0.0f,1.0f,0.0f);
	glVertex3f(-1.0f,0.0f,1.0f);
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(-1.0f,0.0f,1.0f);
	glVertex3f(0.0f,1.0f,0.0f);
	glVertex3f(-1.0f,0.0f,-1.0f);
	glColor3f(1.0f,0.0f,1.0f);
	glVertex3f(-1.0f,0.0f,-1.0f);
	glVertex3f(0.0f,1.0f,0.0f);
	glVertex3f(1.0f,0.0f,-1.0f);
	glColor3f(1.0f,1.0f,0.0f);
	glVertex3f(1.0f,0.0f,-1.0f);
	glVertex3f(0.0f,1.0f,0.0f);
	glVertex3f(1.0f,0.0f,1.0f);
	glEnd();
	// End of frame
	glutSwapBuffers();
}

// write function to process keyboard events
void keyboardSC(unsigned char key,int xs,int ys){
	switch(key){
		case 'w':
			y+=0.01f;
			break;
		case 's':
			y-=0.01f;
			break;
		case 'a':
			x-=0.01f;
			break;
		case 'd':
			x+=0.01f;
			break;
	}
	glutPostRedisplay();
}

void keyboardSpecialSC(int keycode, int xs, int ys) {
	switch(keycode){
		case GLUT_KEY_UP:
			angle2+=1.0f;
			break;
		case GLUT_KEY_DOWN:
			angle2-=1.0f;
			break;
		case GLUT_KEY_LEFT:
			angle+=1.0f;
			break;
		case GLUT_KEY_RIGHT:
			angle-=1.0f;
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv){
// init GLUT and the window
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
// put here the registration of the keyboard callbacks
	glutSpecialFunc(keyboardSpecialSC);
	glutKeyboardFunc(keyboardSC);
//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
// enter GLUT's main cycle
	glutMainLoop();	
	return 1;
}