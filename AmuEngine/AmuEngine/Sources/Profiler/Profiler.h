#pragma once
#include <string>
#include <chrono>
#include <list>
#include <map>
namespace MyProfiler
{
	class Block
	{
		std::string name;
		std::chrono::steady_clock::time_point start;
		std::chrono::steady_clock::time_point end;
		std::list<Block*> children;
		Block* parent;
	public:
		Block(const std::string& _name, Block* _parent = nullptr);
		~Block();

		void End();

		double GetSeconds()const;
		std::string GetName()const { return name; };
		Block* GetParent()const { return parent; };

		Block* AddChild(const std::string& _name);
		void Dump(int n = 0)const;
	};
	class Profiler
	{
		std::map<std::string, double> blocks;
		static Profiler* ptr;
		Profiler()=default;
		Profiler(const Profiler& other) = delete;
		const Profiler& operator=(const Profiler& other) = delete;
		~Profiler();

		Block* current = nullptr;

		std::list<Block*> fullyFinishedBlocks;
	public:
		void StartBlock(std::string _name);
		void End();
		void Dump();
		void Clear();

		void InsertBlock(std::string _name, double latency);
		std::map<std::string, double> GetBlocks();
		void ClearBlocks();
		
		static Profiler* GetPtr();
		void DeletePtr();
	};
}
#ifndef  __FUNCTION_NAME__
#ifdef WIN32
#define __FUNCTION_NAME__ __FUNCTION__
#else
#define __FUNCTION_NAME__ __func__
#endif // WIN32
#endif // ! __FUNTION_NAME__



#ifdef _DEBUG
#define DEBUG_PROFILER_START(x) MyProfiler::Profiler::GetPtr()->StartBlock(x);
#define DEBUG_PROFILER_END MyProfiler::Profiler::GetPtr()->End();
#define DEBUG_PROFILER_DUMP MyProfiler::Profiler::GetPtr()->Dump();
#define DEBUG_PROFILER_CLEAR MyProfiler::Profiler::GetPtr()->Clear();
#define DEBUG_PROFILER_DELETE MyProfiler::Profiler::GetPtr()->DeletePtr();

#else
#define DEBUG_PROFILER_START(x) //
#define DEBUG_PROFILER_END		//
#define DEBUG_PROFILER_DUMP		//
#define DEBUG_PROFILER_DELETE	//
#endif // DEBUG

