#include "pch.h"
#include "Utils.h"

void Utils::DrawRect(HDC hdc, Vec2 pos, Vec2Int size)
{
	::Rectangle(hdc, static_cast<int32>(pos.x - size.x / 2), static_cast<int32>(pos.y - size.y / 2), static_cast<int32>(pos.x + size.x / 2), static_cast<int32>(pos.y + size.y / 2));
}

void Utils::DrawRect(HDC hdc, Vec2 pos, int32 w, int32 h)
{
	::Rectangle(hdc, static_cast<int32>(pos.x - w / 2), static_cast<int32>(pos.y - h / 2), static_cast<int32>(pos.x + w / 2), static_cast<int32>(pos.y + h / 2));
}

void Utils::DrawCircle(HDC hdc, Vec2 pos, int32 radius)
{
	::Ellipse(hdc, static_cast<int32>(pos.x - radius), static_cast<int32>(pos.y - radius), static_cast<int32>(pos.x + radius), static_cast<int32>(pos.y + radius));
}

void Utils::DrawString(HDC hdc, const std::wstring& str, RECT rect)
{
	::DrawText(hdc, str.c_str(), -1, &rect, DT_LEFT);
}

void Utils::DrawString(HDC hdc, const std::wstring& str, Vec2Int pos)
{
	::TextOut(hdc, pos.x, pos.y, str.c_str(), static_cast<int32>(str.size()));
}

HFONT Utils::MakeFont(int32 fontSize, LPCWSTR fontName)
{
	return ::CreateFont(
		-fontSize,
		0,
		0,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		fontName);
}
