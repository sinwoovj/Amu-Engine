#include "GSM/GameStateManager.h"
#include "Level/Menu.h"
#include "Example/Rect.h"
#include "Example/Sprite.h"
#include "Example/Triangle.h"
#include <opengl.h>
#include <Utils.h>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "../Editor/MainEditor.h"

GLboolean fullScreen = GL_FALSE;
const GLint WIDTH = 720, HEIGHT = 480;
const GLint FULLSCREENWIDTH = 2560, FULLSCREENHEIGHT = 1080;

//---------------------------------------------
GLFWwindow* mainWindow;

int AMSysInit(GLint width, GLint height, const char* title)
{
    // 로케일 국가 한국 지정
    _wsetlocale(LC_ALL, L"Korean");

    // + GLFW 초기화
    if (glfwInit() == GLFW_FALSE)
    {
        wprintf(L"GLFW 초기화 실패\n");
        glfwTerminate();
        return (1);
    }

    // + OpenGL 버전 지정
    // OpenGL MAJOR.MINOR 방식으로 표현
    // 이번엔 3.3을 사용한다.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // + OpenGL Profile과 호환성 설정
    // OpenGL 코어 프로필 설정
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // OpenGL 상위호환 활성화
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // + GLFW 윈도우 생성
    mainWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (mainWindow == NULL)
    {
        wprintf(L"GLFW 윈도우 생성이 실패했습니다.\n");
        glfwTerminate();
        return (1);
    }

    // + 버퍼 생성
    // 버퍼 가로, 버퍼 세로 선언
    int bufferWidth, bufferHeight;
    // mainWindow로부터 버퍼 가로 크기와 버퍼 세로 크기를 받아온다.
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // + OpenGL Context 설정
    glfwMakeContextCurrent(mainWindow);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    // + GLEW 초기화
    // GLEW의 모든 기능 활성화
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        wprintf(L"GLEW 초기화가 실패했습니다.\n");
        // mainWindow 삭제
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return (1);
    }

    // + OpenGL Viewport 생성
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
            glfwSetWindowSize(mainWindow, WIDTH, HEIGHT);
            fullScreen = GL_FALSE;
        }
        else
        {
            glfwSetWindowSize(mainWindow, FULLSCREENWIDTH, FULLSCREENHEIGHT);
            fullScreen = GL_TRUE;
        }
    }

    LastFrameFullscreenKey = currentFullscreenKey;
}

int main(void)
{
    if (AMSysInit(WIDTH, HEIGHT, "Amu Engine") )
        return 1;

    // Editor Init
    editor::MainEditor* mainEditor = new editor::MainEditor();
    mainEditor->MainEditorInit(mainWindow);

    GSM::GameStateManager& gsm = GSM::GameStateManager::GetInstance();

    gsm.ChangeLevel(new level::Menu);

    int LastFrameFullscreenKey = GLFW_RELEASE;

    /* Loop until the user closes the window */
    while (gsm.ShouldExit() == false && !glfwWindowShouldClose(mainWindow))
    {

        //frame setting

        /* Poll for and process events */
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(); // Show demo window! :)

        glClear(GL_COLOR_BUFFER_BIT);

        gsm.Update();

        // Rendering
        // Editor Update
        mainEditor->MainEditorUpdate();
        static bool show_window = true;
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        processInput();
        fullscreenInput(LastFrameFullscreenKey);

        glfwSwapBuffers(mainWindow);
    }

    gsm.Exit();

    // Editor Exit
    mainEditor->MainEditorExit();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
