#pragma once
#include "Timer.h"
#include "GameObject.h"

class CCamera;
class CShader;

class CScene
{
public:
	CScene();
	~CScene();

	// Scene에서 마우스와 키보드 메시지 처리
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	
	void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	void ReleaseObjects();
	
	bool ProcessInput(UCHAR* pKeysBuffer);
	void AnimateObjects(float fTimeElapsed);

	void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);

	void ReleaseUploadBuffers();

	// 그래픽 루트 시그니처 생성
	ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);
	ID3D12RootSignature* GetGraphicsRootSignature();

protected:
	//씬은 셰이더들의 집합, 게임 객체는 쉐이더를 포함함.
	CGameObject** m_ppObjects = NULL;
	int m_nObjects = 0;

	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;
};

