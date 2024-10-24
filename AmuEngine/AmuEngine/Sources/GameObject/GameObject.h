#pragma once
#include <map>
#include <string>
#include <json.hpp>

using json = nlohmann::ordered_json;	// Map. Orders the order the variables were declared in

class BaseComponent;

class GameObject
{
private:
	//GO now will have a container of BaseComponent*
	std::map<std::string, BaseComponent*> component;
	std::string prefabName;
	std::string name;
	std::string layer;
	std::string tag;

public:

	enum Type
	{
		None,
		Square,
		LeftTri,
		RightTri,
		Point,
		Player,
		Button,
		Enemy,
		Particle,
		Checker,
	};

	GameObject(std::string str);
	GameObject(const GameObject& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;

	//Layer & Tag
	void SetLayer(std::string str) { layer = str; }
	std::string GetLayer() { return layer; }
	void SetTag(std::string str) { tag = str; }
	std::string GetTag() { return tag; }

	void LoadLayer();

	void LoadTag();

	//Components in the GO container are ALLOCATED IN THE HEAP, 
	//so. When to GO is destroyed, the GO must be as well
	~GameObject();

	//GO will have a function to add ANY TYPE of component class to their container
	template <typename T>
	T* AddComponent();

	template <typename T>
	T* AddComponent(BaseComponent* comp);

	void AddComponent(std::string name);
	
	bool ExistSingletonComponent(std::string name);

	bool ExistComponent(std::string name);

	//GO will have a function to find if it already has a component of ANY TYPE
	template <typename T>
	T* GetComponent();
	template <typename T>
	T* GetComponent() const;

	std::string GetName() { return name; } 
	void LoadFromJson(std::string name, json& comp);
	
	std::map<std::string, BaseComponent*> GetComponents() { return component; }

	//GO will have a function to delete ANY TYPE of component
	template <typename T>
	void DeleteComponent();

	void RemoveComponent(std::string name);

	void clear(); // 이미 Gameobject 소멸자에서 이 함수의 역할을 해줌.

	Type type;

	friend class Serializer;
	friend class Prefab;
};

#include "GameObject.inl"