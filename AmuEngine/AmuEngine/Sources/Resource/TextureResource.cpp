#include "TextureResource.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../Components/SpriteComp.h"
#include <Utils.h>

struct textureData
{
	unsigned char* tex;
	int height;
	int width;
};

TextureResource::~TextureResource()
{
    UnloadData();
}

void TextureResource::LoadData(const std::string& filename)
{
	// 텍스처 로드 및 생성
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(1);
	//bool isMultibyte = Utility::isMultibyte(filename);
	data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (stbi_failure_reason())
		std::cout << stbi_failure_reason() << std::endl;
	SpriteComp::SetFileExt(filename, fileExtension);
	SpriteComp::SetNativeSize(filename, { width, height });
	SpriteComp::SetNativeChannel(filename, nrChannels);
}

void TextureResource::UnloadData()
{
    if (data != nullptr)
		stbi_image_free(data);

    data = nullptr;
}
