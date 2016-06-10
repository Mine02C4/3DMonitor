// Copyright 2011 MineStudio.
// ObjectBoxクラスを宣言します。3Dオブジェクトの情報を格納します。
// このクラス単体でも使用できますが継承して使った方が制御しやすいです。

#ifndef NPCA3DMONITOR__OBJECTBOX_H_
#define NPCA3DMONITOR__OBJECTBOX_H_

#include <d3dx9.h>

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