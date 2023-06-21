#include "Application.h"

namespace PROKARYOTIC
{
    extern std::vector<Vertex> rectangle_vertices;

    Camera  main_camera(WINDOW_WIDTH, WINDOW_HEIGHT);
     float  alpha{ 0.2f };
      bool  mirror{ false };

    Application* Application::s_Instance = nullptr;

	Application::Application()
    : m_screen(WINDOW_WIDTH, WINDOW_HEIGHT)
	{
        PRKRTC_CORE_ASSERT(!s_Instance, "Application already exist!");
        s_Instance = this;

        m_Window = init();
	}

	Application::~Application()
	{
        glfwTerminate();
	}

    GLFWwindow* Application::init()
    {  
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Prokaryotic", NULL, NULL);

        if (window == nullptr)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(window);
        //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetKeyCallback(window, deb_input);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return nullptr;
        }

        //glEnable(GL_DEPTH_TEST);    // Activate the zed buffer so that the fragments are not drawn one on top of the other.        

        //glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

        return window;
    }

	void Application::run()
	{
        Renderer  renderer;

        Cube<Vertex>* boxie = new Cube<Vertex>();

        Shader* vertex_shader = new Shader("vertex.glsl", VERTEX);
        Shader* fragment_shader = new Shader("fragment.glsl", FRAGMENT);
        Shader* vertex_light_shader = new Shader("vertex_light.glsl", VERTEX);
        Shader* fragment_light_shader = new Shader("fragment_light.glsl", FRAGMENT);
        Shader* vertex_ui_shader = new Shader("vertex_ui.glsl", VERTEX);
        Shader* fragment_ui_shader = new Shader("fragment_ui.glsl", FRAGMENT);
        Shader_program* shader_program = new Shader_program();
        Shader_program* shader_light_program = new Shader_program();
        Shader_program* ui_shader_prg = new Shader_program();

        Texture    wood_box = Texture_loader::Load_texture("wooden_container.jpg", GL_TEXTURE_2D, GL_RGB);
        Texture awesomeface = Texture_loader::Load_texture("awesomeface.png", GL_TEXTURE_2D, GL_RGBA);

        shader_program->load_shader(vertex_shader);
        shader_program->load_shader(fragment_shader);

        shader_light_program->load_shader(vertex_light_shader);
        shader_light_program->load_shader(fragment_light_shader);

        ui_shader_prg->load_shader(vertex_ui_shader);
        ui_shader_prg->load_shader(fragment_ui_shader);

        Material* smiled_wood = new Material(shader_program);
    
        //smiled_wood->set_Texture("s_Texture_1", &wood_box, 0);
        //smiled_wood->set_Texture("s_Texture_2", &awesomeface, 1);

        Light_source* light_bulb = new Light_source(&light_cube_vertices, shader_light_program);
        Scene_object* simple_Box = new Scene_object(dynamic_cast<Mesh<Vertex>*>(boxie), smiled_wood);
                 UI_item* button = new UI_item(&rectangle_vertices, ui_shader_prg);

        renderer.push_to_render(light_bulb);
        renderer.push_to_render(simple_Box);

        main_camera.set_floating();

        float Radius = 5.0f;
        float X0 = 0.0f;
        float Y0 = 0.0f;

        while (!m_should_quit())
        {
            double current_frame = m_get_time();
            m_dt = current_frame - m_last_frame;
            m_last_frame = current_frame;

            process_input(m_Window);   // process key input

            m_screen.use();
            m_screen.clear_to_color(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
            m_screen.clear();

            //m_cull(GL_BACK);
            m_depth_test(true);
            m_transparency(false);

            light_bulb->set_Transform(glm::mat4(1.0f));
            light_bulb->set_Position(glm::vec3(1.2f, 1.0f, 2.0f));
            light_bulb->set_Scale(glm::vec3(0.2f));

            //button->set_Transform(glm::mat4(1.0f));
            //button->set_Position(glm::vec3(1.2f, 1.0f, 2.0f));
            //button->set_Scale(glm::vec3(0.1f));

            glm::vec4 v4_Light_src_position = light_bulb->get_v4_Position();
            glm::vec3 v3_Circle_path = glm::vec3(X0 + cos((float)glfwGetTime()) * Radius,
                                                 Y0 + sin((float)glfwGetTime()) * Radius,
                                                 0.0f);
            glm::mat4 m4_Circle_move = glm::mat4(1.0f);
            m4_Circle_move = glm::translate(m4_Circle_move, v3_Circle_path);
            light_bulb->set_Position(m4_Circle_move * v4_Light_src_position);

            shader_program->set_Uniform("object_Color", glm::vec3(1.0f, 0.5f, 0.31f));
            shader_program->set_Uniform("light_Color", glm::vec3(1.0f, 1.0f, 1.0f));
            shader_program->set_Uniform("light_Position", light_bulb->get_v3_Position());
            shader_program->set_Uniform("view_Position", main_camera.Position);

            simple_Box->set_Transform(glm::mat4(1.0f));
            //simple_Box->set_Position(glm::vec3(0.0f, -2.2f, -2.5f));

            main_camera.set_Projection(-1.0f, 0.1f, 100.f);     // -1.0f for camera zoom through mouse scroll
            main_camera.update_View();

            // first processing 3D objects in 3D space
            renderer.process_objects(&main_camera);

            //m_cull(GL_FRONT);
            //m_depth_test(false);
            //m_transparency(true);
            
            // then process GUI
            //handle_gui(*button, &main_camera);

            m_swap_buffers();
            m_poll();
        }

        delete vertex_shader;
        delete fragment_shader;
        delete shader_program;
        delete smiled_wood;
	}

    void Application::process_input(GLFWwindow* window)
    {   
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            main_camera.move_forward(m_dt);

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            main_camera.move_backward(m_dt);

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            main_camera.move_left(m_dt);

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            main_camera.move_right(m_dt);
    }

    void deb_input(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            if (alpha < 1.0f)
                alpha += 0.05;
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            if (alpha > 0.0f)
                alpha -= 0.05;
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

    void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        static bool first_mouse = true;
        static float last_X = WINDOW_WIDTH / 2.0f;
        static float last_Y = WINDOW_HEIGHT / 2.0f;

        if (first_mouse)
        {
            last_X = xpos;
            last_Y = ypos;
            first_mouse = false;
        }

        float xoffset = xpos - last_X;
        float yoffset = last_Y - ypos; // reversed since y-coordinates go from bottom to top

        last_X = xpos;
        last_Y = ypos;

        main_camera.process_mouse(xoffset, yoffset);
    }

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        main_camera.process_scroll(yoffset);
    }

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void  handle_gui(UI_item& ui_obj, Camera* p_camera)
    {
        ui_obj.get_Shader_program().use();

        if (p_camera != nullptr)
        {
            ui_obj.set_Matrix("projection", p_camera->Projection);
            ui_obj.set_Matrix("view", p_camera->View);
        }

        ui_obj.set_Matrix("model", ui_obj.get_Transform());

        // set uniform state of material
        auto* uniforms = ui_obj.get_Uniforms();
        for (auto u_it = uniforms->begin(); u_it != uniforms->end(); ++u_it)
        {
            switch (u_it->second.Type)
            {
            case UNIFORM_TYPE_BOOL:
                ui_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Bool);
                break;
            case UNIFORM_TYPE_INT:
                ui_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Int);
                break;
            case UNIFORM_TYPE_FLOAT:
                ui_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Float);
                break;
            case UNIFORM_TYPE_VEC2:
                ui_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Vec2);
                break;
            case UNIFORM_TYPE_VEC3:
                ui_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Vec3);
                break;
            case UNIFORM_TYPE_VEC4:
                ui_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Vec4);
                break;
            case UNIFORM_TYPE_MAT2:
                ui_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Mat2);
                break;
            case UNIFORM_TYPE_MAT3:
                ui_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Mat3);
                break;
            case UNIFORM_TYPE_MAT4:
                ui_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Mat4);
                break;
            default:
                printf("Unrecognized Uniform type set.");
                break;
            }
        }

        ui_obj.draw<Shader_program>(nullptr);
    }

}


