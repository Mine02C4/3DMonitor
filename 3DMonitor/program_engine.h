// Copyright 2011 MineStudio.
// ProgramEngineクラスを宣言します。プログラムの制御を司り、プログラムの進行役を担います。

#ifndef NPCA3DMONITOR__PROGRAMENGINE_H_
#define NPCA3DMONITOR__PROGRAMENGINE_H_

class GraphicsEngine;

class ProgramEngine
{
	ProgramMode			program_mode_;
	DXEngine*			dx_engine_;
	GraphicsEngine*		graphics_engine_;
public:
	ProgramEngine(DXEngine* ,HRESULT*);
	~ProgramEngine(void);
	HRESULT		ProcessProgram(void);
};

#endif