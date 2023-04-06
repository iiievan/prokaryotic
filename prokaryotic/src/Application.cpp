#include "Application.h"

namespace PROKARYOTIC
{
    Application* Application::s_Instance = nullptr;

	Application::Application()
    : main_camera(WINDOW_WIDTH, WINDOW_HEIGHT)
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

        glEnable(GL_DEPTH_TEST);    // Activate the zed buffer so that the fragments are not drawn one on top of the other.

        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

        return window;
    }

	void Application::run()
	{
        Renderer  renderer;

        Cube<Vertex>* boxie = new Cube<Vertex>();

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

        std::vector<Scene_object*> Cubes_and_boxes;

        glm::vec3 cube_positions[] = 
        {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };  

        main_camera.set_Projection(glm::radians(45.0f), 0.1f, 100.f);

        for (std::uint32_t i = 0; i < 10; i++)
        {
            Cubes_and_boxes.push_back(new Scene_object(dynamic_cast<Mesh<Vertex>*>(boxie), smiled_wood));
            renderer.push_to_render(Cubes_and_boxes[i]);
        }

        while (!glfwWindowShouldClose(m_Window))
        {
            float current_frame = static_cast<float>(glfwGetTime());
            m_dt = current_frame - m_last_frame;
            m_last_frame = current_frame;

            process_input(m_Window);   // process key input

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the z buffer

            smiled_wood->set_Float("f_Alpha", m_alpha);
            smiled_wood->set_Bool("b_Mirror", m_mirror);

            for (std::uint32_t i = 0; i < 10; i++)
            {
                Cubes_and_boxes[i]->set_Transform(glm::mat4(1.0f));
                Cubes_and_boxes[i]->set_Position(cube_positions[i]);               

                if (i % 3 == 0)
                {
                    Cubes_and_boxes[i]->set_Rotation((float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
                }
                else
                {
                    float angle = 20.0f * i;
                    Cubes_and_boxes[i]->set_Rotation(glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                }
            }            

            main_camera.update_view();

            renderer.process_objects(&main_camera);

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }

        delete vertex_shader;
        delete fragment_shader;
        delete shader_program;
        delete smiled_wood;

        glfwTerminate();
	}

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void Application::process_input(GLFWwindow* window)
    {
        float cameraSpeed = static_cast<float>(2.5 * m_dt);

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
        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            main_camera.Position += cameraSpeed * main_camera.Front;

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            main_camera.Position -= cameraSpeed * main_camera.Front;

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            main_camera.Position -= glm::normalize(glm::cross(main_camera.Front, main_camera.Up)) * cameraSpeed;

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            main_camera.Position += glm::normalize(glm::cross(main_camera.Front, main_camera.Up)) * cameraSpeed;
    }
}
