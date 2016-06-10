// Copyright 2011 MineStudio.
// �G���g���|�C���g��WinMain���`���܂�

#include "common_head.h"

#include <Windows.h>

#include "DXUT.h"
#include "DXUTmisc.h"
#include "SDKmisc.h"
#include "SDKmesh.h"

#include "defines.h"
#include "call_backs.h"
#include "globals.h"
#include "d3d_engine.h"

INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int ) {
	d3d_engine = new D3DEngine();

	 // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // DXUT will create and use the best device (either D3D9 or D3D10) 
    // that is available on the system depending on which D3D callbacks are set below

    // Set DXUT callbacks
    DXUTSetCallbackD3D10DeviceAcceptable( IsD3D10DeviceAcceptable );
    DXUTSetCallbackD3D10DeviceCreated( OnD3D10CreateDevice );
    DXUTSetCallbackD3D10SwapChainResized( OnD3D10ResizedSwapChain );
    DXUTSetCallbackD3D10SwapChainReleasing( OnD3D10ReleasingSwapChain );
    DXUTSetCallbackD3D10DeviceDestroyed( OnD3D10DestroyDevice );
    DXUTSetCallbackD3D10FrameRender( OnD3D10FrameRender );

    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackKeyboard( OnKeyboard );
    DXUTSetCallbackFrameMove( OnFrameMove );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );

    DXUTInit(true, true, NULL); // DXUT��������(�ڂ�����MSDN)
    DXUTSetCursorSettings(true, true); // �J�[�\����\�����A�S��ʂ̎��ɂ́A�̈悩��͂ݏo�Ȃ��悤�ɂ��܂�
	DXUTCreateWindow(kWindowTitle);
    DXUTCreateDevice(true, kWindowWidth, kWindowHeight);
    DXUTMainLoop(); // DXUT�̃����_�����O���[�v���J�n

    return DXUTGetExitCode();
}