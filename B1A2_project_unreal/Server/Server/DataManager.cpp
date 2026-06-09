#include "pch.h"
#include "DataManager.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

DataManager::DataManager()
{
    _dataPath = std::filesystem::current_path().parent_path() / "Data";

    LoadCubeConditionInfos();
    LoadCubeInfos();
    LoadCubeTilemaps();
    LoadMainQuestInfos();
	LoadSubQuestInfos();
    LoadItemInfos();
    LoadPlayerStat();
    LoadSpiderStat();
}

void DataManager::LoadCubeConditionInfos()
{
    std::ifstream file(_dataPath / "GameRoomConditions.json");
    json data = json::parse(file);

    // GameRoomConditionInfo 추출
    for (const auto& condition : data["conditions"])
    {
        CubeConditionInfo info;

        info.totalCubeCount = condition["totalRoomCount"];

        info.createItemCount.first = condition["createItemCount"]["min"];
        info.createItemCount.second = condition["createItemCount"]["max"];

        info.createExitCount.first = condition["createExitCount"]["min"];
        info.createExitCount.second = condition["createExitCount"]["max"];

        info.createSellingMachineCount = condition["createSellingMachineCount"];
       
        info.createSpecialSellingMachineCount = condition["createSpecialSellingMachineCount"];

        info.sellingMachineCreditLimit.first = condition["sellingMachineCreditLimit"]["min"];
        info.sellingMachineCreditLimit.second = condition["sellingMachineCreditLimit"]["max"];
        
        info.power = condition["power"];

        info.exitPos.first = condition["exitPos"]["min"];
        info.exitPos.second = condition["exitPos"]["max"];

        info.floor.first = condition["floor"]["min"];
        info.floor.second = condition["floor"]["max"];

       _cubeConditionInfos[{condition["current"], condition["detail"]}] = info;
    }
}

void DataManager::LoadCubeInfos()
{
    std::ifstream file(_dataPath/"CubeInfos.json");
    json data = json::parse(file);

    // GameRoomInfo 추출
    for (const auto& room : data["rooms"])
    {
        CubeInfo info;

        info.type = room["type"];
        info.size.x = room["size"][0];
        info.size.y = room["size"][1];
        info.size.z = room["size"][2];
            
        info.isCreateItem = room["isCreateItem"];
        info.isCreateExit = room["isCreateExit"];
        info.isCreateSellingMachine = room["isCreateSellingMachine"];

        for (int i = 0; i < DifficultyCount; i++)
            info.minCreateCount[static_cast<Difficulty>(i)] = room["minCreateCount"][i];
        for (int i = 0; i < DifficultyCount; i++)
            info.maxCreateCount[static_cast<Difficulty>(i)] = room["maxCreateCount"][i];
        for (int i = 0; i < DifficultyCount; i++)
            info.spawnChance[static_cast<Difficulty>(i)] = room["spawnChance"][i];

        /*info.f1DoorCount.first = room["f1DoorCount"]["min"];
        info.f1DoorCount.second = room["f1DoorCount"]["max"];
        info.f2DoorCount.first = room["f2DoorCount"]["min"];
        info.f2DoorCount.second = room["f2DoorCount"]["max"];

        for (const auto& doorPos : room["f1DoorPos"])
        {
            Vector pos;
            pos.x = doorPos[0];
            pos.y = doorPos[1];
            pos.z = doorPos[2];

            info.f1DoorPos.push_back(pos);
        }

        for (const auto& doorPos : room["f2DoorPos"])
        {
            Vector pos;
            pos.x = doorPos[0];
            pos.y = doorPos[1];
            pos.z = doorPos[2];

            info.f2DoorPos.push_back(pos);
        }*/

        for (const auto& sellingMachinePos : room["sellingMachinePos"])
        {
            Vector pos;
            pos.x = sellingMachinePos[0];
            pos.y = sellingMachinePos[1];
            pos.z = sellingMachinePos[2];

            info.sellingMachinePos.push_back(pos);
        }

        for (const auto& sellingMachineDir : room["sellingMachineDir"])
            info.sellingMachineDir.push_back(sellingMachineDir);
 
        for (const auto& doorPos : room["doorPos"])
        {
            Vector pos;
            pos.x = doorPos[0];
            pos.y = doorPos[1];
            pos.z = doorPos[2];

            info.doorPos.push_back(pos);
        }

        for (const auto& doorDir : room["doorDir"])
            info.doorDir.push_back(doorDir);

        info.enterDistance = room["enterDistance"];

        _cubeInfos[info.type] = info;
    }
}

void DataManager::LoadCubeTilemaps()
{
    std::ifstream file(_dataPath / "GameRoomTilemaps.json");
    json data = json::parse(file);

    // GameRoomTilemap 추출
    for (const auto& tilemap : data["tilemaps"])
    {
        CubeType type = tilemap["type"];
        Vector tileCount{ tilemap["tileCount"][0], tilemap["tileCount"][1], tilemap["tileCount"][2] };

        std::vector<std::vector<std::vector<short>>> tilemap3D;
        for (const auto& layer : tilemap["tilemap"])
        {
            std::vector<std::vector<short>> tilemap2D;
            for (const auto& matrix : layer["layer"])
            {
                std::vector<short> tilemap1D;
                for (const auto& pattern : matrix["pattern"])
                {
                    for (int i = 0; i < pattern[1]; i++)
                        tilemap1D.push_back(pattern[0]);
                }

                for (int i = 0; i < matrix["repeatY"]; i++)
                    tilemap2D.push_back(tilemap1D);
            }

            for (int i = 0; i < layer["repeatZ"]; i++)
                tilemap3D.push_back(tilemap2D);
        }

        _cubeTilemaps[type] = tilemap3D;
    }
}

void DataManager::LoadMainQuestInfos()
{
    std::ifstream file(_dataPath / "MainQuestInfos.json");
    json data = json::parse(file);

    // MainQuestInfo 추출
    for (const auto& item : data["mainQuests"])
    {
        MainQuestInfo info;

        info.targetItemType = item["targetItemType"];
        info.targetAmount = item["targetAmount"];
        info.rewardType = item["rewardType"];
        info.rewardItemType = item["rewardItemType"];
        info.rewardAmount = item["rewardAmount"];

        _mainQuestInfos.push_back(info);
    }
}

void DataManager::LoadSubQuestInfos()
{
    std::ifstream file(_dataPath / "SubQuestInfos.json");
    json data = json::parse(file);

    // SubQuestInfo 추출
    for (const auto& item : data["subQuests"])
    {
        SubQuestInfo info;

        info.targetItemType = item["targetItemType"];
        info.targetAmount = item["targetAmount"];
        info.rewardType = item["rewardType"];
        info.rewardItemType = item["rewardItemType"];
        info.rewardAmount = item["rewardAmount"];
        info.deadLine = item["deadLine"];

        _subQuestInfos.push_back(info);
    }
}

void DataManager::LoadItemInfos()
{
    std::ifstream file(_dataPath / "ItemInfos.json");
    json data = json::parse(file);

    // ItemInfo 추출
    for (const auto& item : data["items"])
    {
        ItemInfo info;

        info.type = item["type"];
        info.size.x = item["size"][0];
        info.size.y = item["size"][1];
        info.size.z = item["size"][2];
        info.weight = item["weight"];
        info.cost = item["cost"];

        _itemInfos[info.type] = info;
    }
}

void DataManager::LoadPlayerStat()
{
    std::ifstream file(_dataPath / "PlayerStat.json");
    json data = json::parse(file);

    PlayerStat stat;

    stat.hp = data["hp"];
    stat.stamina = data["stamina"];
    stat.recoveryStamina = data["recoveryStamina"];
    stat.walkSpeed = data["walkSpeed"];
    stat.runSpeed = data["runSpeed"];
    stat.jumpSpeed = data["jumpSpeed"];
    stat.playerWeight = data["playerWeight"];
    stat.maxWeight = data["maxWeight"];
    stat.size.x = data["size"][0];
    stat.size.y = data["size"][1];
    stat.size.z = data["size"][2];

    _playerStat = stat;
}

void DataManager::LoadSpiderStat()
{
    std::ifstream file(_dataPath / "SpiderStat.json");
    json data = json::parse(file);

    SpiderStat stat;

    stat.hp = data["hp"];
    stat.isInvincible = data["isInvincible"];
    stat.roaminSpeed = data["roaminSpeed"];
    stat.returnSpeed = data["returnSpeed"];
    stat.chaseSpeed = data["chaseSpeed"];
    stat.idleTime = data["idleTime"];
    stat.roamingTime = data["roamingTime"];
    stat.chaseTime = data["chaseTime"];
    stat.makeWebTime = data["makeWebTime"];
    stat.aggroRange = data["aggroRange"];
    stat.aggroAngle = data["aggroAngle"];
    stat.aggroHeight = data["aggroHeight"];
    stat.attackAngle = data["attackAngle"];
    stat.attackHeight = data["attackHeight"];
    stat.attackDelay = data["attackDelay"];
    stat.damage = data["damage"];
    stat.maxWebCount = data["maxWebCount"];
    stat.power = data["power"];
    stat.size.x = data["size"][0];
    stat.size.y = data["size"][1];
    stat.size.z = data["size"][2];

    _spidrStat = stat;
}

void DataManager::LoadEmotionGameStat()
{
}

void DataManager::LoadGhostStat()
{
}

void DataManager::LoadTrashCollectorStat()
{
}

void DataManager::LoadPollutionMonitorStat()
{
}