// Copyright 2011 MineStudio.
// ProgramEngine�N���X��錾���܂��B�v���O�����̐�����i��A�v���O�����̐i�s����S���܂��B

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