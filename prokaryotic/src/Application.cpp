#include "Application.h"

namespace PROKARYOTIC
{
    Application* Application::s_Instance = nullptr;

	Application::Application()
	{
        PRKRTC_CORE_ASSERT(!s_Instance, "Application already exist!");
        s_Instance = this;

        m_Window = init();
	}

	Application::~Application()
	{

	}

    GLFWwindow* Application::init()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Prokaryotic", NULL, NULL);

        if (window == nullptr)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return nullptr;
        }

        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

        return window;
    }

	void Application::run()
	{
        Mesh<Vertex>* rectangle = new Mesh<Vertex>(&rectangle_vertices, &rectangle_indices);
        Cube* boxie = new Cube();

        Shader* vertex_shader = new Shader("vertex.glsl", VERTEX);
        Shader* fragment_shader = new Shader("fragment.glsl", FRAGMENT);
        Shader_program* shader_program = new Shader_program();

        Texture wood_box = Texture_loader::Load_texture("wooden_container.jpg", GL_TEXTURE_2D, GL_RGB);
        Texture awesomeface = Texture_loader::Load_texture("awesomeface.png", GL_TEXTURE_2D, GL_RGBA);

        shader_program->load_shader(vertex_shader);
        shader_program->load_shader(fragment_shader);

        Material* smiled_wood = new Material(shader_program);
        smiled_wood->set_Texture("s_Texture_1", &wood_box, 0);
        smiled_wood->set_Texture("s_Texture_2", &awesomeface, 1);

        Scene_object* so_korobkins = new Scene_object(rectangle, smiled_wood);
        Scene_object* so_yaschik = new Scene_object(rectangle, smiled_wood);

        Camera  main_camera(WINDOW_WIDTH, WINDOW_HEIGHT);
        Renderer  renderer;

        main_camera.Rotate(glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        main_camera.set_Projection(glm::radians(45.0f), 0.1f, 100.f);
        main_camera.set_View(glm::vec3(0.0f, 0.0f, -3.0f));

        renderer.push_to_render(so_korobkins);
        renderer.push_to_render(so_yaschik);

        while (!glfwWindowShouldClose(m_Window))
        {
            process_input(m_Window);   // process key input

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            smiled_wood->set_Float("f_Alpha", m_alpha);
            smiled_wood->set_Bool("b_Mirror", m_mirror);

            so_korobkins->set_Transform(glm::mat4(1.0f));
            so_korobkins->set_Position(glm::vec3(0.5f, -0.5f, 0.0f));
            so_korobkins->set_Rotation((float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

            so_yaschik->set_Transform(glm::mat4(1.0f));
            so_yaschik->set_Position(glm::vec3(-0.5f, 0.5f, 0.0f));

            float scale_Value = abs(sin(glfwGetTime()) / 2.0f) + 0.1f;
            so_yaschik->set_Scale(glm::vec3(glm::vec2(scale_Value), 0.0f));

            renderer.process_objects(&main_camera);

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }

        delete rectangle;
        delete vertex_shader;
        delete fragment_shader;
        delete shader_program;
        delete smiled_wood;
        delete so_korobkins;

        glfwTerminate();
	}

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void Application::process_input(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            if (m_alpha < 1.0f)
                m_alpha += 0.01;
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            if (m_alpha > 0.0f)
                m_alpha -= 0.01;
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            m_mirror = true;
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            m_mirror = false;
        }
    }
}
