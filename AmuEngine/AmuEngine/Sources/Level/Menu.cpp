#include "Menu.h"
#include <iostream>

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
GLuint VAO, VBO, shader, uniformModel;
//---------------------------------------------

// ���Ⱚ(����, ������)
bool direction = true;
// �ﰢ���� ���̰�
float triOffset = 0.0f;
// �ﰢ���� �ִ� ���̰�
float triMaxOffset = 1.0f;
// �ﰢ���� ��ȭ��
float triIncrement = 0.01f;

// ���� ���̴�
static const char* vShader = R"(
#version 330

layout (location = 0) in vec3 pos;

//---------------------------------------------
// model�� ����
uniform mat4 model;
//---------------------------------------------

void main()
{
    //---------------------------------------------
    // model�� �����ش�.
    gl_Position = model * vec4(0.5 * pos.x, 0.5 * pos.y, pos.z, 1.0);
    //---------------------------------------------
})";

// ���� ���̴�
static const char* fShader = R"(
#version 330

out vec4 colour;

void main()
{
    colour = vec4(1.0, 1.0, 1.0, 1.0);
})";

void CreateTriangle()
{
    // ���� ��ǥ
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    // OpenGL ���� �迭 �����⸦ ����ؼ� VAO�� ����
    glGenVertexArrays(1, &VAO);
    // �츮�� ������ VAO�� ���� ���� �����ϵ��� �����Ѵ�.
    glBindVertexArray(VAO);

    // OpenGL ���� �迭 �����⸦ ����ؼ� VBO�� ����
    glGenBuffers(1, &VBO);
    // �츮�� ������ VBO�� ���� ���� �����ϵ��� �����Ѵ�.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // �츮�� ���� �ﰢ�� ���� ��ǥ�� VBO�� �����Ѵ�.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // VAO�� �� VAO�� ��� �ؼ��ؾ� �� �� �˷��ݴϴ�.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // VAO ��� ���
    glEnableVertexAttribArray(0);
    // VBO ���� ���� �� ���� �ʱ�ȭ
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // ������ �Ϸ� �Ǹ� ������ ���� ���� �ʱⰪ���� �����Ѵ�.
    glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    // ���̴� ����
    GLuint theShader = glCreateShader(shaderType);

    // ���̴� �ڵ带 ������ �迭 ����
    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    // ���̴� �ڵ� ���̸� ������ �迭 ����
    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    // ���̴��� �츮�� �ۼ��� ���̴� �ڵ带 �����Ѵ�.
    glShaderSource(theShader, 1, theCode, codeLength);
    // ���̴� ������
    glCompileShader(theShader);

    // ���� ������ ���� ���� ����
    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    // ���̴� ������ ����Ϸ� ���� ����
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        // ���̴� ���� �α׸� �����ϰ� ����մϴ�.
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("Error Compiling the %d shader: '%s'\n", shaderType, eLog);
        return;
    }

    // ���̴� ���α׷��� ���̴��� ����մϴ�.
    glAttachShader(theProgram, theShader);
}

void CompileShader()
{
    shader = glCreateProgram();

    if (shader == NULL)
    {
        printf("Error Creating Shader Program!\n");
        return;
    }

    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    // ���̴� ���α׷� ����
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result); // shader �߰��Լ��� �����Լ��� ���� glGetShaderiv-> glGetProgramiv
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error Linking Program: '%s'\n", eLog);
        return;
    }

    // ���̴� ���α׷� ����
    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error Validating Program: '%s'\n", eLog);
        return;
    }

    //---------------------------------------------
    // unifomModel�� ���̴��� model�� �����Ѵ�.
    uniformModel = glGetUniformLocation(shader, "model");
    //---------------------------------------------
}


void level::Menu::Init() 
{
    CreateTriangle();
    CompileShader();
}

void level::Menu::Update() 
{
    // ������ ���������� ��������
    if (direction == true)
    {
        triOffset += triIncrement;
    }
    else
    {
        triOffset -= triIncrement;
    }

    // �ִ� ���̰��� �ѱ�� �Ǹ� ���� ��ȯ
    if (abs(triOffset) >= triMaxOffset)
    {
        direction = !direction;
    }


    // Shader ����
    glUseProgram(shader);

    //---------------------------------------------
    // mat4 model �ʱ�ȭ
    glm::mat4 model = glm::mat4(1.0f);
    // �츮�� ���ϴ� ����ŭ ��� ����
    model = glm::translate(model, glm::vec3(triOffset, triOffset, 0.0f));

    // Mat4�� uniformModel�� ��ȯ�Ѵ�.
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    //---------------------------------------------

    // VBO�� �ִ� ������ ���ε�
    glBindVertexArray(VBO);
    // �����͸� �������� �׸���
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // ������ ���ε� ����
    glBindVertexArray(0);

    // Shader ����
    glUseProgram(0);
}

void level::Menu::Exit() 
{

}
