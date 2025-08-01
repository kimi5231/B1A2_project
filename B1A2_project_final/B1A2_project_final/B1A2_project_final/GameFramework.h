#pragma once
#include "Timer.h"

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
	void CreateRtvAndDsvDescriptorHeaps();
	void CreateDirect3DDevice();
	void CreateCommandQueueAndList();

	// 렌더 타겟 뷰, 뎁스 스텐실 뷰 생성
	void CreateRenderTargetViews();
	void CreateDepthStencilView();

	// 렌더링할 메쉬와 게임 객체 생성하고 소멸
	void BuildObjects();
	void ReleaseObjects();

	// 사용자 입력, 애니메이션, 렌더링
	void ProcessInput();
	void AnimateObjects();
	void FrameAdvance();

	// CPU와 GPU 동기화
	void WaitForGpuComplete();

	// 키보드, 마우스 입력 처리
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	// 전체 화면 
	void ChangeSwapChainState();
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	// 화면 크기
	int m_nWndClientWidth;
	int m_nWndClientHeight;

	// DirectX
	IDXGIFactory4* m_pdxgiFactory;	// DXGI 팩토리 
	IDXGISwapChain3* m_pdxgiSwapChain;	// 스왑 체인(디스플레이 제어에 필요)
	ID3D12Device* m_pd3dDevice;	// Direct3D 디바이스(리소스 생성에 필요)
	
	// MSAA 다중 샘플링 활성화 및 샘플링 레벨 설정
	bool m_bMsaa4xEnable = false;
	UINT m_nMsaa4xQualityLevels = 0;	

	static const UINT m_nSwapChainBuffers = 2;	// 스왑 체인의 후면 버퍼 개수
	UINT m_nSwapChainBufferIndex;	// 현재 스왑 체인의 후면 버퍼 인덱스

	// 렌더 타겟 버퍼, 디스크립터 힙 인터페이스 포인터, 렌더 타켓 디스크립터 원소 크기
	ID3D12Resource* m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;
	UINT m_nRtvDescriptorIncrementSize;

	// 뎁스-스텐실 버퍼, 디스크립터 힙 인터페이스 포인터, 뎁스-스텐실 디스크립터 원소 크기
	ID3D12Resource* m_pd3dDepthStencilBuffer;
	ID3D12DescriptorHeap* m_pd3dDsvDescriptorHeap;
	UINT m_nDsvDescriptorIncrementSize;

	// 커맨드 큐, 커맨드 할당자, 커맨드 리스트 인터페이스 포인터
	ID3D12CommandQueue* m_pd3dCommandQueue;
	ID3D12CommandAllocator* m_pd3dCommandAllocator;
	ID3D12GraphicsCommandList* m_pd3dCommandList;

	ID3D12PipelineState* m_pd3dPipelineState;	// 그래픽스 파이프라인 상태 객체

	ID3D12Fence* m_pd3dFence;	// 펜스 
	UINT64 m_nFenceValue;	// 펜스 값
	HANDLE m_hFenceEvent;	// 이벤트 핸들

	// 뷰포트, 씨저 사각형
	D3D12_VIEWPORT m_d3dViewport;	
	D3D12_RECT m_d3dScissorRect;	

	// 타이머
	CGameTimer m_GameTimer;
	_TCHAR m_pszFrameRate[50];	// 출력 위한 문자열
};

