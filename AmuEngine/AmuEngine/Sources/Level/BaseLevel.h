#pragma once
#include <string>
namespace GSM
{
	class BaseLevel
	{
		//Pure Abstract - Can not be instatiated
		//Others will inherit from me, I am just an Interface
		
	public:
		virtual ~BaseLevel() = default;
		//Init
		virtual void Init() = 0;
		//Update
		virtual void Update() = 0;
		//Exit
		virtual void Exit() = 0;
		//Get Name
		virtual std::string GetName() = 0;
	};
}