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
	bool selected;

	//texture 
	glm::vec2 textureSize;
	static std::map<std::string, glm::vec2> nativeSize;
	static std::map<std::string, std::string> fileExt;

	unsigned char* texture = nullptr;

	//trans
	TransformComp* trans;
	
	//shader
	GLuint _shader;

	//sprite
	GLuint sprite_VAO;
	GLuint sprite_VBO;
	GLuint sprite_EBO;
	GLuint sprite_texture;
	std::string texturePath;

	//select edge
	GLuint select_edge_VAO;
	GLuint select_edge_VBO;
	GLuint select_edge_EBO;

	//collider edge
	GLuint collider_edge_VAO;
	GLuint collider_edge_VBO;
	GLuint collider_edge_EBO;


	int orderinLayer = 0;
public:
	GameObject* owner;
	SpriteComp(GameObject* _owner);
	~SpriteComp();

	//Setting
	bool SetTexture(std::string s);
	void SpriteAddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	void SpriteCompileShader();
	void SpriteSetSprite();
	void SpriteCreateSprite();
	void SpriteDrawSprite();
	void SpriteCreateRect(GLuint& vao, GLuint& vbo, GLuint& ebo);
	void SpriteDrawRectBorder(GLuint& vao, GLfloat lineWidth, glm::vec3 color);
	void SpriteApplyTransform(float offset = 0.0f);
	
	//Draw
	void Update();

	//Gettors/Settors

	glm::vec3& GetColor() { return color; }
	void SetColor(glm::vec3 Color);

	glm::vec2 GetTextureSize() { return textureSize; }
	void SetTextureSize(glm::vec2 size) { textureSize = size; }

	static glm::vec2 GetNativeSize(std::string str);
	static void SetNativeSize(std::string str, glm::vec2 size);

	static std::string GetFileExt(std::string str);
	static void SetFileExt(std::string str, std::string str2);
	
	void SetScale();
	
	std::string GetTexturePath() { return texturePath; }
	
	unsigned char& GetTexture() { return *texture; }
	
	float GetAlpha() { return alpha; }
	void SetAlpha(float Alpha) { alpha = Alpha; }
	
	void SetTransparency();

	void SetBoolShader(const std::string& name, bool value) const;

	void SetFloatShader(const std::string& name, float value) const;

	void SetVector2Shader(const std::string& name, glm::vec2 value) const;

	void SetVector3Shader(const std::string& name, glm::vec3 value) const;

	void SetVector4Shader(const std::string& name, glm::vec4 value) const;

	int GetOrderInlayer() { return orderinLayer; }
	void GetOrderInlayer(int num) { orderinLayer = num; }

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void Edit() override;

	static BaseRTTI* CreateSpriteComponent(GameObject* owner);
	static constexpr const char* TypeName = "SpriteComp";
	static constexpr const char* DefaultSprite = "./Sources/Assets/Sprite/default.png";
};
