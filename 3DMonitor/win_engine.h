// Copyright 2011 MineStudio.
// ウィンドウハンドラの制御を中心にWindowsAPI関連の対応を行います

#ifndef NPCA3DMONITOR__WINENGINE_H_
#define NPCA3DMONITOR__WINENGINE_H_

#include <Windows.h>

class DXEngine;
class ProgramEngine;

class WinEngine
{
private:
	HANDLE			hMutex_;
	WNDCLASSEX		main_window_class_;
	WNDCLASSEX		buffer_window_class_;
	HWND			main_window_;
	HWND			buffer_window_;
	DXEngine*		dx_engine_;
	ProgramEngine*	program_engine_;
public:
	WinEngine(HINSTANCE, HRESULT*, int);
	~WinEngine(void);
	LRESULT		WINAPI MsgProc(HWND,UINT,WPARAM,LPARAM);
	HRESULT		MsgLoop(void);
	DXEngine*	GetDXEngine(void);
	void		RenderBuffer(HDC*);
	void		DebugRender();
};

//関数プロトタイプ
LRESULT	CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

#endif
