#include "TextureResource.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../Components/SpriteComp.h"

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

	data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	SpriteComp::SetNativeSize(filename, { width, height });
}

void TextureResource::UnloadData()
{
    if (data != nullptr)
		stbi_image_free(data);

    data = nullptr;
}
