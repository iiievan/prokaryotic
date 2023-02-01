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
    Mesh* trangle = new Mesh(mesh_vertices);

    shader_program->load_shader(vertex_shader);
    shader_program->load_shader(fragment_shader);
    shader_program->link_program();    

    trangle->load_to_GPU(3);
 
    while (!glfwWindowShouldClose(window))
    {        
        processInput(window);   // process key input

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_program->use();

        trangle->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete trangle;
    delete shader_program;

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

