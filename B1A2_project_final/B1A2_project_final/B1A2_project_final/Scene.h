#pragma once
#include "Timer.h"
#include "GameObject.h"
#include "Shader.h"

class CCamera;

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

	//씬의 모든 게임 객체들에 대한 마우스 픽킹을 수행
	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);

protected:
	// Batch(배치) 처리를 하기 위해 Scene을 쉐이더들의 리스트로 표현
	CObjectsShader* m_pShaders = NULL;	// 인스턴싱 객체일 때는 CInstancingShader* m_pShaders = NULL;
	int m_nShaders = 0;

	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;
};

