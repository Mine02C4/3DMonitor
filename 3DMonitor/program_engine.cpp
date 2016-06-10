// Copyright 2011 MineStudio.
// ProgramEngine�N���X���`���܂��B���̃N���X�̓v���O�����̐�����s���܂��B

#include "chead.h"

#include "program_engine.h"

#include "graphics_engine.h"

// �R���X�g���N�^
ProgramEngine::ProgramEngine(DXEngine* tmp_dx, HRESULT* result)
{
	graphics_engine_	= NULL;
	dx_engine_ = tmp_dx;
	program_mode_	= kProgramModeMain;
	graphics_engine_	= new GraphicsEngine(dx_engine_, result);

//	GameMode = kG_MODE_GAME;
//	GameMainEngine = new GameEngine(kV_TYPE_AIR_F14,GameMainData,DEngine);
}

//�f�X�g���N�^
ProgramEngine::~ProgramEngine()
{
	SAFE_DELETE(graphics_engine_);
}

// �Q�[���̏������s��
HRESULT ProgramEngine::ProcessProgram()
{
	switch (program_mode_) {
	case kProgramModeMain:
		graphics_engine_->ProcessGraphics();
		break;
	case kProgramModeDebug:
		frame_counter++;
		win_engine->DebugRender();
		break;
	}
	return(S_OK);
}