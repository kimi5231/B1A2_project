#include "stdafx.h"
#include "GameNet.h"

GameNet::GameNet()
{
}

GameNet::~GameNet()
{
    ::closesocket(_clientSocket);
    ::WSACleanup();
}

void GameNet::Init()
{
    //소켓 프로그래밍을 위한 WinSock 라이브러리 초기화 
    WSAData wsaData;
    if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return;

    // server에 접속할 clientSocket 생성
    // AF_INET: IPv4
    // SOCK_STREAM: TCP
    _clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (_clientSocket == INVALID_SOCKET)
        return;

    // clientSocket을 Non-Blocking Socket으로 설정
    u_long mode = 1;
    ioctlsocket(_clientSocket, FIONBIO, &mode);

    SOCKADDR_IN serverAddr;
    // 주소/포트 정보를 담을 구조체 초기화
    ::memset(&serverAddr, 0, sizeof(serverAddr));
    // IPv4
    serverAddr.sin_family = AF_INET;
    // IP 주소 설정
    ::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    // 포트 번호 설정
    serverAddr.sin_port = ::htons(7777);

    // 소켓에 주소/포트 정보 설정 후, server와 연결 시도
    if (::connect(_clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
        return;

    // clientSocket 관찰 대상 등록
    _pollfd.events = POLLRDNORM | POLLWRNORM;
    _pollfd.fd = _clientSocket;
    _pollfd.revents = 0;
}

void GameNet::Update()
{
    // 이벤트 발생 관찰
    ::WSAPoll(&_pollfd, 1, 100);

    // 이벤트가 발생했을 경우
    if (_pollfd.revents != 0)
    {
        // 송신
        // 패킷 본문 작성
        Protocol::TEST pkt;
        pkt.mutable_test()->set_num(100);

        // 패킷 헤더 작성 
        int pktSize = pkt.ByteSizeLong();
        // 헤더 빅엔디안으로 변환
        int header = ::htonl(pktSize);

        // sendBuffer 생성
        std::vector<char> sendBuffer(sizeof(header) + pktSize);
        // sendBuffer에 패킷 헤더 추가
        std::memcpy(sendBuffer.data(), &header, sizeof(header));
        // sendBuffer에 패킷 본문 추가
        // Protobuf 객체를 Byte 배열(sendBuffer)로 변환
        // 이 과정에서 숫자형 필드도 빅엔디안으로 변환
        pkt.SerializeToArray(sendBuffer.data() + sizeof(header), pktSize);

        int resultCode = ::send(_clientSocket, sendBuffer.data(), sendBuffer.size(), 0);
        if (resultCode == SOCKET_ERROR)
        {
            // 연결 끊김 처리
        }

        ::Sleep(1000);
    }
}