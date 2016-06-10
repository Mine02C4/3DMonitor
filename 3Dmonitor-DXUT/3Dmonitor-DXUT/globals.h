// Copyright 2011 MineStudio.
// ƒOƒ[ƒoƒ‹•Ï”‚ğéŒ¾‚µ‚Ä‚¢‚«‚Ü‚·

#ifndef NPCA3DMONITOR__GLOBALS_H_
#define NPCA3DMONITOR__GLOBALS_H_

#include <Windows.h>

class D3DEngine;

#ifdef ___GLOBAL_DEFINE
#define EXTERN /* */
#define VAL(x) =(x)
#else
#define EXTERN extern
#define VAL(x) /* */
#endif

// EXTERN int*		sampleinteger;
// EXTERN char*		samplechar		VAL(1);

EXTERN	D3DEngine*	d3d_engine		VAL(NULL);
//EXTERN	long		frame_counter	VAL(0);

#endif