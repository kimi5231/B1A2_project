#pragma once
class DataManager
{
public:
	DataManager();
	~DataManager() {}

public:
	void LoadCubeTilemaps();

public:
	const std::vector<std::vector<std::vector<short>>>& GetTilemap(CubeType type) { return _cubeTilemaps[type]; }

private:
	std::filesystem::path _dataPath;

	std::unordered_map<CubeType, std::vector<std::vector<std::vector<short>>>> _cubeTilemaps;
};