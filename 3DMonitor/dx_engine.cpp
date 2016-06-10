// Copyright 2011 MineStudio.
// DxEngineクラスの定義を行います。

#include "chead.h"

#include "dx_engine.h"

#include <stdio.h>

#include <windows.h>

// コンストラクタ
DXEngine::DXEngine(HWND buffer_window,BOOL boolFullScreen,WNDCLASSEX buffer_window_class,HRESULT* result,HINSTANCE hInstance, HWND main_window)
{
	// 変数初期化
	d3d_			= NULL;
	d3d_device_		= NULL;
	direct_input_	= NULL;
	din_keybord_	= NULL;
	din_mouse_		= NULL;
	ZeroMemory(&mouse_state_,sizeof(DIMOUSESTATE2));
	ZeroMemory(key_state_,sizeof(key_state_));
	// フルスクリーンの設定
	full_screen_flag_	= boolFullScreen;
	/*
	※注意　この値をTRUEにするとフルスクリーンモードとしてビルトされ、バグが発生した場合に画面が占領されていて停止できなくなり場合があります。
	バグを完全に修正してからこの値をTRUEにしてください。
	*/
	// Direct3Dより先に初期化すると、フルスクリーンモードのときエラーダイアログが見えなくなるため
	/*if(FAILED(InitDirectInput(main_window,hInstance)))
	{
		//ZeroMemory(DInkey_state_,sizeof(DInkey_state_)); //念のためキーボードステータスバッファを初期化
		MessageBox( NULL, TEXT("direct_input_の初期化に失敗しました。"), kErrorMessage, MB_OK|MB_ICONHAND );
		*result = E_FAIL;
		return;
	}*/
	// Direct3Dの初期化
	if(FAILED(InitDirect3D(buffer_window)))
	{
		MessageBox( NULL, TEXT("DirectXの初期化に失敗しました。"), kErrorMessage, MB_OK|MB_ICONHAND );
		*result = E_FAIL;
		return;
	}
	*result = S_OK;
}

// デストラクタ
DXEngine::~DXEngine()
{
	CleanUpDirectInput();
	CleanUpDirect3D();
}

// Direct3Dの初期化
HRESULT DXEngine::InitDirect3D(HWND hWnd)
{
	effect_		= NULL;
	technique_	= NULL;
	for(int i=0;i<kNumOfParallax;i++) {
		parallax_buffers_[i] = NULL;
	}

	// D3Dオブジェクトの生成。
	if(NULL == (d3d_ = Direct3DCreate9(D3D_SDK_VERSION))){return(E_FAIL);}
	// D3Dディバイスを生成するための構造体を設定する。
	ZeroMemory(&d3d_present_params_,sizeof(D3DPRESENT_PARAMETERS));

	//現在のプライマリディスプレイアダプタのモードを取得する
	D3DDISPLAYMODE aDisplayMode;		//ディスプレイモードの情報を収めるため
	if(FAILED( d3d_->GetAdapterDisplayMode( D3DADAPTER_DEFAULT , &aDisplayMode )))
	{
		MessageBox(NULL,TEXT("ディスプレイモードの取得に失敗しました"),kWindowTitle,MB_OK | MB_ICONSTOP);
		return( E_FAIL ); 
	}
	// プレゼンテーションパラメータの設定
	//if(full_screen_flag_)
	//{
		//d3d_present_params_.BackBufferHeight			= aDisplayMode.Height;			// バックバッファの高さ
		//d3d_present_params_.BackBufferWidth				= aDisplayMode.Width;			// バックバッファの幅
		d3d_present_params_.BackBufferHeight			= kMonitorHeight;			// バックバッファの高さ
		d3d_present_params_.BackBufferWidth				= kMonitorWidth;			// バックバッファの幅

		d3d_present_params_.BackBufferFormat			= D3DFMT_X8R8G8B8;			// バックバッファのフォーマット
	//	d3d_present_params_.Windowed					= FALSE;	
		// フルスクリーンモード
	//}
	//else
	//{
	//	d3d_present_params_.BackBufferFormat			= D3DFMT_UNKNOWN;				// フォーマットは今の画面モードに従う
		d3d_present_params_.Windowed					= TRUE;							// ウィンドウモード
	//}
	//共通パラメータ
	d3d_present_params_.BackBufferCount				= 1;							// バックバッファの数
	d3d_present_params_.MultiSampleType				= D3DMULTISAMPLE_NONE;			// マルチサンプリングは行わない
	d3d_present_params_.MultiSampleQuality			= 0;							// マルチサンプリングは行わないので0
	d3d_present_params_.SwapEffect					= D3DSWAPEFFECT_DISCARD;		// Direct3Dにスワップエフェクトを任せる
	d3d_present_params_.EnableAutoDepthStencil		= TRUE;							// Direct3Dに深度バッファの管理を任せる
	d3d_present_params_.AutoDepthStencilFormat		= D3DFMT_D16;					// 深度バッファのフォーマット（通常はこの値で問題ない）
	d3d_present_params_.hDeviceWindow				= hWnd;							// カバーウィンドウ＝アプリケーションのウィンドウ
	d3d_present_params_.Flags						= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	d3d_present_params_.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;		// 今のリフレッシュレートをそのまま使う
	d3d_present_params_.PresentationInterval		= D3DPRESENT_INTERVAL_DEFAULT;	// モニタの垂直回帰を待つ

	// Direct3Dデバイスの使用の可否を確認
	if(FAILED(d3d_->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, aDisplayMode.Format, D3DFMT_X8R8G8B8, TRUE))) {
		MessageBox(NULL,TEXT("Direct3Dを初期化する条件を満たしていないです。"),kWindowTitle,MB_OK | MB_ICONSTOP);
		return E_FAIL;
	}

	// D3Dディバイスの生成
	// 頂点シェーダ＆ピクセルシェーダ
	if( FAILED( d3d_->CreateDevice( D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL, hWnd,
										D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3d_present_params_, &d3d_device_ ) ) )
	{
		// 失敗したら頂点シェーダのみ
		// なお、今回のプロジェクトではこれ以降は無意味
		if( FAILED( d3d_->CreateDevice( D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL, hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3d_present_params_, &d3d_device_ ) ) )
		{
			// それでもダメなら、REFでやってみる
			if( FAILED( d3d_->CreateDevice( D3DADAPTER_DEFAULT,D3DDEVTYPE_REF, hWnd,
												D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3d_present_params_, &d3d_device_ ) ) )
			{
				// ダメなら諦め
				MessageBox(NULL,TEXT("Direct3Dを初期化できませんでした"),kWindowTitle,MB_OK | MB_ICONSTOP);
				return( E_FAIL ); 
			} else {
				MessageBox(NULL,TEXT("対応してないためためピクセルシェーダと頂点シェーダは動きません"),kWindowTitle,MB_OK | MB_ICONSTOP);
			}
		} else {
			MessageBox(NULL,TEXT("対応してないためためピクセルシェーダは動きません"),kWindowTitle,MB_OK | MB_ICONSTOP);
		}
	}
	// テクスチャステージステートの設定
	d3d_device_->SetTextureStageState( 0 , D3DTSS_COLORARG1,	D3DTA_TEXTURE );	// テクスチャの色を使用
	d3d_device_->SetTextureStageState( 0 , D3DTSS_COLORARG2,	D3DTA_DIFFUSE );	// 頂点の色を使用
	d3d_device_->SetTextureStageState( 0 , D3DTSS_COLOROP,		D3DTOP_MODULATE );	// 乗算する

	LPD3DXBUFFER err = NULL;
	if(FAILED(D3DXCreateEffectFromFile(d3d_device_, TEXT("hlsl.fx"), NULL, NULL, 0, NULL, &effect_, &err))) {
		TCHAR error_message[1000];
#ifdef UNICODE
		if(MultiByteToWideChar(CP_ACP,0,(LPCSTR)err->GetBufferPointer(),-1,error_message,(int)(sizeof(error_message)/sizeof(TCHAR))-1) == 0)
		{
			return(E_FAIL);
		}
#else
		error_message = (LPTSTR)err->GetBufferPointer();
#endif
		MessageBox( NULL, error_message, kErrorMessage, MB_OK);
		return E_FAIL;
	}
	technique_ = effect_->GetTechniqueByName("P0");
	SAFE_RELEASE(err);

	// バックバッファを取得
	d3d_device_->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &back_buffer_);
	// 各視点用のバッファを用意
	for(int i=0;i<kNumOfParallax;i++) {
		d3d_device_->CreateTexture(kWidth3DPixel, kHeight3DPixel, 1,D3DUSAGE_DYNAMIC, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &parallax_textures_[i],NULL);
		parallax_textures_[i]->GetSurfaceLevel(0,&parallax_buffers_[i]);
		//d3d_device_->CreateRenderTarget(kWidth3DPixel, kHeight3DPixel, D3DFMT_X8R8G8B8, D3DMULTISAMPLE_NONE, 0, FALSE, &parallax_buffers_[i], NULL);
		char value_name[10];
		sprintf_s(value_name,"tex%d",i);
		texture_handle_[i] = effect_->GetParameterByName(NULL,(LPCSTR)value_name);
		//effect_->SetTexture(,parallax_textures_[i]);
	}

	return ( S_OK );
}

// D3Dの後始末
VOID DXEngine::CleanUpDirect3D()
{
	// サーフェイルの解放
	for(int i=0;i<kNumOfParallax;i++) {
		SAFE_RELEASE(parallax_buffers_[i]);
	}

	// DirectXディバイスなどの解放	
	SAFE_RELEASE(d3d_device_);
	SAFE_RELEASE(d3d_);
}

// フルスクリーンかどうかを返す
BOOL DXEngine::CheckFullScreen()
{
	return full_screen_flag_;
}

// Direct3Dデバイスを返します
LPDIRECT3DDEVICE9 DXEngine::get_d3d_device()
{
	return d3d_device_;
}

// レンダリングの設定
void DXEngine::SetRender(RenderState RState)
{
	switch(RState)
	{
	case kRenderStateNormal:
		// レンダリングステートの設定
		d3d_device_->SetRenderState( D3DRS_CULLMODE,			D3DCULL_NONE	);		// ポリゴンの裏表チェックをしない
		d3d_device_->SetRenderState( D3DRS_ALPHABLENDENABLE,	FALSE			);		// αブレンディング無効
		d3d_device_->SetRenderState( D3DRS_ALPHATESTENABLE,		FALSE			);		// αテストを無効に
		d3d_device_->SetRenderState( D3DRS_ZWRITEENABLE,		TRUE			);		// Zバッファへの書き込み許可
		d3d_device_->SetRenderState( D3DRS_ZENABLE,				D3DZB_TRUE		);		// Zバッファを有効にする。
		d3d_device_->SetRenderState( D3DRS_AMBIENT,				0x00888888		);		// 環境光
		d3d_device_->SetRenderState( D3DRS_SRCBLEND,			D3DBLEND_ONE	);		// ソース側の色の比率
		d3d_device_->SetRenderState( D3DRS_DESTBLEND,			D3DBLEND_ZERO	);		// 書き込み側の色の比率
		d3d_device_->SetRenderState( D3DRS_SHADEMODE,			D3DSHADE_GOURAUD);		// シェードモードを滑らかにする

		d3d_device_->LightEnable( kLightNumberMain, TRUE );	// ライトの有効化

		// テクスチャステージステートの設定
		d3d_device_->SetTextureStageState( 0 , D3DTSS_ALPHAOP,	D3DTOP_DISABLE );	//αチャネルは無効に


		// サンプラーステートの設定
		SetTextureSamplerState(D3DTEXF_LINEAR);
		break;

	case kRenderStateSq:
		// レンダリングステートの設定
		d3d_device_->SetRenderState( D3DRS_CULLMODE,			D3DCULL_NONE		);		// ポリゴンの裏表チェックをしない
		d3d_device_->SetRenderState( D3DRS_ALPHABLENDENABLE,	TRUE				);
		d3d_device_->SetRenderState( D3DRS_ALPHATESTENABLE,		TRUE				);
		d3d_device_->SetRenderState( D3DRS_ZWRITEENABLE,		FALSE				);
		d3d_device_->SetRenderState( D3DRS_ZENABLE,				D3DZB_TRUE			);		// Zバッファを有効にする。
		d3d_device_->SetRenderState( D3DRS_AMBIENT,				0xFFFFFFFF			);		// 環境光
		d3d_device_->SetRenderState( D3DRS_SRCBLEND,			D3DBLEND_SRCALPHA	);		// ソース側の色の比率
		d3d_device_->SetRenderState( D3DRS_DESTBLEND,			D3DBLEND_INVSRCALPHA);		// 書き込み側の色の比率
		d3d_device_->SetRenderState( D3DRS_SHADEMODE,			D3DSHADE_GOURAUD	);		// シェードモードを滑らかにする

		d3d_device_->LightEnable( kLightNumberMain, TRUE );	// ライトの有効化

		// テクスチャステージステートの設定
		d3d_device_->SetTextureStageState( 0 , D3DTSS_ALPHAOP,	D3DTOP_DISABLE );	//αチャネルは無効に
		d3d_device_->SetTextureStageState( 0 , D3DTSS_ALPHAARG1,	D3DTA_TEXTURE );

		// サンプラーステートの設定
		SetTextureSamplerState(D3DTEXF_LINEAR);
		break;

	case kRenderStateTest:
		d3d_device_->SetRenderState( D3DRS_CULLMODE,		D3DCULL_NONE					);
		d3d_device_->SetRenderState( D3DRS_AMBIENT,			D3DCOLOR_XRGB(0xff,0xff,0xff)	);
		d3d_device_->SetRenderState( D3DRS_COLORVERTEX,		TRUE							);
		d3d_device_->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE,	D3DMCS_COLOR1			);
		break;
	}
}

// サンプラーステートの設定用関数
void DXEngine::SetTextureSamplerState(D3DTEXTUREFILTERTYPE SMode)
{
	d3d_device_->SetSamplerState(0,D3DSAMP_MIPFILTER,SMode);
	d3d_device_->SetSamplerState(0,D3DSAMP_MAGFILTER,SMode);
	d3d_device_->SetSamplerState(0,D3DSAMP_MINFILTER,SMode);
}

// ライトの設定を行う
void DXEngine::SetLight(LightNumber LNum,D3DLIGHT9 LParam)
{
	D3DXVECTOR3	tmpVec	= LParam.Direction;
	D3DXVec3Normalize((D3DXVECTOR3*)&LParam.Direction,&tmpVec);
	d3d_device_->SetLight(LNum,&LParam);
}

// カメラの設定を行う
void DXEngine::SetCamera(CameraParam CParam)
{
	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView,&CParam.position,&CParam.look_position,&CParam.up_vector);
	D3DXMATRIXA16	matProj;
	float	tmpAspect = (float)d3d_present_params_.BackBufferWidth / (float)d3d_present_params_.BackBufferHeight;
	D3DXMatrixPerspectiveFovLH(&matProj,CParam.fov_y,tmpAspect,CParam.z_near,CParam.z_far);
	// ビューマトリクスの設定
	d3d_device_->SetTransform(D3DTS_VIEW,&matView);
	// 投影行列設定
	d3d_device_->SetTransform(D3DTS_PROJECTION,&matProj);
}

// モデルの位置を設定
void DXEngine::SetObjectMatrix(D3DXVECTOR3 Vec, DirectionYPR Dir,float Scale)
{
	D3DXMATRIX	ScaleMatrix;	// 拡縮用行列
	D3DXMATRIX	PosMatrix;		// 位置用行列
	D3DXMATRIX	RotMatrix;		// 回転用行列
	D3DXMATRIX	ResultMatrix;	// 結果の行列
	//単位行列を収める（念のため）
	D3DXMatrixIdentity(&ScaleMatrix);
	D3DXMatrixIdentity(&PosMatrix);
	D3DXMatrixIdentity(&RotMatrix);
	D3DXMatrixIdentity(&ResultMatrix);
	// 行列を設定
	D3DXMatrixScaling(&ScaleMatrix,Scale,Scale,Scale);
	D3DXMatrixTranslation(&PosMatrix,Vec.x,Vec.y,Vec.z);
	D3DXMatrixRotationYawPitchRoll(&RotMatrix,Dir.Yaw,Dir.Roll,Dir.Pitch);
	// 行列の合成
	ResultMatrix = ScaleMatrix * RotMatrix * PosMatrix;
	// 描画ディバイスへ適用
	d3d_device_->SetTransform(D3DTS_WORLD,&ResultMatrix);
}

// 指定した視点用のバックバッファをレンダリング対象に
void DXEngine::SetViewTarget(int view_id) {
	d3d_device_->SetRenderTarget(0, parallax_buffers_[view_id]);
}

// デフォルトのバックバッファをセット
void DXEngine::SetDefaultBuffer() {
	d3d_device_->SetRenderTarget(0,back_buffer_);
}

// バックバッファーのデバイスコンテキストを取得
HRESULT DXEngine::GetBufferDC( HDC* buffer_dc ) {
	return back_buffer_->GetDC( buffer_dc );
}

// バックバッファーのデバイスコンテキストを解放
HRESULT DXEngine::ReleaseBufferDC( HDC* buffer_dc ) {
	return back_buffer_->ReleaseDC( *buffer_dc );
}

// DirectInputの初期化
HRESULT DXEngine::InitDirectInput(HWND hWnd,HINSTANCE hInstance)
{
	HRESULT		hr = S_OK;			//ずっこけた時用の結果返し用
	// 最初に初期化しておく
	CleanUpDirectInput();

	// DirectInputオブジェクトの生成
	// 以下、ほとんど定型句
	if(FAILED(hr = DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(VOID**)&direct_input_,NULL)))
	{return(hr);}

	// キーボードのセットアップ
	if(FAILED(hr = SetupKeybord(hWnd))){return(hr);}
	if(FAILED(hr = SetupMouse(hWnd))){return(hr);}

	return(hr);
}

// DirectInput関係の変数の初期化
VOID DXEngine::CleanUpDirectInput(void)
{
	// DirectInputでキーボードが使用中だった場合、使用を終了する。
	if(din_keybord_){din_keybord_->Unacquire();}
	if(din_mouse_){din_mouse_->Unacquire();}
	// デバイスを開放する
	SAFE_RELEASE(din_keybord_);
	SAFE_RELEASE(din_mouse_);
	// DirectInputの解放
	SAFE_RELEASE(direct_input_);
}

// DirectInputでキーボードを使用可能にする
HRESULT DXEngine::SetupKeybord(HWND hWnd)
{
	HRESULT		hr;			//ずっこけた時用の結果返し用

	// システムキーボードディバイスを探して確保しておく。
	// キーボードが無い場合（展示用にキーボードをは外すなどしている）は注意が必要
	if(FAILED(hr = direct_input_->CreateDevice(GUID_SysKeyboard,&din_keybord_,NULL)))
	{return(hr);}

	if(din_keybord_ == NULL)
	{
		MessageBox(NULL,TEXT("キーボードを発見できませんでした。\n（そんなバカな？）"),kErrorMessage,MB_ICONERROR|MB_OK);
		return(S_OK);		//ここで帰ってしまう
	}

	// DirectInputから受け取るデータフォーマットをキーボードに設定する
	// c_dfDIKeyboardは、DirectInputが用意したグローバル変数
	// const設定されていて変数の値は変更できない
	if(FAILED(hr = din_keybord_->SetDataFormat(&c_dfDIKeyboard)))
	{return(hr);}

	// システムや、他のDirectInputを利用したアプリケーションと、どのように連携すればよいのか
	// DirectInputに通知するために、協調レベルをセットする。
	//（フォアグランド・直接入力・協調モード・Windowsキー無効に固定）
	if(FAILED(hr = din_keybord_->SetCooperativeLevel(hWnd,DISCL_NONEXCLUSIVE|DISCL_FOREGROUND|DISCL_NOWINKEY)))
	{return(hr);}

	// キーボードの入力を有効にする。
	din_keybord_->Acquire();

	return(S_OK);
}

// マウスをセットアップ
HRESULT DXEngine::SetupMouse(HWND hWnd)
{
	HRESULT		hr = S_OK;	//戻り値の設定

	// システムマウスデバイスを探して確保する。
	if(FAILED(hr = direct_input_->CreateDevice(GUID_SysMouse,&din_mouse_,NULL))){return(hr);}

	if(NULL == din_mouse_)
	{
		MessageBox(NULL,TEXT("マウスが見つかりませんでした（そんなバカな？）\n他のデバイスで操作をします"),kErrorMessage,MB_ICONERROR|MB_OK);
		return(hr);	//ここで帰ってしまう
	}

	// DirectInputから受け取るデータフォーマットをマウス（拡張仕様）に設定する
	// c_dfDIMouse2はDirectInputが用意したグローバル変数でconst設定されていて変数の値は変更できない。
	// この部分はJoystickの処理と同様。ただし複数のマウスがある事は考えられていない。
	if(FAILED(hr = din_mouse_->SetDataFormat(&c_dfDIMouse2)))
	{return(hr);}

	// 他のデバイスと同様に協調レベルをセットする。
	// ここではフォアグランド・排他的利用モードに固定
	// ゲームの操作のためにマウスを使う場合は、通常このモードでかまわない。
	// しかし、このモードでは、マウスカーソルが見えなくなるため、
	// アプリケーション側でマウスカーソルを独自に表示させるなど工夫が必要になるので要注意。
	if(FAILED(hr = din_mouse_->SetCooperativeLevel(hWnd,DISCL_EXCLUSIVE|DISCL_FOREGROUND)))
	{
		CleanUpDirectInput();
		if(hr == DIERR_UNSUPPORTED)
		{
			MessageBox(NULL,TEXT("DirectInputがサポートしていない協調レベルです。"),kErrorMessage,MB_ICONERROR|MB_OK);
		}
		return(hr);
	}

	// マウスの入力を有効にする。
	din_mouse_->Acquire();

	return(S_OK);
}

// 入力を受け取る
void DXEngine::GetInput()
{
	if(din_keybord_){GetKeybordInput();}
	if(din_mouse_){GetMouseInput();}
}

// キーボードの状態を格納
void DXEngine::GetKeybordInput()
{
	HRESULT	hr;
	// キーボードの状態初期化
	ZeroMemory(key_state_,sizeof(key_state_));
	// キーボードディバイスが無い場合は、滑らかに去る。
	if(NULL == din_keybord_){return;}
	// 状態を取得
	hr = din_keybord_->GetDeviceState(sizeof(key_state_),key_state_);
	if(FAILED(hr))
	{
		// もし入力が失われていた場合、確保し、維持を試みる。
		hr = din_keybord_->Acquire();
		while(hr == DIERR_INPUTLOST){hr = din_keybord_->Acquire();}
		// エラー時は帰る。
		if(FAILED(hr)){return;}
	}
}

// マウスの状態を格納
void DXEngine::GetMouseInput()
{
	HRESULT			hr;
	// マウスの状態初期化
	ZeroMemory(&mouse_state_,sizeof(DIMOUSESTATE2));
	// マウスが無い場合は、滑らかに去る。
	if(NULL == din_mouse_){return;}
	hr = din_mouse_->GetDeviceState(sizeof(DIMOUSESTATE2),&mouse_state_);
	if(FAILED(hr))
	{
		// もし入力が失われていた場合、再確保を試みる。
		hr = din_mouse_->Acquire();
		while(hr == DIERR_INPUTLOST){hr = din_mouse_->Acquire();}
		// エラー時は他のアプリケーションがフォアグランドになっていたりするので何もしないで帰る。
		if(FAILED(hr))
		{
			return;
		}
	}
}

// キーボードの状態を返す
BYTE* DXEngine::get_keybord_state()
{
	return key_state_;
}

// マウスの状態を返す
DIMOUSESTATE2 DXEngine::get_mouse_state()
{
	return mouse_state_;
}