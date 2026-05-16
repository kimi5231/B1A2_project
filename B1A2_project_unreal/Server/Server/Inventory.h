#pragma once
class Inventory
{
public:
	Inventory();
	~Inventory();

public:
	bool AddItem(bool isTool, int id);
	bool RemoveItem(bool isTool, int id);
	bool ExistItem(bool isTool, int id);

private:
	std::vector<int> _scraps;
	std::vector<int> _tools;
};