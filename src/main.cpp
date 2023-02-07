#include "main.h"
#include "init.h"

int main()
{
    GLFWwindow* window = init_GLFW_GLAD();

    if (window == nullptr)
        return -1;

    Shader * vertex_shader = new Shader("vertex.glsl", VERTEX);
    Shader * fragment_shader = new Shader("fragment.glsl", FRAGMENT);
    Shader_program* shader_program = new Shader_program();

    Mesh* rectangle = new Mesh(rectangle_vertices, rectangle_indices);

    Texture wood_box = Texture_loader::Load_texture("wooden_container.jpg", GL_TEXTURE_2D ,GL_RGB);
    Texture awesomeface= Texture_loader::Load_texture("awesomeface.png", GL_TEXTURE_2D, GL_RGBA);
 
    shader_program->load_shader(vertex_shader);
    shader_program->load_shader(fragment_shader);

    shader_program->use();

    int texture_1_loc = shader_program->get_Uniform_location("s_Texture_1");
    int texture_2_loc = shader_program->get_Uniform_location("s_Texture_2");
    shader_program->set_Uniform(texture_1_loc, (int)0);
    shader_program->set_Uniform(texture_2_loc, (int)1);

    while (!glfwWindowShouldClose(window))
    {        
        processInput(window);   // process key input

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        wood_box.Bind(0);
        awesomeface.Bind(1);
        shader_program->use();

        rectangle->draw_with_EBO(nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete rectangle;

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

