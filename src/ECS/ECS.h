#pragma once
// declarations of the classes, and their members, but not the implementation of the functions.

#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENTS =
    32;  // maximum number of components that can be attached to an entity.
//
typedef std::bitset<MAX_COMPONENTS>
    Signature;  // a bitset to keep track of which components are attached to an entity.

class Component {
    // TODO
};

class Entity {
    // TODO
    //  At start the the entity would be
    //  just a simple id.

    // TODO
private:
    int id;

public:
    // this would be the constructor.
    Entity(int id) : id(id) {};
    int GetId() const;  // constant function, it doesn't modify the state of the object.
};

class System {
    // TODO
    // the system would be responsible for processing entities that have a specific set of
    // components.
private:
    Signature signature;  // the signature of the system, which components it is interested in.
    std::vector<Entity> entities;  // the entities that are currently being processed by the system.

public:
    // this would be the constructor.
    System() = default;   // default constructor, it doesn't do anything special.
    ~System() = default;  // default destructor, it doesn't do anything special.

    // utilities for managing the entities in the system.
    void AddEntity(Entity entity);  // not const because it modifies the state of the object.
    void RemoveEntityFromSystem(Entity entity);
    std::vector<Entity> GetSystemEntities()
        const;  // constant function, it doesn't modify the state of the object.
    Signature& GetComponentSignature()
        const;  // the const method are not meant to change the state of the object
};

class Registry {
    // TODO
};
