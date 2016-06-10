// Copyright 2011 MineStudio.
// ウィンドウハンドラの制御を中心にWindowsAPIの使用を行います。

#include "chead.h"

#include "win_engine.h"

#include <stdio.h>
#include <tchar.h>

#include "dx_engine.h"
#include "program_engine.h"

// コンストラクタ
WinEngine::WinEngine(HINSTANCE hInstance, HRESULT* result, int nCmdShow) {
	// 多重起動のチェック
	hMutex_ = CreateMutex(NULL, FALSE, kWindowTitle);
	DWORD theErr = GetLastError();
	//ShowCursor(false);
	if(theErr == ERROR_ALREADY_EXISTS)
	{
		// 多重起動している
		if(hMutex_) CloseHandle(hMutex_);
		MessageBox(NULL,TEXT("このアプリケーションは多重起動できません。"),kErrorMessage,MB_OK|MB_ICONHAND);
		*result	= E_FAIL;
		return;
	}

	// ウィンドウクラスの設定
	main_window_class_.cbSize			= sizeof(WNDCLASSEX);
	main_window_class_.style			= CS_CLASSDC;
	main_window_class_.lpfnWndProc		= WndProc;
	main_window_class_.cbClsExtra		= 0L;
	main_window_class_.cbWndExtra		= 0L;
	main_window_class_.hInstance		= GetModuleHandle(NULL);
	main_window_class_.hIcon			= NULL;
	main_window_class_.hCursor			= NULL;
	main_window_class_.hbrBackground	= NULL;
	main_window_class_.lpszMenuName		= NULL;
	main_window_class_.lpszClassName	= kWindowTitle;
	main_window_class_.hIconSm			= NULL;
	if(!RegisterClassEx(&main_window_class_))
	{
		*result = E_FAIL;
		return;
	}

	// ウィンドウの作成
	//DWORD	main_window_style = (WS_VISIBLE | WS_POPUP);
	DWORD	main_window_style = ~(WS_MAXIMIZEBOX | WS_THICKFRAME) & WS_OVERLAPPEDWINDOW;

	main_window_ = CreateWindow( kWindowTitle, kWindowTitle, 
		main_window_style, 0, 0, kWindowWidth, kWindowHeight,
							NULL, NULL, main_window_class_.hInstance, NULL );

	MoveWindow(main_window_, GetSystemMetrics(SM_XVIRTUALSCREEN),
		GetSystemMetrics(SM_YVIRTUALSCREEN),
		GetSystemMetrics(SM_CXVIRTUALSCREEN),
		GetSystemMetrics(SM_CYVIRTUALSCREEN), TRUE);

	// ウィンドウクラスの設定
	buffer_window_class_.cbSize			= sizeof(WNDCLASSEX);
	buffer_window_class_.style			= CS_CLASSDC;
	buffer_window_class_.lpfnWndProc	= NULL;
	buffer_window_class_.cbClsExtra		= 0L;
	buffer_window_class_.cbWndExtra		= 0L;
	buffer_window_class_.hInstance		= GetModuleHandle(NULL);
	buffer_window_class_.hIcon			= NULL;
	buffer_window_class_.hCursor		= NULL;
	buffer_window_class_.hbrBackground	= NULL;
	buffer_window_class_.lpszMenuName	= NULL;
	buffer_window_class_.lpszClassName	= kBufferTitle;
	buffer_window_class_.hIconSm		= NULL;
	if(!RegisterClassEx(&buffer_window_class_))
	{
		*result = E_FAIL;
		return;
	}
	//最大化ボタンを持たない・境界変更のできないwindow
	DWORD	dwWindowStyle= ~(WS_MAXIMIZEBOX | WS_THICKFRAME) & WS_OVERLAPPEDWINDOW;

	// ウィンドウの作成
	buffer_window_ = CreateWindow( kBufferTitle, kBufferTitle, 
							dwWindowStyle, CW_USEDEFAULT, CW_USEDEFAULT, 1, 1,
							NULL, NULL, buffer_window_class_.hInstance, NULL );

	dx_engine_ = new DXEngine(buffer_window_ ,TRUE ,buffer_window_class_ ,result ,hInstance, main_window_);
	if(FAILED(*result))
	{
		return;
	}
	program_engine_ = new ProgramEngine(dx_engine_ ,result);
	if(FAILED(*result))
	{
		return;
	}

	// ウィンドウの表示
	ShowWindow(main_window_ , nCmdShow);
	UpdateWindow(main_window_);

	// タイマをセットする。
	SetTimer(main_window_ ,kTimerId ,kTimerLap ,NULL);

	*result = S_OK;
}

// デストラクタ
WinEngine::~WinEngine()
{
	SAFE_DELETE(program_engine_);
	SAFE_DELETE(dx_engine_);
	UnregisterClass(kWindowTitle,main_window_class_.hInstance);	//ウィンドウの破棄
	UnregisterClass(kWindowTitle,buffer_window_class_.hInstance);
	if(hMutex_){CloseHandle(hMutex_);}
}

// アプリケーションウィンドウのメッセージハンドラ
LRESULT WINAPI WinEngine::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static BOOL sWinActivFlag = FALSE;
	static BOOL sMsgBoxFlag = FALSE;

	switch(msg)
	{
		//escキーを押したときの自沈処理
        case WM_KEYUP: 
			if(VK_ESCAPE == (int)wParam)
			{
				// フルスクリーンモードの場合はいきなり終わる
				//if(dx_engine_->CheckFullScreen()) {
					PostQuitMessage( 0 ); return (0);
				//}
				//else {
					sMsgBoxFlag = TRUE;
					//確認ダイアログが出ている場合は処理を中断する
					if( MessageBoxEx(	hWnd, TEXT("中断しますか？"), kWindowTitle,
										MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2 ,LANG_JAPANESE) == IDYES )
					{ PostQuitMessage( 0 ); return (0); }
					sMsgBoxFlag = FALSE;
				//}
			} 
		break; 

		case WM_DESTROY:
			PostQuitMessage( 0 );// ウィンドウ破棄時の自沈処理
			return (0);
		break;

		case WM_ACTIVATE:		// ウィンドウが再びアクティブになりました
			if( WA_INACTIVE != wParam)
			{
				// ウィンドウアクティブフラグをtrueに
				sWinActivFlag = TRUE;
			}
			else if( wParam == WA_INACTIVE )
			{
				// もしウィンドウが背後にまわったら処理を中断
				sWinActivFlag = FALSE;
			}
		break;

		case WM_TIMER:					//タイマ割り込み
			//if( !sMsgBoxFlag && sWinActivFlag )
			if( !sMsgBoxFlag  )
			{
				// ウィンドウがアクティブな場合だけ、ゲーム本体の処理を行う。
				if(FAILED(program_engine_->ProcessProgram()))
				{
					PostQuitMessage(0);
					return(0);
				}
			}
		break;

		default:
		break;
	}

	return(DefWindowProc(hWnd,msg,wParam,lParam));
}

// メッセージループ
HRESULT WinEngine::MsgLoop()
{
	// メッセージループ
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	while( msg.message != WM_QUIT ) {
		// イベントの取得
		// PM_NOREMOVEとするのは、Window9x/Me系OSで
		// プロセスがゾンビ化するのを防ぐため。
		if( PeekMessage (&msg,NULL,0,0,PM_NOREMOVE) ) {
			// ここでイベントを取得する。
			if( !GetMessage (&msg,NULL,0,0) ){ msg.message = WM_QUIT; }	// 終了
			else {
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		} else {
			Sleep(kSleep);	//CPU HUG解消のため。
		}
	}

	return( S_OK );
}

// DirectXエンジンを返します
DXEngine* WinEngine::GetDXEngine()
{
	return dx_engine_;
}

// DirectXのバックバッファーをHDC経由で画面にレンダリング
void WinEngine::RenderBuffer(HDC* buffer_dc ) {
	HDC hdc = GetDC(main_window_);
	BitBlt( hdc, 0, 0, kWindowWidth, kWindowHeight, *buffer_dc, 0, 0, SRCCOPY );
	TCHAR count_text[40];
	_stprintf_s(count_text, 40, TEXT("COUNT%ld"), frame_counter);
	TextOut(hdc, 100, 100, count_text, lstrlen(count_text));
	ReleaseDC(main_window_, hdc);
}

// デバッグ用レンダリング
void WinEngine::DebugRender() {
	PAINTSTRUCT paint_struct;
	HDC hdc = BeginPaint( main_window_, &paint_struct );
	TCHAR count_text[40];
	_stprintf_s(count_text, 40, TEXT("COUNT%ld"), frame_counter);
	TextOut(hdc, 100, 100, count_text, lstrlen(count_text));
	EndPaint( main_window_, &paint_struct );
}

LRESULT	CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return win_engine->MsgProc(hwnd, uMsg, wParam, lParam);
}
