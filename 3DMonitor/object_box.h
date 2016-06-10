// Copyright 2011 MineStudio.
// ObjectBox�N���X��錾���܂��B3D�I�u�W�F�N�g�̏����i�[���܂��B
// ���̃N���X�P�̂ł��g�p�ł��܂����p�����Ďg�����������䂵�₷���ł��B

#ifndef NPCA3DMONITOR__OBJECTBOX_H_
#define NPCA3DMONITOR__OBJECTBOX_H_

#include <d3dx10.h>

#include "dx_engine.h"

class ModelData;

class ObjectBox {
	D3DXVECTOR3		position_;
	DirectionYPR	direction_;
	ModelData*		model_;
	float			scale_;
public:
	ObjectBox(ModelData*);
	ObjectBox(ModelData*,D3DXVECTOR3);
	ObjectBox(ModelData*,D3DXVECTOR3,DirectionYPR);
	~ObjectBox(void);
	void	Render(DXEngine*);
	void	TestSpin(void);
};

#endif