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

        info.exitPos.first = condition["exitPos"]["min"];
        info.exitPos.second = condition["exitPos"]["max"];

        info.floor.first = condition["floor"]["min"];
        info.floor.second = condition["floor"]["max"];

       _gameRoomconditionInfos[{condition["current"], condition["detail"]}] = info;
    }
}

void DataManager::LoadGameRoomInfos()
{
    std::ifstream file(_dataPath/"GameRoomInfos_TEST.json");
    json data = json::parse(file);

    // GameRoomInfo 추출
    for (const auto& room : data["rooms"])
    {
        GameRoomInfo info;

        info.type = room["type"];
        info.size.x = room["size"][0];
        info.size.y = room["size"][1];
        info.size.z = room["size"][2];

        for (int i = 0; i < DirCount; i++)
        {
            info.leftTopPos[static_cast<Dir>(i)].x = room["leftTopPos"][i][0];
            info.leftTopPos[static_cast<Dir>(i)].y = room["leftTopPos"][i][1];
            info.leftTopPos[static_cast<Dir>(i)].z = room["leftTopPos"][i][2];
        }
            
        info.isCreateItem = room["isCreateItem"];
        info.isCreateExit = room["isCreateExit"];

        for (int i = 0; i < DifficultyCount; i++)
            info.minCreateCount[static_cast<Difficulty>(i)] = room["minCreateCount"][i];
        for (int i = 0; i < DifficultyCount; i++)
            info.maxCreateCount[static_cast<Difficulty>(i)] = room["maxCreateCount"][i];
        for (int i = 0; i < DifficultyCount; i++)
            info.spawnChance[static_cast<Difficulty>(i)] = room["spawnChance"][i];

        info.f1DoorCount.first = room["f1DoorCount"]["min"];
        info.f1DoorCount.second = room["f1DoorCount"]["max"];
        info.f2DoorCount.first = room["f2DoorCount"]["min"];
        info.f2DoorCount.second = room["f2DoorCount"]["max"];
    
        for (const auto& doorPos : room["f1DoorPos"]) 
        {            
            Vector pos;
            pos.x = doorPos[1];
            pos.y = doorPos[2];
            pos.z = doorPos[3];
            
            info.f1DoorPos[doorPos[0]].push_back(pos);
        }

        for (const auto& doorPos : room["f2DoorPos"])
        {
            Vector pos;
            pos.x = doorPos[1];
            pos.y = doorPos[2];
            pos.z = doorPos[3];

            info.f2DoorPos[doorPos[0]].push_back(pos);
        }

        for (const auto& doorDir : room["doorDir"])
            info.doorDir.push_back(doorDir);

        _gameRoomInfos[info.type] = info;
    }
}