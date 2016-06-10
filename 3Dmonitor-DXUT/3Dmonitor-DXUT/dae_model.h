// Copyright 2011 MineStudio.
// DAEModel�N���X�̐錾���s���܂�

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
//	vector<IDirect3DVertexBuffer9*> m_pVB;		// ���_�o�b�t�@
//	vector<IDirect3DIndexBuffer9*>	m_pIB;		// �C���f�b�N�X�o�b�t�@
//	vector<IDirect3DTexture9*>		m_pTexture;	// �e�N�X�`��

//	vector<DWORD> m_dwVertices;				// ���_��
//	vector<DWORD> m_dwIndecies;			// �C���f�b�N�X��

	// �I�t�Z�b�g�̍ő吔��Ԃ�
//	unsigned int getMaxOffset( domInputLocalOffset_Array &input_array );
	// �O�p�`�̏ꍇ
//	HRESULT ConstructTriangles(domMesh *thisMesh, domTriangles *thisTriangles, IDirect3DDevice9* pd3dDevice);
	// Polylisit�̏ꍇ
//	HRESULT ConstructPolylist(domMesh *thisMesh, domPolylist *thisPolylist, IDirect3DDevice9* pd3dDevice);
	// Polygon�̏ꍇ
//	HRESULT ConstructPolygon(domMesh *thisMesh, domPolygons *thisPolygons, IDirect3DDevice9* pd3dDevice);

public:
	DAEModel();
	~DAEModel();

	VOID Cleanup();

	// �ǂݍ���
	HRESULT LoadDAE(char strFilename[], IDirect3DDevice9* pd3dDevice);

	// �`��
	HRESULT Render( IDirect3DDevice9* pd3dDevice );

	// �e�N�X�`����Ԃ�
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