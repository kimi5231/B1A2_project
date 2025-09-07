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
    {
        SendEnterRoomPacket();
    }
    
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
    // 송신 
    if (_pollfd.revents & POLLWRNORM)
    {
        // 패킷 본문 작성
        Protocol::TEST pkt;
        pkt.mutable_test()->set_num(100);

        uint32_t pktSize = pkt.ByteSizeLong();
        uint32_t pktID = TEST;

        // 패킷 헤더 작성 및 빅엔디안으로 변환
        std::array<uint32_t, 2> header;
        // 빅엔디안으로 변환
        header[0] = ::htonl(pktSize);
        header[1] = ::htonl(pktID);

        // sendBuffer 생성
        std::vector<char> sendBuffer(sizeof(header) + pktSize);
        // sendBuffer에 패킷 헤더 추가
        std::memcpy(sendBuffer.data(), &header[0], sizeof(uint32_t));
        std::memcpy(sendBuffer.data() + sizeof(uint32_t), &header[1], sizeof(uint32_t));
        // sendBuffer에 패킷 본문 추가
        // Protobuf 객체를 Byte 배열(sendBuffer)로 변환
        // 이 과정에서 숫자형 필드도 빅엔디안으로 변환
        pkt.SerializeToArray(sendBuffer.data() + sizeof(uint32_t) * 2, pktSize);

        int resultCode = ::send(_clientSocket, sendBuffer.data(), sendBuffer.size(), 0);
        if (resultCode == SOCKET_ERROR)
        {
            // 연결 끊김 처리
        }

        //::Sleep(1000);
    }

    // 수신
    if (_pollfd.revents & POLLRDNORM)
    {
        char temp[100];

        int recvLen = ::recv(_clientSocket, temp, sizeof(temp), 0);

        if (recvLen < 0)
        {
            // recv 실패 처리
        }
        else
        {
            // 수신된 데이터 누적
            _recvBuffer.insert(_recvBuffer.end(), temp, temp + recvLen);

            // 헤더 추출
            if (recvLen > sizeof(_header) && !_header[0] && !_header[1])
            {
                // 패킷 size
                std::memcpy(&_header[0], _recvBuffer.data(), sizeof(uint32_t));
                _header[0] = ::ntohl(_header[0]);
                _recvBuffer.erase(_recvBuffer.begin(), _recvBuffer.begin() + sizeof(uint32_t));

                // 패킷 ID
                std::memcpy(&_header[1], _recvBuffer.data(), sizeof(uint32_t));
                _header[1] = ::ntohl(_header[1]);
                _recvBuffer.erase(_recvBuffer.begin(), _recvBuffer.begin() + sizeof(uint32_t));
            }
            /*else if (recvLen > _header[0])*/ // 본문 추출
            {
                switch (_header[1])
                {
                case AddPlayer:
                {
                    Protocol::AddPlayer pkt;

                    // Byte 배열(recvBuffer)을 Protobuf 객체로 변환
                    if (pkt.ParseFromArray(_recvBuffer.data(), _header[0]))
                    {
                        // 플레이어 추가


                        _recvBuffer.erase(_recvBuffer.begin(), _recvBuffer.begin() + _header[0]);
                        _header[0] = 0;
                        _header[1] = 0;
                    }
                    else
                    {
                        // 변환 실패 처리
                    }
                }
                break;
                }
            }
        }
    }
}


bool GameNet::SendEnterRoomPacket()
{
    // 이벤트 발생 관찰
    ::WSAPoll(&_pollfd, 1, 100);

    // 이벤트가 발생했을 경우
    if (_pollfd.revents != 0)
    {
        // 패킷 본문 작성
        Protocol::EnterRoom pkt;
        pkt.set_success(true);

        uint32_t pktSize = pkt.ByteSizeLong();
        uint32_t pktID = EnterRoom;

        // 패킷 헤더 작성 및 빅엔디안으로 변환
        std::array<uint32_t, 2> header;
        // 빅엔디안으로 변환
        header[0] = ::htonl(pktSize);
        header[1] = ::htonl(pktID);

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

        return true;
    }

    return false;
}