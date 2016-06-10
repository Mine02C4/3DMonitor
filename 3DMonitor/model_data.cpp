// Copyright 2011 MineStudio.
// ModelData�N���X�̒�`���s���܂��B

#include "model_data.h"

#include "appdefs.h"

//�R���X�g���N�^
ModelData::ModelData(const TCHAR* ModelName,int* error_flag,float scale, LPDIRECT3DDEVICE9 d3d_device)
{
	InitModel();
	if(FAILED(LoadFromXFileModel(ModelName, d3d_device)))
	{
		*error_flag = TRUE;
	}
	scale_	= scale;
}

//�f�X�g���N�^
ModelData::~ModelData(void)
{
	// ���b�V���}�e���A���̉��
	SAFE_DELETE_ARRAY(materials_);

	// �e�N�X�`���̉��
	if( textures_ )
	{
		for(DWORD j0 = 0; j0 < num_materials_ ; j0++ ){ SAFE_RELEASE( textures_[j0] );}
		SAFE_DELETE_ARRAY( textures_ );
	}

	/*���b�V���̊J��*/
	SAFE_RELEASE( mesh_ );
}

//X�t�@�C������̃��f���f�[�^�̓ǂݍ���
HRESULT ModelData::LoadFromXFileModel(LPCTSTR file_name, LPDIRECT3DDEVICE9 d3d_device)
{
	// �ꎞ�o�b�t�@�p
	LPD3DXBUFFER pD3DXMtrlBuffer;

	// X�t�@�C���̓ǂݍ��݁B
	if(FAILED(D3DXLoadMeshFromX(file_name, D3DXMESH_SYSTEMMEM,d3d_device, NULL,&pD3DXMtrlBuffer,NULL,&num_materials_,&mesh_))) {
		TCHAR caution_string[kStringLength];
		wsprintf(caution_string,TEXT("X�t�@�C���w%s�x��������܂���ł����B"),file_name);
		MessageBox(NULL,caution_string,kWindowTitle,MB_OK);
		return(E_FAIL);
	}

	// pD3DXMtrlBuffer����A�}�e���A����e�N�X�`���̖��̂Ȃǂ̏����擾����B
	D3DXMATERIAL* d3dx_materials	= (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	materials_	= new D3DMATERIAL9[num_materials_];
	textures_	= new LPDIRECT3DTEXTURE9[num_materials_];

	for(DWORD i0=0; i0 < num_materials_ ; i0++ )
	{
		// �����imaterial�j�̃R�s�[
		materials_[i0] = d3dx_materials[i0].MatD3D;

		// �����imaterial�j�Ɋ�����ݒ肷��iD3DX���������Ȃ����߁j
		materials_[i0].Ambient = materials_[i0].Diffuse;

		textures_[i0] = NULL;
		if( d3dx_materials[i0].pTextureFilename != NULL && lstrlenA(d3dx_materials[i0].pTextureFilename) > 0 )
		{
			if(FAILED( LoadTexture(d3dx_materials[i0].pTextureFilename,&textures_[i0],d3d_device)))
			{
				TCHAR caution_string[kStringLength];

				wsprintf(caution_string,TEXT("X�t�@�C���w%s�x�Ŏw�肳�ꂽ�e�N�X�`���}�b�v�t�@�C����������܂���ł����B"),file_name);
				MessageBox(NULL,caution_string,kWindowTitle,MB_OK);
				return( E_FAIL );
			}
		}
	}

	// �����imaterial�j�o�b�t�@�̊J���B
	pD3DXMtrlBuffer->Release();

	return(S_OK);
}

//�摜�t�@�C�����e�N�X�`���Ƃ��ēǂݍ���
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
	// �e�N�X�`���̐���
	if(FAILED(D3DXCreateTextureFromFile(d3d_device,tmp_name,texture)))
	{
		return(E_FAIL);
	}

	return( S_OK );
}

//���f���̏�����
void ModelData::InitModel(void)
{
	mesh_			= NULL;
	materials_		= NULL;
	textures_		= NULL;
	num_materials_	= 0;
}

// ���b�V���������_�����O
VOID ModelData::RenderModel(LPDIRECT3DDEVICE9 D3DDevice)
{
	// �}�e���A���̐��������[�v
	for(DWORD i=0;i<num_materials_;i++)
	{
		// �T�u�Z�b�g�Ƀ}�e���A���ƃe�N�X�`����ݒ�B
		D3DDevice->SetMaterial(&materials_[i]);
		D3DDevice->SetTexture(0,textures_[i]);
		
		// ���b�V���E�T�u�Z�b�g�̕`��B
		mesh_->DrawSubset(i);
	}
}

// �g�嗦���擾
float ModelData::get_scale_()
{
	return scale_;
}