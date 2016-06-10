// Copyright 2011 MineStudio.
// ModelData�N���X��錾���܂��B3D���f���̏����i�[���܂��B

#ifndef NPCA3DMONITOR__MODELDATA_H_
#define NPCA3DMONITOR__MODELDATA_H_

#include <Windows.h>
#include <d3dx10.h>

class ModelData {
	LPD3DXMESH				mesh_;			// �V�X�e�����̃��b�V���I�u�W�F�N�g
	D3DMATERIAL9*			materials_;		// ���b�V���̎���(materials)
	LPDIRECT3DTEXTURE9*		textures_;		// ���b�V���̃e�N�X�`��(texture)
	DWORD					num_materials_;	// ���b�V�������̐�
	float					scale_;			// ���b�V���̔{��

	HRESULT		LoadFromXFileModel(LPCTSTR,LPDIRECT3DDEVICE9);
	HRESULT		LoadTexture(LPSTR,LPDIRECT3DTEXTURE9*,LPDIRECT3DDEVICE9);
	void		InitModel(void);
public:
	// �p�u���b�N�����o�֐�
	ModelData(const TCHAR*,int*,float,LPDIRECT3DDEVICE9);
	~ModelData(void);
	VOID				RenderModel(LPDIRECT3DDEVICE9);
	float				get_scale_(void);
};

#endif