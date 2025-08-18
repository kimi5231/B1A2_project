#pragma once
#include "Timer.h"

class CScene;
class CGameTimer;
class CGameObject;
class CPlayer;
class CCamera;

class CGameFramework
{
private:
	HINSTANCE					m_hInstance;
	HWND						m_hWnd;

	int							m_nWndClientWidth;
	int							m_nWndClientHeight;

	IDXGIFactory4* m_pdxgiFactory;
	IDXGISwapChain3* m_pdxgiSwapChain;
	ID3D12Device* m_pd3dDevice;

	bool						m_bMsaa4xEnable = false;
	UINT						m_nMsaa4xQualityLevels = 0;

	static const UINT			m_nSwapChainBuffers = 2;
	UINT						m_nSwapChainBufferIndex;

	ID3D12Resource* m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;
	UINT						m_nRtvDescriptorIncrementSize;

	ID3D12Resource* m_pd3dDepthStencilBuffer;
	ID3D12DescriptorHeap* m_pd3dDsvDescriptorHeap;
	UINT						m_nDsvDescriptorIncrementSize;

	ID3D12CommandQueue* m_pd3dCommandQueue;
	ID3D12CommandAllocator* m_pd3dCommandAllocator;
	ID3D12GraphicsCommandList* m_pd3dCommandList;

	ID3D12Fence* m_pd3dFence;
	UINT64						m_nFenceValue;
	HANDLE						m_hFenceEvent;

	UINT64						m_nFenceValues[m_nSwapChainBuffers];

	CScene* m_pScene;
	CCamera* m_pCamera = NULL;

#if defined(_DEBUG)
	ID3D12Debug* m_pd3dDebugController;
#endif
	ID3D12PipelineState* m_pd3dPipelineState;

	CGameTimer					m_GameTimer;
	_TCHAR						m_pszFrameRate[50];

	CPlayer* m_pPlayer = NULL;

	POINT m_ptOldCursorPos;

public:

	CGameFramework();
	~CGameFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);

	void OnDestroy();
	void CreateSwapChain();
	void CreateDirect3DDevice();
	void CreateRtvAndDsvDescriptorHeaps();
	void CreateCommandQueueAndList();
	void CreateRenderTargetView();
	void CreateDepthStencilView();
	void BuildObjects();
	void ReleaseObjects();
	void ProcessInput();
	void AnimateObjects();
	void FrameAdvance();
	void WaitForGpuComplete();
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnResizeBackBuffers();

	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void MoveToNextFrame();
};