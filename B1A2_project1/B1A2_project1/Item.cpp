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

        std::getline(wiss, info->ID, L',');

        std::getline(wiss, info->name, L',');
        
        std::getline(wiss, info->explain);
        // ���� ����
        int32 start = 0;
        while ((start = info->explain.find(L"\\n", start)) != std::wstring::npos)
        {
            info->explain.replace(start, 2, L"\n");
            start += 1;
        }

        // �޸� ���� ������ - �ٵ� ������ �ʿ��� ����...
        //if (!std::getline(wiss, info->ID, L',')) { delete info; continue; }
        //if (!std::getline(wiss, info->name, L',')) { delete info; continue; }
        //if (!std::getline(wiss, info->explain)) { delete info; continue; }

        _items[info->ID] = info;
    }

    ifs.close();
}
