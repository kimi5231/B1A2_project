#pragma once
class Inventory
{
public:
	Inventory();
	~Inventory();

public:
	void Init();
	bool AddItem(bool isTool, int id);
	bool RemoveItem(bool isTool, int id);
	bool ExistItem(bool isTool, int id);

private:
	int _maxScrapCount;
	int _maxToolCount;

	std::unordered_set<int> _scraps;
	std::unordered_set<int> _tools;
};