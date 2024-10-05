#include "Rect.h"
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
GLuint rect_VAO, rect_VBO, rect_EBO, rect_shader, rect_uniformModel;
//---------------------------------------------

// ���Ⱚ(����, ������)
bool rectdirection = true;
// �簢���� ���̰�
float rectOffset = 0.0f;
// �簢���� �ִ� ���̰�
float rectMaxOffset = 1.0f;
// �簢���� ��ȭ��
float rectIncrement = 0.001f;

// ���� ���̴�
const char* rectVShader = R"(
#version 330 core

layout (location = 0) in vec3 pos;  // ��ġ ������ attribute position 0�� �����ϴ�.
layout (location = 1) in vec3 aColor; // �÷� ������ attribute position 1�� �����ϴ�.

out vec3 ourColor; // �÷��� fragment shader�� ���

//---------------------------------------------
// model�� ����
uniform mat4 model;
//---------------------------------------------

void main()
{
    //---------------------------------------------
    // model�� �����ش�.
    gl_Position = model * vec4(pos, 1.0);
    //gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
    ourColor = aColor; // vertex data �κ��� ������ �÷� �Է��� ourColor�� ����
    //---------------------------------------------
})";

// ���� ���̴�
const char* rectFShader = R"(
#version 330 core

out vec4 FragColor;
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
})";

void RectCreateTriangle()
{
    // ���� ��ǥ & �簢�� ����
    GLfloat vertexPosition[] = {
        -0.5f, -0.5f, 0.0f,   1.0, 0.0, 0.0,
        -0.5f, 0.5f, 0.0f,    0.0, 1.0, 0.0,
        0.5f, -0.5f, 0.0f,    0.0, 0.0, 1.0,
        0.5f, 0.5f, 0.0f,     1.0, 1.0, 1.0
    };  

    // ���� �ε���
    GLint vertexIndeces[] = {
        0, 1, 2,
        1, 2, 3
    };

    // OpenGL ���� �迭 �����⸦ ����ؼ� VAO�� ����
    glGenVertexArrays(1, &rect_VAO);
    // OpenGL ���� �迭 �����⸦ ����ؼ� VBO�� ����
    glGenBuffers(1, &rect_VBO);
    // OpenGL ���� �迭 �����⸦ ����ؼ� EBO�� ����
    glGenBuffers(1, &rect_EBO);

    // �츮�� ������ VAO�� ���� ���� �����ϵ��� �����Ѵ�.
    glBindVertexArray(rect_VAO);

    // �츮�� ������ VBO�� ���� ���� �����ϵ��� �����Ѵ�.
    glBindBuffer(GL_ARRAY_BUFFER, rect_VBO);
    // �츮�� ���� �ﰢ�� ���� ��ǥ�� VBO�� �����Ѵ�.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);

    // �츮�� ������ VBO�� ���� ���� �����ϵ��� �����Ѵ�.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rect_EBO);
    // �츮�� ���� �ﰢ�� ���� ��ǥ�� VBO�� �����Ѵ�.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndeces), vertexIndeces, GL_STATIC_DRAW);

    // VAO�� �� VAO�� ��� �ؼ��ؾ� �� �� �˷��ݴϴ�. 
    // �Լ� ���� (vertex attribute, Ÿ�� ũ��, Ÿ��, ����ȭ ����, �޸� ũ��, �޸� ������)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    // rect_VAO ��� ���
    glEnableVertexAttribArray(0);

    // �簢�� ���� ���� ���ε�
    glBindBuffer(GL_ARRAY_BUFFER, rect_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ������ �Ϸ� �Ǹ� ������ ���� ���� �ʱⰪ���� �����Ѵ�.
    glBindVertexArray(0);
}

void RectAddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
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

void RectCompileShader()
{
    rect_shader = glCreateProgram();

    if (rect_shader == NULL)
    {
        printf("Error Creating Shader Program!\n");
        return;
    }

    RectAddShader(rect_shader, rectVShader, GL_VERTEX_SHADER);
    RectAddShader(rect_shader, rectFShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    // ���̴� ���α׷� ����
    glLinkProgram(rect_shader);
    glGetProgramiv(rect_shader, GL_LINK_STATUS, &result); // rect_shader �߰��Լ��� �����Լ��� ���� glGetShaderiv-> glGetProgramiv
    if (!result)
    {
        glGetProgramInfoLog(rect_shader, sizeof(eLog), NULL, eLog);
        printf("Error Linking Program: '%s'\n", eLog);
        return;
    }

    // ���̴� ���α׷� ����
    glValidateProgram(rect_shader);
    glGetProgramiv(rect_shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(rect_shader, sizeof(eLog), NULL, eLog);
        printf("Error Validating Program: '%s'\n", eLog);
        return;
    }


    //---------------------------------------------
    // unifomModel�� ���̴��� model�� �����Ѵ�.
    rect_uniformModel = glGetUniformLocation(rect_shader, "model");
    //---------------------------------------------
    
}


void level::Rect::Init() 
{
    RectCreateTriangle();
    RectCompileShader();
}

void level::Rect::Update()
{
    // ������ ���������� ��������
    if (rectdirection == true)
    {
        rectOffset += rectIncrement;
    }
    else
    {
        rectOffset -= rectIncrement;
    }

    // �ִ� ���̰��� �ѱ�� �Ǹ� ���� ��ȯ
    if (abs(rectOffset) >= rectMaxOffset)
    {
        rectdirection = !rectdirection;
    }


    // Shader ����
    glUseProgram(rect_shader);

    //---------------------------------------------
    // mat4 model �ʱ�ȭ
    glm::mat4 model = glm::mat4(1.0f);
    // �츮�� ���ϴ� ����ŭ ��� ����
    model = glm::translate(model, glm::vec3(rectOffset, rectOffset, 0.0f));

    // Mat4�� uniformModel�� ��ȯ�Ѵ�.
    glUniformMatrix4fv(rect_uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    //---------------------------------------------
    
    // VBO�� �ִ� ������ ���ε�
    glBindVertexArray(rect_VBO);

    // �����͸� �������� �׸���
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // ������ ���ε� ����
    glBindVertexArray(0);

    // Shader ����
    glUseProgram(0);
}

void level::Rect::Exit()
{

}
