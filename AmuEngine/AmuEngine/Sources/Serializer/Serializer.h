#pragma once
#include <string>

class Serializer
{
private:
	Serializer() = default;

	Serializer(const Serializer&) = delete;
	Serializer& operator =(const Serializer&) = delete;

	~Serializer() = default;

	static Serializer* ptr;

public:
	static Serializer& GetInstance()
	{
		static Serializer instance;
		return instance;
	}

	bool LoadLevel(const std::string& str);
	bool ExistChangePoint(const std::string& str);
	bool SaveLevel(const std::string& str);
};