#include "main.h"
#include "init.h"

int main()
{
    GLFWwindow* window = init_GLFW_GLAD();

    if (window == nullptr)
        return -1;

    Shader * vertex_shader = new Shader("vertex.GLSL", GL_VERTEX_SHADER);
    Shader * fragment_shader_orange = new Shader("fragment_orange.glsl", GL_FRAGMENT_SHADER);
    Shader*  fragment_shader_yellow = new Shader("fragment_yellow.glsl", GL_FRAGMENT_SHADER);
    Shader_program* shader_program_1 = new Shader_program();
    Shader_program* shader_program_2 = new Shader_program();

    Mesh* rectangle = new Mesh(rectangle_vertices, rectangle_indices);
    Mesh* triangle_1 = new Mesh(triangle_vertices, triangle_indices);
    Mesh* triangle_2 = new Mesh(triangle2_vertices, triangle_indices);

    shader_program_1->load_shader(vertex_shader);
    shader_program_1->load_shader(fragment_shader_orange);
    shader_program_1->link_program();  

    shader_program_2->load_shader(vertex_shader);
    shader_program_2->load_shader(fragment_shader_yellow);
    shader_program_2->link_program();
 
    while (!glfwWindowShouldClose(window))
    {        
        processInput(window);   // process key input

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_program_1->use();
        //rectangle->draw();
        triangle_1->draw_with_EBO(nullptr);

        triangle_2->draw_with_EBO(shader_program_2, true);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete rectangle;
    delete triangle_1;
    delete triangle_2;
    delete shader_program_1;
    delete shader_program_2;

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

