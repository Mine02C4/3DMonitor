// Copyright 2011 MineStudio.
// ModelDataクラスの定義を行います。

#include "model_data.h"

#include "appdefs.h"

//コンストラクタ
ModelData::ModelData(const TCHAR* ModelName,int* error_flag,float scale, LPDIRECT3DDEVICE9 d3d_device)
{
	InitModel();
	if(FAILED(LoadFromXFileModel(ModelName, d3d_device)))
	{
		*error_flag = TRUE;
	}
	scale_	= scale;
}

//デストラクタ
ModelData::~ModelData(void)
{
	// メッシュマテリアルの解放
	SAFE_DELETE_ARRAY(materials_);

	// テクスチャの解放
	if( textures_ )
	{
		for(DWORD j0 = 0; j0 < num_materials_ ; j0++ ){ SAFE_RELEASE( textures_[j0] );}
		SAFE_DELETE_ARRAY( textures_ );
	}

	/*メッシュの開放*/
	SAFE_RELEASE( mesh_ );
}

//Xファイルからのモデルデータの読み込み
HRESULT ModelData::LoadFromXFileModel(LPCTSTR file_name, LPDIRECT3DDEVICE9 d3d_device)
{
	// 一時バッファ用
	LPD3DXBUFFER pD3DXMtrlBuffer;

	// Xファイルの読み込み。
	if(FAILED(D3DXLoadMeshFromX(file_name, D3DXMESH_SYSTEMMEM,d3d_device, NULL,&pD3DXMtrlBuffer,NULL,&num_materials_,&mesh_))) {
		TCHAR caution_string[kStringLength];
		wsprintf(caution_string,TEXT("Xファイル『%s』が見つかりませんでした。"),file_name);
		MessageBox(NULL,caution_string,kWindowTitle,MB_OK);
		return(E_FAIL);
	}

	// pD3DXMtrlBufferから、マテリアルやテクスチャの名称などの情報を取得する。
	D3DXMATERIAL* d3dx_materials	= (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	materials_	= new D3DMATERIAL9[num_materials_];
	textures_	= new LPDIRECT3DTEXTURE9[num_materials_];

	for(DWORD i0=0; i0 < num_materials_ ; i0++ )
	{
		// 質感（material）のコピー
		materials_[i0] = d3dx_materials[i0].MatD3D;

		// 質感（material）に環境光を設定する（D3DXが何もしないため）
		materials_[i0].Ambient = materials_[i0].Diffuse;

		textures_[i0] = NULL;
		if( d3dx_materials[i0].pTextureFilename != NULL && lstrlenA(d3dx_materials[i0].pTextureFilename) > 0 )
		{
			if(FAILED( LoadTexture(d3dx_materials[i0].pTextureFilename,&textures_[i0],d3d_device)))
			{
				TCHAR caution_string[kStringLength];

				wsprintf(caution_string,TEXT("Xファイル『%s』で指定されたテクスチャマップファイルが見つかりませんでした。"),file_name);
				MessageBox(NULL,caution_string,kWindowTitle,MB_OK);
				return( E_FAIL );
			}
		}
	}

	// 質感（material）バッファの開放。
	pD3DXMtrlBuffer->Release();

	return(S_OK);
}

//画像ファイルをテクスチャとして読み込む
HRESULT ModelData::LoadTexture(LPSTR file_name, LPDIRECT3DTEXTURE9* texture,LPDIRECT3DDEVICE9 d3d_device)
{
	TCHAR tmp_name[255];
#ifdef UNICODE
	if(MultiByteToWideChar(CP_ACP,0,file_name,-1,tmp_name,(int)(sizeof(tmp_name)/sizeof(TCHAR))-1) == 0)
	{
		return(E_FAIL);
	}
#else
	*tmp_name = *file_name;
#endif
	// テクスチャの生成
	if(FAILED(D3DXCreateTextureFromFile(d3d_device,tmp_name,texture)))
	{
		return(E_FAIL);
	}

	return( S_OK );
}

//モデルの初期化
void ModelData::InitModel(void)
{
	mesh_			= NULL;
	materials_		= NULL;
	textures_		= NULL;
	num_materials_	= 0;
}

// メッシュをレンダリング
VOID ModelData::RenderModel(LPDIRECT3DDEVICE9 D3DDevice)
{
	// マテリアルの数だけループ
	for(DWORD i=0;i<num_materials_;i++)
	{
		// サブセットにマテリアルとテクスチャを設定。
		D3DDevice->SetMaterial(&materials_[i]);
		D3DDevice->SetTexture(0,textures_[i]);
		
		// メッシュ・サブセットの描画。
		mesh_->DrawSubset(i);
	}
}

// 拡大率を取得
float ModelData::get_scale_()
{
	return scale_;
}