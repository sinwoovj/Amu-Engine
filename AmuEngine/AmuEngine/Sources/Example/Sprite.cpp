
#include "Sprite.h"
#include <iostream>
#include <opengl.h>

#include "stb_image.h"
#include "../ResourceManager/ResourceManager.h"
//---------------------------------------------
namespace SpriteNspc
{
    GLuint sprite_VAO, sprite_VBO, sprite_EBO, sprite_shader, sprite_texture;
};
//---------------------------------------------

// ���� ���̴� Vertex Shader
const char* spriteVShader1 = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
})";

// ���� ���̴� Fragment Shader
const char* spriteFShader1 = R"(
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoord) * vec4(ourColor,1);
})";



void level::Sprite::SetTexture(std::string path)
{
    if (texturePath != path)
        ResourceManager::GetInstance().UnloadResource(texturePath);

    texturePath = path;

    texture = ResourceManager::GetInstance().GetResource<unsigned char>(path);
    W = 1000;
    H = 563;
}

void level::Sprite::SpriteCreateSprite1()
{

    // ���� ��ǥ & �簢�� ���� & �ؽ�ó ��ǥ (��ǥ�谡 stbi ���̺귯���� opengl���̺귯���� ���� �޶� y�ุ -�� �޾Ƽ� ������Ŵ)
    float vertices[] = {
        // positions          // colors           // sprite_texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, -1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 1.0f,   1.0f,  0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f,  0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, -1.0f  // top left 
    };

    // ���� �ε���
    GLint vertexIndeces[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // OpenGL ���� �迭 �����⸦ ����ؼ� VAO�� ����
    glGenVertexArrays(1, &SpriteNspc::sprite_VAO);
    // OpenGL ���� �迭 �����⸦ ����ؼ� VBO�� ����
    glGenBuffers(1, &SpriteNspc::sprite_VBO);
    // OpenGL ���� �迭 �����⸦ ����ؼ� EBO�� ����
    glGenBuffers(1, &SpriteNspc::sprite_EBO);

    
    glBindVertexArray(SpriteNspc::sprite_VAO);// �츮�� ������ VAO�� ���� ���� �����ϵ��� �����Ѵ�.
    
    glBindBuffer(GL_ARRAY_BUFFER, SpriteNspc::sprite_VBO);// �츮�� ������ VBO�� ���� ���� �����ϵ��� �����Ѵ�.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// �츮�� ���� �ﰢ�� ���� ��ǥ�� VBO�� �����Ѵ�.
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SpriteNspc::sprite_EBO);// �츮�� ������ VBO�� ���� ���� �����ϵ��� �����Ѵ�.
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

    glGenTextures(1, &SpriteNspc::sprite_texture);
    glBindTexture(GL_TEXTURE_2D, SpriteNspc::sprite_texture);
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
    SetTexture("./Sources/Assets/Sprite/Background/Exam.png");

    if (texture)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    // End Texture //

}

void level::Sprite::SpriteAddShader1(GLuint theProgram, const char* shaderCode, GLenum shaderType)
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

void level::Sprite::SpriteCompileShader1()
{
    SpriteNspc::sprite_shader = glCreateProgram();

    if (SpriteNspc::sprite_shader == NULL)
    {
        printf("Error Creating Shader Program!\n");
        return;
    }

    SpriteAddShader1(SpriteNspc::sprite_shader, spriteVShader1, GL_VERTEX_SHADER);
    SpriteAddShader1(SpriteNspc::sprite_shader, spriteFShader1, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    // ���̴� ���α׷� ����
    glLinkProgram(SpriteNspc::sprite_shader);
    glGetProgramiv(SpriteNspc::sprite_shader, GL_LINK_STATUS, &result); // sprite_shader �߰��Լ��� �����Լ��� ���� glGetShaderiv-> glGetProgramiv
    if (!result)
    {
        glGetProgramInfoLog(SpriteNspc::sprite_shader, sizeof(eLog), NULL, eLog);
        printf("Error Linking Program: '%s'\n", eLog);
        return;
    }

    // ���̴� ���α׷� ����
    glValidateProgram(SpriteNspc::sprite_shader);
    glGetProgramiv(SpriteNspc::sprite_shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(SpriteNspc::sprite_shader, sizeof(eLog), NULL, eLog);
        printf("Error Validating Program: '%s'\n", eLog);
        return;
    }
}

level::Sprite::~Sprite()
{
    ResourceManager::GetInstance().UnloadResource(texturePath);
}


void level::Sprite::Init() 
{
    SpriteCreateSprite1();
    SpriteCompileShader1();
}

void level::Sprite::Update()
{
    glBindTexture(GL_TEXTURE_2D, SpriteNspc::sprite_texture);
 
    // Shader ����
    glUseProgram(SpriteNspc::sprite_shader);
        
    glBindVertexArray(SpriteNspc::sprite_VAO);

    // �����͸� �������� �׸���
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // ������ ���ε� ����
    glBindVertexArray(0);

    // Shader ����
    glUseProgram(0);
}

void level::Sprite::Exit()
{
    glDeleteVertexArrays(1, &SpriteNspc::sprite_VAO);
    glDeleteBuffers(1, &SpriteNspc::sprite_VBO);
    glDeleteBuffers(1, &SpriteNspc::sprite_EBO);
}