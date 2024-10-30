#include "GSM/GameStateManager.h"
#include "Level/Menu.h"
#include "Example/Rect.h"
#include "Example/Sprite.h"
#include "Example/Triangle.h"
#include <opengl.h>
#include <Utils.h>
#include <EasyImgui.h>
#include "../Editor/MainEditor.h"
#include "../Serializer/Serializer.h"
#include <iostream>
#include <Windows.h>
#include <crtdbg.h> // To check for memory leaks
#include "../Profiler/Profiler.h"


GLboolean fullScreen = GL_FALSE;


//---------------------------------------------
GLFWwindow* mainWindow;

int AMSysInit(GLint width, GLint height, const char* title)
{
    // UTF-8 ����
    SetConsoleOutputCP(CP_UTF8);

    // ������ ���� �ѱ� ����
    _wsetlocale(LC_ALL, L"Korean");

    // + GLFW �ʱ�ȭ
    if (glfwInit() == GLFW_FALSE)
    {
        wprintf(L"GLFW �ʱ�ȭ ����\n");
        glfwTerminate();
        return (1);
    }

    // + OpenGL ���� ����
    // OpenGL MAJOR.MINOR ������� ǥ��
    // �̹��� 3.3�� ����Ѵ�.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // + OpenGL Profile�� ȣȯ�� ����
    // OpenGL �ھ� ������ ����
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // OpenGL ����ȣȯ Ȱ��ȭ
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // + GLFW ������ ����
    mainWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (mainWindow == NULL)
    {
        wprintf(L"GLFW ������ ������ �����߽��ϴ�.\n");
        glfwTerminate();
        return (1);
    }

    // + ���� ����
    // ���� ����, ���� ���� ����
    int bufferWidth, bufferHeight;
    // mainWindow�κ��� ���� ���� ũ��� ���� ���� ũ�⸦ �޾ƿ´�.
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // + OpenGL Context ����
    glfwMakeContextCurrent(mainWindow);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    // + GLEW �ʱ�ȭ
    // GLEW�� ��� ��� Ȱ��ȭ
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        wprintf(L"GLEW �ʱ�ȭ�� �����߽��ϴ�.\n");
        // mainWindow ����
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return (1);
    }

    // + OpenGL Viewport ����
    glViewport(0, 0, bufferWidth, bufferHeight);
    return (0);
};

void processInput()
{
    if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(mainWindow, true);
    }
}

void fullscreenInput(int& LastFrameFullscreenKey)
{
    int currentFullscreenKey = glfwGetKey(mainWindow, GLFW_KEY_F11);

    if (currentFullscreenKey == GLFW_PRESS && currentFullscreenKey != LastFrameFullscreenKey)
    {
        if (fullScreen)
        {
            glfwSetWindowSize(mainWindow, windowWidth, windowHeight);
            fullScreen = GL_FALSE;
        }
        else
        {
            glfwSetWindowSize(mainWindow, fullscreenWindowWidth, fullscreenWindowHeight);
            fullScreen = GL_TRUE;
        }
    }

    LastFrameFullscreenKey = currentFullscreenKey;
}

int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //_CrtSetBreakAlloc(515);
    if (AMSysInit(windowWidth, windowHeight, "Amu Engine") )
        return 1;
    Utility::InitUtility();
    // Editor Init
    editor::MainEditor* mainEditor = new editor::MainEditor();
    mainEditor->MainEditorInit(mainWindow);

    GSM::GameStateManager& gsm = GSM::GameStateManager::GetInstance();

    gsm.ChangeLevel(new level::Menu);

    Serializer::GetInstance().LoadEditorSetting();

    int LastFrameFullscreenKey = GLFW_RELEASE;

    /* Loop until the user closes the window */
    while (gsm.ShouldExit() == false && !glfwWindowShouldClose(mainWindow))
    {
        DEBUG_PROFILER_START("Frame");
        //frame setting

        /* Poll for and process events */
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClear(GL_COLOR_BUFFER_BIT);

        gsm.Update();

        // Rendering
        // Editor Update
        mainEditor->MainEditorUpdate();
        static bool show_window = true;
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //processInput(); // if press exit 
        fullscreenInput(LastFrameFullscreenKey);

        glfwSwapBuffers(mainWindow);
        DEBUG_PROFILER_END;
        DEBUG_PROFILER_DUMP;
        DEBUG_PROFILER_CLEAR;
    }

    gsm.Exit();

    // Editor Exit
    mainEditor->MainEditorExit();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    delete mainEditor;

    glfwTerminate();
    DEBUG_PROFILER_DELETE;

    return 0;
}
