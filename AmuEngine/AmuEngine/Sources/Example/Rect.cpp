#include "Rect.h"
#include <iostream>

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
GLuint VAO, VBO, EBO, shader, uniformModel;
//---------------------------------------------

// 방향값(왼쪽, 오른쪽)
bool direction = true;
// 사각형의 차이값
float rectOffset = 0.0f;
// 사각형의 최대 차이값
float rectMaxOffset = 1.0f;
// 사각형의 변화값
float rectIncrement = 0.01f;

// 정점 쉐이더
const char* vShader = R"(
#version 330 core

layout (location = 0) in vec3 pos;  // 위치 변수는 attribute position 0을 가집니다.
layout (location = 1) in vec3 aColor; // 컬러 변수는 attribute position 1을 가집니다.

out vec3 ourColor; // 컬러를 fragment shader로 출력

//---------------------------------------------
// model로 수정
uniform mat4 model;
//---------------------------------------------

void main()
{
    //---------------------------------------------
    // model을 곱해준다.
    gl_Position = model * vec4(pos, 1.0);
    //gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
    ourColor = aColor; // vertex data 로부터 가져온 컬러 입력을 ourColor에 설정
    //---------------------------------------------
})";

// 조각 쉐이더
const char* fShader = R"(
#version 330 core

out vec4 FragColor;
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
})";

void CreateTriangle()
{
    // 정점 좌표 & 사각형 색상
    GLfloat vertexPosition[] = {
        -0.5f, -0.5f, 0.0f,   1.0, 0.0, 0.0,
        -0.5f, 0.5f, 0.0f,    0.0, 1.0, 0.0,
        0.5f, -0.5f, 0.0f,    0.0, 0.0, 1.0,
        0.5f, 0.5f, 0.0f,     1.0, 1.0, 1.0
    };  

    // 정점 인덱스
    GLint vertexIndeces[] = {
        0, 1, 2,
        1, 2, 3
    };

    // OpenGL 정점 배열 생성기를 사용해서 VAO를 생성
    glGenVertexArrays(1, &VAO);
    // OpenGL 정점 배열 생성기를 사용해서 VBO를 생성
    glGenBuffers(1, &VBO);
    // OpenGL 정점 배열 생성기를 사용해서 EBO를 생성
    glGenBuffers(1, &EBO);

    // 우리가 생성한 VAO를 현재 수정 가능하도록 연결한다.
    glBindVertexArray(VAO);

    // 우리가 생성한 VBO를 현재 수정 가능하도록 연결한다.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 우리가 만든 삼각형 정점 좌표를 VBO에 저장한다.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);

    // 우리가 생성한 VBO를 현재 수정 가능하도록 연결한다.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // 우리가 만든 삼각형 정점 좌표를 VBO에 저장한다.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndeces), vertexIndeces, GL_STATIC_DRAW);

    // VAO에 이 VAO를 어떻게 해석해야 할 지 알려줍니다. 
    // 함수 인자 (vertex attribute, 타입 크기, 타입, 정규화 여부, 메모리 크기, 메모리 오프셋)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    // VAO 사용 허용
    glEnableVertexAttribArray(0);

    // 사각형 색상 버퍼 바인드
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 수정이 완료 되면 연결을 끊기 위해 초기값으로 연결한다.
    glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
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

    // 쉐이더 프로그램 연결
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result); // shader 추가함수와 연결함수의 차이 glGetShaderiv-> glGetProgramiv
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error Linking Program: '%s'\n", eLog);
        return;
    }

    // 쉐이더 프로그램 검증
    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error Validating Program: '%s'\n", eLog);
        return;
    }


    //---------------------------------------------
    // unifomModel과 쉐이더의 model을 연결한다.
    uniformModel = glGetUniformLocation(shader, "model");
    //---------------------------------------------
    
}


void level::Rect::Init() 
{
    CreateTriangle();
    CompileShader();
}

void level::Rect::Update()
{
    // 방향이 오른쪽인지 왼쪽인지
    if (direction == true)
    {
        rectOffset += rectIncrement;
    }
    else
    {
        rectOffset -= rectIncrement;
    }

    // 최대 차이값을 넘기게 되면 방향 전환
    if (abs(rectOffset) >= rectMaxOffset)
    {
        direction = !direction;
    }


    // Shader 적용
    glUseProgram(shader);

    //---------------------------------------------
    // mat4 model 초기화
    glm::mat4 model = glm::mat4(1.0f);
    // 우리가 원하는 값만큼 행렬 연산
    model = glm::translate(model, glm::vec3(rectOffset, rectOffset, 0.0f));

    // Mat4를 uniformModel로 변환한다.
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    //---------------------------------------------
    
    // VBO에 있는 데이터 바인딩
    glBindVertexArray(VBO);

    // 데이터를 바탕으로 그리기
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // 데이터 바인딩 해제
    glBindVertexArray(0);

    // Shader 해제
    glUseProgram(0);
}

void level::Rect::Exit()
{

}
