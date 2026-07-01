#pragma once

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include <SDL.h>
#include "../AssetStore/AssetStore.h"

class RenderSystem: public System
{
    public:
    RenderSystem()
    {
        //TODO:
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
    }

    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore)
    {
        // Approach to implement a Z order funtionality
        struct RendereableEntity
        {
            TransformComponent transformComponent;
            SpriteComponent spriteComponent;
        };
        std::vector<RendereableEntity> rendereableEntities;

        // Fill the rendereableEntities array
        for (auto entity: GetSystemEntities())
        {
            RendereableEntity rendereableEntity;
            rendereableEntity.transformComponent = entity.GetComponent<TransformComponent>();
            rendereableEntity.spriteComponent = entity.GetComponent<SpriteComponent>();
            rendereableEntities.emplace_back(rendereableEntity);
        }

        //Applying the sort
        std::sort(rendereableEntities.begin(), rendereableEntities.end(),
                  [](const RendereableEntity& a, const RendereableEntity& b) {
                      //
                      return a.spriteComponent.zIndex < b.spriteComponent.zIndex;
                  });

        for (auto entity : rendereableEntities) {
            //const auto transform = entity.GetComponent<TransformComponent>();
            //const auto sprite = entity.GetComponent<SpriteComponent>();
            const auto transform = entity.transformComponent;
            const auto sprite = entity.spriteComponent;

            // Set the source
            SDL_Rect srcRect = sprite.srcRect;

            // Set the destination
            SDL_Rect dstRect = {static_cast<int>(transform.position.x),
                                static_cast<int>(transform.position.y),
                                static_cast<int>(sprite.width * transform.scale.x),
                                static_cast<int>(sprite.height * transform.scale.y)
            };

            SDL_RenderCopyEx(
                renderer,
                assetStore->GetTexture(sprite.assetId),
                &srcRect,
                &dstRect,
                transform.rotation,
                NULL,
                SDL_FLIP_NONE);
        }
    }
};
