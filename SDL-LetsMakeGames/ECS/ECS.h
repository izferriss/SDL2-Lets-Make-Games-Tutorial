#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

/* ENTITY COMPONENT SYSTEM (<_< advanced)

Entities are things in the (game) world
Components are the data within entities
Systems update the entity data

*/

//Forward declarations

//A base class from which components will inherit
class Component;
//A class that acts a collection of components
class Entity;

//typedef for the component ID type
using ComponentID = std::size_t;

//Returns next usable unique ID
inline ComponentID getComponentTypeID()
{
	//static allows each call of this function to refer to the same "lastID"
	static ComponentID lastID = 0;
	return lastID++;
}

//Returns a component's typeID
//Calling this function multiple times with the ***same type "T"*** will return the same results
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

//Maximum number of components
constexpr std::size_t maxComponents = 32;

//typedef a bitset of maxComponents
using ComponentBitSet = std::bitset<maxComponents>;

//typedef an array of component pointers with maxComponents bitset
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

//Keeps a list of components
class Entity
{
private:
	bool active = true;

	//vector of unique pointers to Components
	std::vector<std::unique_ptr<Component>> components;

	//Array to quickly get a component with a specific ID
	ComponentArray componentArray;
	//Bitset to check the existence of a component with a specific ID
	ComponentBitSet componentBitSet;
public:
	void update()
	{
		for (auto& c : components) c->update();
	}
	void draw() 
	{
		for (auto& c : components) c->draw();
	}

	bool isActive() const { return active; }
	void destroy() { active = false; }

	//Checks if this entity has a component by checking the bitset for a specific ID
	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	//Allows adding of components to an entity
	//T is the type of component
	//TArgs are any arguments
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&...mArgs)
	{

		//Allocates "T" on the heap by forwarding the passed arguments to the constructor and stores it in "c" (component)
		T* c(new T(std::forward<TArgs>(mArgs)...));

		//We set the component's entity to the current instance
		c->entity = this;

		//Wraps the above pointer into a smart pointer and places it into the vector
		std::unique_ptr<Component>uPtr{ c };
		components.emplace_back(std::move(uPtr));

		//Adds component type "T" to the bitset and array of the Entity
		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		//Initializes the component
		c->init();
		return *c;
	}

	//Retrieves a specific component from this entity
	template <typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

//Keeps a list of entities
class Manager
{
private:
	//vector of unique pointers to Entities
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update()
	{
		for (auto& e : entities) e->update();
	}

	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	//Cleans up "dead" entities
	void refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(entities));
	}

	Entity& addEntity()
	{
		Entity* e = new Entity();

		//Wraps the above pointer into a smart pointer and places it into the vector
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));

		return *e;
	}
};