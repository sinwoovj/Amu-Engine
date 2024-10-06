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
// �ʿ� GLM ��� �߰�
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//---------------------------------------------

const GLint WIDTH = 720, HEIGHT = 480;

//---------------------------------------------
GLFWwindow* mainWindow;

int AMSysInit(GLint width, GLint height, const char* title)
{
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
