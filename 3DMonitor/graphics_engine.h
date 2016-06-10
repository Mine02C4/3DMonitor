// Copyright 2011 MineStudio.
// GraphicsEngine�N���X��錾���܂��B3D�O���t�B�b�N�X����̒��S��S���܂��B

#ifndef NPCA3DMONITOR__GRAPHICSENGINE_H_
#define NPCA3DMONITOR__GRAPHICSENGINE_H_

#include <d3dx10.h>

#include "typedefs.h"

class DXEngine;
class ModelData;
class ObjectBox;

class GraphicsEngine
{
	DXEngine*			dx_engine_;
//	ModelData*			model_f14_;
//	ObjectBox*			object_box_f14_;
//	D3DLIGHT9			main_light_;
	CameraParam			main_camera_;

	void		Render(void);
	void		GetCameraParamByViewId(const CameraParam*,const int, CameraParam*);
public:
	GraphicsEngine(DXEngine*, HRESULT*);
	~GraphicsEngine(void);
	void		ProcessGraphics(void);
};

#endif