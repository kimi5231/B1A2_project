#include "pch.h"
#include "DataManager.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

DataManager::DataManager()
{
    _dataPath = std::filesystem::current_path().parent_path() / "Data";

    LoadGameRoomConditionInfos();
    LoadGameRoomInfos();
}

void DataManager::LoadGameRoomConditionInfos()
{
    std::ifstream file(_dataPath / "GameRoomConditions.json");
    json data = json::parse(file);

    // GameRoomConditionInfo 추출
    for (const auto& condition : data["conditions"])
    {
        GameRoomConditionInfo info;

        info.totalGameRoomCount = condition["totalRoomCount"];

        info.createItemCount.first = condition["createItemCount"]["min"];
        info.createItemCount.second = condition["createItemCount"]["max"];

        info.createExitCount.first = condition["createExitCount"]["min"];
        info.createExitCount.second = condition["createExitCount"]["max"];

        info.exitPos.first = condition["exitCount"]["min"];
        info.exitPos.second = condition["exitCount"]["max"];

        info.floor.first = condition["floor"]["min"];
        info.floor.second = condition["floor"]["max"];

        _gameRoomconditionInfos[{condition["current"], condition["detail"]}] = info;
    }
}

void DataManager::LoadGameRoomInfos()
{
    std::ifstream file(_dataPath/"test.json");
    json data = json::parse(file);

    // GameRoomInfo 추출
    for (const auto& room : data["rooms"])
    {
        GameRoomInfo info;

        info.type = room["type"];
        info.size.x = room["size"][0];
        info.size.y = room["size"][1];
        info.size.z = room["size"][2];
        info.isCreateItem = room["isCreateItem"];
        info.isCreateExit = room["isCreateExit"];

        for (int i = 0; i < DifficultyCount; i++)
            info.minCreateCount[static_cast<Difficulty>(i)] = room["minCreateCount"][i];
        for (int i = 0; i < DifficultyCount; i++)
            info.maxCreateCount[static_cast<Difficulty>(i)] = room["minCreateCount"][i];
        for (int i = 0; i < DifficultyCount; i++)
            info.spawnChance[static_cast<Difficulty>(i)] = room["minCreateCount"][i];

        info.doorCount.first = room["doorCount"]["min"];
        info.doorCount.second = room["doorCount"]["max"];
    
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