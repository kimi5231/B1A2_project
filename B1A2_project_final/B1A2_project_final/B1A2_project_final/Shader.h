#pragma once
#include "GameObject.h"

class CShader
{
public:
	CShader();
	virtual ~CShader();

public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

	// 입력 조립기에게 정점 버퍼의 구조를 알려주기 위한 구조체 반환
	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	// 레스터라이저 상태를 설정하기 위한 구조체 반환
	virtual D3D12_RASTERIZER_DESC CreateRasterizerState();
	// 블렌딩 상태를 설정하기 위한 구조체 반환
	virtual D3D12_BLEND_DESC CreateBlendState();
	// 깊이-스텐실 검사를 위한 상태를 설정하기 위한 구조체 반환
	virtual D3D12_DEPTH_STENCIL_DESC CreateDepthStencilState();
	
	// 정점 쉐이더 바이트 코드를 생성(컴파일)
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob** ppd3dShaderBlob);
	// 픽셀 쉐이더 바이트 코드를 생성(컴파일)
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob** ppd3dShaderBlob);
	
	// 쉐이더 소스 코드를 컴파일하여 바이트 코드 구조체를 반환
	D3D12_SHADER_BYTECODE CompileShaderFromFile(const WCHAR* pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderProfile, ID3DBlob** ppd3dShaderBlob);
	
	// 그래픽스 파이프라인 상태 객체를 생성
	virtual void CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature);
	
	virtual void CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void ReleaseShaderVariables();
	virtual void UpdateShaderVariable(ID3D12GraphicsCommandList* pd3dCommandList, XMFLOAT4X4* pxmf4x4World);

	virtual void OnPrepareRender(ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);

private:
	int m_nReferences = 0;

protected:
	//셰이더가 포함하는 게임 객체들의 리스트(배열)
	CGameObject** m_ppObjects = NULL;
	int m_nObjects = 0;

	//파이프라인 상태 객체들의 리스트(배열)
	ID3D12PipelineState** m_ppd3dPipelineStates = NULL;
	int m_nPipelineStates = 0;
};

class CPlayerShader : public CShader
{
public:
	CPlayerShader();
	virtual ~CPlayerShader();

	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob** ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob** ppd3dShaderBlob);
	
	virtual void CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature * pd3dGraphicsRootSignature);
};

// 게임 객체들을 포함하는 쉐이더 객체
class CObjectsShader : public CShader
{
public:
	CObjectsShader();
	virtual ~CObjectsShader();

	virtual void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void ReleaseObjects();
	
	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob** ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob** ppd3dShaderBlob);
	
	virtual void CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature);
	
	virtual void ReleaseUploadBuffers();
	
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);

protected:
	CGameObject** m_ppObjects = NULL;
	int m_nObjects = 0;
};
