#include "main.h"
#include "init.h"

int main()
{
    GLFWwindow* window = init_GLFW_GLAD();

    if (window == nullptr)
        return -1;

    Shader * vertex_shader = new Shader("vertex.GLSL", GL_VERTEX_SHADER);
    Shader * fragment_shader = new Shader("fragment.GLSL", GL_FRAGMENT_SHADER);
    Shader_program* shader_program = new Shader_program();
    Mesh* rectangle = new Mesh(rectangle_vertices, rectangle_indices);
    Mesh* triangle = new Mesh(triangle_vertices, triangle_indices);

    shader_program->load_shader(vertex_shader);
    shader_program->load_shader(fragment_shader);
    shader_program->link_program();    
 
    while (!glfwWindowShouldClose(window))
    {        
        processInput(window);   // process key input

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_program->use();

        //rectangle->draw();
        triangle->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete rectangle;
    delete triangle;
    delete shader_program;

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

