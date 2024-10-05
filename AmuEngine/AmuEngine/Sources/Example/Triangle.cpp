#include "Triangle.h"
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
GLuint tri_VAO, tri_VBO, tri_shader, tri_uniformModel;
//---------------------------------------------

// 방향값(왼쪽, 오른쪽)
bool tridirection = true;
// 삼각형의 차이값
float triOffset = 0.0f;
// 삼각형의 최대 차이값
float triMaxOffset = 1.0f;
// 삼각형의 변화값
float triIncrement = 0.01f;

// 정점 쉐이더
static const char* triVShader = R"(
#version 330

layout (location = 0) in vec3 pos;

//---------------------------------------------
// model로 수정
// uniform mat4 model;
//---------------------------------------------

void main()
{
    //---------------------------------------------
    // model을 곱해준다.
    //gl_Position = model * vec4(0.5 * pos.x, 0.5 * pos.y, pos.z, 1.0);
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
    //---------------------------------------------
})";

// 조각 쉐이더
static const char* triFShader = R"(
#version 330

out vec4 colour;

void main()
{
    colour = vec4(1.0, 1.0, 1.0, 1.0);
})";

void TriCreateTriangle()
{
    // 정점 좌표
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    // OpenGL 정점 배열 생성기를 사용해서 VAO를 생성
    glGenVertexArrays(1, &tri_VAO);
    // 우리가 생성한 VAO를 현재 수정 가능하도록 연결한다.
    glBindVertexArray(tri_VAO);

    // OpenGL 정점 배열 생성기를 사용해서 VBO를 생성
    glGenBuffers(1, &tri_VBO);
    // 우리가 생성한 VBO를 현재 수정 가능하도록 연결한다.
    glBindBuffer(GL_ARRAY_BUFFER, tri_VBO);

    // 우리가 만든 삼각형 정점 좌표를 VBO에 저장한다.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // VAO에 이 VAO를 어떻게 해석해야 할 지 알려줍니다.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // tri_VAO 사용 허용
    glEnableVertexAttribArray(0);
    // tri_VBO 수정 종료 및 연결 초기화
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 수정이 완료 되면 연결을 끊기 위해 초기값으로 연결한다.
    glBindVertexArray(0);
}

void TriAddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
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

void TriCompileShader()
{
    tri_shader = glCreateProgram();

    if (tri_shader == NULL)
    {
        printf("Error Creating Shader Program!\n");
        return;
    }

    TriAddShader(tri_shader, triVShader, GL_VERTEX_SHADER);
    TriAddShader(tri_shader, triFShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    // 쉐이더 프로그램 연결
    glLinkProgram(tri_shader);
    glGetProgramiv(tri_shader, GL_LINK_STATUS, &result); // tri_shader 추가함수와 연결함수의 차이 glGetShaderiv-> glGetProgramiv
    if (!result)
    {
        glGetProgramInfoLog(tri_shader, sizeof(eLog), NULL, eLog);
        printf("Error Linking Program: '%s'\n", eLog);
        return;
    }

    // 쉐이더 프로그램 검증
    glValidateProgram(tri_shader);
    glGetProgramiv(tri_shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(tri_shader, sizeof(eLog), NULL, eLog);
        printf("Error Validating Program: '%s'\n", eLog);
        return;
    }

    //---------------------------------------------
    // unifomModel과 쉐이더의 model을 연결한다.
    // tri_uniformModel = glGetUniformLocation(tri_shader, "model");
    //---------------------------------------------
}


void level::Triangle::Init() 
{
    TriCreateTriangle();
    TriCompileShader();
}

void level::Triangle::Update()
{
    // 방향이 오른쪽인지 왼쪽인지
    if (tridirection == true)
    {
        triOffset += triIncrement;
    }
    else
    {
        triOffset -= triIncrement;
    }

    // 최대 차이값을 넘기게 되면 방향 전환
    if (abs(triOffset) >= triMaxOffset)
    {
        tridirection = !tridirection;
    }


    // Shader 적용
    glUseProgram(tri_shader);

    //---------------------------------------------
    // mat4 model 초기화
    glm::mat4 model = glm::mat4(1.0f);
    // 우리가 원하는 값만큼 행렬 연산
    model = glm::translate(model, glm::vec3(triOffset, triOffset, 0.0f));

    // Mat4를 uniformModel로 변환한다.
    // glUniformMatrix4fv(tri_uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    //---------------------------------------------

    // VBO에 있는 데이터 바인딩
    glBindVertexArray(tri_VBO);
    // 데이터를 바탕으로 그리기
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // 데이터 바인딩 해제
    glBindVertexArray(0);

    // Shader 해제
    glUseProgram(0);
}

void level::Triangle::Exit()
{

}
