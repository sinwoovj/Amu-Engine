#include "GSM/GameStateManager.h"
#include "Level/Menu.h"
#include "Example/Sprite.h"
#include "Example/Rect.h"
#include "Example/Triangle.h"
#include <cstdio>
#include <clocale>
#include <cstdlib>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//---------------------------------------------
// 필요 GLM 헤더 추가
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//---------------------------------------------

const GLint WIDTH = 720, HEIGHT = 480;

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

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(void)
{
    if ( AMSysInit(WIDTH, HEIGHT, "Amu Engine") )
        return 1;

    GSM::GameStateManager& gsm = GSM::GameStateManager::GetInstance();

    gsm.ChangeLevel(new level::Sprite);

    /* Loop until the user closes the window */
    while (gsm.ShouldExit() == false && !glfwWindowShouldClose(mainWindow))
    {
        processInput(mainWindow);

        //frame setting

        /* Poll for and process events */
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        gsm.Update();

        /* Swap front and back buffers */
        glfwSwapBuffers(mainWindow);

    }

    gsm.Exit();
    glfwTerminate();
    return 0;
}
