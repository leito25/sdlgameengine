#include "AssetStore.h"
#include "../Logger/MyLogger.h"

AssetStore::AssetStore() { MyLogger::Log("Asset Store constructor called"); }

AssetStore::~AssetStore() { MyLogger::Log("Asset Store destructor called"); }

void AssetStore::ClearAssets()
{
    //TODO: Clear Assets
    for ( auto texture : textures)
    {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();
}

void AssetStore::AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath)
{
    //TODO: Add a new texture
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Add the texture tot he map
    textures.emplace(assetId, texture);

    MyLogger::Log("New texture to the asset store with id: " + assetId);
}

SDL_Texture* AssetStore::GetTexture(const std::string& assetId)
{
    //TODO: GEtting a texture based on the id
    return textures[assetId];
}
