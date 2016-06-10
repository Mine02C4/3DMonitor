// Copyright 2011 MineStudio.
// DAEModelクラスの宣言を行います

#ifndef FLIGHT__DAEMODEL_H_
#define FLIGHT__DAEMODEL_H_

#include <d3dx10.h>

#include <Vector>

#include <dae.h>
#include <dom/domCOLLADA.h>

#include "DXUT.h"

class DAEModel {
protected:
	DAE*	m_dae;
//	vector<IDirect3DVertexBuffer9*> m_pVB;		// 頂点バッファ
//	vector<IDirect3DIndexBuffer9*>	m_pIB;		// インデックスバッファ
//	vector<IDirect3DTexture9*>		m_pTexture;	// テクスチャ

//	vector<DWORD> m_dwVertices;				// 頂点数
//	vector<DWORD> m_dwIndecies;			// インデックス数

	// オフセットの最大数を返す
//	unsigned int getMaxOffset( domInputLocalOffset_Array &input_array );
	// 三角形の場合
//	HRESULT ConstructTriangles(domMesh *thisMesh, domTriangles *thisTriangles, IDirect3DDevice9* pd3dDevice);
	// Polylisitの場合
//	HRESULT ConstructPolylist(domMesh *thisMesh, domPolylist *thisPolylist, IDirect3DDevice9* pd3dDevice);
	// Polygonの場合
//	HRESULT ConstructPolygon(domMesh *thisMesh, domPolygons *thisPolygons, IDirect3DDevice9* pd3dDevice);

public:
	DAEModel();
	~DAEModel();

	VOID Cleanup();

	// 読み込み
	HRESULT LoadDAE(char strFilename[], IDirect3DDevice9* pd3dDevice);

	// 描画
	HRESULT Render( IDirect3DDevice9* pd3dDevice );

	// テクスチャを返す
	BOOL GetTexture(const DWORD dwIndex, IDirect3DTexture9** pTexture)
	{
		if(dwIndex > m_pTexture.size() || m_pTexture.size()==0)
		{
			*pTexture = NULL;
			return FALSE;
		}

		*pTexture = m_pTexture[dwIndex];
		return TRUE;
	}
};

#endif