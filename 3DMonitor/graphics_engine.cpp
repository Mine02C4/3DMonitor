// Copyright 2011 MineStudio.
// GraphicsEngineクラスの定義を行います。

#include "chead.h"

#include "graphics_engine.h"

#include <math.h>

#include "dx_engine.h"
#include "file_names.h"
//#include "model_data.h"
//#include "object_box.h"

// コンストラクタ
GraphicsEngine::GraphicsEngine(DXEngine* tmp_dx, HRESULT* result) {
	dx_engine_	= tmp_dx;
//	model_f14_	= NULL;
//	object_box_f14_	= NULL;

/*	int	error_flag = FALSE;
	model_f14_	= new ModelData(kFilePot, &error_flag, 0.5f, dx_engine_->get_d3d_device());
	if(error_flag==TRUE) {
		*result = E_FAIL;
		return;
	}*/

	//object_box_f14_	= new ObjectBox(model_f14_, D3DXVECTOR3(0.0f,0.0f,0.0f), DirectionYPR(0.0f,0.0f,-(D3DX_PI/2.0f)));

	// ライト
/*	ZeroMemory(&main_light_,sizeof(D3DLIGHT9));
	main_light_.Type		= D3DLIGHT_DIRECTIONAL;
	main_light_.Diffuse.r	= 1.0f;
	main_light_.Diffuse.g	= 0.9f;
	main_light_.Diffuse.b	= 0.95f;
	main_light_.Diffuse.a	= 0.0f;
	main_light_.Direction	= D3DXVECTOR3(1.0f,-1.0f,1.0f);

	// カメラ
	main_camera_	= CameraParam(D3DX_PI/4,1.0f,800.0f,D3DXVECTOR3(0.0f,20.0f,-80.0f));*/
}

// デストラクタ
GraphicsEngine::~GraphicsEngine() {
//	SAFE_DELETE(object_box_f14_);
//	SAFE_DELETE(model_f14_);
}

// レンダリング
void GraphicsEngine::Render()
{
	ID3D10Device*	d3d_device = dx_engine_->get_d3d_device();
	 float color[4] = { 0.0f, 0.125f, 0.6f, 1.0f };
	dx_engine_->ClearRenderTargetView(color);

	//// シーンの開始
	//if(SUCCEEDED(d3d_device->BeginScene()))
	//{
	//	// ライトの設定
	//	dx_engine_->SetLight(kLightNumberMain,main_light_);
	//	// カメラの設定
	//	//dx_engine_->SetCamera(main_camera_);
	//	// レンダリングの設定
	//	dx_engine_->SetRender(kRenderStateNormal);
	//	// F14をレンダリング
	//	//object_box_f14_->Render(dx_engine_);

	//	// 全視点でレンダリング開始
	//	CameraParam	tmp_camera;
	//	for(int i=0;i<kNumOfParallax;i++) {
	//		//d3d_device->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00,0x00,0x00),1.0f,0);
	//		dx_engine_->SetViewTarget(i);
	//		GetCameraParamByViewId(&main_camera_, i, &tmp_camera);
	//		dx_engine_->SetCamera(tmp_camera);
	//		object_box_f14_->Render(dx_engine_);
	//	}

	//	// 各視点レンダリングの結果をバックバッファーのコピー
	//	dx_engine_->SetDefaultBuffer();
	//	dx_engine_->SetCamera(main_camera_);
	//	object_box_f14_->Render(dx_engine_);

	//	HDC buffer_dc;
	//	dx_engine_->GetBufferDC(&buffer_dc);
	//	
	//	win_engine->RenderBuffer(&buffer_dc);

	//	dx_engine_->ReleaseBufferDC(&buffer_dc);

	//	// シーンの終了
	//	d3d_device->EndScene();
	//}

	frame_counter++;
	if((frame_counter == 101)||(frame_counter == 1)){
		_asm {
			NOP
		}
	}

	// 描画を反映
	//d3d_device->Present(NULL,NULL,NULL,NULL);
}

// 中央カメラのパラメータと視点IDからカメラのパラメータを生成
void GraphicsEngine::GetCameraParamByViewId(const CameraParam* main_camera,const int camera_id, CameraParam* out_camera) {
	*out_camera = CameraParam(*main_camera);
	double difference_view	= NULL;
	if(((float)(kNumOfParallax-1))/2.0f+1.0f==(float)camera_id) {
		return;
	}else {
		difference_view	= (-((double)kNumOfParallax*kRadAnglePitch/2.0))+kRadAnglePitch*(double)(camera_id-1);
		out_camera->position	= main_camera->look_position+(float)cos(difference_view)*(main_camera->position - main_camera->look_position);
		D3DXVECTOR3 tmp_vec;
		out_camera->position += (*D3DXVec3Normalize(&tmp_vec, D3DXVec3Cross(&tmp_vec, &D3DXVECTOR3(0.0f,-1.0f,0.0f), &(main_camera->look_position - main_camera->position))))*(float)sin(difference_view)*D3DXVec3Length(&(main_camera->look_position - main_camera->position));
	}
}

// 1フレームの処理
void GraphicsEngine::ProcessGraphics() {
//	dx_engine_->GetInput();
//	object_box_f14_->TestSpin();
	Render();
}