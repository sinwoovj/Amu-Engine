#pragma once
#include <map>
#include <string>
#include "../GameObject/GameObject.h"

namespace BOMB
{
	class BombManager
	{
		//Singleton = Only 1 object
		//	Prevent others creating me
	private:
		std::map<std::string, GameObject*> bombs;

		BombManager() = default;

		//	Remove the compiler defined Copy Constructor and Assignment operator
		BombManager(const BombManager& other) = delete;
		const BombManager& operator=(const BombManager& other) = delete;

		//	Prevent others destroying me
		~BombManager();

		//	Pointer to the exisiting Singleton can be accessed without an obj and from me only
		static BombManager* ptr;

		//	Functions that anyone can access to:
	public:
		static BombManager& GetInstance()
		{
			static BombManager instance;
			return instance;
		}

		///////////////////////////////
	private:


	public:
		//Functions to call Init, Update, Exit
		void Update();

		std::map<std::string, GameObject*>& GetAllBombs() { return bombs; }

		void AddBomb(GameObject* obj);

		void RemoveBomb(GameObject* obj);
	};
}