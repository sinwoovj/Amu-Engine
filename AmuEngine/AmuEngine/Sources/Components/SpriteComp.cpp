#include "SpriteComp.h"
#include "TransformComp.h"
#include "../ResourceManager/ResourceManager.h"
#include <EasyImgui.h>
#include <EasyOpengl.h>
#include <Utils.h>
#include "../Editor/MainEditor.h"
// 정점 쉐이더 Vertex Shader
const char* spriteVShader = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 ortho;
uniform mat3 transform;

void main()
{
	gl_Position = vec4(vec3(transform * aPos), 1.0f) * ortho;
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
})";

// 조각 쉐이더 Fragment Shader
const char* spriteFShader = R"(
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform vec4 ucolor;
// texture sampler
uniform sampler2D texture1;

void main()
{
	FragColor = texture2D(texture1, TexCoord) * ucolor;
})";

std::map<std::string, glm::vec2> SpriteComp::nativeSize;

SpriteComp::SpriteComp(GameObject* _owner) : GraphicComponent(_owner)
{
	//기본 세팅
	owner = _owner;
	color = { 1.f,1.f,1.f };
	alpha = 1;
	sprite_EBO = 0;
	sprite_VAO = 0;
	sprite_VBO = 0;
	sprite_shader = 0;
	sprite_texture = 0;
	texturePath = "";
	textureSize = { 400, 400 };
	trans = nullptr;
	SpriteSetSprite();
}

SpriteComp::~SpriteComp()
{
	ResourceManager::GetInstance().UnloadResource(texturePath);
	//TODO delete gl stuff that i generated (glGen...)
	glDeleteVertexArrays(1, &sprite_VAO);
	glDeleteBuffers(1, &sprite_VBO);
	glDeleteBuffers(1, &sprite_EBO);

}

void SpriteComp::SpriteSetSprite()
{
	SpriteCreateSprite();
	SpriteCompileShader();
}

void SpriteComp::SpriteCreateSprite()
{
	// 정점 좌표 & 사각형 색상 & 텍스처 좌표 (좌표계가 stbi 라이브러리와 opengl라이브러리의 서로 달라서 y축만 -를 달아서 반전시킴)
	float vertices[] = {
		// positions   // colors           // sprite_texture coords
		 -0.5f,  -0.5f, 1.0f,  1.0f, 1.0f, 1.0f,   0.0f,  0.0f, // top right
		 0.5f, -0.5f, 1.0f,  1.0f, 1.0f, 1.0f,   1.0f,  0.0f, // bottom right
		 0.5f,  0.5f, 1.0f,  1.0f, 1.0f, 1.0f,   1.0f,  1.0f, // bottom left
		-0.5f,  0.5f, 1.0f,  0.0f, 1.0f, 1.0f,   0.0f,  1.0f  // top left 
	};
	// 2D를 표현할 때 정점좌표의 z값은 1이여야 transform할 때 mat랑 연산 할 때 정상적인 값이 도출된다.

	// 정점 인덱스
	GLint vertexIndeces[] = {
		0, 1, 2, // first triangle
		2, 3, 0  // second triangle
	};

	// OpenGL 정점 배열 생성기를 사용해서 VAO를 생성
	glGenVertexArrays(1, &sprite_VAO);
	// OpenGL 정점 배열 생성기를 사용해서 VBO를 생성
	glGenBuffers(1, &sprite_VBO);
	// OpenGL 정점 배열 생성기를 사용해서 EBO를 생성
	glGenBuffers(1, &sprite_EBO);


	glBindVertexArray(sprite_VAO);// 우리가 생성한 VAO를 현재 수정 가능하도록 연결한다.

	glBindBuffer(GL_ARRAY_BUFFER, sprite_VBO);// 우리가 생성한 VBO를 현재 수정 가능하도록 연결한다.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// 우리가 만든 삼각형 정점 좌표를 VBO에 저장한다.

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite_EBO);// 우리가 생성한 VBO를 현재 수정 가능하도록 연결한다.
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

	//Generate texture
	glGenTextures(1, &sprite_texture);
	glBindTexture(GL_TEXTURE_2D, sprite_texture);
	// 텍스처 wrapping/filtering 옵션 설정(현재 바인딩된 텍스처 객체에 대해)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	/*
	if in option of gl_clamp_to_border
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	*/
	// 텍스처 로드 및 생성
	SetTexture(texturePath);

	// End Texture //
}

void SpriteComp::SpriteAddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	// 쉐이더 생성
	GLuint theShader = glCreateShader(shaderType);

	// 쉐이더 코드를 저장할 배열 생성
	const GLchar* theCode[1]{};
	theCode[0] = shaderCode;

	// 쉐이더 코드 길이를 저장할 배열 생성
	GLint codeLength[1];
	codeLength[0] = (GLint)strlen(shaderCode);

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

void SpriteComp::SpriteCompileShader()
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

	// 쉐이더 프로그램 연결
	glLinkProgram(sprite_shader);
	glGetProgramiv(sprite_shader, GL_LINK_STATUS, &result); // sprite_shader 추가함수와 연결함수의 차이 glGetShaderiv-> glGetProgramiv
	if (!result)
	{
		glGetProgramInfoLog(sprite_shader, sizeof(eLog), NULL, eLog);
		printf("Error Linking Program: '%s'\n", eLog);
		return;
	}

	// 쉐이더 프로그램 검증
	glValidateProgram(sprite_shader);
	glGetProgramiv(sprite_shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(sprite_shader, sizeof(eLog), NULL, eLog);
		printf("Error Validating Program: '%s'\n", eLog);
		return;
	}
}

void SpriteComp::SpriteDrawSprite()
{

	// Shader 적용
	glUseProgram(sprite_shader);

	glBindVertexArray(sprite_VAO);

	glBindTexture(GL_TEXTURE_2D, sprite_texture);
	// 데이터를 바탕으로 그리기
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// 데이터 바인딩 해제
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Shader 해제
	glUseProgram(0);
}

void SpriteComp::SpriteApplyTransform()
{
	if(!trans)
		trans = owner->GetComponent<TransformComp>();

	// Shader 적용
	glUseProgram(sprite_shader);

	unsigned int transformLoc = glGetUniformLocation(sprite_shader, "transform");

	glm::mat3 transform = trans->GetMatrix();

	Mtx33Scale(&transform, textureSize.x, textureSize.y);

	glUniformMatrix3fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glUseProgram(0);
}

bool SpriteComp::SetTexture(std::string path)
{
	if (path == "")
		path = DefaultSprite;
	/*else
		glDeleteTextures(1, &sprite_texture);*/

	/*if (path == texturePath)
		return true;*/

	ResourceManager::GetInstance().UnloadResource(texturePath);
	
	texturePath = path;

	texture = ResourceManager::GetInstance().GetResource<unsigned char>(path);

	if (texture)
	{
		textureSize = nativeSize.find(path)->second;

		glBindTexture(GL_TEXTURE_2D, sprite_texture);
		glUseProgram(sprite_shader);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)textureSize.x, (GLsizei)textureSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
		glGenerateMipmap(GL_TEXTURE_2D);

		unsigned char loc = glGetUniformLocation(sprite_shader, "ortho");

		glm::mat4 ortho = glm::ortho((float)-windowWidthHalf, (float)windowWidthHalf, (float)-windowHeightHalf, (float)windowHeightHalf);
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(ortho));
		glUseProgram(0);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		std::cout << "Failed to load texture : " << texturePath << std::endl;
		return false;
	}
	return true;
}

void SpriteComp::SetTransparency()
{
	/*
	쉐이더 관련 수정 (example. uniform)
	은 전부 무조건 제발 shader 프로그램을 켜고 수정을 하도록 하자!!!!!
	*/
	glUseProgram(sprite_shader);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);;
	
	//Set transparency
	// 알파 값 조절 (1.0은 불투명, 0.0은 완전 투명);
	unsigned char loc = glGetUniformLocation(sprite_shader, "ucolor");
	
	glUniform4f(loc, color.r, color.g, color.b, alpha);

	glUseProgram(0);
}

void SpriteComp::Update()
{
	//Set render mode
	//glRenderMode(GL_RENDER);

	//Set transform
	//Get the transform from my owner transfrom comp
	SpriteApplyTransform();
	// Set Texture
	
	//Set color 
	SetTransparency();

	// Draw
	SpriteDrawSprite();
}

void SpriteComp::SetColor(glm::vec3 Color)
{
	color = Color;
}

glm::vec2 SpriteComp::GetNativeSize(std::string str)
{
	if (nativeSize.find(str) != nativeSize.end())
	{
		return nativeSize.find(str)->second;
	}
	std::cout << "Invaild fileName" << std::endl;
	return { -1, -1 };
}

void SpriteComp::SetNativeSize(std::string str, glm::vec2 size)
{
	if (nativeSize.find(str) == nativeSize.end())
	{
		nativeSize.insert({ str, size });
	}
}

void SpriteComp::SetScale()
{
	if (textureSize != owner->GetComponent<TransformComp>()->GetScale())
		textureSize = owner->GetComponent<TransformComp>()->GetScale();
}

void SpriteComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("color");
		color.r = it->begin().value();
		color.g = (it->begin() + 1).value();
		color.b = (it->begin() + 2).value();
		it = compData->find("alpha");
		alpha = it.value();
		it = compData->find("texturePath");
		SetTexture(it.value());
		texturePath = it.value();
		it = compData->find("textureSize");
		SetTextureSize({ it->begin().value(), (it->begin() + 1).value() });
		it = compData->find("orderinLayer");
		orderinLayer = it.value();
	}
}

json SpriteComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["color"] = { color.r,color.g,color.b };
	compData["alpha"] = alpha;
	compData["texturePath"] = texturePath;
	compData["textureSize"] = { textureSize.x, textureSize.y };
	compData["orderinLayer"] = orderinLayer;
	data["compData"] = compData;

	return data;
}

void SpriteComp::Edit()
{
	ImGui::LabelText("label", "Value");

	//Color
	ImGui::SeparatorText("Color");
	{
		float* clr[4] = {&color.r, &color.g, &color.b, &alpha};
		ImGui::ColorEdit4("Color", *clr);
	}

	//Texture Sized
	ImGui::SeparatorText("Scale");
	{
		ImGui::DragFloat("Width", &textureSize.x, 1, 0.0000001f);
		ImGui::DragFloat("Height", &textureSize.y, 1, 0.0000001f);
		if (ImGui::Button("Native Size"))
		{
			textureSize = owner->GetComponent<SpriteComp>()->GetNativeSize(owner->GetComponent<SpriteComp>()->GetTexturePath());
		}
	}
	//Texture Path
	//std::cout << this->owner->GetName() << std::endl;
	ImGui::SeparatorText("Texture Path");
	{
		editor::MainEditor::editor_data.modifySpritePath = texturePath;

		if (ImGui::InputText("Path", &editor::MainEditor::editor_data.modifySpritePath, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			std::cout << this->owner->GetName() << std::endl;
			SetTexture(editor::MainEditor::editor_data.modifySpritePath);
		}
		if (ImGui::Button("Select Path"))
		{
			editor::MainEditor::editor_data.modifySpritePath = Utility::OpenFileDialog();
			SetTexture(editor::MainEditor::editor_data.modifySpritePath);
		}
	}
	//OrderInLayer
	ImGui::SeparatorText("Order In Layer");
	{
		ImGui::DragInt("order in layer", &orderinLayer, 1, -100, 100);
		if (ImGui::Button("Initialize"))
		{
			orderinLayer = 0;
		}
	}
}


BaseRTTI* SpriteComp::CreateSpriteComponent(GameObject* owner)
{
	BaseRTTI* p = new SpriteComp(owner);
	owner->AddComponent<SpriteComp>(static_cast<SpriteComp*>(p));
	return p;
}
