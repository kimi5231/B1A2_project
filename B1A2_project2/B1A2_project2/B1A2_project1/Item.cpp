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

        _items[info->ID] = info;
    }

    ifs.close();
}
