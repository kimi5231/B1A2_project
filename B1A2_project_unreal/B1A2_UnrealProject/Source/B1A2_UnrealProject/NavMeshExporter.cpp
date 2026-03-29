// Fill out your copyright notice in the Description page of Project Settings.


#include "NavMeshExporter.h"
#include "NavigationSystem.h"
#include "NavMesh/RecastNavMesh.h"
#include "detour/DetourNavMesh.h"
#include "Serialization/BufferArchive.h"
#include "Misc/FileHelper.h"

// Detour 표준 헤더 구조체와 유사하게 정의 (서버와 약속된 포맷)
struct FNavMeshHeader {
    int32 Magic;
    int32 Version;
    int32 NumTiles;
    dtNavMeshParams Params; // Detour의 표준 파라미터 구조체
};

void ANavMeshExporter::ExportNavMeshToBinary(FString FilePath)
{
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (!NavSys) return;

    ARecastNavMesh* RecastNavMesh = Cast<ARecastNavMesh>(NavSys->GetDefaultNavDataInstance());
    if (!RecastNavMesh) return;

    // 1. 언리얼 내부의 진짜 Detour 포인터 추출
    const dtNavMesh* DetourMesh = RecastNavMesh->GetRecastMesh();
    if (!DetourMesh) return;

    FBufferArchive ToBinary;

    // 2. 헤더 정보 구성
    FNavMeshHeader Header;
    Header.Magic = 0x4E41564D; // 'NAVM'
    Header.Version = 1;
    Header.Params = *DetourMesh->getParams(); // 중요: NavMesh의 원점, 타일 크기 등 설정 정보

    // 실제 데이터가 있는 타일 개수만 세기
    int32 ActualTileCount = 0;
    for (int32 i = 0; i < DetourMesh->getMaxTiles(); ++i)
    {
        const dtMeshTile* Tile = DetourMesh->getTile(i);
        if (Tile && Tile->header && Tile->dataSize > 0) ActualTileCount++;
    }
    Header.NumTiles = ActualTileCount;

    // 3. 헤더 먼저 쓰기 (구조체 통째로 직렬화)
    ToBinary.Serialize(&Header, sizeof(FNavMeshHeader));

    // 4. 각 타일의 데이터 쓰기
    for (int32 i = 0; i < DetourMesh->getMaxTiles(); ++i)
    {
        const dtMeshTile* Tile = DetourMesh->getTile(i);
        if (!Tile || !Tile->header || Tile->dataSize <= 0) continue;

        // 서버에서 addTile 시 필요한 정보들
        uint32 TileDataSize = Tile->dataSize;

        // [타일 데이터 크기] -> [타일 바이너리] 순서로 기록
        ToBinary << TileDataSize;
        ToBinary.Serialize(Tile->data, TileDataSize);
    }

    if (FFileHelper::SaveArrayToFile(ToBinary, *FilePath))
    {
        UE_LOG(LogTemp, Log, TEXT("Detour Compatible NavMesh Export Success!"));
    }
}