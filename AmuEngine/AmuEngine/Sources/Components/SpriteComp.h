#pragma once
#include <string> 
#include "../ComponentManager/GraphicComponent.h"
#include "../Components/TransformComp.h"
#include <opengl.h>
#include <Size.h>

class SpriteComp : public GraphicComponent
{
private:
	//color
	glm::vec3 color;
	float alpha;

	//texture 
	glm::vec2 textureSize;
	static std::map<std::string, glm::vec2> nativeSize;

	unsigned char* texture = nullptr;

	//trans
	TransformComp* trans;
	
	GLuint sprite_VAO;
	GLuint sprite_VBO;
	GLuint sprite_EBO;
	GLuint sprite_shader;
	GLuint sprite_texture;

	std::string texturePath;

	int orderinLayer = 0;
public:
	GameObject* owner;
	SpriteComp(GameObject* _owner);
	~SpriteComp();

	//Setting
	bool SetTexture(std::string s);
	void SpriteSetSprite();
	void SpriteCreateSprite();
	void SpriteAddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	void SpriteCompileShader();
	void SpriteDrawSprite();
	void SpriteApplyTransform();

	
	//Draw
	void Update();

	//Gettors/Settors

	glm::vec3& GetColor() { return color; }
	void SetColor(glm::vec3 Color);

	glm::vec2 GetTextureSize() { return textureSize; }
	void SetTextureSize(glm::vec2 size) { textureSize = size; }

	static glm::vec2 GetNativeSize(std::string str);
	static void SetNativeSize(std::string str, glm::vec2 size);
	
	void SetScale();
	
	std::string GetTexturePath() { return texturePath; }
	
	unsigned char& GetTexture() { return *texture; }
	
	float GetAlpha() { return alpha; }
	void SetAlpha(float Alpha) { alpha = Alpha; }
	
	void SetTransparency();

	int GetOrderInlayer() { return orderinLayer; }
	void GetOrderInlayer(int num) { orderinLayer = num; }

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void Edit() override;

	static BaseRTTI* CreateSpriteComponent(GameObject* owner);
	static constexpr const char* TypeName = "SpriteComp";
	static constexpr const char* DefaultSprite = "./Sources/Assets/Sprite/default.png";
};
