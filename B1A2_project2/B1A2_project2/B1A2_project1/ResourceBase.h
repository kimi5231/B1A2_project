#pragma once

class ResourceBase
{
public:
	ResourceBase();
	virtual ~ResourceBase();

	virtual void LoadFile(const std::wstring& path);
	virtual void SaveFile(const std::wstring& path);
};

