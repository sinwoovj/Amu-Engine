#include "Sprite.h"
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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//---------------------------------------------
GLuint sprite_VAO, sprite_VBO, sprite_EBO, sprite_shader, sprite_uniformModel, texture;
//---------------------------------------------

// ���Ⱚ(����, ������)
bool spritedirection = true;
// �簢���� ���̰�
float spriteOffset = 0.0f;
// �簢���� �ִ� ���̰�
float spriteMaxOffset = 1.0f;
// �簢���� ��ȭ��
float spriteIncrement = 0.001f;

// ���� ���̴� Vertex Shader
const char* spriteVShader = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

//---------------------------------------------
// model�� ����
uniform mat4 model;
//---------------------------------------------

void main()
{ 
    //---------------------------------------------
    // model�� �����ش�.
    gl_Position = model * vec4(aPos, 1.0);
    //---------------------------------------------
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
})";

// ���� ���̴� Fragment Shader
const char* spriteFShader = R"(
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoord);
})";

void SpriteCreateSprite()
{
    // ���� ��ǥ & �簢�� ���� & �ؽ�ó ��ǥ
    float vertices[] = {
        // ��ġ              // �÷�             // �ؽ�ó ��ǥ
       -1.0f, -1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ���� ���
       -1.0f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ���� �ϴ�
        1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ���� �ϴ�
        1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ���� ���
    };
    
    // ���� �ε���
    GLint vertexIndeces[] = {
        0, 1, 2,
        1, 2, 3
    };

    // OpenGL ���� �迭 �����⸦ ����ؼ� VAO�� ����
    glGenVertexArrays(1, &sprite_VAO);
    // OpenGL ���� �迭 �����⸦ ����ؼ� VBO�� ����
    glGenBuffers(1, &sprite_VBO);
    // OpenGL ���� �迭 �����⸦ ����ؼ� EBO�� ����
    glGenBuffers(1, &sprite_EBO);

    
    glBindVertexArray(sprite_VAO);// �츮�� ������ VAO�� ���� ���� �����ϵ��� �����Ѵ�.
    
    glBindBuffer(GL_ARRAY_BUFFER, sprite_VBO);// �츮�� ������ VBO�� ���� ���� �����ϵ��� �����Ѵ�.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// �츮�� ���� �ﰢ�� ���� ��ǥ�� VBO�� �����Ѵ�.
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite_EBO);// �츮�� ������ VBO�� ���� ���� �����ϵ��� �����Ѵ�.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndeces), vertexIndeces, GL_STATIC_DRAW);// �츮�� ���� �ﰢ�� ���� ��ǥ�� VBO�� �����Ѵ�.

    // VAO�� �� VAO�� ��� �ؼ��ؾ� �� �� �˷��ݴϴ�. 
    // �Լ� ���� (vertex attribute, Ÿ�� ũ��, Ÿ��, ����ȭ ����, �޸� ũ��, �޸� ������)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0); // sprite_VAO ��� ���

    // �簢�� ���� ���� ���ε�
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // �ؽ��� S, T ����
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // https://heinleinsgame.tistory.com/9#google_vignette

    // Texture //

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // �ؽ�ó wrapping/filtering �ɼ� ����(���� ���ε��� �ؽ�ó ��ü�� ����)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    /*
    if in option of gl_clamp_to_border
    float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    */
    // �ؽ�ó �ε� �� ����
    int width, height, nrChannels;
    unsigned char* data = stbi_load("Sources/Assets/Exam.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // End Texture //
}

void SpriteAddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
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

void SpriteCompileShader()
{
    sprite_shader = glCreateProgram();

    if (sprite_shader == NULL)
    {
        printf("Error Creating Shader Program!\n");
        return;
    }

    SpriteAddShader(sprite_shader, spriteVShader, GL_VERTEX_SHADER);
    SpriteAddShader(sprite_shader, spriteFShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    // ���̴� ���α׷� ����
    glLinkProgram(sprite_shader);
    glGetProgramiv(sprite_shader, GL_LINK_STATUS, &result); // sprite_shader �߰��Լ��� �����Լ��� ���� glGetShaderiv-> glGetProgramiv
    if (!result)
    {
        glGetProgramInfoLog(sprite_shader, sizeof(eLog), NULL, eLog);
        printf("Error Linking Program: '%s'\n", eLog);
        return;
    }

    // ���̴� ���α׷� ����
    glValidateProgram(sprite_shader);
    glGetProgramiv(sprite_shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(sprite_shader, sizeof(eLog), NULL, eLog);
        printf("Error Validating Program: '%s'\n", eLog);
        return;
    }


    //---------------------------------------------
    // unifomModel�� ���̴��� model�� �����Ѵ�.
    sprite_uniformModel = glGetUniformLocation(sprite_shader, "model");
    //---------------------------------------------
    
}


void level::Sprite::Init() 
{
    SpriteCreateSprite();
    SpriteCompileShader();
}

void level::Sprite::Update()
{
    // ������ ���������� ��������
    if (spritedirection == true)
    {
        spriteOffset += spriteIncrement;
    }
    else
    {
        spriteOffset -= spriteIncrement;
    }

    // �ִ� ���̰��� �ѱ�� �Ǹ� ���� ��ȯ
    if (abs(spriteOffset) >= spriteMaxOffset)
    {
        spritedirection = !spritedirection;
    }


    // Shader ����
    glUseProgram(sprite_shader);

    //---------------------------------------------
    // mat4 model �ʱ�ȭ
    glm::mat4 model = glm::mat4(1.0f);
    // �츮�� ���ϴ� ����ŭ ��� ����
    model = glm::translate(model, glm::vec3(spriteOffset, spriteOffset, 0.0f));

    // Mat4�� uniformModel�� ��ȯ�Ѵ�.
    glUniformMatrix4fv(sprite_uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    //---------------------------------------------
    

    glBindTexture(GL_TEXTURE_2D, texture);

    
    glBindVertexArray(sprite_VAO);

    // �����͸� �������� �׸���
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // ������ ���ε� ����
    glBindVertexArray(0);

    // Shader ����
    glUseProgram(0);
}

void level::Sprite::Exit()
{

}
