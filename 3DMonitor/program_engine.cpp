// Copyright 2011 MineStudio.
// ProgramEngineクラスを定義します。このクラスはプログラムの制御を行います。

#include "chead.h"

#include "program_engine.h"

#include "graphics_engine.h"

// コンストラクタ
ProgramEngine::ProgramEngine(DXEngine* tmp_dx, HRESULT* result)
{
	graphics_engine_	= NULL;
	dx_engine_ = tmp_dx;
	program_mode_	= kProgramModeMain;
	graphics_engine_	= new GraphicsEngine(dx_engine_, result);

//	GameMode = kG_MODE_GAME;
//	GameMainEngine = new GameEngine(kV_TYPE_AIR_F14,GameMainData,DEngine);
}

//デストラクタ
ProgramEngine::~ProgramEngine()
{
	SAFE_DELETE(graphics_engine_);
}

// ゲームの処理を行う
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