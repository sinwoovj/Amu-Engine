#include <GLFW/glfw3.h>
#include "GSM/GameStateManager.h"
#include "Level/Menu.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "AmuEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    GSM::GameStateManager& gsm = GSM::GameStateManager::GetInstance();

    gsm.ChangeLevel(new level::Menu);

    /* Loop until the user closes the window */
    while (gsm.ShouldExit() == false && !glfwWindowShouldClose(window))
    {
        //frame setting

        gsm.Update();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    gsm.Exit();
    glfwTerminate();
    return 0;
}