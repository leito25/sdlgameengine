// definitions of the classes, and their members, but not the implementation of the functions.
#include "ECS.h"

int Entity::GetId() const { return id; }


void System::AddEntity(Entity entity)
{
    //TODO. // adding entities
    entities.push_back(entity);
}  // not const because it modifies the state of the object.
void System::RemoveEntityFromSystem(Entity entity)
{
    //TODO // removing entities
    if (auto it = std::find(entities.begin(), entities.end(), entity); it != entities.end())
    {
        entities.erase(it);
    }
}
std::vector<Entity> System::GetSystemEntities() const
{
    return entities;
}  // constant function, it doesn't modify the state of the object.
const Signature& System::GetComponentSignature() const
{
    return componentSignature;
}  // the const method are not meant to change the state of the object
