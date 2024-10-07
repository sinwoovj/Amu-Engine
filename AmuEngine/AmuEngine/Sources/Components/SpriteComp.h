#pragma once
#include <string> 
#include "../ComponentManager/GraphicComponent.h"

#include <opengl.h>

class SpriteComp : public GraphicComponent
{
private:

public:
	// 정점 좌표 & 사각형 색상 & 텍스처 좌표 (좌표계가 stbi 라이브러리와 opengl라이브러리의 서로 달라서 y축만 -를 달아서 반전시킴)
	float vertices[24];
	// 정점 인덱스
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
