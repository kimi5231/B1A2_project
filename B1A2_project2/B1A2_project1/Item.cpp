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

        _items[info->ID] = info;
    }

    ifs.close();
}
