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

		std::getline(wiss, info.speakerName, L',');

		// ���ڿ� ������ ��ȯ
		std::wstring id;
		std::getline(wiss, id, L',');
		info.speakerID = std::stoi(id);

		// ���ڿ� ������ ��ȯ
		std::wstring state;
		std::getline(wiss, state, L',');
		info.state = std::stoi(state);

		std::wstring dir;
		std::getline(wiss, dir, L',');
		info.dir = std::stoi(dir);

		std::getline(wiss, info.speech, L',');
		// ���๮�� ó��
		int32 start = 0;
		while ((start = info.speech.find(L"\\n", start))!= std::wstring::npos)
		{
			info.speech.replace(start, 2, L"\n");
			start += 1;
		}

		infos.push_back(info);
	}

	ifs.close();
}