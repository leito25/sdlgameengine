#pragma once

#include <map>
#include <string>
#include <SDL.h>
#include <iostream>

class AssetStore
{
    private:
        std::map<std::string, SDL_Texture*> textures;
        //TODO: create map with fonts
        //TODO: create map with audios

    public:
        AssetStore();
        ~AssetStore();

        void ClearAssets();
        void AddTexture(const std::string& assetId, const std::string& filePath);
        SDL_Texture* GetTexture(const std::string&) const;
};
