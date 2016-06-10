// Copyright 2011 MineStudio.
// �E�B���h�E�n���h���̐���𒆐S��WindowsAPI�̎g�p���s���܂��B

#include "chead.h"

#include "win_engine.h"

#include <stdio.h>
#include <tchar.h>

#include "dx_engine.h"
#include "program_engine.h"

// �R���X�g���N�^
WinEngine::WinEngine(HINSTANCE hInstance, HRESULT* result, int nCmdShow) {
	// ������
	dx_engine_		= NULL;
	program_engine_	= NULL;

	// ���d�N���̃`�F�b�N
	hMutex_ = CreateMutex(NULL, FALSE, kWindowTitle);
	DWORD theErr = GetLastError();
	//ShowCursor(false);
	if(theErr == ERROR_ALREADY_EXISTS)
	{
		// ���d�N�����Ă���
		if(hMutex_) CloseHandle(hMutex_);
		MessageBox(NULL,TEXT("���̃A�v���P�[�V�����͑��d�N���ł��܂���B"),kErrorMessage,MB_OK|MB_ICONHAND);
		*result	= E_FAIL;
		return;
	}

	// �E�B���h�E�N���X�̐ݒ�
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

	// �E�B���h�E�̍쐬
	//DWORD	main_window_style = (WS_VISIBLE | WS_POPUP);
	DWORD	main_window_style = ~(WS_MAXIMIZEBOX | WS_THICKFRAME) & WS_OVERLAPPEDWINDOW;

	main_window_ = CreateWindow( kWindowTitle, kWindowTitle, 
		main_window_style, 0, 0, kWindowWidth, kWindowHeight,
							NULL, NULL, main_window_class_.hInstance, NULL );

	MoveWindow(main_window_, GetSystemMetrics(SM_XVIRTUALSCREEN),
		GetSystemMetrics(SM_YVIRTUALSCREEN),
		GetSystemMetrics(SM_CXVIRTUALSCREEN),
		GetSystemMetrics(SM_CYVIRTUALSCREEN), TRUE);

	// �E�B���h�E�N���X�̐ݒ�
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
	//�ő剻�{�^���������Ȃ��E���E�ύX�̂ł��Ȃ�window
	DWORD	dwWindowStyle= ~(WS_MAXIMIZEBOX | WS_THICKFRAME) & WS_OVERLAPPEDWINDOW;

	// �E�B���h�E�̍쐬
	buffer_window_ = CreateWindow( kBufferTitle, kBufferTitle, 
							dwWindowStyle, CW_USEDEFAULT, CW_USEDEFAULT, 1, 1,
							NULL, NULL, buffer_window_class_.hInstance, NULL );

	dx_engine_ = new DXEngine(main_window_ ,TRUE ,buffer_window_class_ ,result ,hInstance, main_window_);
	if(FAILED(*result))
	{
		return;
	}
	program_engine_ = new ProgramEngine(dx_engine_ ,result);
	if(FAILED(*result))
	{
		return;
	}

	// �E�B���h�E�̕\��
	ShowWindow(main_window_ , nCmdShow);
	UpdateWindow(main_window_);

	// �^�C�}���Z�b�g����B
	SetTimer(main_window_ ,kTimerId ,kTimerLap ,NULL);

	*result = S_OK;
}

// �f�X�g���N�^
WinEngine::~WinEngine()
{
	SAFE_DELETE(program_engine_);
	SAFE_DELETE(dx_engine_);
	UnregisterClass(kWindowTitle,main_window_class_.hInstance);	//�E�B���h�E�̔j��
	UnregisterClass(kWindowTitle,buffer_window_class_.hInstance);
	if(hMutex_){CloseHandle(hMutex_);}
}

// �A�v���P�[�V�����E�B���h�E�̃��b�Z�[�W�n���h��
LRESULT WINAPI WinEngine::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static BOOL sWinActivFlag = FALSE;
	static BOOL sMsgBoxFlag = FALSE;

	switch(msg)
	{
		//esc�L�[���������Ƃ��̎�������
        case WM_KEYUP: 
			if(VK_ESCAPE == (int)wParam)
			{
				// �t���X�N���[�����[�h�̏ꍇ�͂����Ȃ�I���
				//if(dx_engine_->CheckFullScreen()) {
					PostQuitMessage( 0 ); return (0);
				//}
				//else {
					sMsgBoxFlag = TRUE;
					//�m�F�_�C�A���O���o�Ă���ꍇ�͏����𒆒f����
					if( MessageBoxEx(	hWnd, TEXT("���f���܂����H"), kWindowTitle,
										MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2 ,LANG_JAPANESE) == IDYES )
					{ PostQuitMessage( 0 ); return (0); }
					sMsgBoxFlag = FALSE;
				//}
			} 
		break; 

		case WM_DESTROY:
			PostQuitMessage( 0 );// �E�B���h�E�j�����̎�������
			return (0);
		break;

		case WM_ACTIVATE:		// �E�B���h�E���ĂуA�N�e�B�u�ɂȂ�܂���
			if( WA_INACTIVE != wParam)
			{
				// �E�B���h�E�A�N�e�B�u�t���O��true��
				sWinActivFlag = TRUE;
			}
			else if( wParam == WA_INACTIVE )
			{
				// �����E�B���h�E���w��ɂ܂�����珈���𒆒f
				sWinActivFlag = FALSE;
			}
		break;

		case WM_TIMER:					//�^�C�}���荞��
			//if( !sMsgBoxFlag && sWinActivFlag )
			if( !sMsgBoxFlag  )
			{
				// �E�B���h�E���A�N�e�B�u�ȏꍇ�����A�Q�[���{�̂̏������s���B
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

// ���b�Z�[�W���[�v
HRESULT WinEngine::MsgLoop()
{
	// ���b�Z�[�W���[�v
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	while( msg.message != WM_QUIT ) {
		// �C�x���g�̎擾
		// PM_NOREMOVE�Ƃ���̂́AWindow9x/Me�nOS��
		// �v���Z�X���]���r������̂�h�����߁B
		if( PeekMessage (&msg,NULL,0,0,PM_NOREMOVE) ) {
			// �����ŃC�x���g���擾����B
			if( !GetMessage (&msg,NULL,0,0) ){ msg.message = WM_QUIT; }	// �I��
			else {
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		} else {
			Sleep(kSleep);	//CPU HUG�����̂��߁B
		}
	}

	return( S_OK );
}

// DirectX�G���W����Ԃ��܂�
DXEngine* WinEngine::GetDXEngine()
{
	return dx_engine_;
}

// DirectX�̃o�b�N�o�b�t�@�[��HDC�o�R�ŉ�ʂɃ����_�����O
void WinEngine::RenderBuffer(HDC* buffer_dc ) {
	HDC hdc = GetDC(main_window_);
	BitBlt( hdc, 0, 0, kWindowWidth, kWindowHeight, *buffer_dc, 0, 0, SRCCOPY );
	TCHAR count_text[40];
	_stprintf_s(count_text, 40, TEXT("COUNT%ld"), frame_counter);
	TextOut(hdc, 100, 100, count_text, lstrlen(count_text));
	ReleaseDC(main_window_, hdc);
}

// �f�o�b�O�p�����_�����O
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
