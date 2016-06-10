// Copyright 2011 MineStudio.
// �A�v���P�[�V�����Ŏg�p����^����(typedef)�����Ă����܂�

#ifndef NPCA3DMONITOR__TYPEDEFS_H_
#define NPCA3DMONITOR__TYPEDEFS_H_

#include <d3dx10.h>

// ------
// �񋓌^
// ------

// �v���O�������[�h���`
enum ProgramMode {
	kProgramModeStaring,	// �N����
	kProgramModeMain,		// ���C��
	kProgramModeDebug
};

// ------
// �\����
// ------

// �J�����̏��i�[
struct CameraParam {
	D3DXVECTOR3	position;
	D3DXVECTOR3	look_position;
	D3DXVECTOR3	up_vector;
	float		fov_y;		// Y�������ւ̎���p
	float		z_near;		// �ŒZ����
	float		z_far;		// �Œ�����
	CameraParam(){};
	CameraParam(float c_fov,float c_z_near,float c_z_far,D3DXVECTOR3 c_position) {
		fov_y			= c_fov;
		z_near			= c_z_near;
		z_far			= c_z_far;
		position		= c_position;
		look_position	= D3DXVECTOR3(0.0f,0.0f,0.0f);
		up_vector		= D3DXVECTOR3(0.0f,1.0f,0.0f);
	};
	CameraParam(float c_fov,float c_z_near,float c_z_far,D3DXVECTOR3 c_position,D3DXVECTOR3 c_look_position) {
		fov_y			= c_fov;
		z_near			= c_z_near;
		z_far			= c_z_far;
		position		= c_position;
		look_position	= c_look_position;
		up_vector		= D3DXVECTOR3(0.0f,1.0f,0.0f);
	};
	CameraParam(float c_fov,float c_z_near,float c_z_far,D3DXVECTOR3 c_position,D3DXVECTOR3 c_look_position,D3DXVECTOR3 c_up_vector) {
		fov_y			= c_fov;
		z_near			= c_z_near;
		z_far			= c_z_far;
		position		= c_position;
		look_position	= c_look_position;
		up_vector		= c_up_vector;
	};
};

#endif