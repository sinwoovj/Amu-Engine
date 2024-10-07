#pragma once
#include <string> 
#include "../ComponentManager/GraphicComponent.h"

#include <opengl.h>

class SpriteComp : public GraphicComponent
{
private:

public:
	// ���� ��ǥ & �簢�� ���� & �ؽ�ó ��ǥ (��ǥ�谡 stbi ���̺귯���� opengl���̺귯���� ���� �޶� y�ุ -�� �޾Ƽ� ������Ŵ)
	float vertices[24];
	// ���� �ε���
	GLint vertexIndeces[6];

private:
	//color
	struct Color
	{
		float r = 0.f;
		float g = 0.f;
		float b = 0.f;
	} color;
	float Alpha;
	
	GLuint sprite_VAO;
	GLuint sprite_VBO;
	GLuint sprite_EBO;
	GLuint sprite_shader;
	GLuint sprite_texture;

	std::string texturePath;

public:
	SpriteComp(GameObject* _owner);
	~SpriteComp();

	//Setting
	void SpriteCreateSprite();
	void SpriteAddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	void SpriteCompileShader();
	void SpriteDrawSprite();
	void SpriteApplyTexture(std::string path);

	//Draw
	void Update() override;

	//Gettors/Settors

	Color& GetColor() { return color; }
	void SetColor(Color Color) { color = Color; }

	void SetTexture(std::string s);
	float GetAlpha() { return Alpha; }
	void SetAlpha(float alpha) { Alpha = alpha; }
	void SetTransparency(float alpha);
	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateSpriteComponent(GameObject* owner);
	static constexpr const char* TypeName = "SpriteComp";
};
