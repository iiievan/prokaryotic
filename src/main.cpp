#include "main.h"
#include "init.h"

float vertices[] = 
{
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

int main()
{
    GLFWwindow* window = init_GLFW_GLAD();

    Shader * vertex_shader = new Shader("vertex.GLSL", GL_VERTEX_SHADER);
    Shader * fragment_shader = new Shader("fragment.GLSL", GL_FRAGMENT_SHADER);

    Shader_program* shader_program = new Shader_program();

    if (window == nullptr)
        return -1;

    shader_program->load_shader(vertex_shader);
    shader_program->load_shader(fragment_shader);

    shader_program->link_program();

    unsigned int VBO,VAO;
    glGenVertexArrays(1, &VAO);             // generate vertex array buffer for VBO
    glGenBuffers(1, &VBO);                  // generate VBO buffer on GPU
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);     // set type of buffer 
    glBufferData(GL_ARRAY_BUFFER,           // fill buffer with vertices
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW);

    //GL_STREAM_DRAW: данные устанавливаются только один раз и используются графическим процессором не более нескольких раз.
    //GL_STATIC_DRAW : данные устанавливаются только один раз и используются многократно.
    //GL_DYNAMIC_DRAW : данные сильно изменяются и используются многократно.

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
 
    while (!glfwWindowShouldClose(window))
    {        
        processInput(window);   // process key input

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_program->use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);   // 3. now draw the object 

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    delete shader_program;

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

