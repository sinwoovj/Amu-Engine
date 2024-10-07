#include "SpriteComp.h"
#include "TransformComp.h"
#include "../ResourceManager/ResourceManager.h"

// ���� ���̴� Vertex Shader
const char* spriteVShader = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 transform;

void main()
{
	gl_Position = vec4(aPos, 1.0f);	// transform * vec problem
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
	FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1); //texture is white
})";

int SpriteComp::textureWidth = 0;
int SpriteComp::textureHeight = 0;

SpriteComp::SpriteComp(GameObject* _owner) : GraphicComponent(_owner)
{
	texturePath = "";
	color = { 1.f,1.f,1.f };
	Alpha = 1;
	sprite_EBO = 0;
	sprite_VAO = 0;
	sprite_VBO = 0;
	sprite_shader = 0;
	sprite_texture = 0;
	trans = nullptr;
	SpriteSetSprite();
}

SpriteComp::~SpriteComp()
{
	ResourceManager::GetInstance().UnloadResource(texturePath);
}

void SpriteComp::SpriteSetSprite()
{
	SpriteCreateSprite();
	SpriteCompileShader();
}

void SpriteComp::SpriteCreateSprite()
{
	// ���� ��ǥ & �簢�� ���� & �ؽ�ó ��ǥ (��ǥ�谡 stbi ���̺귯���� opengl���̺귯���� ���� �޶� y�ุ -�� �޾Ƽ� ������Ŵ)
	float vertices[] = {
		// positions   // colors           // sprite_texture coords
		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, -1.0f, // top right
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f,   1.0f,  0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   0.0f,  0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, -1.0f  // top left 
	};

	// ���� �ε���
	GLint vertexIndeces[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
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

	glGenTextures(1, &sprite_texture);
	glBindTexture(GL_TEXTURE_2D, sprite_texture);
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
	SetTexture(texturePath);

	// End Texture //
}

void SpriteComp::SpriteAddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
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
}

void SpriteComp::SpriteDrawSprite()
{
	glBindTexture(GL_TEXTURE_2D, sprite_texture);

	// Shader ����
	glUseProgram(sprite_shader);

	glBindVertexArray(sprite_VAO);

	// �����͸� �������� �׸���
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// ������ ���ε� ����
	glBindVertexArray(0);

	// Shader ����
	glUseProgram(0);
}

void SpriteComp::SpriteApplyTransform()
{
	if(!trans)
		trans = owner->GetComponent<TransformComp>();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(trans->GetScale(), 0.0f));
	model = glm::rotate(model, trans->GetRot(), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(trans->GetScale(),1.0f));


	unsigned int transformLoc = glGetUniformLocation(sprite_shader, "transform");





	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void SpriteComp::SetTexture(std::string path)
{
	if (path == texturePath || path == "")
		return;

	if (texturePath != path)
		ResourceManager::GetInstance().UnloadResource(texturePath);
	
	texturePath = path;

	texture = ResourceManager::GetInstance().GetResource<unsigned char>(path);

	if (texture)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture : " << texturePath << std::endl;
	}
}

void SpriteComp::SetTransparency(float alpha)
{
	//Set blend Mode
	glEnable(GL_BLEND);// you enable blending function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//GfxSetBlendMode(GFX_BM_BLEND);

	//Set transparency
	// ���� �� ���� (1.0�� ������, 0.0�� ���� ����)
	glColor4f(color.r, color.g, color.b, alpha);
}

void SpriteComp::Update()
{
	//Set render mode
	//glRenderMode(GL_RENDER);

	//Set color 
	SetColor({ color.r, color.g, color.b });
	SetTransparency(Alpha);


	//Set transform
	//Get the transform from my owner transfrom comp
	SpriteApplyTransform();

	SpriteDrawSprite();
}

void SpriteComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("texturePath");
		texturePath = it.value();
		SetTexture(texturePath);

		it = compData->find("alpha");
		Alpha = it.value();
	}
}

json SpriteComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["texturePath"] = texturePath;
	compData["alpha"] = Alpha;
	data["compData"] = compData;

	return data;
}

BaseRTTI* SpriteComp::CreateSpriteComponent(GameObject* owner)
{
	BaseRTTI* p = new SpriteComp(owner);
	owner->AddComponent<SpriteComp>(static_cast<SpriteComp*>(p));
	return p;
}
