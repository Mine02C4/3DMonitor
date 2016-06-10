// Copyright 2011 MineStudio.
// �G���g���|�C���g��WinMain���`���܂�

#include "chead.h"

#include <Windows.h>
#include <tchar.h>

#include "win_engine.h"

int WINAPI _tWinMain(	HINSTANCE hInstance ,
					HINSTANCE hPrevInstance ,
					LPTSTR lpCmdLine ,
					int nCmdShow )
{
	HRESULT	result = NULL;
	win_engine = new WinEngine(hInstance, &result, nCmdShow);
	if(FAILED(result))
	{
		SAFE_DELETE(win_engine);
		return(E_FAIL);
	}
	
	// ���b�Z�[�W���[�v
	win_engine->MsgLoop();

	SAFE_DELETE(win_engine);

	return(S_OK);
}
