#include "GUI.h"

namespace PROKARYOTIC
{
	//Texture gui_Font(GL_TEXTURE_2D,"fontSDF.png", GL_RGB);
	Shader_buffer gui_buffer(GL_SHADER_STORAGE_BUFFER, 256 * sizeof(GLfloat), nullptr, GL_STREAM_DRAW);	
	Shader gui_shader("GUI_vert.glsl", "GUI_frag.glsl", "");
	Mesh<float> gui_mesh;

	GUI::GUI(int screen_width, int screen_height, double element_width, double element_height, glm::vec3 backgrnd_clr, double transparency)
	: m_font(new Texture( GL_TEXTURE_2D, "fontSDF.png", GL_RGB, true, false)),
	  m_text_verts
	  {
	  	  1.0f, 0.0f,  1.0f, 0.0f,
	  	  0.0f, 0.0f,  0.0f, 0.0f,
	  	  0.0f, 1.0f,  0.0f, 1.0f,
	  	  
	  	  1.0f, 1.0f,  1.0f, 1.0f,
	  	  1.0f, 0.0f,  1.0f, 0.0f,
	  	  0.0f, 1.0f,  0.0f, 1.0f,
	  } 
	{	
		m_aspect_ratio = double(screen_height) / double(screen_width);
		m_element_width = element_width;
		m_element_height = element_height;
		m_element_aspect_ratio = element_width / element_height;
		m_background_col = backgrnd_clr;
		m_transparency = transparency;
		m_position = glm::vec2(0.0);

		gui_shader.use();
		gui_shader.set_Uniform("font_texture", (int)0);
		gui_shader.set_Uniform("aspect_ratio", (float)m_aspect_ratio);
		gui_shader.set_Uniform("box_aspect_ratio", (float)m_element_aspect_ratio);
		gui_shader.set_Uniform("background_col", m_background_col);
		gui_shader.set_Uniform("alpha_val", (float)m_transparency);

		gui_buffer.bind();
		gui_buffer.bind_to(2);
		gui_buffer.unbind();

		Shader_buffer uv_buf(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), m_text_verts, GL_STATIC_DRAW);

		uv_buf.bind();

		gui_mesh.bind();
		gui_mesh.set_vertex_size(6);
		gui_mesh.attach(GL_FLOAT, 2, 4 * sizeof(GLfloat), 0, false);				    // GUI_vert.glsl layout (location = 0) in vec2 position;
		gui_mesh.attach(GL_FLOAT, 2, 4 * sizeof(GLfloat), 2 * sizeof(GLfloat), false);	// GUI_vert.glsl layout (location = 1) in vec2 texcoords;
		gui_mesh.unbind();
	}

	GUI::~GUI()
	{
		m_elements.clear();

		delete m_buffer;
		delete m_shader;
		delete m_mesh;
	}

	void GUI::draw()
	{
		float data[256];

		gui_shader.use();
		gui_shader.set_Uniform("scale", glm::vec2(m_element_width, m_element_height));

		m_font->Bind(0);

		double py = 0.0;
		for (GUI_element element : m_elements)
		{
			if (element.type == GUI_SLIDER)
			{
				char str[256];
				int s = snprintf(str, 256, element.string, *element.data);

				for (int i = 0; i < s; i++)
				{
					data[i] = float(str[i]);
				}

				gui_shader.set_Uniform("string_count", (int)s);
			}
			else
			{
				int i = 0;
				while (element.string[i] != '\0')
				{
					data[i] = float(element.string[i]);
					i++;
				}

				gui_shader.set_Uniform("string_count", (int)i);
			}

			gui_buffer.update(0, 256, data);

			glm::vec2 p = m_position + glm::vec2(0.0, py);

			double slider_val = 0.0;

			if (element.data)
			{
				slider_val = *element.data;
				slider_val = (slider_val - element.min) / (element.max - element.min);
			}
			if (element.type == GUI_TEXT && element.min == 0.0)
			{
				slider_val = 1.0;
			}

			gui_shader.set_Uniform("pos", p);
			gui_shader.set_Uniform("char_size", (float)element.char_size);
			gui_shader.set_Uniform("slider_val", (float)slider_val);
			gui_shader.set_Uniform("side", (int)element.side);
			gui_shader.set_Uniform("text_col", element.text_col);
			gui_shader.set_Uniform("active_col", element.active_col);

			gui_mesh.draw();

			py += m_element_height;
		}
	}

	void GUI::update(glm::vec4 mouse, bool mouse_down)
	{
		if (!mouse_down)
			m_mouse_already_down = false;

		double py = 0.0;
		int i = 0;

		for (int i = 0; i < m_elements.size(); i++)
		{
			if (mouse_down &&
				mouse.y > m_position.y + m_element_height * i &&
				mouse.y < m_position.y + m_element_height * (i + 1) &&
				mouse.x > m_position.x &&
				mouse.x < m_position.x + m_element_width)
			{
				if (m_elements[i].type == GUI_SLIDER)
				{
					double val = (mouse.x - m_position.x) / m_element_width;

					val = glm::clamp(val, 0.0, 1.0);

					val = m_elements[i].min + val * (m_elements[i].max - m_elements[i].min);

					*m_elements[i].data = val;
				}
				else
					if (m_elements[i].type == GUI_BUTTON &&
						!m_mouse_already_down)
					{
						if (*m_elements[i].data == 1.0)
							*m_elements[i].data = 0.0;
						else
							*m_elements[i].data = 1.0;
					}
			}
		}

		if (mouse_down)
			m_mouse_already_down = true;
	}

	void GUI::add_text(char* str, double char_size, int side, glm::vec3 text_col)
	{
		GUI_element element;

		element.type = GUI_TEXT;
		element.data = nullptr;
		element.char_size = char_size;
		element.string = str;
		element.min = -1.0;
		element.max = -1.0;
		element.side = side;
		element.text_col = text_col;
		element.active_col = glm::vec3(0.0);

		m_elements.push_back(element);
	}

	void GUI::add_text(char* str, double char_size, int side, glm::vec3 text_col, glm::vec3 active_col)
	{
		GUI_element element;

		element.type = GUI_TEXT;
		element.data = nullptr;
		element.char_size = char_size;
		element.string = str;
		element.min = 0.0;
		element.max = -1.0;
		element.side = side;
		element.text_col = text_col;
		element.active_col = active_col;

		m_elements.push_back(element);
	}

	void GUI::add_slider(char* str, double char_size, double* data, double min, double max, int side, glm::vec3 text_col, glm::vec3 slider_col)
	{
		GUI_element element;

		element.type = GUI_SLIDER;
		element.data = data;
		element.char_size = char_size;
		element.string = str;
		element.min = min;
		element.max = max;
		element.side = side;
		element.text_col = text_col;
		element.active_col = slider_col;

		m_elements.push_back(element);
	}

	void GUI::add_button(char* str, double char_size, double* data, int side, glm::vec3 text_col, glm::vec3 button_col)
	{
		GUI_element element;

		element.type = GUI_BUTTON;
		element.data = data;
		element.char_size = char_size;
		element.string = str;
		element.min = 0.0;
		element.max = 1.0;
		element.side = side;
		element.text_col = text_col;
		element.active_col = button_col;

		m_elements.push_back(element);
	}

	bool GUI::inside_GUI(glm::vec2 p)
	{
		glm::vec2 a = m_position;
		glm::vec2 b = m_position + glm::vec2(m_element_width, m_element_height * m_elements.size());
		return (p.x > a.x && p.x < b.x&& p.y > a.y && p.y < b.y);
	}

	void GUI::remove_at(int index)
	{
		m_elements.erase(m_elements.begin() + index);
	}

	void GUI::remeve_all()
	{
		m_elements.clear();
	}

	void GUI::set_position(glm::vec2 position)
	{
		m_position = position;
	}

	void GUI::set_size(glm::vec2 size)
	{
		m_element_width = size.x;
		m_element_height = size.y;
	}

	void GUI::set_background_color(glm::vec3 color)
	{
		m_background_col = color;
	}

	void GUI::set_transparency(double transparancy)
	{
		m_transparency = transparancy;
	}
}

