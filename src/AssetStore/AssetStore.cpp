#include "AssetStore.h"
#include "../Logger/MyLogger.h"

AssetStore::AssetStore() { MyLogger::Log("Asset Store constructor called"); }

AssetStore::~AssetStore() { MyLogger::Log("Asset Store constructor called"); }

void AssetStore::ClearAssets()
{
    //TODO: Clear Assets
}

void AssetStore::AddTexture(const std::string& assetId, const std::string& filePath)
{
    //TODO: Add a new texture
}

SDL_Texture* AssetStore::GetTexture(const std::string& assetId) const
{
    //TODO: GEtting a texture based on the id

}
