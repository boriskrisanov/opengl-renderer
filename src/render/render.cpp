#include "defs.hpp"

using glm::vec2;
using std::vector;

namespace render
{
GLFWwindow *window;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
Camera camera{};
const float WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
Mesh triangle;

GLFWwindow *initAndCreateWindow()
{
    if (!glfwInit())
    {
        return nullptr;
    }

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        DEBUG_LOG("Failed to create window");
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        DEBUG_LOG("Failed initialize GLEW");
        return nullptr;
    }

    triangle = Mesh{vector{-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f}};

    // imgui setup

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glEnable(GL_DEPTH_TEST);

    return window;
}

void initCamera(unsigned int shaderProgram)
{
    camera = Camera{window, vec2(WINDOW_WIDTH, WINDOW_HEIGHT), shaderProgram, 0.05f};
}

void updateDeltaTime()
{
    double currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void updateUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void drawFrame()
{
    updateDeltaTime();
    updateUI();

    camera.respondToMouseInput();
    camera.respondToKeyboardInput(deltaTime);
    camera.updateMatrixUniforms();

    // glDrawArrays(GL_TRIANGLES, 0, 3);

    triangle.draw();

    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
}

void setWireframeDrawEnabled(bool enabled)
{
    glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
}

void setVsyncEnabled(bool enabled)
{
    glfwSwapInterval((int)enabled);
}
} // namespace render