#pragma once
class Inventory
{
public:
	Inventory();
	~Inventory();

public:
	bool AddItem(bool isTool, uint id);
	bool RemoveItem(bool isTool, uint id);
	bool ExistItem(bool isTool, uint id);

private:
	std::vector<uint> _scraps;
	std::vector<uint> _tools;
};