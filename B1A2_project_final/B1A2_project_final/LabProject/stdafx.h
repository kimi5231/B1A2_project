// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
/* stdafx.h에 header를 추가하는 이유 */
/* PCH( PreCompiled Header ) 를 통하여 자주 변경하지 않는  */
/* 헤더 파일에 대한 컴파일을 매번하지 않아도 되는 기능을 제공하기 때문 */
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.

#define FRAME_BUFFER_WIDTH	640
#define FRAME_BUFFER_HEIGHT	480

// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

// C++
#include <string>				
#include <wrl.h>				
#include <iostream>
#include <shellapi.h>			


#include <d3d12.h>				
#include <dxgi1_4.h>			
#include <D3Dcompiler.h>		

// DirectXMath 함수
#include <DirectXMath.h>		
#include <DirectXPackedVector.h>
#include <DirectXColors.h>		
#include <DirectXCollision.h>	

#include <Mmsystem.h>

#include <random>

using namespace DirectX;
using namespace DirectX::PackedVector;
using Microsoft::WRL::ComPtr;

#pragma comment( lib , "d3dCompiler.lib" )
#pragma comment( lib , "d3d12.lib" )
#pragma comment( lib , "dxgi.lib" )
#pragma comment( lib , "winmm.lib" )


/*정점의 색상을 무작위로(Random) 설정하기 위해 사용한다. 각 정점의 색상은 난수(Random Number)를 생성하여 지정한다.*/
#define RANDOM_COLOR XMFLOAT4(rand() / float(RAND_MAX), rand() / float(RAND_MAX), rand() / float(RAND_MAX), rand() / float(RAND_MAX))


// 버퍼 리소스 생성
// 업로드로 모든 리소스를 올려놓은 뒤, 그래픽 카드에서만 이용하게 할 것
extern ID3D12Resource* CreateBufferResource(ID3D12Device* pd3dDevice,	ID3D12GraphicsCommandList* pd3dCommandList, void* pData, UINT nBytes,
	D3D12_HEAP_TYPE d3dHeapType = D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATES d3dResourceStates = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, ID3D12Resource** ppd3dUploadBuffer = NULL
);

//3차원 벡터의 연산 
namespace Vector3 {

	inline bool IsZero(XMFLOAT3& xmf3Vector) 
	{
		if (xmf3Vector.x == 0.0f && xmf3Vector.y == 0.0f && xmf3Vector.z == 0.0f)
			return(true);

		return(false);
	}

	// Vector를 XMFloat3으로 바꿈
	inline XMFLOAT3 XMVectorToFloat3(const XMVECTOR& xmvVector) 
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, xmvVector);
		
		return(xmf3Result);
	}

	// 벡터에 스칼라 곱연산
	inline XMFLOAT3 ScalarProduct(XMFLOAT3& xmf3Vector, float fScalar, bool bNormalize = true) 
	{

		XMFLOAT3 xmf3Result;

		if (bNormalize)
			XMStoreFloat3(&xmf3Result, XMVector3Normalize(XMLoadFloat3(&xmf3Vector)) * fScalar);
		else
			XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector) * fScalar);

		return(xmf3Result);
	}

	// 벡터의 합연산
	inline XMFLOAT3 Add(const XMFLOAT3& xmf3Vector1, const XMFLOAT3& xmf3Vector2) 
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector1) + XMLoadFloat3(&xmf3Vector2));

		return(xmf3Result);
	}

	inline XMFLOAT3 Add(const XMFLOAT3& xmf3Vector1, const XMFLOAT3& xmf3Vector2, float fScalar) 
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector1) + (XMLoadFloat3(&xmf3Vector2) * fScalar));

		return(xmf3Result);

	}

	inline XMFLOAT3 Subtract(const XMFLOAT3& xmf3Vector1, const XMFLOAT3& xmf3Vector2)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector1) - XMLoadFloat3(&xmf3Vector2));

		return(xmf3Result);
	}

	// 벡터의 내적 연산 
	inline float DotProduct(const XMFLOAT3& xmf3Vector1, const XMFLOAT3& xmf3Vector2) 
	{

		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMVector3Dot(XMLoadFloat3(&xmf3Vector1), XMLoadFloat3(&xmf3Vector2)));
		
		return(xmf3Result.x);
	}

	// 벡터의 외적 연산 
	inline XMFLOAT3 CrossProduct(const XMFLOAT3& xmf3Vector1, const XMFLOAT3& xmf3Vector2, bool bNormalize = true) 
	{
		XMFLOAT3 xmf3Result;

		if (bNormalize)
			XMStoreFloat3(&xmf3Result, XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&xmf3Vector1), XMLoadFloat3(&xmf3Vector2)))); else XMStoreFloat3(&xmf3Result, XMVector3Cross(XMLoadFloat3(&xmf3Vector1), XMLoadFloat3(&xmf3Vector2)));

		return(xmf3Result);
	}

	// 벡터를 노말라이즈 해서 XMFLOAT3으로 반환
	inline XMFLOAT3 Normalize(const XMFLOAT3& xmf3Vector) 
	{
		XMFLOAT3 m_xmf3Normal;
		XMStoreFloat3(&m_xmf3Normal, XMVector3Normalize(XMLoadFloat3(&xmf3Vector)));

		return(m_xmf3Normal);
	}

	// 벡터의 길이를 구함
	inline float Length(XMFLOAT3& xmf3Vector) 
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMVector3Length(XMLoadFloat3(&xmf3Vector)));

		return(xmf3Result.x);
	}

	// 두 Vector 사이의 각을 구함
	inline float Angle(const XMVECTOR& xmvVector1, const XMVECTOR& xmvVector2)
	{
		XMVECTOR xmvAngle = XMVector3AngleBetweenNormals(xmvVector1, xmvVector2); 
		
		return(XMConvertToDegrees(acosf(XMVectorGetX(xmvAngle))));
	}

	// 두 XMFLOAT3 형식의 Vector사이의 각을 구해주는 함수
	inline float Angle(const XMFLOAT3& xmf3Vector1, const XMFLOAT3& xmf3Vector2) 
	{
		return(Angle(XMLoadFloat3(&xmf3Vector1), XMLoadFloat3(&xmf3Vector2)));
	}

	// TransformNormal의 경우 w를 0으로 만듦
	inline XMFLOAT3 TransformNormal(XMFLOAT3& xmf3Vector, XMMATRIX& xmmtxTransform) 
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMVector3TransformNormal(XMLoadFloat3(&xmf3Vector), xmmtxTransform));

		return(xmf3Result);
	}

	// TransformCoord의 경우 w를 1로 만들어줌(포인트(좌표) 변환에 주로 쓰임)
	inline XMFLOAT3 TransformCoord(const XMFLOAT3 xmf3Vector, const XMMATRIX xmxm4x4Transform)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMVector3TransformCoord(XMLoadFloat3(&xmf3Vector), xmxm4x4Transform));

		return(xmf3Result);
	}

	inline XMFLOAT3 TransformCoord(const XMFLOAT3& xmf3Vector, const XMFLOAT4X4& xmmtx4x4Matrix)
	{
		return(TransformCoord(xmf3Vector, XMLoadFloat4x4(&xmmtx4x4Matrix)));
	}
}

//4차원 벡터의 연산 
namespace Vector4 {

	inline XMFLOAT4 Add(const XMFLOAT4& xmf4Vector1, const XMFLOAT4& xmf4Vector2) 
	{
		XMFLOAT4 xmf4Result;
		XMStoreFloat4(&xmf4Result, XMLoadFloat4(&xmf4Vector1) + XMLoadFloat4(&xmf4Vector2));

		return(xmf4Result);
	}

	inline XMFLOAT4 Multiply(float fScalar, XMFLOAT4& xmf4Vector) 
	{
		XMFLOAT4 xmf4Result; XMStoreFloat4(&xmf4Result, fScalar * XMLoadFloat4(&xmf4Vector));

		return(xmf4Result);

	}

}

//행렬의 연산 
namespace Matrix4x4 {

	// 단위 행렬을 반환
	inline XMFLOAT4X4 Identity() {
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixIdentity());

		return(xmmtx4x4Result);

	}

	// 두 행렬을 곱하고 결과를 반환
	inline XMFLOAT4X4 Multiply(XMFLOAT4X4& xmmtx4x4Matrix1, XMFLOAT4X4& xmmtx4x4Matrix2)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMLoadFloat4x4(&xmmtx4x4Matrix1) * XMLoadFloat4x4(&xmmtx4x4Matrix2));

		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 Multiply(XMFLOAT4X4& xmmtx4x4Matrix1, XMMATRIX& xmmtxMatrix2) 
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMLoadFloat4x4(&xmmtx4x4Matrix1) * xmmtxMatrix2);

		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 Multiply(XMMATRIX& xmmtxMatrix1, XMFLOAT4X4& xmmtx4x4Matrix2) 
	{

		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, xmmtxMatrix1 * XMLoadFloat4x4(&xmmtx4x4Matrix2));

		return(xmmtx4x4Result);
	}

	// 역행렬을 구함
	inline XMFLOAT4X4 Inverse(XMFLOAT4X4& xmmtx4x4Matrix) 
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixInverse(NULL, XMLoadFloat4x4(&xmmtx4x4Matrix)));

		return(xmmtx4x4Result);
	}

	// 행렬에 대한 전치 행렬을 반환
	inline XMFLOAT4X4 Transpose(XMFLOAT4X4& xmmtx4x4Matrix) 
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixTranspose(XMLoadFloat4x4(&xmmtx4x4Matrix)));

		return(xmmtx4x4Result);
	}

	// 투영 행렬을 반환
	inline XMFLOAT4X4 PerspectiveFovLH(float FovAngleY, float AspectRatio, float NearZ, float FarZ) 
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixPerspectiveFovLH(FovAngleY, AspectRatio, NearZ, FarZ));

		return(xmmtx4x4Result);
	}

	// 카메라 변환 행렬을 반환
	inline XMFLOAT4X4 LookAtLH(const XMFLOAT3& xmf3EyePosition, const XMFLOAT3& xmf3LookAtPosition, const XMFLOAT3& xmf3UpDirection) 
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixLookAtLH(XMLoadFloat3(&xmf3EyePosition), XMLoadFloat3(&xmf3LookAtPosition), XMLoadFloat3(&xmf3UpDirection)));

		return(xmmtx4x4Result);
	}
}