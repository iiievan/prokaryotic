#include "main.h"
#include "init.h"
float alpha = 0.2f;
 bool mirror = false;

int main()
{
    GLFWwindow* window = init_GLFW_GLAD();

    if (window == nullptr)
        return -1;

    Mesh* rectangle = new Mesh(rectangle_vertices, rectangle_indices);

    Shader * vertex_shader = new Shader("vertex.glsl", VERTEX);
    Shader * fragment_shader = new Shader("fragment.glsl", FRAGMENT);
    Shader_program* shader_program = new Shader_program();    

    Texture wood_box = Texture_loader::Load_texture("wooden_container.jpg", GL_TEXTURE_2D ,GL_RGB);
    Texture awesomeface= Texture_loader::Load_texture("awesomeface.png", GL_TEXTURE_2D, GL_RGBA);

    shader_program->load_shader(vertex_shader);
    shader_program->load_shader(fragment_shader);



    Material * smiled_wood = new Material(shader_program);
    smiled_wood->set_Texture("s_Texture_1", &wood_box, 0);
    smiled_wood->set_Texture("s_Texture_2", &awesomeface, 1);

    Renderer renderer;
    renderer.push_to_render(rectangle, smiled_wood);

    while (!glfwWindowShouldClose(window))
    {        
        processInput(window);   // process key input

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        smiled_wood->set_Float("f_Alpha", alpha);
        smiled_wood->set_Bool("b_Mirror", mirror);

        renderer.process_objects();

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

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if (alpha < 1.0f)
            alpha += 0.01;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (alpha > 0.0f)
            alpha -= 0.01;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        mirror = true;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        mirror = false;
    }
}

