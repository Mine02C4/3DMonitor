// Copyright 2011 MineStudio.
// アプリケーションで使用する型命名(typedef)をしていきます

#ifndef NPCA3DMONITOR__TYPEDEFS_H_
#define NPCA3DMONITOR__TYPEDEFS_H_

#include <d3dx10.h>

// ------
// 列挙型
// ------

// プログラムモードを定義
enum ProgramMode {
	kProgramModeStaring,	// 起動中
	kProgramModeMain,		// メイン
	kProgramModeDebug
};

// ------
// 構造体
// ------

// カメラの情報格納
struct CameraParam {
	D3DXVECTOR3	position;
	D3DXVECTOR3	look_position;
	D3DXVECTOR3	up_vector;
	float		fov_y;		// Y軸方向への視野角
	float		z_near;		// 最短距離
	float		z_far;		// 最長距離
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