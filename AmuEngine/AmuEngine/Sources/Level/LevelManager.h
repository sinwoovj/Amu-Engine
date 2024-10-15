#pragma once
#include <string>
#include <vector>
class LevelManager
{
private:
	LevelManager() = default;

	LevelManager(const LevelManager&) = delete;
	LevelManager& operator =(const LevelManager&) = delete;

	~LevelManager() = default;
	std::string directory = "./Sources/Assets/Level/"; // ex) ./Sources/Assets/Level/
	std::string filenameExtension = ".lvl"; // ex) .lvl
	static LevelManager* ptr;
	std::vector<std::string> levels;
public:
	static LevelManager& GetInstance()
	{
		static LevelManager instance;
		return instance;
	}
	std::string GetDirectory();
	std::string GetFilenameExtension();
	void SetDirectory(const std::string& str);
	void SetFilenameExtension(const std::string& str);
	bool FindLevel(const std::string& str);
	std::vector<std::string> GetLevels() { return levels; }
	bool LoadLevels();
	bool SaveLevels();
	bool LoadLevel(const std::string& str);
	bool SaveLevel(const std::string& str);
	bool AddLevel(const std::string& str);
	bool DeleteLevel(const std::string& str);
};