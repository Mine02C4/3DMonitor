// Copyright 2011 MineStudio.
// DXEngine�N���X��錾���܂��B���̃N���X��DirectX�̒��S�����i�镔�i���W�߂����ł��B

#ifndef NPCA3DMONITOR__DXENGINE_H_
#define NPCA3DMONITOR__DXENGINE_H_

#include <Windows.h>
#include <d3dx10.h>
#include <dinput.h>

#include "typedefs.h"
#include "appdefs.h"

// DirectInput�o�[�W�����w��
#define kDirectInputVersion 0x0800

// Direct3D �t���L�V�u�����_�t�H�[�}�b�g�ɂ�钸�_�錾
#define kDirect3DFVFCustomVertex1	(D3DFVF_XYZ|D3DFVF_DIFFUSE)

// �����_�����O�X�e�[�g�̐ݒ�
enum RenderState {
	kRenderStateNormal,	// �ʏ�̃����_�����O���@
	kRenderStateSq,
	kRenderStateTest
};

// ���C�g�̃��X�g
enum LightNumber {
	kLightNumberMain,		// ���C���̃��C�g
	kLightNumberEnd
};

// FVF�̍\����
struct CustomVertex1 {
	D3DXVECTOR3	position;
	D3DCOLOR	color;
};

// DX10
struct SimpleVertex
{
    D3DXVECTOR3 Pos;
};

// 3D�I�u�W�F�N�g�̌������i�[
struct DirectionYPR {
	float	Yaw;
	float	Pitch;
	float	Roll;
	DirectionYPR() {
		Yaw		= 0.0f;
		Pitch	= 0.0f;
		Roll	= 0.0f;
	};
	DirectionYPR(float tYaw,float tPitch,float tRoll) {
		Yaw		= tYaw;
		Pitch	= tPitch;
		Roll	= tRoll;
	};
};

class DXEngine
{
	// Direct3D
	BOOL					full_screen_flag_;	// �t���X�N���[���t���O�B�������TRUE�Ńt���X�N���[���AFALSE�ŃE�B���h�E���[�h
	/*LPDIRECT3D9			d3d_;				// D3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		d3d_device_;		// D3D�f�o�C�X
	D3DPRESENT_PARAMETERS	d3d_present_params_;// �v���[���e�[�V�����p�����[�^�̊i�[
	LPDIRECT3DSURFACE9		back_buffer_;		//�o�b�N�o�b�t�@�i�[�p
	LPDIRECT3DTEXTURE9		parallax_textures_[kNumOfParallax];
	LPDIRECT3DSURFACE9		parallax_buffers_[kNumOfParallax];	// �e���_�p�̃o�b�t�@���i�[*/

	// Direct 3D 10
	DXGI_SWAP_CHAIN_DESC	swap_desc_;
	IDXGISwapChain*			swap_chain_;
	ID3D10Device*			d3d_device_;
	ID3D10RenderTargetView*	render_target_view_;
	ID3D10Effect*			def_effect_;
	ID3D10EffectTechnique*	def_technique_;
	ID3D10InputLayout*		vertex_layout_;
	ID3D10Buffer*			vertex_buffer_;

	//LPD3DXEFFECT			effect_;
	//D3DXHANDLE				technique_;
	//D3DXHANDLE				texture_handle_[kNumOfParallax];
	// DirectInput
	LPDIRECTINPUT8			direct_input_;		// DirectInput�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8	din_keybord_;		// �L�[�{�[�h
	LPDIRECTINPUTDEVICE8	din_mouse_;			// �}�E�X
	BYTE					key_state_[256];	// �L�[�{�[�g�̏�Ԋi�[
	DIMOUSESTATE2			mouse_state_;		// �}�E�X�̏��

	HRESULT		InitDirect3D(HWND);
	VOID		CleanUpDirect3D(void);
	//void		SetTextureSamplerState(D3DTEXTUREFILTERTYPE);
	HRESULT		InitDirectInput(HWND ,HINSTANCE);
	VOID		CleanUpDirectInput(void);
	HRESULT		SetupKeybord(HWND);
	HRESULT		SetupMouse(HWND);
	void		GetKeybordInput(void);
	void		GetMouseInput(void);
public:
	DXEngine(HWND ,BOOL ,WNDCLASSEX ,HRESULT* ,HINSTANCE, HWND);
	~DXEngine(void);
	// Direct3D
	BOOL				CheckFullScreen(void);
	ID3D10Device*		get_d3d_device(void);
	/*void				SetRender(RenderState);
	void				SetLight(LightNumber ,D3DLIGHT9);
	void				SetCamera(CameraParam);
	void				SetObjectMatrix(D3DXVECTOR3 ,DirectionYPR ,float);
	void				SetViewTarget(int);
	void				SetDefaultBuffer();
	HRESULT				GetBufferDC( HDC* );
	HRESULT				ReleaseBufferDC( HDC* );*/
	void				ClearRenderTargetView(const float[4]);
	// DirectInput
	void				GetInput(void);
	BYTE*				get_keybord_state(void);
	DIMOUSESTATE2		get_mouse_state(void);
};

#endif