#include "pch.h"
#include "DataManager.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

DataManager::DataManager()
{
    _dataPath = std::filesystem::current_path().parent_path() / "Data";

    LoadGameRoomInfos();
}

void DataManager::LoadGameRoomInfos()
{
    std::ifstream file(_dataPath/"test.json");
    json data = json::parse(file);

    // GameRoomInfo √ﬂ√‚
    for (const auto& room : data["rooms"])
    {
        GameRoomInfo info;

        info.type = room["type"];
        info.size.x = room["size"][0];
        info.size.y = room["size"][1];
        info.size.z = room["size"][2];
        info.isCreateItem = room["isCreateItem"];
        info.isCreateExit = room["isCreateExit"];

        for (const auto& [key, value] : room["minCreateCount"].items())
            info.minCreateCount[key] = value;
        for (const auto& [key, value] : room["maxCreateCount"].items())
            info.maxCreateCount[key] = value;

        info.spawnChance = room["spawnChance"];
        info.minDoorCount = room["minDoorCount"];
        info.maxDoorCount = room["maxDoorCount"];
    
        for (const auto& doorPos : room["doorPos"]) 
        {
            Vector pos;
            pos.x = doorPos[0];
            pos.y = doorPos[1];
            pos.z = doorPos[2];
            
            info.doorPos.push_back(pos);
        }

        _gameRoomInfos[info.type] = info;
    }
}