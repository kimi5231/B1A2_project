#pragma once
#include "Timer.h"

class CScene
{
public:
	CScene();
	~CScene();

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	
	void CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);
	void CreateGraphicsPipelineState(ID3D12Device* pd3dDevice);
	
	void BuildObjects(ID3D12Device* pd3dDevice);
	void ReleaseObjects();
	
	bool ProcessInput();
	void AnimateObjects(float fTimeElapsed);
	
	void PrepareRender(ID3D12GraphicsCommandList* pd3dCommandList);
	void Render(ID3D12GraphicsCommandList* pd3dCommandList);

	// 루트 시그니처
	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;

	// 파이프라인 상태
	ID3D12PipelineState* m_pd3dPipelineState = NULL;
};

