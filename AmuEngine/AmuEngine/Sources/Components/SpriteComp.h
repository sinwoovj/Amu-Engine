#pragma once
#include <string> 
#include "../ComponentManager/GraphicComponent.h"
#include "../Components/TransformComp.h"
#include <opengl.h>

class SpriteComp : public GraphicComponent
{
private:
	//color
	glm::vec3 color;
	float alpha;

	//texture 
	static int textureWidth;
	static int textureHeight;
	unsigned char* texture = nullptr;

	//trans
	TransformComp* trans;
	
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
	void SetTexture(std::string s);
	void SpriteSetSprite();
	void SpriteCreateSprite();
	void SpriteAddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	void SpriteCompileShader();
	void SpriteDrawSprite();
	void SpriteApplyTransform();

	//Draw
	void Update() override;

	//Gettors/Settors

	glm::vec3& GetColor() { return color; }
	void SetColor(glm::vec3 Color);
	static int GetTextureWidth() { return textureWidth; }
	static void SetTextureWidth(int width) { textureWidth = width; }
	static int GetTextureHeight() { return textureHeight; }
	static void SetTextureHeight(int height) { textureHeight = height; }
	
	unsigned char& GetTexture() { return *texture; }
	float GetAlpha() { return alpha; }
	void SetAlpha(float Alpha) { alpha = Alpha; }
	void SetTransparency();
	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateSpriteComponent(GameObject* owner);
	static constexpr const char* TypeName = "SpriteComp";
};
