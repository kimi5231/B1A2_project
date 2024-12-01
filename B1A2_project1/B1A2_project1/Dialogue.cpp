#include "pch.h"
#include "Dialogue.h"
#include <fstream>
#include <iostream>
#include <string>

Dialogue::Dialogue()
{
}

Dialogue::~Dialogue()
{
}

void Dialogue::LoadFile(const std::wstring& path)
{
	std::wifstream ifs;

	// �ѱ� ���ڵ� ����
	ifs.imbue(std::locale("ko_KR.UTF-8"));

	ifs.open(path);

	// �̺�Ʈ ������ ���� Ű, �� ����
	std::wstring key;
	std::vector<LineInfo> infos;

	std::wstring str;

	while (std::getline(ifs, str))
	{
		// ���ڿ� ��Ʈ�� ����
		std::wistringstream wiss(str);

		std::wstring eventName;
		std::getline(wiss, eventName, L',');

		if (eventName == L"end")
		{
			_lines[key] = infos;
			continue;
		}
		else if (!eventName.empty())
		{
			key = eventName;
			continue;
		}
		
		LineInfo info;

		std::getline(wiss, info.speaker, L',');
		std::getline(wiss, info.state, L',');

		// ���ڿ� ������ ��ȯ
		std::wstring dir;
		std::getline(wiss, dir, L',');
		info.dir = std::stoi(dir);

		std::getline(wiss, info.speech, L',');
		//::MultiByteToWideChar(CP_UTF8, 0, &info.speech, (int)utf8Speech.size(), &info.speech[0], size_needed);

		infos.push_back(info);
	}

	ifs.close();
}