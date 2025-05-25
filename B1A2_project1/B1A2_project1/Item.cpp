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

    // �� �پ� �о ó��
    while (std::getline(ifs, line))
    {
        if (line.empty())
            continue;

        std::wstringstream wiss(line);
        auto* info = new ItemInfo(); // ���� �Ҵ�

        // ID
        std::wstring strID;
        std::getline(wiss, strID, L',');
        info->ID = std::stoi(strID);

        // ������ �̸�
        std::getline(wiss, info->name, L',');
        
        // ���� 
        std::wstring strExplain;
        std::getline(wiss, strExplain, L',');

        // ���� ���� "\n" ó��
        size_t start = 0;
        while ((start = strExplain.find(L"\\n", start)) != std::wstring::npos)
        {
            strExplain.replace(start, 2, L"\n");
            start += 1; // ���� Ž�� ��ġ (�ߺ� ��ȯ ����)
        }

        info->explain = strExplain;

        // F Ű�� ����
        std::wstring strAcquiredByFkey;
        std::getline(wiss, strAcquiredByFkey, L',');
        int32 intAcquiredByFkey = std::stoi(strAcquiredByFkey);
        if (intAcquiredByFkey == -1)
            info->acquiredByFKey = false;
        else
            info->acquiredByFKey = true;

        // ����ϴ� ���� ���� ID - ������ 0
        std::wstring strDroppingMonsterPersonalID;
        std::getline(wiss, strDroppingMonsterPersonalID, L',');
        info->droppingMonsterPersonalID = std::stoi(strDroppingMonsterPersonalID);

        // ��������
        std::wstring strStage;
        std::getline(wiss, strStage, L',');
        info->stage = std::stoi(strStage);

        // ���� ��ġ - ������ ������
        std::wstring strSpawnPosX;
        std::getline(wiss, strSpawnPosX, L',');
        info->spawnPos.x = std::stoi(strSpawnPosX);

        std::wstring strSpawnPosY;
        std::getline(wiss, strSpawnPosY, L',');
        info->spawnPos.y = std::stoi(strSpawnPosY);
 
        _items[info->ID] = info;
    }

    ifs.close();
}
