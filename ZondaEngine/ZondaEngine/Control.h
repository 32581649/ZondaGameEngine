#ifndef CONTROL_H
#define CONTROL_H

/**
* Control class - Plentoon Games
* Read user input and make changes in the game world
* Can be separated as different input devices by inheritance, in the future development
*/
class Control{
	public:
		/**
		* Ctor
		*/
		Control(){};

		/// Keyboard Down function
		/// For activating the camera movement wasd
		void KeyboardDownFunc(unsigned char key, int x, int y);

		/// Keyboard Up function
		/// For deactivating the camera movement wasd
		void KeyboardUpFunc(unsigned char key, int x, int y);

		/// Mouse Passive Movement function
		/// For controlling the camera rotation
		void MouseMovementFunc(int x, int y);

	private:
		/// records previous mouse location on the game window
		int mouse_x_org, mouse_y_org;

		/// screen width and height of the current game window
		//int screen_width, screen_height;

		/// key pressed at the moment
		char key_pressed;
};

#endif