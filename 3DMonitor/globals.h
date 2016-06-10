// Copyright 2011 MineStudio.
// グローバル変数を宣言していきます

#ifndef NPCA3DMONITOR__GLOBALS_H_
#define NPCA3DMONITOR__GLOBALS_H_

#include <Windows.h>

#include "win_engine.h"

#ifdef ___GLOBAL_DEFINE
#define EXTERN /* */
#define VAL(x) =(x)
#else
#define EXTERN extern
#define VAL(x) /* */
#endif

// EXTERN int*		sampleinteger;
// EXTERN char*		samplechar		VAL(1);

EXTERN	WinEngine*	win_engine		VAL(NULL);
EXTERN	long		frame_counter	VAL(0);

#endif