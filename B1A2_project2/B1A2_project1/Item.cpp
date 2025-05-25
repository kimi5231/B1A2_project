#include "pch.h"
#include "Item.h"
#include <fstream>
#include <iostream>
#include <string>

Item::Item()
{
}

Item::~Item()
{
}

void Item::LoadFile(const std::wstring& path)
{
	std::wifstream ifs;
	ifs.imbue(std::locale("ko_KR.UTF-8"));
	ifs.open(path);

    std::wstring line;

    // 한 줄씩 읽어서 처리
    while (std::getline(ifs, line))
    {
        if (line.empty())
            continue;

        std::wstringstream wiss(line);
        auto* info = new ItemInfo(); // 동적 할당

        // ID
        std::wstring strID;
        std::getline(wiss, strID, L',');
        info->ID = std::stoi(strID);

        // 아이템 이름
        std::getline(wiss, info->name, L',');
        
        // 설명 
        std::wstring strExplain;
        std::getline(wiss, strExplain, L',');

        // 개행 문자 "\n" 처리
        size_t start = 0;
        while ((start = strExplain.find(L"\\n", start)) != std::wstring::npos)
        {
            strExplain.replace(start, 2, L"\n");
            start += 1; // 다음 탐색 위치 (중복 변환 방지)
        }

        info->explain = strExplain;

        // F 키로 습득
        std::wstring strAcquiredByFkey;
        std::getline(wiss, strAcquiredByFkey, L',');
        int32 intAcquiredByFkey = std::stoi(strAcquiredByFkey);
        if (intAcquiredByFkey == -1)
            info->acquiredByFKey = false;
        else
            info->acquiredByFKey = true;

        // 드랍하는 몬스터 고유 ID - 없으면 0
        std::wstring strDroppingMonsterPersonalID;
        std::getline(wiss, strDroppingMonsterPersonalID, L',');
        info->droppingMonsterPersonalID = std::stoi(strDroppingMonsterPersonalID);

        // 스폰 위치 - 없으면 음수값
        std::wstring strSpawnPosX;
        std::getline(wiss, strSpawnPosX, L',');
        info->spawnPos.x = std::stoi(strSpawnPosX);

        std::wstring strSpawnPosY;
        std::getline(wiss, strSpawnPosY, L',');
        info->spawnPos.y = std::stoi(strSpawnPosY);

        
        // 메모리 누수 방지용 - 근데 지금은 필요없어서 보류...
        //if (!std::getline(wiss, info->ID, L',')) { delete info; continue; }
        //if (!std::getline(wiss, info->name, L',')) { delete info; continue; }
        //if (!std::getline(wiss, info->explain)) { delete info; continue; }

        _items[info->ID] = info;
    }

    ifs.close();
}
