#pragma once
// declarations of the classes, and their members, but not the implementation of the functions.

#include <bitset>
#include <vector>
#include <algorithm>
#include <set>
#include <typeindex>
#include <unordered_map>
#include "../Logger/MyLogger.h"

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
    public:
    static int GetId()
    {
        static auto id = nextId++;  // assign the current value of nextId to id,
        // and then increment nextId for the next component type.
        // each time GetId is called for a new component type T, it will return a unique ID,
        // starting from 0 and incrementing for each new component type.
        return id;
    }
};

/////////
/// Entity
///////////

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
    Entity(const Entity& other) = default;
    Entity& operator = (const Entity& other) = default;

    int GetId() const;  // constant function, it doesn't modify the state of the object.
    bool operator == (const Entity& other) const{return id == other.id;};
    bool operator != (const Entity& other) const{return id != other.id;};
    bool operator < (const Entity& other) const{return id < other.id;};


    // public function taht simulate the registry funtion but
    // into the Entity class
    // this is good to simple use entity tank, tank.addComponent and not registry->ADdcomponent(tank, Component Args)
    template <typename TComponent, typename... TArgs> void AddComponent(TArgs&&... args);
    template <typename TComponent> void RemoveComponent();
    template <typename TComponent> bool HasComponent() const;
    template <typename TComponent> TComponent& GetComponent() const;

    class Registry* registry;



};

/////////
//System
/////////

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
    void AddEntityToSystem(Entity entity);  // not const because it modifies the state of the object.
    void RemoveEntityFromSystem(Entity entity);
    std::vector<Entity> GetSystemEntities() const;  // constant function, it doesn't modify the state of the object.
    const Signature& GetComponentSignature() const;  // the const method are not meant to change the state of the object

    // Template for the components that the system is interested in.
    template <typename TComponent> void RequireComponent();
    // the implementation of the template function would be in the header file,
    // because it needs to be instantiated for each type T that is used in the system.
};



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

    // VEctor with componentPools
    // Vector index is the component id
    // Pool index is the entity id
    //std::vector<IPool*> componentPools;
    // TODO // Another case that could change a raw pointe by
    // a smart pointer
    std::vector<std::shared_ptr<IPool>> componentPools;

    // Vector of component signatures per entity
    // show the components active for each entity
    // per example ENTITY A has transform and sprite renderer but not light
    // Ent A signature 011 in the bitset
    std::vector<Signature> entityComponentSignatures;

    // List of systems, systems type id
    // std:;type_index creates an index for each system
    // [vector index =  entity id]
    //std::unordered_map<std::type_index, System*> systems;
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

    // there is an interesting approach of create a set for add
    // and a set for delete, this way this process is made in every loop in one shot
    std::set<Entity> entitiesToBeAdded;
    std::set<Entity> entitiesToBeKilled;

public:
    //Registry() = default;
    // as the registry is a smart pointer,
    // we need to define the constructor and destructor
    Registry() { MyLogger::Log("Registry constructor called!"); }
    ~Registry() { MyLogger::Log("Registry destructor called!"); }

    // TODO
    // At start the main focus is create

    // the update is perfomed first
    void Update();

    //Create an entity
    Entity CreateEntity();


    // COMPONENT MANAGER
    //Add Component to an entity, the econd argument is the component data
    //for example, if we want to add a transform component to an entity,
    // we would call AddComponent<Transform>(entity, x, y, z);
    template <typename TComponent, typename... TArgs> void AddComponent(Entity entity, TArgs&&... args);
    // remove component prototype definition
    template <typename TComponent> void RemoveComponent(Entity entity);
    // has component prototype definition
    template <typename TComponent> bool HasComponent(Entity entity) const;
    // Get thecomponent
    template <typename TComponent> TComponent& GetComponent(Entity Entity) const;



    // System API SYSTEM MANAGER
    //add system, remove system, has system, get system
    template <typename TSystem, typename... TArgs> void AddSystem(TArgs&&... args);
    template <typename TSystem> void RemoveSystem();
    template <typename TSystem> bool HasSystem() const;
    template <typename TSystem> TSystem& GetSystem() const;

    // Check the component signature of an entity
    // and add the entity to the systems
    // this is not a template
    // this is implemented on the CPP
    void AddEntityToSystems(Entity entity);

    // I think it lacks of a getting Pool



};

// System Class Template Functions
template <typename TComponent>
void System::RequireComponent() {
    // TODO
    // this function would set the bit corresponding to the component type TComponent in the system's signature.
    // we would need a way to get the index of the component type TComponent, which could be done using a static variable that increments for each new component type.
    const auto componentId = Component<TComponent>::GetId();  // get the index of the component type TComponent.
    componentSignature.set(componentId);  // set the bit corresponding to the component type TComponent in the system's signature.
}

////////// Systems Registry API
// These are the template functions for the Registry class,
// they need to be defined in the header file because they are templates and need to be instantiated for each type T that is used in the system.
template <typename TSystem, typename... TArgs>
void Registry::AddSystem(TArgs&&... args)
{
    //TSystem* newSystem(new TSystem(std::forward<TArgs>(args)...));
    // TODO good place to use smart pointer here.
    // std::shared_ptr<TSystem> type of the pointer
    // std::make_shared<TSystem> cretes an instance of the system
    std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
    systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem>
void Registry::RemoveSystem()
{
    // a new refrence of the system is created and
    // afterwards the system is removed from the systems map using the erase function
    // which takes an iterator as an argument.
    auto system = systems.find(std::type_index(typeid(TSystem)));
    systems.erase(system);
}

template <typename TSystem>
bool Registry::HasSystem() const
{
    return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

template <typename TSystem>
TSystem& Registry::GetSystem() const
{
    //return systems.find(std::type_index(typeid(TSystem)))->second;
    // this line of code is doing the same thing as the previous one,
    //but it is more efficient because it doesn't need to search for the system twice.
    auto system = systems.find(std::type_index(typeid(TSystem)));
    //then get the system from the map using the iterator,
    // and return the second element of the pair, which is a pointer to the system,
    // and cast it to the correct type using static_pointer_cast.
    return *(std::static_pointer_cast<TSystem>(system->second));
    // the cast is made because the systems map stores pointers
    // to the base class System, but we need to return a reference
    // to the derived class TSystem.
}





/////////////////////////////////////
////////// Components Registry API
/////////////////////////////////////
// Component Template Functions
template <typename TComponent, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs&&... args)
{
    // get the component id for the component type TComponent
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();

    // check before create the component object
    if(componentId >= static_cast<int>(componentPools.size())) // could be also //componentPools.size() <= componentId
    {
        // if the component pool for this component type doesn't exist, create it
        componentPools.resize(componentId + 1, nullptr);
    }

    if (!componentPools[componentId])//componentPools[componentId] == nullptr
    {
        // if the component pool for this component type doesn't exist, create it
        // Here a new Pool is allocated in the heap,
        // and a pointer to it is stored in the componentPools vector
        //  at the index corresponding to the componentId.
        //Pool<TComponent>* newComponentPool = new Pool<TComponent>();
        // TODO here could be a good place tot use smart ptr.

        std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();

        componentPools[componentId] = newComponentPool;
    }

    //Pool<TComponent>* componentPool = static_cast<Pool<TComponent>*>(componentPools[componentId]);
    //Pool<TComponent>* componentPool = componentPools[componentId];
    std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);

    if(entityId >= static_cast<int>(componentPool->GetSize()))
    {
        componentPool->Resize(numEntities);
    }

    // this is a kind of instance of the component, with the provided arguments,
    // and it is added to the component pool for this component type,
    // at the index corresponding to the entity ID.
    TComponent newComponent(std::forward<TArgs>(args)...);
    // create a new component of type TComponent with the provided arguments.

    componentPool->Set(entityId, newComponent);
    // add the new component to the component pool

    entityComponentSignatures[entityId].set(componentId);
    // set the bit corresponding to the component type TComponent in the entity's signature,
    // to indicate that this entity now has this component type.

    MyLogger::Log("Component id = " + std::to_string(componentId) + " was added to entity id = " + std::to_string(entityId));
}

template <typename TComponent>
void Registry::RemoveComponent(Entity entity)
{
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();

    // this simply disables the bit corresponding to the component type T
    // in the entity's signature.
    entityComponentSignatures[entityId].set(componentId, false);
}

template <typename TComponent>
bool Registry::HasComponent(Entity entity) const
{
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();

    // this checks if the bit corresponding to the component type T
    // is set in the entity's signature,
    // the test function of the bitset returns true if the bit is set, and false otherwise.
    return entityComponentSignatures[entityId].test(componentId);
}

template <typename TComponent>// I think this should be get Components plural
TComponent& Registry::GetComponent(Entity entity) const
{
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();
    // GEtting the component pool
    auto componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);
    return componentPool->Get(entityId);
}




//////////
/// Entity same REgistry function copy
/////////

template <typename TComponent, typename ...TArgs>
void Entity::AddComponent(TArgs&&... args)
{
    //TODO
    // I'll use the same function of registry
    // and passing the entity as pointer
    registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);

}

template <typename TComponent>
void Entity::RemoveComponent()
{
    //TODO
    registry->RemoveComponent<TComponent>(*this);
}

template <typename TComponent>
bool Entity::HasComponent() const
{
    //TODO
    return registry->HasComponent<TComponent>(*this);
}

template <typename TComponent>// I think this should be get Components plural
TComponent& Entity::GetComponent() const
{
    //TODO
    return registry->GetComponent<TComponent>(*this);
}
