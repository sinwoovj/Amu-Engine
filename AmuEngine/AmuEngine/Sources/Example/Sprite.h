#pragma once
#include "../Level/BaseLevel.h"
#include <string>
#include <opengl.h>

namespace level
{
	class Sprite : public GSM::BaseLevel
	{
		std::string texturePath;
		unsigned char* texture;
		int W, H = 0;
	public:
		void Init() override;
		void Update() override;
		void Exit() override;
		void SetTexture(std::string path);
		void SpriteCreateSprite1();
		void SpriteAddShader1(GLuint theProgram, const char* shaderCode, GLenum shaderType);
		void SpriteCompileShader1();

		~Sprite();

	};
}
