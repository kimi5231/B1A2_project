#include "DataManager.h"
#include "json.hpp"
#include <fstream>
#include "Misc/Paths.h"

using json = nlohmann::json;

DataManager::DataManager()
{
    FString projectDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    std::filesystem::path rawPath = std::filesystem::path(TCHAR_TO_UTF8(*projectDir)) / "../Server/Data";
    _dataPath = std::filesystem::weakly_canonical(rawPath);

    LoadMainQuestInfos();
	LoadSubQuestInfos();
}

void DataManager::LoadMainQuestInfos()
{
    std::filesystem::path fullPath = _dataPath / "MainQuestInfos.json";
    std::ifstream file(fullPath);

    if (!file.is_open())
    {
        UE_LOG(LogTemp, Error, TEXT("MainQuestInfos.json file is not found: %s"), *FString(fullPath.c_str()));
        return;
    }

    try
    {
        json data = json::parse(file);

        if (data.contains("mainQuests") && data["mainQuests"].is_array())
        {
            for (const auto& item : data["mainQuests"])
            {
                QuestInfo info;

                info.title = FString(UTF8_TO_TCHAR(item["title"].get<std::string>().c_str()));
                info.client = FString(UTF8_TO_TCHAR(item["client"].get<std::string>().c_str()));
                info.request = FString(UTF8_TO_TCHAR(item["request"].get<std::string>().c_str()));
                info.reward = FString(UTF8_TO_TCHAR(item["reward"].get<std::string>().c_str()));
                info.complete = FString(UTF8_TO_TCHAR(item["complete"].get<std::string>().c_str()));

                _mainQuestInfos.push_back(info);
            }
            UE_LOG(LogTemp, Log, TEXT("MainQuestInfos.json Load Success! (num: %d)"), _mainQuestInfos.size());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Is Not Array MainQuest."));
        }
    }
    catch (const json::parse_error& e)
    {
        FString ErrorMsg = FString(UTF8_TO_TCHAR(e.what()));
        UE_LOG(LogTemp, Error, TEXT("MainQuestInfos.json failed: %s"), *ErrorMsg);
    }
}

void DataManager::LoadSubQuestInfos()
{
    std::filesystem::path fullPath = _dataPath / "SubQuestInfos.json";
    std::ifstream file(fullPath);

    if (!file.is_open())
    {
        UE_LOG(LogTemp, Error, TEXT("SubQuestInfos.json is not found °æ·Î: %s"), *FString(fullPath.c_str()));
        return; 
    }

    try
    {
        json data = json::parse(file);

        if (data.contains("subQuests") && data["subQuests"].is_array())
        {
            for (const auto& item : data["subQuests"])
            {
                QuestInfo info;

                info.title = FString(UTF8_TO_TCHAR(item["title"].get<std::string>().c_str()));
                info.client = FString(UTF8_TO_TCHAR(item["client"].get<std::string>().c_str()));
                info.request = FString(UTF8_TO_TCHAR(item["request"].get<std::string>().c_str()));
                info.reward = FString(UTF8_TO_TCHAR(item["reward"].get<std::string>().c_str()));
                info.complete = FString(UTF8_TO_TCHAR(item["complete"].get<std::string>().c_str()));

                _subQuestInfos.push_back(info);
            }
            UE_LOG(LogTemp, Log, TEXT("SubQuestInfos.json Load Success! (num: %d)"), _subQuestInfos.size());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("SubQuestInfos.json is not arry subQuest"));
        }
    }
    catch (const json::parse_error& e)
    {
        FString ErrorMsg = FString(UTF8_TO_TCHAR(e.what()));
        UE_LOG(LogTemp, Error, TEXT("SubQuestInfos.json failed: %s"), *ErrorMsg);
    }
}