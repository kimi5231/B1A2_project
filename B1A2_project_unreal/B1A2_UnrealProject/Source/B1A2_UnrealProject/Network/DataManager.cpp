#include "DataManager.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

DataManager::DataManager()
{
    _dataPath = std::filesystem::current_path();

    //LoadMainQuestInfos();
	//LoadSubQuestInfos();
}

void DataManager::LoadMainQuestInfos()
{
    std::ifstream file(_dataPath / "MainQuestInfos.json");
    json data = json::parse(file);

    // MainQuestInfo 추출
    for (const auto& item : data["mainQuests"])
    {
        QuestInfo info;

        info.title = item["title"];
        info.client = item["client"];
        info.request = item["request"];
        info.reward = item["reward"];
        info.complete = item["complete"];

        _mainQuestInfos.push_back(info);
    }
}

void DataManager::LoadSubQuestInfos()
{
    std::ifstream file(_dataPath / "SubQuestInfos.json");
    json data = json::parse(file);

    // SubQuestInfo 추출
    for (const auto& item : data["subQuests"])
    {
        QuestInfo info;

        info.title = item["title"];
        info.client = item["client"];
        info.request = item["request"];
        info.reward = item["reward"];
        info.complete = item["complete"];

        _subQuestInfos.push_back(info);
    }
}