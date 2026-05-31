#pragma once
#include "Includes.h"

struct QuestInfo
{
	// 퀘스트 제목
	std::string title;
	// 퀘스트 요청을 보낸 NPC 이름
	std::string client;
	// 퀘스트 요구 사항(시나리오)
	std::string request;
	// 퀘스트 보상 정보
	std::string reward;
	// 퀘스트 완료시 띄워야 될 문구
	std::string complete;
};

class DataManager
{
public:
	DataManager();
	~DataManager() {}

public:
	void LoadMainQuestInfos();
	void LoadSubQuestInfos();

public:
	const QuestInfo& GetMainQuestInfo(int id) { return _mainQuestInfos[id]; }
	const QuestInfo& GetSubQuestInfo(int id) { return _subQuestInfos[id]; }

private:
	std::filesystem::path _dataPath;

	std::vector<QuestInfo> _mainQuestInfos;
	std::vector<QuestInfo> _subQuestInfos;
};