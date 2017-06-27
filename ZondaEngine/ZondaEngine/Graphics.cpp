#include <string>

#include "World.h"
#include "Graphics.h"
#include "Camera.h"

OpenGL* OpenGL::opengl_instance;

void OpenGL::CreateGameWindow(const int & width,
	const int & height,
	const char* window_name,
	int* argc, char* argv[]){

	SetInstance();

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	screen_width = width;
	screen_height = height;
	glutInitWindowSize(screen_width, screen_height);
	glutCreateWindow(window_name);

	Initialize();

	glutDisplayFunc(DisplayWrap);
	glutReshapeFunc(ReshapeWrap);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(KeyboardDownFuncWrap);
	glutKeyboardUpFunc(KeyboardUpFuncWrap);
	glutPassiveMotionFunc(MouseMovementFuncWrap);
	
	glutMainLoop();
}

void OpenGL::Initialize(){
	glClearColor(97.0f / 255.0f, 140.0f / 255.0f, 185.0f / 255.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void OpenGL::Display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CallLookAt();

	glColor4f(1.0, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3i(0, 0, 10);
		glVertex3i(10, 0, 10);
		glVertex3i(10, 10, 10);
		glVertex3i(0, 10, 10);
	glEnd();

	World* world_instance = Singleton<World>::Instance();
	world_instance->UpdateGame();

	glutSwapBuffers();
	glutPostRedisplay();
}

void OpenGL::Reshape(int width, int height){
	double ratio;

	screen_width = width;
	screen_height = height;

	// prevent divide by zero
	if (screen_height == 0) screen_height = 1;
	ratio = 1.0 * screen_width / screen_height;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, screen_width, screen_height);
	gluPerspective(45.0, ratio, 0.01, 3000.0);
	glMatrixMode(GL_MODELVIEW);
}

void OpenGL::CallLookAt(){
	Reshape(screen_width, screen_height);
	glLoadIdentity();
	
	Camera* camera_instance = Singleton<Camera>::Instance();
	gluLookAt(camera_instance->GetCameraPos().x, camera_instance->GetCameraPos().y, camera_instance->GetCameraPos().z,
		camera_instance->GetCameraLookAt().x, camera_instance->GetCameraLookAt().y, camera_instance->GetCameraLookAt().z,
		0, 1, 0);
}

Graphics* GraphicsFactory::Create(const char* type){
	std::string type_str = type;
	if (type_str == "OpenGL"){
		return new OpenGL;
	}
	/*
	else if (type_str == "DirectX"){
		return new DirectX;
	}
	*/
	else{
		return NULL;
	}
}