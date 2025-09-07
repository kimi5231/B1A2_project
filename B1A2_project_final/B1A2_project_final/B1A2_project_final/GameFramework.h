#pragma once

#include "Timer.h"
#include "Player.h"
#include "Scene.h"

class CGameFramework
{
public:
	CGameFramework();
	~CGameFramework();

	// 프레임워크 초기화(주 윈도우가 생성되면 호출)
	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	// 스왑체인, 디스크립터힙, 디바이스, 커맨드 큐/할당자/리스트 생성
	void CreateSwapChain();
	void CreateDirect3DDevice();
	void CreateRtvAndDsvDescriptorHeaps();
	void CreateCommandQueueAndList();

	// RTV, DSV 생성
	void CreateRenderTargetView();
	void CreateDepthStencilView();

	void OnResizeBackBuffers();

	// 렌더링할 메쉬와 객체 생성/소멸
	void BuildObjects();
	void ReleaseObjects();

	// 사용자 입력
	void ProcessInput();

	// 애니메이션 
	void AnimateObjects();

	// 렌더링
	void FrameAdvance();

	// CPU - GPU 동기화
	void WaitForGpuComplete();

	void MoveToNextFrame();

	// 키보드, 마우스 입력 처리
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void CreatePlayer(__int32 id, XMFLOAT3 pos);

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	// 화면 크기
	int	m_nWndClientWidth;
	int	m_nWndClientHeight;

	// DirectX
	IDXGIFactory4* m_pdxgiFactory = NULL;
	IDXGISwapChain3* m_pdxgiSwapChain = NULL;
	ID3D12Device* m_pd3dDevice = NULL;

	// MSAA 다중 샘플링 활성화 및 샘플링 레벨 설정
	bool m_bMsaa4xEnable = false;
	UINT m_nMsaa4xQualityLevels = 0;

	// Swap Chain
	static const UINT	m_nSwapChainBuffers = 2;
	UINT				m_nSwapChainBufferIndex;

	// 렌더 타겟 버퍼, 디스크립터 힙 인터페이스 포인터, 렌더 타켓 디스크립터 원소 크기
	ID3D12Resource* m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap = NULL;
	UINT						m_nRtvDescriptorIncrementSize;

	// 뎁스-스텐실 버퍼, 디스크립터 힙 인터페이스 포인터, 뎁스-스텐실 디스크립터 원소 크기
	ID3D12Resource* m_pd3dDepthStencilBuffer = NULL;
	ID3D12DescriptorHeap* m_pd3dDsvDescriptorHeap = NULL;
	UINT m_nDsvDescriptorIncrementSize;
	
	// 커맨드 큐, 커맨드 할당자, 커맨드 리스트 인터페이스 포인터
	ID3D12CommandAllocator* m_pd3dCommandAllocator = NULL;
	ID3D12CommandQueue* m_pd3dCommandQueue = NULL;
	ID3D12GraphicsCommandList* m_pd3dCommandList = NULL;

	// 펜스, 펜스 값, 이벤트 핸들
	ID3D12Fence* m_pd3dFence = NULL;
	UINT64 m_nFenceValues[m_nSwapChainBuffers];
	HANDLE m_hFenceEvent;

#if defined(_DEBUG)
	ID3D12Debug* m_pd3dDebugController;
#endif

	// 타이머, 출력 문자열
	CGameTimer m_GameTimer;
	_TCHAR	m_pszFrameRate[50];

	CScene* m_pScene = NULL;
	std::vector<CPlayer*> m_pPlayers;
	CCamera* m_pCamera = NULL;

	// 마지막으로 마우스 버튼을 클릭할 때의 커서 위치
	POINT m_ptOldCursorPos;
};

