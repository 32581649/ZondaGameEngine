#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "GL\glut.h"
#include "Singleton.h"
#include "Control.h"

class Graphics{
public:
	Graphics(){};
	~Graphics(){};
	Graphics(const Graphics & cpy){
		this->screen_width = cpy.screen_width;
		this->screen_height = cpy.screen_height;
	};

	virtual void CreateGameWindow(const int & width,
									const int & height,
									const char* window_name,
									int* argc, char* argv[]) = 0;

	virtual void OpenPolygonMode() = 0;
	virtual void ClosePolygonMode() = 0;
	virtual void WarpPointerToCentre() = 0;


	int GetScreenWidth(){ return screen_width; };
	int GetScreenHeight(){ return screen_height; };
									
protected:
	int screen_width, screen_height;
};

// reference: https://github.com/PaulSolt/GLUT-Object-Oriented-Framework/blob/master/src/GlutFramework.h
// wrap the function to static so the original function dont need to be static. 
class OpenGL : public Graphics{
public:
	OpenGL(){};
	~OpenGL(){};
	OpenGL(const OpenGL & cpy){};
	
private:
	void CreateGameWindow(const int & width,
		const int & height,
		const char* window_name,
		int* argc, char* argv[]);

	void Initialize();
	void Display();
	void Reshape(int width, int height);
	void KeyboardDownFunc(unsigned char key, int x, int y){
		Control* control_instance = Singleton<Control>::Instance();
		control_instance->KeyboardDownFunc(key, x, y);
		glutPostRedisplay();
	};
	void KeyboardUpFunc(unsigned char key, int x, int y){
		Control* control_instance = Singleton<Control>::Instance();
		control_instance->KeyboardUpFunc(key, x, y);
		glutPostRedisplay();
	};
	void MouseMovementFunc(int x, int y){
		Control* control_instance = Singleton<Control>::Instance();
		control_instance->MouseMovementFunc(x, y);
		glutPostRedisplay();
	};

	void OpenPolygonMode(){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	};
	void ClosePolygonMode(){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	};
	void WarpPointerToCentre(){
		glutWarpPointer(screen_width / 2, screen_height / 2);
	};

	/**
	* call the glut look at function to update the camera
	*/
	void CallLookAt();

	// wrap the callback func used in glut
	static OpenGL *opengl_instance;
	void SetInstance(){ opengl_instance = this; };
	static void DisplayWrap(){
		opengl_instance->Display();
	};
	static void ReshapeWrap(int width, int height){
		opengl_instance->Reshape(width, height);
	};
	static void KeyboardDownFuncWrap(unsigned char key, int x, int y){
		opengl_instance->KeyboardDownFunc(key, x, y);
	};
	static void KeyboardUpFuncWrap(unsigned char key, int x, int y){
		opengl_instance->KeyboardUpFunc(key, x, y);
	};
	static void MouseMovementFuncWrap(int x, int y){
		opengl_instance->MouseMovementFunc(x, y);
	};
};

class GraphicsFactory{
public:
	GraphicsFactory(){};
	~GraphicsFactory(){};
	GraphicsFactory(const GraphicsFactory & cpy){};

	Graphics* Create(const char* type);
};

#endif