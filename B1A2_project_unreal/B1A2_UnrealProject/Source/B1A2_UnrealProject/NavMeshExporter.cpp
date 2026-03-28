// Fill out your copyright notice in the Description page of Project Settings.


#include "NavMeshExporter.h"
#include "NavigationSystem.h"
#include "NavMesh/RecastNavMesh.h"
#include "detour/DetourNavMesh.h"
#include "Serialization/BufferArchive.h"
#include "Misc/FileHelper.h"

void ANavMeshExporter::ExportNavMeshToBinary(FString FilePath)
{
    // 네비게이션 시스템 가져오기
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (!NavSys) return;

    // RecastNavMesh 데이터 찾기
    ARecastNavMesh* RecastNavMesh = Cast<ARecastNavMesh>(NavSys->GetDefaultNavDataInstance());
    if (!RecastNavMesh) return;

    // 내부 Detour 데이터 접근
    const dtNavMesh* DetourMesh = RecastNavMesh->GetRecastMesh();
    if (!DetourMesh) return;

    // 바이너리 아카이브 준비
    FBufferArchive ToBinary;

    // 헤더 저장 (NAVM 마커 및 버전)
    int32 Magic = 0x4E41564D;
    int32 Version = 1;
    ToBinary << Magic;
    ToBinary << Version;

    // 타일 데이터 직렬화
    int32 MaxTiles = DetourMesh->getMaxTiles();
    ToBinary << MaxTiles;

    for (int32 i = 0; i < MaxTiles; ++i)
    {
        const dtMeshTile* Tile = DetourMesh->getTile(i);
        if (!Tile || !Tile->header || Tile->dataSize <= 0) continue;

        int32 TileDataSize = Tile->dataSize;
        ToBinary << i;             // 타일 인덱스
        ToBinary << TileDataSize;  // 타일 크기
        ToBinary.Serialize(Tile->data, TileDataSize); // 원본 바이너리 복사
    }

    // 파일 저장
    if (FFileHelper::SaveArrayToFile(ToBinary, *FilePath))
    {
        UE_LOG(LogTemp, Log, TEXT("NavMesh Export Success! Path: %s"), *FilePath);
    }
}
