// definitions of the classes, and their members, but not the implementation of the functions.
#include "ECS.h"

#include <bitset>
#include <vector>
#include <algorithm>
#include <set>
#include <typeindex>
#include <unordered_map>

#include "../Logger/MyLogger.h"

int Entity::GetId() const { return id; }


void System::AddEntity(Entity entity)
{
    //TODO. // adding entities
    entities.push_back(entity);
}  // not const because it modifies the state of the object.
void System::RemoveEntityFromSystem(Entity entity)
{
    // removing entities
    // Here is a lambda expression [&entity](Entity other)
    // that means the entity pointer that come in the RemoveEntityFromSystem(parameters)
    // is compared with the all other entities for this kind of loop
    // for (Entity other : entities) {  'other' va cambiando en cada vuelta del bucle:
    // En la vuelta 1 es la primera entidad, en la 2 la segunda, etc.}
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other)
    {
        //return entity.GetId() == other.GetId();
        return entity == other;//after add the == operator overloading
    }), entities.end());
}
std::vector<Entity> System::GetSystemEntities() const
{
    return entities;
}  // constant function, it doesn't modify the state of the object.
const Signature& System::GetComponentSignature() const
{
    return componentSignature;
}  // the const method are not meant to change the state of the object

// ENtity Logic
Entity Registry::CreateEntity()
{
    int entityId;

    entityId = numEntities++;

    Entity entity(entityId);

    entitiesToBeAdded.insert(entity);

    MyLogger::Log("Entity created with the id = " + std::to_string(entityId));

    return entity;
}

void Registry::Update()
{
    //TODO Add the entities that are waiting to be created in the next frame
    //TODO Remove the entities that are waiting to be killed from the active ssytems
    
}