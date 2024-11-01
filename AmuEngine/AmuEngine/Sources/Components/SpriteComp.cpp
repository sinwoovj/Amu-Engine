#include "SpriteComp.h"
#include "TransformComp.h"
#include "../ResourceManager/ResourceManager.h"
#include <EasyImgui.h>
#include <EasyOpengl.h>
#include <Utils.h>
#include "../Editor/MainEditor.h"
// ���� ���̴� Vertex Shader
const char* spriteVShader = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float isBorder;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 ortho;
uniform mat3 transform;
uniform vec2 offset;
uniform bool useBorder;

void main()
{
	vec3 pos = transform * aPos;
	if(useBorder)
	{
		if(isBorder == 1)
			pos = vec3(pos.x - offset.x, pos.y - offset.y, pos.z);
		if(isBorder == 2)
			pos = vec3(pos.x + offset.x, pos.y - offset.y, pos.z);
		if(isBorder == 3)
			pos = vec3(pos.x + offset.x, pos.y + offset.y, pos.z);
		if(isBorder == 4)
			pos = vec3(pos.x - offset.x, pos.y + offset.y, pos.z);
	}
	gl_Position = vec4(pos, 1.0f) * ortho;
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
})";

// ���� ���̴� Fragment Shader
const char* spriteFShader = R"(
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform vec4 ucolor;
uniform vec4 ecolor;
// texture sampler
uniform sampler2D texture1;
uniform bool useTexture;


void main()
{
	if(useTexture)
    {
        FragColor = texture2D(texture1, TexCoord) * ucolor;
    }
    else
    {
        // �ݸ��� �ڽ� ������
        FragColor = ecolor;
    }
})";

std::map<std::string, glm::vec2> SpriteComp::nativeSize;
std::map<std::string, std::string> SpriteComp::fileExt;

SpriteComp::SpriteComp(GameObject* _owner) : GraphicComponent(_owner)
{
	//�⺻ ����
	owner = _owner;
	color = { 1.f,1.f,1.f };
	alpha = 1;
	selected = false;
	sprite_EBO = 0;
	sprite_VAO = 0;
	sprite_VBO = 0;
	select_edge_VAO = 0;
	select_edge_VBO = 0;
	select_edge_EBO = 0;
	collider_edge_VAO = 0;
	collider_edge_VBO = 0;
	collider_edge_EBO = 0;
	_shader = 0;
	sprite_texture = 0;
	texturePath = "";
	textureSize = { 400, 400 };
	trans = nullptr;
	SpriteSetSprite();
	SpriteCreateRect(select_edge_VAO, select_edge_VBO, select_edge_EBO);
	//SpriteCreateRect(collider_edge_VAO, collider_edge_VBO, collider_edge_EBO);
	SetBoolShader("useTexture", true);
}

SpriteComp::~SpriteComp()
{
	ResourceManager::GetInstance().UnloadResource(texturePath);
	//TODO delete gl stuff that i generated (glGen...)
	glDeleteVertexArrays(1, &sprite_VAO);
	glDeleteBuffers(1, &sprite_VBO);
	glDeleteBuffers(1, &sprite_EBO);
	glDeleteVertexArrays(1, &select_edge_VAO);
	glDeleteBuffers(1, &select_edge_VBO);
	glDeleteBuffers(1, &select_edge_EBO);
	/*glDeleteVertexArrays(1, &collider_edge_VAO);
	glDeleteBuffers(1, &collider_edge_VBO);
	glDeleteBuffers(1, &collider_edge_EBO);*/

}

void SpriteComp::SpriteSetSprite()
{
	SpriteCreateSprite();
	SpriteCompileShader();
}

void SpriteComp::SpriteCreateRect(GLuint& vao, GLuint& vbo, GLuint& ebo)
{
	// ���� ��ǥ & �簢�� ���� & �ؽ�ó ��ǥ (��ǥ�谡 stbi ���̺귯���� opengl���̺귯���� ���� �޶� y�ุ -�� �޾Ƽ� ������Ŵ)
	float vertices[] = {
		// positions         // colors	// isBorder
		-0.5f, -0.5f, 1.0f,  1.0f, 1.0f, 1.0f,	0,	// top right
		 0.5f, -0.5f, 1.0f,  1.0f, 1.0f, 1.0f,	0,	// bottom right
		 0.5f,  0.5f, 1.0f,  1.0f, 1.0f, 1.0f,	0,	// bottom left
		-0.5f,  0.5f, 1.0f,  1.0f, 1.0f, 1.0f,	0,	// top left 
		-0.5f, -0.5f, 1.0f,  1.0f, 1.0f, 1.0f,	1,	// top right
		 0.5f, -0.5f, 1.0f,  1.0f, 1.0f, 1.0f,	2,	// bottom right
		 0.5f,  0.5f, 1.0f,  1.0f, 1.0f, 1.0f,	3,	// bottom left
		-0.5f,  0.5f, 1.0f,  1.0f, 1.0f, 1.0f,	4	// top left 
	};
	// ���� �ε���
	GLint vertexIndeces[] = {
		0, 4, 5,
		0, 1, 5,
		1, 6, 5,
		1, 2, 6,
		2, 6, 7,
		2, 3, 7,
		3, 7, 4,
		3, 0, 4
	};

	// OpenGL ���� �迭 �����⸦ ����ؼ� VAO�� ����
	glGenVertexArrays(1, &vao);
	// OpenGL ���� �迭 �����⸦ ����ؼ� VBO�� ����
	glGenBuffers(1, &vbo);
	// OpenGL ���� �迭 �����⸦ ����ؼ� EBO�� ����
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);// �츮�� ������ VAO�� ���� ���� �����ϵ��� �����Ѵ�.

	glBindBuffer(GL_ARRAY_BUFFER, vbo);// �츮�� ������ VBO�� ���� ���� �����ϵ��� �����Ѵ�.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// �츮�� ���� �ﰢ�� ���� ��ǥ�� VBO�� �����Ѵ�.

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);// �츮�� ������ VBO�� ���� ���� �����ϵ��� �����Ѵ�.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndeces), vertexIndeces, GL_STATIC_DRAW);// �츮�� ���� �ﰢ�� ���� ��ǥ�� VBO�� �����Ѵ�.
	
	// VAO�� �� VAO�� ��� �ؼ��ؾ� �� �� �˷��ݴϴ�. 
	// �Լ� ���� (vertex attribute, Ÿ�� ũ��, Ÿ��, ����ȭ ����, �޸� ũ��, �޸� ������)
	// GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0); // VAO ��� ��� // layout �ּ� �Ҵ�

	// �簢�� ���� ���� ���ε�
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// �׵θ� id ���� ���ε�
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(3);
}
void SpriteComp::SpriteDrawRectBorder(GLuint& vao, GLfloat lineWidth, glm::vec3 color)
{
	SetBoolShader("useTexture", false);
	SetBoolShader("useBorder", true);
	SetVector2Shader("offset", { lineWidth, lineWidth });
	SetVector4Shader("ecolor", { color.r / 255.f, color.g / 255.f, color.b / 255.f, 1 });
	// Shader ����
	glUseProgram(_shader);

	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	// Shader ����
	glUseProgram(0);
	SetBoolShader("useTexture", true);
	SetBoolShader("useBorder", false);
}

void SpriteComp::SpriteCreateSprite()
{
	// ���� ��ǥ & �簢�� ���� & �ؽ�ó ��ǥ (��ǥ�谡 stbi ���̺귯���� opengl���̺귯���� ���� �޶� y�ุ -�� �޾Ƽ� ������Ŵ)
	float vertices[] = {
		// positions         // colors           // sprite_texture coords
		-0.5f, -0.5f, 1.0f,  1.0f, 1.0f, 1.0f,   0.0f,  0.0f, // top right
		 0.5f, -0.5f, 1.0f,  1.0f, 1.0f, 1.0f,   1.0f,  0.0f, // bottom right
		 0.5f,  0.5f, 1.0f,  1.0f, 1.0f, 1.0f,   1.0f,  1.0f, // bottom left
		-0.5f,  0.5f, 1.0f,  1.0f, 1.0f, 1.0f,   0.0f,  1.0f  // top left 
	};
	// 2D�� ǥ���� �� ������ǥ�� z���� 1�̿��� transform�� �� mat�� ���� �� �� �������� ���� ����ȴ�.

	// ���� �ε���
	GLint vertexIndeces[] = {
		0, 1, 2, // first triangle
		2, 3, 0  // second triangle
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

	//Generate texture
	glGenTextures(1, &sprite_texture);
	glBindTexture(GL_TEXTURE_2D, sprite_texture);
	// �ؽ�ó wrapping/filtering �ɼ� ����(���� ���ε��� �ؽ�ó ��ü�� ����)
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
	// �ؽ�ó �ε� �� ����
	SetTexture(texturePath);

	// End Texture //
}

void SpriteComp::SpriteAddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	// ���̴� ����
	GLuint theShader = glCreateShader(shaderType);

	// ���̴� �ڵ带 ������ �迭 ����
	const GLchar* theCode[1]{};
	theCode[0] = shaderCode;

	// ���̴� �ڵ� ���̸� ������ �迭 ����
	GLint codeLength[1];
	codeLength[0] = (GLint)strlen(shaderCode);

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

void SpriteComp::SpriteCompileShader()
{
	_shader = glCreateProgram();

	if (_shader == NULL)
	{
		printf("Error Creating Shader Program!\n");
		return;
	}

	SpriteAddShader(_shader, spriteVShader, GL_VERTEX_SHADER);
	SpriteAddShader(_shader, spriteFShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	// ���̴� ���α׷� ����
	glLinkProgram(_shader);
	glGetProgramiv(_shader, GL_LINK_STATUS, &result); // _shader �߰��Լ��� �����Լ��� ���� glGetShaderiv-> glGetProgramiv
	if (!result)
	{
		glGetProgramInfoLog(_shader, sizeof(eLog), NULL, eLog);
		printf("Error Linking Program: '%s'\n", eLog);
		return;
	}

	// ���̴� ���α׷� ����
	glValidateProgram(_shader);
	glGetProgramiv(_shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(_shader, sizeof(eLog), NULL, eLog);
		printf("Error Validating Program: '%s'\n", eLog);
		return;
	}
}

void SpriteComp::SpriteDrawSprite()
{
	// Shader ����
	glUseProgram(_shader);

	glBindVertexArray(sprite_VAO);

	glBindTexture(GL_TEXTURE_2D, sprite_texture);

	// �����͸� �������� �׸���
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// ������ ���ε� ����
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	// Shader ����
	glUseProgram(0);
	
}

void SpriteComp::SpriteApplyTransform(float offset)
{
	if(!trans)
		trans = owner->GetComponent<TransformComp>();

	// Shader ����
	glUseProgram(_shader);

	unsigned int transformLoc = glGetUniformLocation(_shader, "transform");

	glm::mat3 transform = trans->GetMatrix();

	Mtx33Scale(&transform, textureSize.x + offset, textureSize.y + offset);

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
		glUseProgram(_shader);
		int channel = 0;
		if (owner->GetComponent<SpriteComp>() != nullptr)
		{
			if (GetFileExt(owner->GetComponent<SpriteComp>()->GetTexturePath()) == "png")
				channel = GL_RGBA;
			else if (GetFileExt(owner->GetComponent<SpriteComp>()->GetTexturePath()) == "jpg")
				channel = GL_RGB;
		}
		
		glTexImage2D(GL_TEXTURE_2D, 0, channel, (GLsizei)textureSize.x, (GLsizei)textureSize.y, 0, channel, GL_UNSIGNED_BYTE, texture);
		glGenerateMipmap(GL_TEXTURE_2D);

		GLint loc = glGetUniformLocation(_shader, "ortho");

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
	���̴� ���� ���� (example. uniform)
	�� ���� ������ ���� shader ���α׷��� �Ѱ� ������ �ϵ��� ����!!!!!
	*/
	glUseProgram(_shader);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);;
	
	//Set transparency
	// ���� �� ���� (1.0�� ������, 0.0�� ���� ����);
	unsigned char loc = glGetUniformLocation(_shader, "ucolor");
	
	glUniform4f(loc, color.r, color.g, color.b, alpha);

	glUseProgram(0);
}

void SpriteComp::SetBoolShader(const std::string& name, bool value) const
{
	glUseProgram(_shader);
	glUniform1i(glGetUniformLocation(_shader, name.c_str()), (int)value);
	glUseProgram(0);
}

void SpriteComp::SetFloatShader(const std::string& name, float value) const
{
	glUseProgram(_shader);
	glUniform1f(glGetUniformLocation(_shader, name.c_str()), value);
	glUseProgram(0);
}

void SpriteComp::SetVector2Shader(const std::string& name, glm::vec2 value) const
{
	glUseProgram(_shader);
	glUniform2f(glGetUniformLocation(_shader, name.c_str()), value.x, value.y);
	glUseProgram(0);
}

void SpriteComp::SetVector3Shader(const std::string& name, glm::vec3 value) const
{
	glUseProgram(_shader);
	glUniform3f(glGetUniformLocation(_shader, name.c_str()), value.x, value.y, value.z);
	glUseProgram(0);
}

void SpriteComp::SetVector4Shader(const std::string& name, glm::vec4 value) const
{
	glUseProgram(_shader);
	glUniform4f(glGetUniformLocation(_shader, name.c_str()), value.x, value.y, value.z, value.w);
	glUseProgram(0);
}

void SpriteComp::Update()
{
	//Set render mode
	//glRenderMode(GL_RENDER);

	//Set transform
	//Get the transform from my owner transfrom comp
	SpriteApplyTransform();

	//Set color 
	SetTransparency();

	// Draw
	SpriteDrawSprite();

	selected = true;
	if (selected || editor::MainEditor::editor_data.ShowCollision)
		SpriteDrawRectBorder(select_edge_VAO, 5, { 255, 0, 0 });

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

std::string SpriteComp::GetFileExt(std::string str)
{
	if (fileExt.find(str) != fileExt.end())
	{
		return fileExt.find(str)->second;
	}
	std::cout << "Invaild fileName" << std::endl;
	return "";
}

void SpriteComp::SetFileExt(std::string str, std::string str2)
{
	if (fileExt.find(str) == fileExt.end())
	{
		fileExt.insert({ str, str2 });
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
