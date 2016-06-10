// Copyright 2011 MineStudio.
// ModelDataクラスを宣言します。3Dモデルの情報を格納します。

#ifndef NPCA3DMONITOR__MODELDATA_H_
#define NPCA3DMONITOR__MODELDATA_H_

#include <Windows.h>
#include <d3dx9.h>

class ModelData {
	LPD3DXMESH				mesh_;			// システム中のメッシュオブジェクト
	D3DMATERIAL9*			materials_;		// メッシュの質感(materials)
	LPDIRECT3DTEXTURE9*		textures_;		// メッシュのテクスチャ(texture)
	DWORD					num_materials_;	// メッシュ質感の数
	float					scale_;			// メッシュの倍率

	HRESULT		LoadFromXFileModel(LPCTSTR,LPDIRECT3DDEVICE9);
	HRESULT		LoadTexture(LPSTR,LPDIRECT3DTEXTURE9*,LPDIRECT3DDEVICE9);
	void		InitModel(void);
public:
	// パブリックメンバ関数
	ModelData(const TCHAR*,int*,float,LPDIRECT3DDEVICE9);
	~ModelData(void);
	VOID				RenderModel(LPDIRECT3DDEVICE9);
	float				get_scale_(void);
};

#endif