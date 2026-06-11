#pragma once
// declarations of the classes, and their members, but not the implementation of the functions.

#include <bitset>
#include <vector>
#include <algorithm>
#include <set>
#include <typeindex>
#include <unordered_map>

const unsigned int MAX_COMPONENTS = 32;  // maximum number of components that can be attached to an entity.
//
typedef std::bitset<MAX_COMPONENTS> Signature;  // a bitset to keep track of which components are attached to an entity.

struct IComponent{
    protected:
    static int nextId;  // static variable to keep track of the next available component ID
};

// use to assign a unique ID to each component type.
template <typename T>
class Component : public IComponent {
    // TODO
    //return the unique ID for the component type T,
    //which would be used to set the bit in the entity's signature.
    static int GetId()
    {
        static auto id = nextId++;  // assign the current value of nextId to id,
        // and then increment nextId for the next component type.
        // each time GetId is called for a new component type T, it will return a unique ID,
        // starting from 0 and incrementing for each new component type.
        return id;
    }
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
    bool operator == (const Entity& other) const{return id == other.id;};
    bool operator != (const Entity& other) const{return id != other.id;};
    bool operator < (const Entity& other) const{return id < other.id;};
    Entity& operator = (const Entity& other) = default;
};

class System {
    // TODO
    // the system would be responsible for processing entities that have a specific set of
    // components.
private:
    Signature componentSignature;  // the signature of the system, which components it is interested in.
    std::vector<Entity> entities;  // the entities that are currently being processed by the system.

public:
    // this would be the constructor.
    System() = default;   // default constructor, it doesn't do anything special.
    ~System() = default;  // default destructor, it doesn't do anything special.

    // utilities for managing the entities in the system.
    void AddEntity(Entity entity);  // not const because it modifies the state of the object.
    void RemoveEntityFromSystem(Entity entity);
    std::vector<Entity> GetSystemEntities() const;  // constant function, it doesn't modify the state of the object.
    const Signature& GetComponentSignature() const;  // the const method are not meant to change the state of the object

    // Template for the components that the system is interested in.
    template <typename TComponent> void RequireComponent();
    // the implementation of the template function would be in the header file,
    // because it needs to be instantiated for each type T that is used in the system.
};

template <typename TComponent> void System::RequireComponent() {
    // TODO
    // this function would set the bit corresponding to the component type TComponent in the system's signature.
    // we would need a way to get the index of the component type TComponent, which could be done using a static variable that increments for each new component type.
    const auto componentId = Component<TComponent>::GetId();  // get the index of the component type TComponent.
    componentSignature.set(componentId);  // set the bit corresponding to the component type TComponent in the system's signature.
}

///
/// Registry Area
/// Registry manages the creation and destruction of the entities, as well as adding systems
///
///Pool Class
///
class IPool
{
public:
    virtual ~IPool() = default;
};
template <typename T>
class Pool : public IPool
{
private:
    std::vector<T> data;

public:
    Pool(int size = 100)
    {
        data.resize(size);
    }
    virtual ~Pool() = default;

    bool isEmpty() const
    {
        return data.empty();
    }

    int GetSize() const
    {
        return data.size();
    }

    void Resize(int n)
    {
        data.resize(n);
    }

    void Clear()
    {
        data.clear();
    }

    void Add(T object)
    {
        data.push_back(object);
    }

    // Set is like replaced
    //  in a CRUD approach would be update
    void Set(int index, T object)
    {
        data[index] = object;
    }

    T& Get(int index)
    {
        return static_cast<T&>(data[index]);
    }

    T& operator [](unsigned int index)
    {
        return data[index];
    }

};


class Registry {
    // TODO // Manager // Entity manager// World
    // how many entities are registered

    private:
    //Keep track of many entities were added to the scene
    int numEntities = 0;

    // there is an interesting approach of create a set for add
    // and a set for delete, this way this process is made in every loop
    std::set<Entity> entitiesToBeAdded;
    std::set<Entity> entitiesToBeKilled;

    // VEctor with componentPools
    // Vector index is the component id
    // Pool index is the entity id
    std::vector<IPool*> componentPools;

    // Vector of component signatures per entity
    // show the components active for each entity
    // per example ENTITY A has transform and sprite renderer but not light
    // Ent A signature 011 in the bitset
    std::vector<Signature> entityComponentSignatures;

    // List of systems, systems type id
    // std:;type_index creates an index for each system
    // [vector index =  entity id]
    std::unordered_map<std::type_index, System*> systems;

public:
    Registry() = default;

    // TODO
    // At start the main focus is create

    void Update();

    //Create an entity
    Entity CreateEntity();

    // Is needed a function to add a component to the entity
    // TODO: AddComponent<T>(...);

    void AddEntityToSystem(Entity entity);

    // kill an entity
    //
    // add component
    // remove component
    // has component
    //
    //add system
    //remove system
    // has system
    // get system






};
