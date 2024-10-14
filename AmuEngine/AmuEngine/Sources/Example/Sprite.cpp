
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

// 정점 쉐이더 Vertex Shader
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

// 조각 쉐이더 Fragment Shader
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

    // 정점 좌표 & 사각형 색상 & 텍스처 좌표 (좌표계가 stbi 라이브러리와 opengl라이브러리의 서로 달라서 y축만 -를 달아서 반전시킴)
    float vertices[] = {
        // positions          // colors           // sprite_texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, -1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 1.0f,   1.0f,  0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f,  0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, -1.0f  // top left 
    };

    // 정점 인덱스
    GLint vertexIndeces[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // OpenGL 정점 배열 생성기를 사용해서 VAO를 생성
    glGenVertexArrays(1, &SpriteNspc::sprite_VAO);
    // OpenGL 정점 배열 생성기를 사용해서 VBO를 생성
    glGenBuffers(1, &SpriteNspc::sprite_VBO);
    // OpenGL 정점 배열 생성기를 사용해서 EBO를 생성
    glGenBuffers(1, &SpriteNspc::sprite_EBO);

    
    glBindVertexArray(SpriteNspc::sprite_VAO);// 우리가 생성한 VAO를 현재 수정 가능하도록 연결한다.
    
    glBindBuffer(GL_ARRAY_BUFFER, SpriteNspc::sprite_VBO);// 우리가 생성한 VBO를 현재 수정 가능하도록 연결한다.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// 우리가 만든 삼각형 정점 좌표를 VBO에 저장한다.
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SpriteNspc::sprite_EBO);// 우리가 생성한 VBO를 현재 수정 가능하도록 연결한다.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndeces), vertexIndeces, GL_STATIC_DRAW);// 우리가 만든 삼각형 정점 좌표를 VBO에 저장한다.

    // VAO에 이 VAO를 어떻게 해석해야 할 지 알려줍니다. 
    // 함수 인자 (vertex attribute, 타입 크기, 타입, 정규화 여부, 메모리 크기, 메모리 오프셋)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0); // sprite_VAO 사용 허용

    // 사각형 색상 버퍼 바인드
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 텍스쳐 S, T 설정
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // https://heinleinsgame.tistory.com/9#google_vignette

    // Texture //

    glGenTextures(1, &SpriteNspc::sprite_texture);
    glBindTexture(GL_TEXTURE_2D, SpriteNspc::sprite_texture);
    // 텍스처 wrapping/filtering 옵션 설정(현재 바인딩된 텍스처 객체에 대해)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    /*
    if in option of gl_clamp_to_border
    float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    */
    // 텍스처 로드 및 생성
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
    // 쉐이더 생성
    GLuint theShader = glCreateShader(shaderType);

    // 쉐이더 코드를 저장할 배열 생성
    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    // 쉐이더 코드 길이를 저장할 배열 생성
    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    // 쉐이더에 우리가 작성한 쉐이더 코드를 저장한다.
    glShaderSource(theShader, 1, theCode, codeLength);
    // 쉐이더 컴파일
    glCompileShader(theShader);

    // 에러 검출을 위한 변수 선언
    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    // 쉐이더 컴파일 정상완료 여부 저장
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        // 쉐이더 오류 로그를 저장하고 출력합니다.
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("Error Compiling the %d shader: '%s'\n", shaderType, eLog);
        return;
    }

    // 쉐이더 프로그램에 쉐이더를 등록합니다.
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

    // 쉐이더 프로그램 연결
    glLinkProgram(SpriteNspc::sprite_shader);
    glGetProgramiv(SpriteNspc::sprite_shader, GL_LINK_STATUS, &result); // sprite_shader 추가함수와 연결함수의 차이 glGetShaderiv-> glGetProgramiv
    if (!result)
    {
        glGetProgramInfoLog(SpriteNspc::sprite_shader, sizeof(eLog), NULL, eLog);
        printf("Error Linking Program: '%s'\n", eLog);
        return;
    }

    // 쉐이더 프로그램 검증
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
 
    // Shader 적용
    glUseProgram(SpriteNspc::sprite_shader);
        
    glBindVertexArray(SpriteNspc::sprite_VAO);

    // 데이터를 바탕으로 그리기
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // 데이터 바인딩 해제
    glBindVertexArray(0);

    // Shader 해제
    glUseProgram(0);
}

void level::Sprite::Exit()
{
    glDeleteVertexArrays(1, &SpriteNspc::sprite_VAO);
    glDeleteBuffers(1, &SpriteNspc::sprite_VBO);
    glDeleteBuffers(1, &SpriteNspc::sprite_EBO);
}