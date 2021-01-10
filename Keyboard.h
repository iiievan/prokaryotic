#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include <map>
#include <vector>
#include <algorithm>

class Keyboard
{
public:
								Keyboard() : _isEnabled(true)
								{ _instances.push_back(this);	}
							   ~Keyboard() 
							    { _instances.erase(std::remove(_instances.begin(), _instances.end(), this), _instances.end()); }

			    static void		setInputWindow(Window* window) { glfwSetKeyCallback(window->getWindow(), Keyboard::callback); }
				     GLbyte		getIsKeyDown(int key) 
								{
									if (_isEnabled)
										return _keys[key];	
									else
										return 0;
								}

		std::map<int, GLbyte>&	getKeys() 
								{
									std::map<int, GLbyte> &ref = _keys;
									return ref;
								}

					   bool		getIsEnabled()			 { return _isEnabled; } 
					   void		setIsEnabled(bool value) { _isEnabled = value; }
private:
static std::vector<Keyboard*>	_instances;
	    std::map<int, GLbyte>   _keys; 	
				         bool	_isEnabled; // If disabled, Keyboard.getIsKeyDown always returns false
				         void	setIsKeyDown(int key, GLbyte isDown) 
								{
									 if (_keys.find(key) == _keys.end())
										 _keys.insert(std::make_pair(key, isDown));
									 else
										 _keys[key] = isDown;
								}

				 static void	callback(GLFWwindow* window, int key, int scancode, int action, int mods);
   
};
#endif // _KEYBOARD_H