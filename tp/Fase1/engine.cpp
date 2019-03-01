#include "engine.h"

#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4
#define FILL 1
#define LINE 2
#define SHRINK 1
#define NORMAL 2

float alfa = 0.0f, beta = 0.0f, radius = 20.0f, camX, camY, camZ;
float red = 1.0f, blue = 0.5f, green = 0.5f;
int fillMenu, shrinkMenu, mainMenu, colorMenu;
int menuFlag = 0;

void spherical2Cartesian() {
	camX = radius * cos(beta)*sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta)*cos(alfa);
}
void changeSize(int w,int h){
	//Prevent a divide by zero,when window is too short
	//(you cant make a window with zero width).
	if(h==0)
		h=1;
	//compute window's aspect ratio 
	float ratio=w*1.0 / h;
	//Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	//Load Identity Matrix
	glLoadIdentity();
	//Set the viewport to be the entire window
	glViewport(0,0,w,h);
	//Set perspective
	gluPerspective(45.0f,ratio,1.0f,1000.0f);
	//return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}
void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// set the camera
	glLoadIdentity();
	glColor3f(red, green, blue);
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);
	// drawing instructions
	processModels();
	// End of frame
	glutSwapBuffers();
}
void processKeys(unsigned char c, int xx, int yy) {
	if (c == 'l')
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (c == 'f')
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void processSpecialKeys(int key,int xx,int yy){
	switch(key){
	case GLUT_KEY_RIGHT:
		alfa+=0.05f;
		break;
	case GLUT_KEY_LEFT:
		alfa-=0.05f;
		break;
	case GLUT_KEY_UP:
		beta+=0.05f;
		if(beta>1.5f)
			beta=1.5f;
		break;
	case GLUT_KEY_DOWN:
		beta-=0.05f;
		if(beta<-1.5f)
			beta=-1.5f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		radius-=1.0f;
		if(radius<0.1f)
			radius=0.1f;
		break;
	case GLUT_KEY_PAGE_UP:
		radius+=1.0f;
		break;
	case GLUT_KEY_HOME:
		alfa=0.0f,beta=0.0f,radius=50.0f,
		camX=50.0f,camY=0.0f,camZ=0.0f;
	}
	spherical2Cartesian();
	glLoadIdentity();
	gluLookAt(camX,camY,camZ,0,0,0,0,1,0);
	glutPostRedisplay();
}
void processMenuStatus(int status, int x, int y){
	if (status == GLUT_MENU_IN_USE)
		menuFlag = 1;
	else
		menuFlag = 0;
}
void processMainMenu(int option){
	// nothing to do in here
	// all actions are for submenus
}
void processFillMenu(int option) {
	switch (option) {
		case FILL: 
			glPolygonMode(GL_FRONT, GL_FILL);
			break;
		case LINE: 
			glPolygonMode(GL_FRONT, GL_LINE);
			break;
	}
}
void processColorMenu(int option){
	switch (option) {
	case RED:
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f; 
		break;
	case GREEN:
		glColor3f(0, 1, 0);
		red = 0.0f;
		green = 1.0f;
		blue = 0.0f; 
		break;
	case BLUE:
		red = 0.0f;
		green = 0.0f;
		blue = 1.0f; 
		break;
	case ORANGE:
		red = 1.0f;
		green = 0.5f;
		blue = 0.5f; 
		break;
	}
}
void createPopupMenus(){
	fillMenu = glutCreateMenu(processFillMenu);
	glutAddMenuEntry("Fill", FILL);
	glutAddMenuEntry("Line", LINE);
	colorMenu = glutCreateMenu(processColorMenu);
	glutAddMenuEntry("Red", RED);
	glutAddMenuEntry("Blue", BLUE);
	glutAddMenuEntry("Green", GREEN);
	glutAddMenuEntry("Orange", ORANGE);
	mainMenu = glutCreateMenu(processMainMenu);
	glutAddSubMenu("Polygon Mode", fillMenu);
	glutAddSubMenu("Color", colorMenu);
	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	// this will allow us to know if the menu is active
	glutMenuStatusFunc(processMenuStatus);
}
int main(int argc, char **argv) {
	// init GLUT and the window
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1350,675);
	glutCreateWindow("Phase 1 - Geometrical Transforms");
	//Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	createPopupMenus();
	//XML Pasring
	string xmlPath = "config.xml";
	const char *strPath = xmlPath.c_str();
	xmlParser(strPath);
	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// enter GLUT's main cycle
	glutMainLoop();
	return 1;
}