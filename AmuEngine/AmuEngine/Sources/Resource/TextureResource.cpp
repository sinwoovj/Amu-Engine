#include "TextureResource.h"

TextureResource::~TextureResource()
{
    UnloadData();
}

void TextureResource::LoadData(const std::string& filename)
{
    data = GfxTextureLoad(filename.c_str());
}

void TextureResource::UnloadData()
{
    if (data != nullptr)
        GfxTextureUnload(static_cast<GfxTexture*>(data));

    data = nullptr;
}
