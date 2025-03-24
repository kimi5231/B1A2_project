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
	std::vector<Line> lines;

	std::wstring str;

	while (std::getline(ifs, str))
	{
		// ���ڿ� ��Ʈ�� ����
		std::wistringstream wiss(str);

		std::wstring eventName;
		std::getline(wiss, eventName, L',');

		if (eventName == L"end")
		{
			_events[key] = lines;
			lines.clear();
			continue;
		}
		else if (!eventName.empty())
		{
			key = eventName;
			continue;
		}
		
		Line line;

		std::getline(wiss, line.speakerName, L',');

		// ���ڿ� ������ ��ȯ
		std::wstring id;
		std::getline(wiss, id, L',');
		line.speakerID = std::stoi(id);

		std::wstring state;
		std::getline(wiss, state, L',');
		line.state = std::stoi(state);

		std::wstring dir;
		std::getline(wiss, dir, L',');
		line.dir = std::stoi(dir);

		std::getline(wiss, line.type, L',');

		std::getline(wiss, line.cutScene, L',');

		// ���ڿ� �Ǽ��� ��ȯ
		std::wstring x;
		std::getline(wiss, x, L',');
		line.moveDistance.x = std::stof(x);

		std::wstring y;
		std::getline(wiss, y, L',');
		line.moveDistance.y = std::stof(y);

		std::getline(wiss, line.speech, L',');
		// ���๮�� ó��
		int32 start = 0;
		while ((start = line.speech.find(L"\\n", start))!= std::wstring::npos)
		{
			line.speech.replace(start, 2, L"\n");
			start += 1;
		}

		lines.push_back(line);
	}

	ifs.close();
}