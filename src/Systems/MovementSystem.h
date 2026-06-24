#pragma once

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"

class MovementSystem: public System
{
    public:
    MovementSystem()
    {
        //TODO:
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    void Update()
    {
        //TODO:
        // Loop all the entities that the system is interested in
        for (auto entity: GetSystemEntities())
        {
            MyLogger::Log("Entity id: " + std::to_string(entity.GetId()));
            auto& transform = entity.GetComponent<TransformComponent>();
            const auto rigidbody = entity.GetComponent<RigidBodyComponent>();

            transform.position.x += rigidbody.velocity.x;
            transform.position.y += rigidbody.velocity.y;

            MyLogger::Log(
                "Entity id = " + std::to_string(entity.GetId()) +
                    " Positionis now:  " + "( X: " + std::to_string(transform.position.x) +
                    ("Adding componenets a un encaul") + std::to_string(transform.position.y));
        }
    }
};
