#ifndef _GUI_H_
#define _GUI_H_

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model/Mesh.h"
#include "model/Texture_params.h"
#include "model/Texture.h"
#include "shader/Shader.h"
#include "utils/Shader_buffer.h"

#include <iostream>

namespace PROKARYOTIC
{
	enum e_GUI_element_type : std::uint32_t
	{
		GUI_TEXT,
		GUI_SLIDER,
		GUI_BUTTON
	};
	
	enum e_GUI_text_side : std::uint32_t
	{
		GUI_LEFT_SIDE,
		GUI_CENTER_SIDE,
		GUI_RIGHT_SIDE
	};

	struct GUI_element 
	{
		e_GUI_element_type  type;
				      char* string;
				    double  char_size;
					double* data;
					double  min;
					double  max;
					   int  side;
		         glm::vec3  text_col;
		         glm::vec3  active_col;
	};


	template <GLenum TEXTYPE>
	struct Texture_params;

	template <typename T>
	class Mesh;

	class GUI 
	{
	public:
		      GUI(int screen_width, int screen_height, double element_width, double element_height, glm::vec3 backgrnd_clr, double transparency);
		     ~GUI();
	
		void  draw();
		void  update(glm::vec4 mouse, bool mouse_down);
	
		//adds a text element with the default background color
		void  add_text(char* str, double char_size, int side, glm::vec3 text_col);
		
		// adds a text element with the specified background color	
		void  add_text(char* str, double char_size, int side, glm::vec3 text_col, glm::vec3 active_col);
	
		void  add_slider(char* str, double char_size, double* data, double min, double max, int side, glm::vec3 text_col, glm::vec3 slider_col);
		void  add_button(char* str, double char_size, double* data, int side, glm::vec3 text_col, glm::vec3 button_col);
		void  remove_at(int index);
		void  remeve_all();
	
		bool  inside_GUI(glm::vec2 p);
	
		void  set_position(glm::vec2 position);
		void  set_size(glm::vec2 size);
		void  set_background_color(glm::vec3 color);
		void  set_transparency(double transparancy);
	
		
	private:
		              double  m_aspect_ratio;
		              double  m_element_width;
		              double  m_element_height;
		              double  m_element_aspect_ratio;
					    bool  m_mouse_already_down {false};
		           glm::vec2  m_position;
		           glm::vec3  m_background_col;
		              double  m_transparency;
	
	std::vector<GUI_element>  m_elements;
	
				Shader_buffer  *m_buffer;
		              Texture  *m_font;
		               Shader  *m_shader;
		          Mesh<float>  *m_mesh;
	
		              GLfloat  m_text_verts[]; 
	};
}

#endif // _GUI_H_