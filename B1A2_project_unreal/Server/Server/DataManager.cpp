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
    LoadGameRoomTilemaps();
    //LoadCubeNavMesh();
}

void DataManager::LoadGameRoomConditionInfos()
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

        info.exitPos.first = condition["exitPos"]["min"];
        info.exitPos.second = condition["exitPos"]["max"];

        info.floor.first = condition["floor"]["min"];
        info.floor.second = condition["floor"]["max"];

       _gameRoomconditionInfos[{condition["current"], condition["detail"]}] = info;
    }
}

void DataManager::LoadGameRoomInfos()
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

        _gameRoomInfos[info.type] = info;
    }
}

void DataManager::LoadGameRoomTilemaps()
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

        _gameRoomTilemaps[type] = tilemap3D;
    }
}

void DataManager::LoadCubeNavMesh()
{
    std::ifstream file(_dataPath / "MainNavMesh.bin", std::ios::binary);

    // 1. NavMesh 파라미터 읽기
    dtNavMeshParams params;
    file.read(reinterpret_cast<char*>(&params), sizeof(dtNavMeshParams));

    // 2. NavMesh 객체 생성 및 초기화
    dtNavMesh* navMesh = dtAllocNavMesh();
    navMesh->init(&params);

    // 3. 타일 데이터 읽기
    for (int i = 0; i < params.maxTiles; ++i)
    {
        int dataSize = 0;
        file.read(reinterpret_cast<char*>(&dataSize), sizeof(int));
        if (dataSize == 0) continue;

        std::unique_ptr<unsigned char[]> data(new unsigned char[dataSize]);
        file.read(reinterpret_cast<char*>(data.get()), dataSize);

        navMesh->addTile(data.release(), dataSize, DT_TILE_FREE_DATA, 0, 0);
    }

	_cubeNavMesh[CubeType::MainEntranceRoom] = navMesh;
}