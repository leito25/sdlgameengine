#pragma once

#include "../ECS/ECS.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"


class AnimationSystem: public System
{
    public:
    AnimationSystem()
    {
        //TODO:
        RequireComponent<SpriteComponent>();
        RequireComponent<AnimationComponent>();
    }

    void Update()
    {
        //TODO:
        // run the animation based on the sprite data
        for ( auto entity : GetSystemEntities())
        {
            auto& animation = entity.GetComponent<AnimationComponent>();//reference beacuse may could change their value
            auto& sprite = entity.GetComponent<SpriteComponent>();

            animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.frameSpeedRate / 1000) % animation.numFrames;
            sprite.srcRect.x = animation.currentFrame * sprite.width;
            /*MyLogger::Log("AnimSys SDL GetTicks: " + std::to_string(SDL_GetTicks()));
            MyLogger::Log("AnimSys animation.startTime: " + std::to_string(animation.startTime));
            MyLogger::Log("AnimSys animation.frameSpeedRate: " + std::to_string(animation.frameSpeedRate));
            MyLogger::Log("AnimSys animation.numFrames: " + std::to_string(animation.numFrames));

            MyLogger::Log("--> AnimSys animation.currentFrame: " + std::to_string(animation.currentFrame));*/
        }
    }
};
