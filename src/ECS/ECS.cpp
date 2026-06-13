// definitions of the classes, and their members, but not the implementation of the functions.
#include "ECS.h"

#include <bitset>
#include <vector>
#include <algorithm>
#include <set>
#include <typeindex>
#include <unordered_map>

#include "../Logger/MyLogger.h"

int IComponent::nextId = 0;
// initialize the static variable to keep track of the next available component ID

int Entity::GetId() const { return id; }


void System::AddEntityToSystem(Entity entity)
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

    // this is the id of the entity, and it is incremented for each new entity created.
    entityId = numEntities++;
    // the contructor of the entity class is called with the id, and the entity is created.
    Entity entity(entityId);

    // the set  of entities to be added
    entitiesToBeAdded.insert(entity);

    MyLogger::Log("Entity created with the id = " + std::to_string(entityId));

    return entity;
}

void Registry::AddEntityToSystems(Entity entity)
{
    const auto entityId = entity.GetId();
    const auto& entityComponentSignature = entityComponentSignatures[entityId];

    // Loop for comparison
    for (auto& system: systems)
    {
        const auto& systemComponentSignature = system.second->GetComponentSignature();

        // this part check bit by bit if the entity has all the components that the system requires,
        // and if it does, it adds the entity to the system.
        bool isInterested = (entityComponentSignature & systemComponentSignature) == systemComponentSignature;

        if (isInterested)
        {
            system.second->AddEntityToSystem(entity);
        }
    }
}

void Registry::Update()
{
    //TODO Add the entities that are waiting to be created in the next frame
    //TODO Remove the entities that are waiting to be killed from the active ssytems

}
