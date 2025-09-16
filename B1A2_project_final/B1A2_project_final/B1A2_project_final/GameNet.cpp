#include "stdafx.h"
#include "GameNet.h"
#include "GameFramework.h"

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
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return;

    // server에 접속할 clientSocket 생성
    // AF_INET: IPv4
    // SOCK_STREAM: TCP
    _clientSocket = socket(AF_INET, SOCK_STREAM, 0);
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

    // server와 연결 시도
    if(connect(_clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        if (WSAGetLastError() == WSAEWOULDBLOCK) // 연결 시도 진행중
        {
            // clientSocket 관찰 대상 등록
            _pollfd.events = POLLOUT | POLLIN;
            _pollfd.fd = _clientSocket;
            _pollfd.revents = 0;
        } 
        else // 오류 발생
        {
            // 연결 실패 처리
            OutputDebugStringA("Server 연결 실패");
        }
    }
    else // 즉시 연결 성공
    {
        // Client 입장 알림
        // 결과 저장(성공 or 실패)
        _isServerConnected = SendEnterRoomPacket();
    }
}

void GameNet::Update()
{
    // 이벤트 발생 관찰
    WSAPoll(&_pollfd, 1, 100);

    // 송신(쓰기 가능 이벤트 발생)
    if (_pollfd.revents & POLLOUT)
    {
        // 최초 연결 or Client 입장 알림 실패 시
        if (_isServerConnected == false)
        {
            // Client 입장 알림
            _isServerConnected = SendEnterRoomPacket();
        }
    }

    // 수신(읽기 가능 이벤트 발생)
    if (_pollfd.revents & POLLIN) 
    {
        char temp[100];

        int recvLen = recv(_clientSocket, temp, sizeof(temp), 0);

        // 오류 발생
        if (recvLen < 0)
        {
            // recv 오류 발생 처리
            OutputDebugStringA("recv 오류 발생");
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

            if (recvLen > _header[0]) // 본문 추출
            {
                switch (_header[1])
                {
                case AddPlayer:
                {
                    Protocol::AddPlayer pkt;

                    // Byte 배열(recvBuffer)을 Protobuf 객체로 변환
                    if (pkt.ParseFromArray(_recvBuffer.data(), _header[0]))
                    {
                        XMFLOAT3 pos;
                        pos.x = pkt.pos().x();
                        pos.y = pkt.pos().y();
                        pos.z = pkt.pos().z();

                        // 플레이어 추가
                        gGameFramework.CreatePlayer(pkt.id(), pos);

                        _recvBuffer.erase(_recvBuffer.begin(), _recvBuffer.begin() + _header[0]);
                        _header[0] = 0;
                        _header[1] = 0;
                    }
                    else
                    {
                        // 변환 실패 처리
                        OutputDebugStringA("Protobuf 변환 실패");
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
    // 패킷 본문 작성
    Protocol::EnterRoom pkt;
    pkt.set_success(true);

    // 패킷 헤더 작성 및 빅엔디안으로 변환
    uint32_t pktSize = pkt.ByteSizeLong();
    uint32_t pktID = EnterRoom;

    std::array<uint32_t, 2> header;
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

    if (send(_clientSocket, sendBuffer.data(), sendBuffer.size(), 0) == SOCKET_ERROR)
    {
        // SendBuffer 자리 없음
        if (WSAGetLastError() == WSAEWOULDBLOCK) 
        {
            return false;
        }
        else // 오류 발생
        {
            // send 오류 발생 처리
            OutputDebugStringA("send 오류 발생");
        }
    }

    return true;
}