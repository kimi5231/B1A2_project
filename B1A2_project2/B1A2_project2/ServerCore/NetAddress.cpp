#include "pch.h"
#include "NetAddress.h"

NetAddress::NetAddress(SOCKADDR_IN sockAddr) : _sockAddr(sockAddr)
{
}

NetAddress::NetAddress(std::wstring ip, uint16 port)
{
	::memset(&_sockAddr, 0, sizeof(_sockAddr));
	// IPv4
	_sockAddr.sin_family = AF_INET;
	// IP주소를 네트워크용 바이너리 주소로 변환
	_sockAddr.sin_addr = Ip2Address(ip.c_str());
	// big endian으로 포트 번호 저장
	_sockAddr.sin_port = ::htons(port);
}

std::wstring NetAddress::GetIpAddress()
{
	WCHAR buffer[100];
	::InetNtopW(AF_INET, &_sockAddr.sin_addr, buffer, len32(buffer));
	return std::wstring(buffer);
}

IN_ADDR NetAddress::Ip2Address(const WCHAR* ip)
{
	IN_ADDR address;
	::InetPtonW(AF_INET, ip, &address);
	return address;
}