// Copyright 2011 MineStudio.
// DxEngine�N���X�̒�`���s���܂��B

#include "chead.h"

#include "dx_engine.h"

#include <stdio.h>

#include <windows.h>

#include "file_names.h"

// �R���X�g���N�^
DXEngine::DXEngine(HWND direct_window,BOOL boolFullScreen,WNDCLASSEX buffer_window_class,HRESULT* result,HINSTANCE hInstance, HWND main_window)
{
	swap_chain_			= NULL;
	d3d_device_			= NULL;
	render_target_view_	= NULL;
	direct_input_		= NULL;
	din_keybord_		= NULL;
	din_mouse_			= NULL;
	ZeroMemory(&mouse_state_,sizeof(DIMOUSESTATE2));
	ZeroMemory(key_state_,sizeof(key_state_));
	// �t���X�N���[���̐ݒ�
	full_screen_flag_	= boolFullScreen;

	// Direct3D�̏�����
	if(FAILED(InitDirect3D(direct_window)))
	{
		MessageBox( NULL, TEXT("DirectX�̏������Ɏ��s���܂����B"), kErrorMessage, MB_OK|MB_ICONHAND );
		*result = E_FAIL;
		return;
	}
	*result = S_OK;
}

// �f�X�g���N�^
DXEngine::~DXEngine()
{
	CleanUpDirectInput();
	CleanUpDirect3D();
}

// Direct3D�̏�����
HRESULT DXEngine::InitDirect3D(HWND hWnd)
{
//	effect_		= NULL;
//	technique_	= NULL;
/*	for(int i=0;i<kNumOfParallax;i++) {
		parallax_buffers_[i] = NULL;
	}*/

	// �ϐ�������
	ZeroMemory(&swap_desc_, sizeof(swap_desc_));
	swap_chain_		= NULL;
	def_technique_	= NULL;
	def_effect_		= NULL;

	// �X���b�v�`�F�[���̐ݒ�
	swap_desc_.BufferCount			= 1;
	swap_desc_.BufferDesc.Width		= kWindowWidth;
	swap_desc_.BufferDesc.Height	= kWindowHeight;
	swap_desc_.BufferDesc.Format	= DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_desc_.BufferDesc.RefreshRate.Numerator		= kSetFps;
	swap_desc_.BufferDesc.RefreshRate.Denominator	= 1;
	swap_desc_.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_desc_.OutputWindow			= hWnd;
	swap_desc_.SampleDesc.Count		= 1;
	swap_desc_.SampleDesc.Quality	= 0;
	swap_desc_.Windowed				= TRUE;
	
	if(FAILED(D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_REFERENCE, NULL, 0,
		D3D10_SDK_VERSION, &swap_desc_, &swap_chain_, &d3d_device_))) {
			return E_FAIL;
	}

	ID3D10Texture2D* back_buffer;
	if(FAILED(swap_chain_->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&back_buffer))) {
		return E_FAIL;
	}
	HRESULT hr = d3d_device_->CreateRenderTargetView(back_buffer, NULL, &render_target_view_);
	back_buffer->Release();
	if(FAILED(hr)) {
		return hr;
	}
	d3d_device_->OMSetRenderTargets(1, &render_target_view_, NULL);

	D3D10_VIEWPORT	view_port;
	view_port.Width		= kMonitorWidth;
	view_port.Height	= kMonitorHeight;
	view_port.MinDepth	= 0.0f;
	view_port.MaxDepth	= 1.0f;
	view_port.TopLeftX	= 0;
	view_port.TopLeftY	= 0;
	d3d_device_->RSSetViewports(1,&view_port);

	// Create the effect
    DWORD shader_flags = D3D10_SHADER_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
	shader_flags |= D3D10_SHADER_DEBUG;
#endif
	if(FAILED(D3DX10CreateEffectFromFile(kFileDefFX, NULL, NULL, "fx_4_0", shader_flags, 0,
											d3d_device_, NULL, NULL, &def_effect_, NULL, NULL)))
	{
		MessageBox( NULL, TEXT("The FX file cannot be located.  Please run this executable from the directory that contains the FX file."), kErrorMessage, MB_OK);
		return E_FAIL;
	}

	// Obtain the technique
	def_technique_ = def_effect_->GetTechniqueByName("Render");

	D3D10_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT num_elements = sizeof( layout ) / sizeof( layout[0] );

	D3D10_PASS_DESC pass_desc;
	def_technique_->GetPassByIndex(0)->GetDesc(&pass_desc);
	if(FAILED(d3d_device_->CreateInputLayout( layout, num_elements, pass_desc.pIAInputSignature,
											pass_desc.IAInputSignatureSize, &vertex_layout_ )))
		return E_FAIL;

	d3d_device_->IASetInputLayout( vertex_layout_ );

	// Create vertex buffer
	SimpleVertex vertices[] =
	{
		D3DXVECTOR3( 0.0f, 0.5f, 0.5f ),
		D3DXVECTOR3( 0.5f, -0.5f, 0.5f ),
		D3DXVECTOR3( -0.5f, -0.5f, 0.5f ),
	};
	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( SimpleVertex ) * 3;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if(FAILED(d3d_device_->CreateBuffer(&bd, &InitData, &vertex_buffer_)))
		return E_FAIL;

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	d3d_device_->IASetVertexBuffers( 0, 1, &vertex_buffer_, &stride, &offset );

	// Set primitive topology
	d3d_device_->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

/*	LPD3DXBUFFER err = NULL;
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

	// �o�b�N�o�b�t�@���擾
	d3d_device_->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &back_buffer_);
	// �e���_�p�̃o�b�t�@��p��
	for(int i=0;i<kNumOfParallax;i++) {
		d3d_device_->CreateTexture(kWidth3DPixel, kHeight3DPixel, 1,D3DUSAGE_DYNAMIC, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &parallax_textures_[i],NULL);
		parallax_textures_[i]->GetSurfaceLevel(0,&parallax_buffers_[i]);
		//d3d_device_->CreateRenderTarget(kWidth3DPixel, kHeight3DPixel, D3DFMT_X8R8G8B8, D3DMULTISAMPLE_NONE, 0, FALSE, &parallax_buffers_[i], NULL);
		char value_name[10];
		sprintf_s(value_name,"tex%d",i);
		texture_handle_[i] = effect_->GetParameterByName(NULL,(LPCSTR)value_name);
		//effect_->SetTexture(,parallax_textures_[i]);
	}*/

	return ( S_OK );
}

// D3D�̌�n��
VOID DXEngine::CleanUpDirect3D()
{
	// �T�[�t�F�C�X�̉��
/*	for(int i=0;i<kNumOfParallax;i++) {
		SAFE_RELEASE(parallax_buffers_[i]);
	}*/
	if(d3d_device_)
		d3d_device_->ClearState();

	// DirectX�f�B�o�C�X�Ȃǂ̉��	
	SAFE_RELEASE(render_target_view_);
	SAFE_RELEASE(swap_chain_);
	SAFE_RELEASE(d3d_device_);
}

// �t���X�N���[�����ǂ�����Ԃ�
BOOL DXEngine::CheckFullScreen()
{
	return full_screen_flag_;
}

// Direct3D�f�o�C�X��Ԃ��܂�
ID3D10Device* DXEngine::get_d3d_device()
{
	return d3d_device_;
}

// �����_�����O�̐ݒ�
//void DXEngine::SetRender(RenderState RState)
//{
//	switch(RState)
//	{
//	case kRenderStateNormal:
//		// �����_�����O�X�e�[�g�̐ݒ�
//		d3d_device_->SetRenderState( D3DRS_CULLMODE,			D3DCULL_NONE	);		// �|���S���̗��\�`�F�b�N�����Ȃ�
//		d3d_device_->SetRenderState( D3DRS_ALPHABLENDENABLE,	FALSE			);		// ���u�����f�B���O����
//		d3d_device_->SetRenderState( D3DRS_ALPHATESTENABLE,		FALSE			);		// ���e�X�g�𖳌���
//		d3d_device_->SetRenderState( D3DRS_ZWRITEENABLE,		TRUE			);		// Z�o�b�t�@�ւ̏������݋���
//		d3d_device_->SetRenderState( D3DRS_ZENABLE,				D3DZB_TRUE		);		// Z�o�b�t�@��L���ɂ���B
//		d3d_device_->SetRenderState( D3DRS_AMBIENT,				0x00888888		);		// ����
//		d3d_device_->SetRenderState( D3DRS_SRCBLEND,			D3DBLEND_ONE	);		// �\�[�X���̐F�̔䗦
//		d3d_device_->SetRenderState( D3DRS_DESTBLEND,			D3DBLEND_ZERO	);		// �������ݑ��̐F�̔䗦
//		d3d_device_->SetRenderState( D3DRS_SHADEMODE,			D3DSHADE_GOURAUD);		// �V�F�[�h���[�h�����炩�ɂ���
//
//		d3d_device_->LightEnable( kLightNumberMain, TRUE );	// ���C�g�̗L����
//
//		// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
//		d3d_device_->SetTextureStageState( 0 , D3DTSS_ALPHAOP,	D3DTOP_DISABLE );	//���`���l���͖�����
//
//
//		// �T���v���[�X�e�[�g�̐ݒ�
//		SetTextureSamplerState(D3DTEXF_LINEAR);
//		break;
//
//	case kRenderStateSq:
//		// �����_�����O�X�e�[�g�̐ݒ�
//		d3d_device_->SetRenderState( D3DRS_CULLMODE,			D3DCULL_NONE		);		// �|���S���̗��\�`�F�b�N�����Ȃ�
//		d3d_device_->SetRenderState( D3DRS_ALPHABLENDENABLE,	TRUE				);
//		d3d_device_->SetRenderState( D3DRS_ALPHATESTENABLE,		TRUE				);
//		d3d_device_->SetRenderState( D3DRS_ZWRITEENABLE,		FALSE				);
//		d3d_device_->SetRenderState( D3DRS_ZENABLE,				D3DZB_TRUE			);		// Z�o�b�t�@��L���ɂ���B
//		d3d_device_->SetRenderState( D3DRS_AMBIENT,				0xFFFFFFFF			);		// ����
//		d3d_device_->SetRenderState( D3DRS_SRCBLEND,			D3DBLEND_SRCALPHA	);		// �\�[�X���̐F�̔䗦
//		d3d_device_->SetRenderState( D3DRS_DESTBLEND,			D3DBLEND_INVSRCALPHA);		// �������ݑ��̐F�̔䗦
//		d3d_device_->SetRenderState( D3DRS_SHADEMODE,			D3DSHADE_GOURAUD	);		// �V�F�[�h���[�h�����炩�ɂ���
//
//		d3d_device_->LightEnable( kLightNumberMain, TRUE );	// ���C�g�̗L����
//
//		// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
//		d3d_device_->SetTextureStageState( 0 , D3DTSS_ALPHAOP,	D3DTOP_DISABLE );	//���`���l���͖�����
//		d3d_device_->SetTextureStageState( 0 , D3DTSS_ALPHAARG1,	D3DTA_TEXTURE );
//
//		// �T���v���[�X�e�[�g�̐ݒ�
//		SetTextureSamplerState(D3DTEXF_LINEAR);
//		break;
//
//	case kRenderStateTest:
//		d3d_device_->SetRenderState( D3DRS_CULLMODE,		D3DCULL_NONE					);
//		d3d_device_->SetRenderState( D3DRS_AMBIENT,			D3DCOLOR_XRGB(0xff,0xff,0xff)	);
//		d3d_device_->SetRenderState( D3DRS_COLORVERTEX,		TRUE							);
//		d3d_device_->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE,	D3DMCS_COLOR1			);
//		break;
//	}
//}
//
//// �T���v���[�X�e�[�g�̐ݒ�p�֐�
////void DXEngine::SetTextureSamplerState(D3DTEXTUREFILTERTYPE SMode)
////{
////	d3d_device_->SetSamplerState(0,D3DSAMP_MIPFILTER,SMode);
////	d3d_device_->SetSamplerState(0,D3DSAMP_MAGFILTER,SMode);
////	d3d_device_->SetSamplerState(0,D3DSAMP_MINFILTER,SMode);
////}
//
//// ���C�g�̐ݒ���s��
//void DXEngine::SetLight(LightNumber LNum,D3DLIGHT9 LParam)
//{
//	D3DXVECTOR3	tmpVec	= LParam.Direction;
//	D3DXVec3Normalize((D3DXVECTOR3*)&LParam.Direction,&tmpVec);
//	d3d_device_->SetLight(LNum,&LParam);
//}
//
//// �J�����̐ݒ���s��
//void DXEngine::SetCamera(CameraParam CParam)
//{
//	D3DXMATRIXA16	matView;
//	D3DXMatrixLookAtLH(&matView,&CParam.position,&CParam.look_position,&CParam.up_vector);
//	D3DXMATRIXA16	matProj;
//	float	tmpAspect = (float)d3d_present_params_.BackBufferWidth / (float)d3d_present_params_.BackBufferHeight;
//	D3DXMatrixPerspectiveFovLH(&matProj,CParam.fov_y,tmpAspect,CParam.z_near,CParam.z_far);
//	// �r���[�}�g���N�X�̐ݒ�
//	d3d_device_->SetTransform(D3DTS_VIEW,&matView);
//	// ���e�s��ݒ�
//	d3d_device_->SetTransform(D3DTS_PROJECTION,&matProj);
//}
//
//// ���f���̈ʒu��ݒ�
//void DXEngine::SetObjectMatrix(D3DXVECTOR3 Vec, DirectionYPR Dir,float Scale)
//{
//	D3DXMATRIX	ScaleMatrix;	// �g�k�p�s��
//	D3DXMATRIX	PosMatrix;		// �ʒu�p�s��
//	D3DXMATRIX	RotMatrix;		// ��]�p�s��
//	D3DXMATRIX	ResultMatrix;	// ���ʂ̍s��
//	//�P�ʍs������߂�i�O�̂��߁j
//	D3DXMatrixIdentity(&ScaleMatrix);
//	D3DXMatrixIdentity(&PosMatrix);
//	D3DXMatrixIdentity(&RotMatrix);
//	D3DXMatrixIdentity(&ResultMatrix);
//	// �s���ݒ�
//	D3DXMatrixScaling(&ScaleMatrix,Scale,Scale,Scale);
//	D3DXMatrixTranslation(&PosMatrix,Vec.x,Vec.y,Vec.z);
//	D3DXMatrixRotationYawPitchRoll(&RotMatrix,Dir.Yaw,Dir.Roll,Dir.Pitch);
//	// �s��̍���
//	ResultMatrix = ScaleMatrix * RotMatrix * PosMatrix;
//	// �`��f�B�o�C�X�֓K�p
//	d3d_device_->SetTransform(D3DTS_WORLD,&ResultMatrix);
//}

// �w�肵�����_�p�̃o�b�N�o�b�t�@�������_�����O�Ώۂ�
//void DXEngine::SetViewTarget(int view_id) {
//	d3d_device_->SetRenderTarget(0, parallax_buffers_[view_id]);
//}

// �f�t�H���g�̃o�b�N�o�b�t�@���Z�b�g
//void DXEngine::SetDefaultBuffer() {
//	d3d_device_->SetRenderTarget(0,back_buffer_);
//}

// �o�b�N�o�b�t�@�[�̃f�o�C�X�R���e�L�X�g���擾
//HRESULT DXEngine::GetBufferDC( HDC* buffer_dc ) {
//	return back_buffer_->GetDC( buffer_dc );
//}

// �o�b�N�o�b�t�@�[�̃f�o�C�X�R���e�L�X�g�����
//HRESULT DXEngine::ReleaseBufferDC( HDC* buffer_dc ) {
//	return back_buffer_->ReleaseDC( *buffer_dc );
//}

// ��ʂ��N���A
void DXEngine::ClearRenderTargetView(const float color[4]) {
	d3d_device_->ClearRenderTargetView(render_target_view_, color);
}

// DirectInput�̏�����
HRESULT DXEngine::InitDirectInput(HWND hWnd,HINSTANCE hInstance)
{
	HRESULT		hr = S_OK;			//�������������p�̌��ʕԂ��p
	// �ŏ��ɏ��������Ă���
	CleanUpDirectInput();

	// DirectInput�I�u�W�F�N�g�̐���
	// �ȉ��A�قƂ�ǒ�^��
	if(FAILED(hr = DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(VOID**)&direct_input_,NULL)))
	{return(hr);}

	// �L�[�{�[�h�̃Z�b�g�A�b�v
	if(FAILED(hr = SetupKeybord(hWnd))){return(hr);}
	if(FAILED(hr = SetupMouse(hWnd))){return(hr);}

	return(hr);
}

// DirectInput�֌W�̕ϐ��̏�����
VOID DXEngine::CleanUpDirectInput(void)
{
	// DirectInput�ŃL�[�{�[�h���g�p���������ꍇ�A�g�p���I������B
	if(din_keybord_){din_keybord_->Unacquire();}
	if(din_mouse_){din_mouse_->Unacquire();}
	// �f�o�C�X���J������
	SAFE_RELEASE(din_keybord_);
	SAFE_RELEASE(din_mouse_);
	// DirectInput�̉��
	SAFE_RELEASE(direct_input_);
}

// DirectInput�ŃL�[�{�[�h���g�p�\�ɂ���
HRESULT DXEngine::SetupKeybord(HWND hWnd)
{
	HRESULT		hr;			//�������������p�̌��ʕԂ��p

	// �V�X�e���L�[�{�[�h�f�B�o�C�X��T���Ċm�ۂ��Ă����B
	// �L�[�{�[�h�������ꍇ�i�W���p�ɃL�[�{�[�h���͊O���Ȃǂ��Ă���j�͒��ӂ��K�v
	if(FAILED(hr = direct_input_->CreateDevice(GUID_SysKeyboard,&din_keybord_,NULL)))
	{return(hr);}

	if(din_keybord_ == NULL)
	{
		MessageBox(NULL,TEXT("�L�[�{�[�h�𔭌��ł��܂���ł����B\n�i����ȃo�J�ȁH�j"),kErrorMessage,MB_ICONERROR|MB_OK);
		return(S_OK);		//�����ŋA���Ă��܂�
	}

	// DirectInput����󂯎��f�[�^�t�H�[�}�b�g���L�[�{�[�h�ɐݒ肷��
	// c_dfDIKeyboard�́ADirectInput���p�ӂ����O���[�o���ϐ�
	// const�ݒ肳��Ă��ĕϐ��̒l�͕ύX�ł��Ȃ�
	if(FAILED(hr = din_keybord_->SetDataFormat(&c_dfDIKeyboard)))
	{return(hr);}

	// �V�X�e����A����DirectInput�𗘗p�����A�v���P�[�V�����ƁA�ǂ̂悤�ɘA�g����΂悢�̂�
	// DirectInput�ɒʒm���邽�߂ɁA�������x�����Z�b�g����B
	//�i�t�H�A�O�����h�E���ړ��́E�������[�h�EWindows�L�[�����ɌŒ�j
	if(FAILED(hr = din_keybord_->SetCooperativeLevel(hWnd,DISCL_NONEXCLUSIVE|DISCL_FOREGROUND|DISCL_NOWINKEY)))
	{return(hr);}

	// �L�[�{�[�h�̓��͂�L���ɂ���B
	din_keybord_->Acquire();

	return(S_OK);
}

// �}�E�X���Z�b�g�A�b�v
HRESULT DXEngine::SetupMouse(HWND hWnd)
{
	HRESULT		hr = S_OK;	//�߂�l�̐ݒ�

	// �V�X�e���}�E�X�f�o�C�X��T���Ċm�ۂ���B
	if(FAILED(hr = direct_input_->CreateDevice(GUID_SysMouse,&din_mouse_,NULL))){return(hr);}

	if(NULL == din_mouse_)
	{
		MessageBox(NULL,TEXT("�}�E�X��������܂���ł����i����ȃo�J�ȁH�j\n���̃f�o�C�X�ő�������܂�"),kErrorMessage,MB_ICONERROR|MB_OK);
		return(hr);	//�����ŋA���Ă��܂�
	}

	// DirectInput����󂯎��f�[�^�t�H�[�}�b�g���}�E�X�i�g���d�l�j�ɐݒ肷��
	// c_dfDIMouse2��DirectInput���p�ӂ����O���[�o���ϐ���const�ݒ肳��Ă��ĕϐ��̒l�͕ύX�ł��Ȃ��B
	// ���̕�����Joystick�̏����Ɠ��l�B�����������̃}�E�X�����鎖�͍l�����Ă��Ȃ��B
	if(FAILED(hr = din_mouse_->SetDataFormat(&c_dfDIMouse2)))
	{return(hr);}

	// ���̃f�o�C�X�Ɠ��l�ɋ������x�����Z�b�g����B
	// �����ł̓t�H�A�O�����h�E�r���I���p���[�h�ɌŒ�
	// �Q�[���̑���̂��߂Ƀ}�E�X���g���ꍇ�́A�ʏ킱�̃��[�h�ł��܂�Ȃ��B
	// �������A���̃��[�h�ł́A�}�E�X�J�[�\���������Ȃ��Ȃ邽�߁A
	// �A�v���P�[�V�������Ń}�E�X�J�[�\����Ǝ��ɕ\��������ȂǍH�v���K�v�ɂȂ�̂ŗv���ӁB
	if(FAILED(hr = din_mouse_->SetCooperativeLevel(hWnd,DISCL_EXCLUSIVE|DISCL_FOREGROUND)))
	{
		CleanUpDirectInput();
		if(hr == DIERR_UNSUPPORTED)
		{
			MessageBox(NULL,TEXT("DirectInput���T�|�[�g���Ă��Ȃ��������x���ł��B"),kErrorMessage,MB_ICONERROR|MB_OK);
		}
		return(hr);
	}

	// �}�E�X�̓��͂�L���ɂ���B
	din_mouse_->Acquire();

	return(S_OK);
}

// ���͂��󂯎��
void DXEngine::GetInput()
{
	if(din_keybord_){GetKeybordInput();}
	if(din_mouse_){GetMouseInput();}
}

// �L�[�{�[�h�̏�Ԃ��i�[
void DXEngine::GetKeybordInput()
{
	HRESULT	hr;
	// �L�[�{�[�h�̏�ԏ�����
	ZeroMemory(key_state_,sizeof(key_state_));
	// �L�[�{�[�h�f�B�o�C�X�������ꍇ�́A���炩�ɋ���B
	if(NULL == din_keybord_){return;}
	// ��Ԃ��擾
	hr = din_keybord_->GetDeviceState(sizeof(key_state_),key_state_);
	if(FAILED(hr))
	{
		// �������͂������Ă����ꍇ�A�m�ۂ��A�ێ������݂�B
		hr = din_keybord_->Acquire();
		while(hr == DIERR_INPUTLOST){hr = din_keybord_->Acquire();}
		// �G���[���͋A��B
		if(FAILED(hr)){return;}
	}
}

// �}�E�X�̏�Ԃ��i�[
void DXEngine::GetMouseInput()
{
	HRESULT			hr;
	// �}�E�X�̏�ԏ�����
	ZeroMemory(&mouse_state_,sizeof(DIMOUSESTATE2));
	// �}�E�X�������ꍇ�́A���炩�ɋ���B
	if(NULL == din_mouse_){return;}
	hr = din_mouse_->GetDeviceState(sizeof(DIMOUSESTATE2),&mouse_state_);
	if(FAILED(hr))
	{
		// �������͂������Ă����ꍇ�A�Ċm�ۂ����݂�B
		hr = din_mouse_->Acquire();
		while(hr == DIERR_INPUTLOST){hr = din_mouse_->Acquire();}
		// �G���[���͑��̃A�v���P�[�V�������t�H�A�O�����h�ɂȂ��Ă����肷��̂ŉ������Ȃ��ŋA��B
		if(FAILED(hr))
		{
			return;
		}
	}
}

// �L�[�{�[�h�̏�Ԃ�Ԃ�
BYTE* DXEngine::get_keybord_state()
{
	return key_state_;
}

// �}�E�X�̏�Ԃ�Ԃ�
DIMOUSESTATE2 DXEngine::get_mouse_state()
{
	return mouse_state_;
}