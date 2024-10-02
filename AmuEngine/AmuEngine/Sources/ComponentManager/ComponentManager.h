#pragma once
#include <vector>

template <typename T>
class ComponentManager
{
private:
	ComponentManager();
	ComponentManager(const ComponentManager& other) = delete;
	const ComponentManager& operator=(const ComponentManager& other) = delete;
	~ComponentManager();

	std::vector<T*> component;

public:
	static ComponentManager& GetInstance()
	{
		static ComponentManager instance;
		return instance;
	};

	void AddComp(T* comp);
	void DelComp(T* comp);

	void Update();
};

#include "ComponentManager.inl"
