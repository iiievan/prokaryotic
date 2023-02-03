#include "main.h"
#include "init.h"

int main()
{
    GLFWwindow* window = init_GLFW_GLAD();

    if (window == nullptr)
        return -1;

    Shader * vertex_shader = new Shader("vertex.glsl", VERTEX);
    Shader * fragment_shader = new Shader("fragment.glsl", FRAGMENT);

    Mesh* rectangle = new Mesh(rectangle_vertices, rectangle_indices);
    Mesh* triangle_1 = new Mesh(triangle_vertices, triangle_indices);
    Mesh* triangle_2 = new Mesh(triangle2_vertices, triangle_indices);

    rectangle->get_max_vertex_attributes();

    vertex_shader->compile();
    vertex_shader->link_and_validate();
    fragment_shader->compile();
    fragment_shader->link_and_validate();
 
    while (!glfwWindowShouldClose(window))
    {        
        processInput(window);   // process key input

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vertex_shader->use();
        fragment_shader->use();

        // update the uniform color
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = fragment_shader->get_Uniform_location("Color_from_PCU");
        fragment_shader->set_Uniform(vertexColorLocation, 
                                     glm::vec4(0.0f, greenValue, 0.0f, 1.0f));

        triangle_1->draw_with_EBO(nullptr);
        triangle_2->draw_with_EBO(nullptr, true);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete rectangle;
    delete triangle_1;
    delete triangle_2;

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

