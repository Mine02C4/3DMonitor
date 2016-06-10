// Copyright 2011 MineStudio.
// D3DEngineクラスの宣言を行います。
// DXUTとDirect3D 10が必須です。

#ifndef FLIGHT__D3DENGINE_H_
#define FLIGHT__D3DENGINE_H_

#include "DXUT.h"
#include "SDKmesh.h"

class D3DEngine {
	ID3D10Effect*						effect_;
	ID3D10InputLayout*					vertex_layout_;
	ID3D10EffectTechnique*				technique_;
	CDXUTSDKMesh						mesh_;
	ID3D10EffectShaderResourceVariable* diffuse_variable_;
	ID3D10EffectMatrixVariable*         world_variable_;
	ID3D10EffectMatrixVariable*         view_variable_;
	ID3D10EffectMatrixVariable*         projection_variable_;
	D3DXMATRIX                          world_;
	D3DXMATRIX                          view_;
	D3DXMATRIX                          projection_;
	void	CreateViews(ID3D10Device*);
public:
	D3DEngine();
	~D3DEngine();
	HRESULT	OnCreateDevice(ID3D10Device*);
	HRESULT	OnResizedSwapChain(const DXGI_SURFACE_DESC*);
	void	OnFrameRender(ID3D10Device*,float);
	void	OnFrameMove(double);
};

#endif