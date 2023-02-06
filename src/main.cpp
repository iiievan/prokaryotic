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
    Mesh* triangle_1 = new Mesh(triangle_vertices, triangle_indices);
    Mesh* triangle_2 = new Mesh(triangle2_vertices, triangle_indices);
    Mesh* interpolated_triangle = new Mesh(coloured_triangle, triangle_indices);

    rectangle->get_max_vertex_attributes();
 
    shader_program->load_shader(vertex_shader);
    shader_program->load_shader(fragment_shader);

    while (!glfwWindowShouldClose(window))
    {        
        processInput(window);   // process key input

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_program->use();

        //float uOffset = 0.5;
        //int uOffset_location = shader_program->get_Uniform_location("u_Offset");
        //shader_program->set_Uniform(uOffset_location, uOffset);
        // update the uniform color
        //float timeValue = glfwGetTime();
        //float greenValue = sin(timeValue) / 2.0f + 0.5f;
        //int vertexColorLocation = shader_program->get_Uniform_location("Color_from_PCU");
        //shader_program->set_Uniform(vertexColorLocation,
        //                             glm::vec4(0.0f, greenValue, 0.0f, 1.0f));

        //triangle_1->draw_with_EBO(nullptr);
        //triangle_2->draw_with_EBO(nullptr);
        interpolated_triangle->draw_with_EBO(nullptr);

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

