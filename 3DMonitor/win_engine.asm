﻿; Listing generated by Microsoft (R) Optimizing Compiler Version 16.00.30319.01 

	TITLE	C:\Users\naoya\Documents\Visual Studio 2010\npca.jp\3Dモニター制作\3DMonitor-分岐\3DMonitor\win_engine.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRTD
INCLUDELIB OLDNAMES

_BSS	SEGMENT
?sWinActivFlag@?1??MsgProc@WinEngine@@QAGJPAUHWND__@@IIJ@Z@4HA DD 01H DUP (?) ; `WinEngine::MsgProc'::`2'::sWinActivFlag
?sMsgBoxFlag@?1??MsgProc@WinEngine@@QAGJPAUHWND__@@IIJ@Z@4HA DD 01H DUP (?) ; `WinEngine::MsgProc'::`2'::sMsgBoxFlag
_BSS	ENDS
PUBLIC	??_C@_1BO@CDGEGDPF@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAB?$AAu?$AAf?$AAf?$AAe?$AAr?$AA?$AA@ ; `string'
PUBLIC	?WndProc@@YGJPAUHWND__@@IIJ@Z			; WndProc
PUBLIC	??_C@_1CM@LKBDIPHI@0S0n0?$KC0?W0?j0?$LB0?$PM0?$LH0?g0?s0oY?$BK?$JB?M?$INwR?U0g0M0?$HO0?$FL0?$JD0?$AC?$AA?$AA@ ; `string'
PUBLIC	??_C@_1DI@FKECHAAB@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAM?$AAo?$AAn?$AAi?$AAt?$AAo?$AAr?$AA?5?$AAP?$AAr?$AAo?$AAj?$AAe?$AAc?$AAt?$AA?50?$KI0?i0?$PM?$AA?$AA@ ; `string'
PUBLIC	??_C@_1DA@GMIFNOFA@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAM?$AAo?$AAn?$AAi?$AAt?$AAo?$AAr?$AA?5?$AAP?$AAr?$AAo?$AAj?$AAe?$AAc?$AAt?$AA?$AA@ ; `string'
PUBLIC	??0WinEngine@@QAE@PAUHINSTANCE__@@PAJH@Z	; WinEngine::WinEngine
EXTRN	__imp__SetTimer@16:PROC
EXTRN	__imp__UpdateWindow@4:PROC
EXTRN	__imp__ShowWindow@8:PROC
EXTRN	??0ProgramEngine@@QAE@PAVDXEngine@@PAJ@Z:PROC	; ProgramEngine::ProgramEngine
EXTRN	??0DXEngine@@QAE@PAUHWND__@@HUtagWNDCLASSEXW@@PAJPAUHINSTANCE__@@0@Z:PROC ; DXEngine::DXEngine
EXTRN	??2@YAPAXI@Z:PROC				; operator new
EXTRN	__imp__MoveWindow@24:PROC
EXTRN	__imp__GetSystemMetrics@4:PROC
EXTRN	__imp__CreateWindowExW@48:PROC
EXTRN	__imp__RegisterClassExW@4:PROC
EXTRN	__imp__GetModuleHandleW@4:PROC
EXTRN	__imp__MessageBoxW@16:PROC
EXTRN	__imp__CloseHandle@4:PROC
EXTRN	__imp__GetLastError@0:PROC
EXTRN	__imp__CreateMutexW@12:PROC
EXTRN	__RTC_CheckEsp:PROC
EXTRN	__RTC_Shutdown:PROC
EXTRN	__RTC_InitBase:PROC
;	COMDAT ??_C@_1BO@CDGEGDPF@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAB?$AAu?$AAf?$AAf?$AAe?$AAr?$AA?$AA@
; File c:\users\naoya\documents\visual studio 2010\npca.jp\3dモニター制作\3dmonitor-分岐\3dmonitor\win_engine.cpp
CONST	SEGMENT
??_C@_1BO@CDGEGDPF@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAB?$AAu?$AAf?$AAf?$AAe?$AAr?$AA?$AA@ DB 'n'
	DB	00H, 'p', 00H, 'c', 00H, 'a', 00H, ' ', 00H, '3', 00H, 'D', 00H
	DB	' ', 00H, 'B', 00H, 'u', 00H, 'f', 00H, 'f', 00H, 'e', 00H, 'r'
	DB	00H, 00H, 00H				; `string'
CONST	ENDS
;	COMDAT ??_C@_1CM@LKBDIPHI@0S0n0?$KC0?W0?j0?$LB0?$PM0?$LH0?g0?s0oY?$BK?$JB?M?$INwR?U0g0M0?$HO0?$FL0?$JD0?$AC?$AA?$AA@
CONST	SEGMENT
??_C@_1CM@LKBDIPHI@0S0n0?$KC0?W0?j0?$LB0?$PM0?$LH0?g0?s0oY?$BK?$JB?M?$INwR?U0g0M0?$HO0?$FL0?$JD0?$AC?$AA?$AA@ DB 'S'
	DB	'0n0', 0a2H, '0', 0d7H, '0', 0eaH, '0', 0b1H, '0', 0fcH, '0', 0b7H
	DB	'0', 0e7H, '0', 0f3H, '0o0', 01aH, 'Y', 0cdH, 091H, 'w', 08dH, 0d5H
	DB	'Rg0M0~0[0', 093H, '0', 02H, '0', 00H, 00H	; `string'
CONST	ENDS
;	COMDAT ??_C@_1DI@FKECHAAB@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAM?$AAo?$AAn?$AAi?$AAt?$AAo?$AAr?$AA?5?$AAP?$AAr?$AAo?$AAj?$AAe?$AAc?$AAt?$AA?50?$KI0?i0?$PM?$AA?$AA@
CONST	SEGMENT
??_C@_1DI@FKECHAAB@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAM?$AAo?$AAn?$AAi?$AAt?$AAo?$AAr?$AA?5?$AAP?$AAr?$AAo?$AAj?$AAe?$AAc?$AAt?$AA?50?$KI0?i0?$PM?$AA?$AA@ DB 'n'
	DB	00H, 'p', 00H, 'c', 00H, 'a', 00H, ' ', 00H, '3', 00H, 'D', 00H
	DB	' ', 00H, 'M', 00H, 'o', 00H, 'n', 00H, 'i', 00H, 't', 00H, 'o'
	DB	00H, 'r', 00H, ' ', 00H, 'P', 00H, 'r', 00H, 'o', 00H, 'j', 00H
	DB	'e', 00H, 'c', 00H, 't', 00H, ' ', 00H, 0a8H, '0', 0e9H, '0', 0fcH
	DB	'0', 00H, 00H				; `string'
CONST	ENDS
;	COMDAT ??_C@_1DA@GMIFNOFA@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAM?$AAo?$AAn?$AAi?$AAt?$AAo?$AAr?$AA?5?$AAP?$AAr?$AAo?$AAj?$AAe?$AAc?$AAt?$AA?$AA@
CONST	SEGMENT
??_C@_1DA@GMIFNOFA@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAM?$AAo?$AAn?$AAi?$AAt?$AAo?$AAr?$AA?5?$AAP?$AAr?$AAo?$AAj?$AAe?$AAc?$AAt?$AA?$AA@ DB 'n'
	DB	00H, 'p', 00H, 'c', 00H, 'a', 00H, ' ', 00H, '3', 00H, 'D', 00H
	DB	' ', 00H, 'M', 00H, 'o', 00H, 'n', 00H, 'i', 00H, 't', 00H, 'o'
	DB	00H, 'r', 00H, ' ', 00H, 'P', 00H, 'r', 00H, 'o', 00H, 'j', 00H
	DB	'e', 00H, 'c', 00H, 't', 00H, 00H, 00H	; `string'
CONST	ENDS
;	COMDAT rtc$TMZ
rtc$TMZ	SEGMENT
__RTC_Shutdown.rtc$TMZ DD FLAT:__RTC_Shutdown
rtc$TMZ	ENDS
;	COMDAT rtc$IMZ
rtc$IMZ	SEGMENT
__RTC_InitBase.rtc$IMZ DD FLAT:__RTC_InitBase
; Function compile flags: /Odtp /RTCsu /ZI
rtc$IMZ	ENDS
;	COMDAT ??0WinEngine@@QAE@PAUHINSTANCE__@@PAJH@Z
_TEXT	SEGMENT
tv243 = -268						; size = 4
tv232 = -268						; size = 4
$T82186 = -260						; size = 4
$T82189 = -248						; size = 4
_dwWindowStyle$ = -44					; size = 4
_main_window_style$ = -32				; size = 4
_theErr$ = -20						; size = 4
_this$ = -8						; size = 4
_hInstance$ = 8						; size = 4
_result$ = 12						; size = 4
_nCmdShow$ = 16						; size = 4
??0WinEngine@@QAE@PAUHINSTANCE__@@PAJH@Z PROC		; WinEngine::WinEngine, COMDAT
; _this$ = ecx
; Line 15
	push	ebp
	mov	ebp, esp
	sub	esp, 268				; 0000010cH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-268]
	mov	ecx, 67					; 00000043H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
; Line 17
	mov	esi, esp
	push	OFFSET ??_C@_1DA@GMIFNOFA@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAM?$AAo?$AAn?$AAi?$AAt?$AAo?$AAr?$AA?5?$AAP?$AAr?$AAo?$AAj?$AAe?$AAc?$AAt?$AA?$AA@
	push	0
	push	0
	call	DWORD PTR __imp__CreateMutexW@12
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	ecx, DWORD PTR _this$[ebp]
	mov	DWORD PTR [ecx], eax
; Line 18
	mov	esi, esp
	call	DWORD PTR __imp__GetLastError@0
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _theErr$[ebp], eax
; Line 20
	cmp	DWORD PTR _theErr$[ebp], 183		; 000000b7H
	jne	SHORT $LN6@WinEngine
; Line 23
	mov	eax, DWORD PTR _this$[ebp]
	cmp	DWORD PTR [eax], 0
	je	SHORT $LN5@WinEngine
	mov	esi, esp
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax]
	push	ecx
	call	DWORD PTR __imp__CloseHandle@4
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN5@WinEngine:
; Line 24
	mov	esi, esp
	push	16					; 00000010H
	push	OFFSET ??_C@_1DI@FKECHAAB@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAM?$AAo?$AAn?$AAi?$AAt?$AAo?$AAr?$AA?5?$AAP?$AAr?$AAo?$AAj?$AAe?$AAc?$AAt?$AA?50?$KI0?i0?$PM?$AA?$AA@
	push	OFFSET ??_C@_1CM@LKBDIPHI@0S0n0?$KC0?W0?j0?$LB0?$PM0?$LH0?g0?s0oY?$BK?$JB?M?$INwR?U0g0M0?$HO0?$FL0?$JD0?$AC?$AA?$AA@
	push	0
	call	DWORD PTR __imp__MessageBoxW@16
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 25
	mov	eax, DWORD PTR _result$[ebp]
	mov	DWORD PTR [eax], -2147467259		; 80004005H
; Line 26
	jmp	$LN7@WinEngine
$LN6@WinEngine:
; Line 30
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+4], 48			; 00000030H
; Line 31
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+8], 64			; 00000040H
; Line 32
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+12], OFFSET ?WndProc@@YGJPAUHWND__@@IIJ@Z ; WndProc
; Line 33
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+16], 0
; Line 34
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+20], 0
; Line 35
	mov	esi, esp
	push	0
	call	DWORD PTR __imp__GetModuleHandleW@4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	ecx, DWORD PTR _this$[ebp]
	mov	DWORD PTR [ecx+24], eax
; Line 36
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+28], 0
; Line 37
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+32], 0
; Line 38
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+36], 0
; Line 39
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+40], 0
; Line 40
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+44], OFFSET ??_C@_1DA@GMIFNOFA@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAM?$AAo?$AAn?$AAi?$AAt?$AAo?$AAr?$AA?5?$AAP?$AAr?$AAo?$AAj?$AAe?$AAc?$AAt?$AA?$AA@
; Line 41
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+48], 0
; Line 42
	mov	eax, DWORD PTR _this$[ebp]
	add	eax, 4
	mov	esi, esp
	push	eax
	call	DWORD PTR __imp__RegisterClassExW@4
	cmp	esi, esp
	call	__RTC_CheckEsp
	movzx	ecx, ax
	test	ecx, ecx
	jne	SHORT $LN4@WinEngine
; Line 44
	mov	eax, DWORD PTR _result$[ebp]
	mov	DWORD PTR [eax], -2147467259		; 80004005H
; Line 45
	jmp	$LN7@WinEngine
$LN4@WinEngine:
; Line 50
	mov	DWORD PTR _main_window_style$[ebp], 13238272 ; 00ca0000H
; Line 54
	mov	esi, esp
	push	0
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+24]
	push	ecx
	push	0
	push	0
	push	2400					; 00000960H
	push	3840					; 00000f00H
	push	0
	push	0
	mov	edx, DWORD PTR _main_window_style$[ebp]
	push	edx
	push	OFFSET ??_C@_1DA@GMIFNOFA@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAM?$AAo?$AAn?$AAi?$AAt?$AAo?$AAr?$AA?5?$AAP?$AAr?$AAo?$AAj?$AAe?$AAc?$AAt?$AA?$AA@
	push	OFFSET ??_C@_1DA@GMIFNOFA@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAM?$AAo?$AAn?$AAi?$AAt?$AAo?$AAr?$AA?5?$AAP?$AAr?$AAo?$AAj?$AAe?$AAc?$AAt?$AA?$AA@
	push	0
	call	DWORD PTR __imp__CreateWindowExW@48
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	ecx, DWORD PTR _this$[ebp]
	mov	DWORD PTR [ecx+100], eax
; Line 59
	mov	esi, esp
	push	1
	mov	edi, esp
	push	79					; 0000004fH
	call	DWORD PTR __imp__GetSystemMetrics@4
	cmp	edi, esp
	call	__RTC_CheckEsp
	push	eax
	mov	edi, esp
	push	78					; 0000004eH
	call	DWORD PTR __imp__GetSystemMetrics@4
	cmp	edi, esp
	call	__RTC_CheckEsp
	push	eax
	mov	edi, esp
	push	77					; 0000004dH
	call	DWORD PTR __imp__GetSystemMetrics@4
	cmp	edi, esp
	call	__RTC_CheckEsp
	push	eax
	mov	edi, esp
	push	76					; 0000004cH
	call	DWORD PTR __imp__GetSystemMetrics@4
	cmp	edi, esp
	call	__RTC_CheckEsp
	push	eax
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+100]
	push	ecx
	call	DWORD PTR __imp__MoveWindow@24
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 62
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+52], 48			; 00000030H
; Line 63
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+56], 64			; 00000040H
; Line 64
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+60], 0
; Line 65
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+64], 0
; Line 66
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+68], 0
; Line 67
	mov	esi, esp
	push	0
	call	DWORD PTR __imp__GetModuleHandleW@4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	ecx, DWORD PTR _this$[ebp]
	mov	DWORD PTR [ecx+72], eax
; Line 68
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+76], 0
; Line 69
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+80], 0
; Line 70
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+84], 0
; Line 71
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+88], 0
; Line 72
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+92], OFFSET ??_C@_1BO@CDGEGDPF@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAB?$AAu?$AAf?$AAf?$AAe?$AAr?$AA?$AA@
; Line 73
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+96], 0
; Line 74
	mov	eax, DWORD PTR _this$[ebp]
	add	eax, 52					; 00000034H
	mov	esi, esp
	push	eax
	call	DWORD PTR __imp__RegisterClassExW@4
	cmp	esi, esp
	call	__RTC_CheckEsp
	movzx	ecx, ax
	test	ecx, ecx
	jne	SHORT $LN3@WinEngine
; Line 76
	mov	eax, DWORD PTR _result$[ebp]
	mov	DWORD PTR [eax], -2147467259		; 80004005H
; Line 77
	jmp	$LN7@WinEngine
$LN3@WinEngine:
; Line 80
	mov	DWORD PTR _dwWindowStyle$[ebp], 13238272 ; 00ca0000H
; Line 85
	mov	esi, esp
	push	0
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+72]
	push	ecx
	push	0
	push	0
	push	1
	push	1
	push	-2147483648				; 80000000H
	push	-2147483648				; 80000000H
	mov	edx, DWORD PTR _dwWindowStyle$[ebp]
	push	edx
	push	OFFSET ??_C@_1BO@CDGEGDPF@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAB?$AAu?$AAf?$AAf?$AAe?$AAr?$AA?$AA@
	push	OFFSET ??_C@_1BO@CDGEGDPF@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAB?$AAu?$AAf?$AAf?$AAe?$AAr?$AA?$AA@
	push	0
	call	DWORD PTR __imp__CreateWindowExW@48
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	ecx, DWORD PTR _this$[ebp]
	mov	DWORD PTR [ecx+104], eax
; Line 87
	push	800					; 00000320H
	call	??2@YAPAXI@Z				; operator new
	add	esp, 4
	mov	DWORD PTR $T82186[ebp], eax
	cmp	DWORD PTR $T82186[ebp], 0
	je	SHORT $LN9@WinEngine
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+100]
	push	ecx
	mov	edx, DWORD PTR _hInstance$[ebp]
	push	edx
	mov	eax, DWORD PTR _result$[ebp]
	push	eax
	mov	esi, DWORD PTR _this$[ebp]
	add	esi, 52					; 00000034H
	sub	esp, 48					; 00000030H
	mov	ecx, 12					; 0000000cH
	mov	edi, esp
	rep movsd
	push	1
	mov	ecx, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR [ecx+104]
	push	edx
	mov	ecx, DWORD PTR $T82186[ebp]
	call	??0DXEngine@@QAE@PAUHWND__@@HUtagWNDCLASSEXW@@PAJPAUHINSTANCE__@@0@Z ; DXEngine::DXEngine
	mov	DWORD PTR tv232[ebp], eax
	jmp	SHORT $LN10@WinEngine
$LN9@WinEngine:
	mov	DWORD PTR tv232[ebp], 0
$LN10@WinEngine:
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR tv232[ebp]
	mov	DWORD PTR [eax+108], ecx
; Line 88
	mov	eax, DWORD PTR _result$[ebp]
	cmp	DWORD PTR [eax], 0
	jge	SHORT $LN2@WinEngine
; Line 90
	jmp	$LN7@WinEngine
$LN2@WinEngine:
; Line 92
	push	12					; 0000000cH
	call	??2@YAPAXI@Z				; operator new
	add	esp, 4
	mov	DWORD PTR $T82189[ebp], eax
	cmp	DWORD PTR $T82189[ebp], 0
	je	SHORT $LN11@WinEngine
	mov	eax, DWORD PTR _result$[ebp]
	push	eax
	mov	ecx, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR [ecx+108]
	push	edx
	mov	ecx, DWORD PTR $T82189[ebp]
	call	??0ProgramEngine@@QAE@PAVDXEngine@@PAJ@Z ; ProgramEngine::ProgramEngine
	mov	DWORD PTR tv243[ebp], eax
	jmp	SHORT $LN12@WinEngine
$LN11@WinEngine:
	mov	DWORD PTR tv243[ebp], 0
$LN12@WinEngine:
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR tv243[ebp]
	mov	DWORD PTR [eax+112], ecx
; Line 93
	mov	eax, DWORD PTR _result$[ebp]
	cmp	DWORD PTR [eax], 0
	jge	SHORT $LN1@WinEngine
; Line 95
	jmp	SHORT $LN7@WinEngine
$LN1@WinEngine:
; Line 99
	mov	esi, esp
	mov	eax, DWORD PTR _nCmdShow$[ebp]
	push	eax
	mov	ecx, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR [ecx+100]
	push	edx
	call	DWORD PTR __imp__ShowWindow@8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 100
	mov	esi, esp
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+100]
	push	ecx
	call	DWORD PTR __imp__UpdateWindow@4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 103
	mov	esi, esp
	push	0
	push	83					; 00000053H
	push	1
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+100]
	push	ecx
	call	DWORD PTR __imp__SetTimer@16
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 105
	mov	eax, DWORD PTR _result$[ebp]
	mov	DWORD PTR [eax], 0
$LN7@WinEngine:
; Line 106
	mov	eax, DWORD PTR _this$[ebp]
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 268				; 0000010cH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	12					; 0000000cH
??0WinEngine@@QAE@PAUHINSTANCE__@@PAJH@Z ENDP		; WinEngine::WinEngine
_TEXT	ENDS
PUBLIC	??_GDXEngine@@QAEPAXI@Z				; DXEngine::`scalar deleting destructor'
PUBLIC	??_GProgramEngine@@QAEPAXI@Z			; ProgramEngine::`scalar deleting destructor'
PUBLIC	??1WinEngine@@QAE@XZ				; WinEngine::~WinEngine
EXTRN	__imp__UnregisterClassW@8:PROC
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ??1WinEngine@@QAE@XZ
_TEXT	SEGMENT
tv80 = -256						; size = 4
tv71 = -256						; size = 4
$T82203 = -248						; size = 4
$T82204 = -236						; size = 4
$T82207 = -224						; size = 4
$T82208 = -212						; size = 4
_this$ = -8						; size = 4
??1WinEngine@@QAE@XZ PROC				; WinEngine::~WinEngine, COMDAT
; _this$ = ecx
; Line 110
	push	ebp
	mov	ebp, esp
	sub	esp, 256				; 00000100H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-256]
	mov	ecx, 64					; 00000040H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
; Line 111
	mov	eax, DWORD PTR _this$[ebp]
	cmp	DWORD PTR [eax+112], 0
	je	SHORT $LN3@WinEngine@2
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+112]
	mov	DWORD PTR $T82204[ebp], ecx
	mov	edx, DWORD PTR $T82204[ebp]
	mov	DWORD PTR $T82203[ebp], edx
	cmp	DWORD PTR $T82203[ebp], 0
	je	SHORT $LN6@WinEngine@2
	push	1
	mov	ecx, DWORD PTR $T82203[ebp]
	call	??_GProgramEngine@@QAEPAXI@Z
	mov	DWORD PTR tv71[ebp], eax
	jmp	SHORT $LN7@WinEngine@2
$LN6@WinEngine@2:
	mov	DWORD PTR tv71[ebp], 0
$LN7@WinEngine@2:
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+112], 0
$LN3@WinEngine@2:
; Line 112
	mov	eax, DWORD PTR _this$[ebp]
	cmp	DWORD PTR [eax+108], 0
	je	SHORT $LN2@WinEngine@2
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+108]
	mov	DWORD PTR $T82208[ebp], ecx
	mov	edx, DWORD PTR $T82208[ebp]
	mov	DWORD PTR $T82207[ebp], edx
	cmp	DWORD PTR $T82207[ebp], 0
	je	SHORT $LN8@WinEngine@2
	push	1
	mov	ecx, DWORD PTR $T82207[ebp]
	call	??_GDXEngine@@QAEPAXI@Z
	mov	DWORD PTR tv80[ebp], eax
	jmp	SHORT $LN9@WinEngine@2
$LN8@WinEngine@2:
	mov	DWORD PTR tv80[ebp], 0
$LN9@WinEngine@2:
	mov	eax, DWORD PTR _this$[ebp]
	mov	DWORD PTR [eax+108], 0
$LN2@WinEngine@2:
; Line 113
	mov	esi, esp
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+24]
	push	ecx
	push	OFFSET ??_C@_1DA@GMIFNOFA@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAM?$AAo?$AAn?$AAi?$AAt?$AAo?$AAr?$AA?5?$AAP?$AAr?$AAo?$AAj?$AAe?$AAc?$AAt?$AA?$AA@
	call	DWORD PTR __imp__UnregisterClassW@8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 114
	mov	esi, esp
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+72]
	push	ecx
	push	OFFSET ??_C@_1DA@GMIFNOFA@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAM?$AAo?$AAn?$AAi?$AAt?$AAo?$AAr?$AA?5?$AAP?$AAr?$AAo?$AAj?$AAe?$AAc?$AAt?$AA?$AA@
	call	DWORD PTR __imp__UnregisterClassW@8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 115
	mov	eax, DWORD PTR _this$[ebp]
	cmp	DWORD PTR [eax], 0
	je	SHORT $LN4@WinEngine@2
	mov	esi, esp
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax]
	push	ecx
	call	DWORD PTR __imp__CloseHandle@4
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN4@WinEngine@2:
; Line 116
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 256				; 00000100H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
??1WinEngine@@QAE@XZ ENDP				; WinEngine::~WinEngine
_TEXT	ENDS
EXTRN	??3@YAXPAX@Z:PROC				; operator delete
EXTRN	??1ProgramEngine@@QAE@XZ:PROC			; ProgramEngine::~ProgramEngine
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ??_GProgramEngine@@QAEPAXI@Z
_TEXT	SEGMENT
_this$ = -8						; size = 4
___flags$ = 8						; size = 4
??_GProgramEngine@@QAEPAXI@Z PROC			; ProgramEngine::`scalar deleting destructor', COMDAT
; _this$ = ecx
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-204]
	mov	ecx, 51					; 00000033H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, DWORD PTR _this$[ebp]
	call	??1ProgramEngine@@QAE@XZ		; ProgramEngine::~ProgramEngine
	mov	eax, DWORD PTR ___flags$[ebp]
	and	eax, 1
	je	SHORT $LN1@scalar
	mov	eax, DWORD PTR _this$[ebp]
	push	eax
	call	??3@YAXPAX@Z				; operator delete
	add	esp, 4
$LN1@scalar:
	mov	eax, DWORD PTR _this$[ebp]
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	4
??_GProgramEngine@@QAEPAXI@Z ENDP			; ProgramEngine::`scalar deleting destructor'
_TEXT	ENDS
EXTRN	??1DXEngine@@QAE@XZ:PROC			; DXEngine::~DXEngine
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ??_GDXEngine@@QAEPAXI@Z
_TEXT	SEGMENT
_this$ = -8						; size = 4
___flags$ = 8						; size = 4
??_GDXEngine@@QAEPAXI@Z PROC				; DXEngine::`scalar deleting destructor', COMDAT
; _this$ = ecx
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-204]
	mov	ecx, 51					; 00000033H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
	mov	ecx, DWORD PTR _this$[ebp]
	call	??1DXEngine@@QAE@XZ			; DXEngine::~DXEngine
	mov	eax, DWORD PTR ___flags$[ebp]
	and	eax, 1
	je	SHORT $LN1@scalar@2
	mov	eax, DWORD PTR _this$[ebp]
	push	eax
	call	??3@YAXPAX@Z				; operator delete
	add	esp, 4
$LN1@scalar@2:
	mov	eax, DWORD PTR _this$[ebp]
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	4
??_GDXEngine@@QAEPAXI@Z ENDP				; DXEngine::`scalar deleting destructor'
_TEXT	ENDS
PUBLIC	??_C@_1BA@PGOGJBHO@N?9e?$KN0W0?$HO0Y0K?$PP?$BP?$AA?$AA@ ; `string'
PUBLIC	?MsgProc@WinEngine@@QAGJPAUHWND__@@IIJ@Z	; WinEngine::MsgProc
EXTRN	__imp__DefWindowProcW@16:PROC
EXTRN	?ProcessProgram@ProgramEngine@@QAEJXZ:PROC	; ProgramEngine::ProcessProgram
EXTRN	__imp__MessageBoxExW@20:PROC
EXTRN	__imp__PostQuitMessage@4:PROC
;	COMDAT ??_C@_1BA@PGOGJBHO@N?9e?$KN0W0?$HO0Y0K?$PP?$BP?$AA?$AA@
CONST	SEGMENT
??_C@_1BA@PGOGJBHO@N?9e?$KN0W0?$HO0Y0K?$PP?$BP?$AA?$AA@ DB '-N', 0adH, 'e'
	DB	'W0~0Y0K0', 01fH, 0ffH, 00H, 00H		; `string'
; Function compile flags: /Odtp /RTCsu /ZI
CONST	ENDS
;	COMDAT ?MsgProc@WinEngine@@QAGJPAUHWND__@@IIJ@Z
_TEXT	SEGMENT
tv64 = -196						; size = 4
_this$ = 8						; size = 4
_hWnd$ = 12						; size = 4
_msg$ = 16						; size = 4
_wParam$ = 20						; size = 4
_lParam$ = 24						; size = 4
?MsgProc@WinEngine@@QAGJPAUHWND__@@IIJ@Z PROC		; WinEngine::MsgProc, COMDAT
; Line 120
	push	ebp
	mov	ebp, esp
	sub	esp, 196				; 000000c4H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-196]
	mov	ecx, 49					; 00000031H
	mov	eax, -858993460				; ccccccccH
	rep stosd
; Line 124
	mov	eax, DWORD PTR _msg$[ebp]
	mov	DWORD PTR tv64[ebp], eax
	cmp	DWORD PTR tv64[ebp], 257		; 00000101H
	ja	SHORT $LN17@MsgProc
	cmp	DWORD PTR tv64[ebp], 257		; 00000101H
	je	SHORT $LN12@MsgProc
	cmp	DWORD PTR tv64[ebp], 2
	je	$LN9@MsgProc
	cmp	DWORD PTR tv64[ebp], 6
	je	$LN8@MsgProc
	jmp	$LN13@MsgProc
$LN17@MsgProc:
	cmp	DWORD PTR tv64[ebp], 275		; 00000113H
	je	$LN4@MsgProc
	jmp	$LN13@MsgProc
$LN12@MsgProc:
; Line 128
	cmp	DWORD PTR _wParam$[ebp], 27		; 0000001bH
	jne	SHORT $LN11@MsgProc
; Line 132
	mov	esi, esp
	push	0
	call	DWORD PTR __imp__PostQuitMessage@4
	cmp	esi, esp
	call	__RTC_CheckEsp
	xor	eax, eax
	jmp	$LN15@MsgProc
; Line 135
	mov	DWORD PTR ?sMsgBoxFlag@?1??MsgProc@WinEngine@@QAGJPAUHWND__@@IIJ@Z@4HA, 1
; Line 138
	mov	esi, esp
	push	17					; 00000011H
	push	292					; 00000124H
	push	OFFSET ??_C@_1DA@GMIFNOFA@?$AAn?$AAp?$AAc?$AAa?$AA?5?$AA3?$AAD?$AA?5?$AAM?$AAo?$AAn?$AAi?$AAt?$AAo?$AAr?$AA?5?$AAP?$AAr?$AAo?$AAj?$AAe?$AAc?$AAt?$AA?$AA@
	push	OFFSET ??_C@_1BA@PGOGJBHO@N?9e?$KN0W0?$HO0Y0K?$PP?$BP?$AA?$AA@
	mov	eax, DWORD PTR _hWnd$[ebp]
	push	eax
	call	DWORD PTR __imp__MessageBoxExW@20
	cmp	esi, esp
	call	__RTC_CheckEsp
	cmp	eax, 6
	jne	SHORT $LN10@MsgProc
; Line 139
	mov	esi, esp
	push	0
	call	DWORD PTR __imp__PostQuitMessage@4
	cmp	esi, esp
	call	__RTC_CheckEsp
	xor	eax, eax
	jmp	$LN15@MsgProc
$LN10@MsgProc:
; Line 140
	mov	DWORD PTR ?sMsgBoxFlag@?1??MsgProc@WinEngine@@QAGJPAUHWND__@@IIJ@Z@4HA, 0
$LN11@MsgProc:
; Line 143
	jmp	SHORT $LN13@MsgProc
$LN9@MsgProc:
; Line 146
	mov	esi, esp
	push	0
	call	DWORD PTR __imp__PostQuitMessage@4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 147
	xor	eax, eax
	jmp	SHORT $LN15@MsgProc
; Line 148
	jmp	SHORT $LN13@MsgProc
$LN8@MsgProc:
; Line 151
	cmp	DWORD PTR _wParam$[ebp], 0
	je	SHORT $LN7@MsgProc
; Line 154
	mov	DWORD PTR ?sWinActivFlag@?1??MsgProc@WinEngine@@QAGJPAUHWND__@@IIJ@Z@4HA, 1
	jmp	SHORT $LN6@MsgProc
$LN7@MsgProc:
; Line 156
	cmp	DWORD PTR _wParam$[ebp], 0
	jne	SHORT $LN6@MsgProc
; Line 159
	mov	DWORD PTR ?sWinActivFlag@?1??MsgProc@WinEngine@@QAGJPAUHWND__@@IIJ@Z@4HA, 0
$LN6@MsgProc:
; Line 161
	jmp	SHORT $LN13@MsgProc
$LN4@MsgProc:
; Line 165
	cmp	DWORD PTR ?sMsgBoxFlag@?1??MsgProc@WinEngine@@QAGJPAUHWND__@@IIJ@Z@4HA, 0
	jne	SHORT $LN13@MsgProc
; Line 168
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+112]
	call	?ProcessProgram@ProgramEngine@@QAEJXZ	; ProgramEngine::ProcessProgram
	test	eax, eax
	jge	SHORT $LN13@MsgProc
; Line 170
	mov	esi, esp
	push	0
	call	DWORD PTR __imp__PostQuitMessage@4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 171
	xor	eax, eax
	jmp	SHORT $LN15@MsgProc
$LN13@MsgProc:
; Line 180
	mov	esi, esp
	mov	eax, DWORD PTR _lParam$[ebp]
	push	eax
	mov	ecx, DWORD PTR _wParam$[ebp]
	push	ecx
	mov	edx, DWORD PTR _msg$[ebp]
	push	edx
	mov	eax, DWORD PTR _hWnd$[ebp]
	push	eax
	call	DWORD PTR __imp__DefWindowProcW@16
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN15@MsgProc:
; Line 181
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 196				; 000000c4H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	20					; 00000014H
?MsgProc@WinEngine@@QAGJPAUHWND__@@IIJ@Z ENDP		; WinEngine::MsgProc
_TEXT	ENDS
PUBLIC	?MsgLoop@WinEngine@@QAEJXZ			; WinEngine::MsgLoop
EXTRN	__imp__Sleep@4:PROC
EXTRN	__imp__DispatchMessageW@4:PROC
EXTRN	__imp__TranslateMessage@4:PROC
EXTRN	__imp__GetMessageW@16:PROC
EXTRN	__imp__PeekMessageW@20:PROC
EXTRN	_memset:PROC
EXTRN	@_RTC_CheckStackVars@8:PROC
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?MsgLoop@WinEngine@@QAEJXZ
_TEXT	SEGMENT
_msg$ = -44						; size = 28
_this$ = -8						; size = 4
?MsgLoop@WinEngine@@QAEJXZ PROC				; WinEngine::MsgLoop, COMDAT
; _this$ = ecx
; Line 185
	push	ebp
	mov	ebp, esp
	sub	esp, 240				; 000000f0H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-240]
	mov	ecx, 60					; 0000003cH
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
; Line 188
	push	28					; 0000001cH
	push	0
	lea	eax, DWORD PTR _msg$[ebp]
	push	eax
	call	_memset
	add	esp, 12					; 0000000cH
$LN6@MsgLoop:
; Line 189
	cmp	DWORD PTR _msg$[ebp+4], 18		; 00000012H
	je	$LN5@MsgLoop
; Line 193
	mov	esi, esp
	push	0
	push	0
	push	0
	push	0
	lea	eax, DWORD PTR _msg$[ebp]
	push	eax
	call	DWORD PTR __imp__PeekMessageW@20
	cmp	esi, esp
	call	__RTC_CheckEsp
	test	eax, eax
	je	SHORT $LN4@MsgLoop
; Line 195
	mov	esi, esp
	push	0
	push	0
	push	0
	lea	eax, DWORD PTR _msg$[ebp]
	push	eax
	call	DWORD PTR __imp__GetMessageW@16
	cmp	esi, esp
	call	__RTC_CheckEsp
	test	eax, eax
	jne	SHORT $LN3@MsgLoop
	mov	DWORD PTR _msg$[ebp+4], 18		; 00000012H
; Line 196
	jmp	SHORT $LN2@MsgLoop
$LN3@MsgLoop:
; Line 197
	mov	esi, esp
	lea	eax, DWORD PTR _msg$[ebp]
	push	eax
	call	DWORD PTR __imp__TranslateMessage@4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 198
	mov	esi, esp
	lea	eax, DWORD PTR _msg$[ebp]
	push	eax
	call	DWORD PTR __imp__DispatchMessageW@4
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN2@MsgLoop:
; Line 200
	jmp	SHORT $LN1@MsgLoop
$LN4@MsgLoop:
; Line 201
	mov	esi, esp
	push	10					; 0000000aH
	call	DWORD PTR __imp__Sleep@4
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN1@MsgLoop:
; Line 203
	jmp	$LN6@MsgLoop
$LN5@MsgLoop:
; Line 205
	xor	eax, eax
; Line 206
	push	edx
	mov	ecx, ebp
	push	eax
	lea	edx, DWORD PTR $LN11@MsgLoop
	call	@_RTC_CheckStackVars@8
	pop	eax
	pop	edx
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 240				; 000000f0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
	npad	1
$LN11@MsgLoop:
	DD	1
	DD	$LN10@MsgLoop
$LN10@MsgLoop:
	DD	-44					; ffffffd4H
	DD	28					; 0000001cH
	DD	$LN9@MsgLoop
$LN9@MsgLoop:
	DB	109					; 0000006dH
	DB	115					; 00000073H
	DB	103					; 00000067H
	DB	0
?MsgLoop@WinEngine@@QAEJXZ ENDP				; WinEngine::MsgLoop
_TEXT	ENDS
PUBLIC	?GetDXEngine@WinEngine@@QAEPAVDXEngine@@XZ	; WinEngine::GetDXEngine
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?GetDXEngine@WinEngine@@QAEPAVDXEngine@@XZ
_TEXT	SEGMENT
_this$ = -8						; size = 4
?GetDXEngine@WinEngine@@QAEPAVDXEngine@@XZ PROC		; WinEngine::GetDXEngine, COMDAT
; _this$ = ecx
; Line 210
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-204]
	mov	ecx, 51					; 00000033H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	DWORD PTR _this$[ebp], ecx
; Line 211
	mov	eax, DWORD PTR _this$[ebp]
	mov	eax, DWORD PTR [eax+108]
; Line 212
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
?GetDXEngine@WinEngine@@QAEPAVDXEngine@@XZ ENDP		; WinEngine::GetDXEngine
_TEXT	ENDS
PUBLIC	??_C@_1BC@NIJKCIBL@?$AAC?$AAO?$AAU?$AAN?$AAT?$AA?$CF?$AAl?$AAd?$AA?$AA@ ; `string'
PUBLIC	__$ArrayPad$
PUBLIC	?RenderBuffer@WinEngine@@QAEXPAPAUHDC__@@@Z	; WinEngine::RenderBuffer
EXTRN	__imp__ReleaseDC@8:PROC
EXTRN	__imp__TextOutW@20:PROC
EXTRN	__imp__lstrlenW@4:PROC
EXTRN	__imp__swprintf_s:PROC
EXTRN	?frame_counter@@3JA:DWORD			; frame_counter
EXTRN	__imp__BitBlt@36:PROC
EXTRN	__imp__GetDC@4:PROC
EXTRN	___security_cookie:DWORD
EXTRN	@__security_check_cookie@4:PROC
;	COMDAT ??_C@_1BC@NIJKCIBL@?$AAC?$AAO?$AAU?$AAN?$AAT?$AA?$CF?$AAl?$AAd?$AA?$AA@
CONST	SEGMENT
??_C@_1BC@NIJKCIBL@?$AAC?$AAO?$AAU?$AAN?$AAT?$AA?$CF?$AAl?$AAd?$AA?$AA@ DB 'C'
	DB	00H, 'O', 00H, 'U', 00H, 'N', 00H, 'T', 00H, '%', 00H, 'l', 00H
	DB	'd', 00H, 00H, 00H				; `string'
; Function compile flags: /Odtp /RTCsu /ZI
CONST	ENDS
;	COMDAT ?RenderBuffer@WinEngine@@QAEXPAPAUHDC__@@@Z
_TEXT	SEGMENT
_count_text$ = -112					; size = 80
_hdc$ = -24						; size = 4
_this$ = -12						; size = 4
__$ArrayPad$ = -4					; size = 4
_buffer_dc$ = 8						; size = 4
?RenderBuffer@WinEngine@@QAEXPAPAUHDC__@@@Z PROC	; WinEngine::RenderBuffer, COMDAT
; _this$ = ecx
; Line 215
	push	ebp
	mov	ebp, esp
	sub	esp, 308				; 00000134H
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-308]
	mov	ecx, 77					; 0000004dH
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	mov	DWORD PTR __$ArrayPad$[ebp], eax
	mov	DWORD PTR _this$[ebp], ecx
; Line 216
	mov	esi, esp
	mov	eax, DWORD PTR _this$[ebp]
	mov	ecx, DWORD PTR [eax+100]
	push	ecx
	call	DWORD PTR __imp__GetDC@4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _hdc$[ebp], eax
; Line 217
	mov	esi, esp
	push	13369376				; 00cc0020H
	push	0
	push	0
	mov	eax, DWORD PTR _buffer_dc$[ebp]
	mov	ecx, DWORD PTR [eax]
	push	ecx
	push	2400					; 00000960H
	push	3840					; 00000f00H
	push	0
	push	0
	mov	edx, DWORD PTR _hdc$[ebp]
	push	edx
	call	DWORD PTR __imp__BitBlt@36
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 219
	mov	esi, esp
	mov	eax, DWORD PTR ?frame_counter@@3JA	; frame_counter
	push	eax
	push	OFFSET ??_C@_1BC@NIJKCIBL@?$AAC?$AAO?$AAU?$AAN?$AAT?$AA?$CF?$AAl?$AAd?$AA?$AA@
	push	40					; 00000028H
	lea	ecx, DWORD PTR _count_text$[ebp]
	push	ecx
	call	DWORD PTR __imp__swprintf_s
	add	esp, 16					; 00000010H
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 220
	mov	esi, esp
	lea	eax, DWORD PTR _count_text$[ebp]
	push	eax
	call	DWORD PTR __imp__lstrlenW@4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	esi, esp
	push	eax
	lea	ecx, DWORD PTR _count_text$[ebp]
	push	ecx
	push	100					; 00000064H
	push	100					; 00000064H
	mov	edx, DWORD PTR _hdc$[ebp]
	push	edx
	call	DWORD PTR __imp__TextOutW@20
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 221
	mov	esi, esp
	mov	eax, DWORD PTR _hdc$[ebp]
	push	eax
	mov	ecx, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR [ecx+100]
	push	edx
	call	DWORD PTR __imp__ReleaseDC@8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 222
	push	edx
	mov	ecx, ebp
	push	eax
	lea	edx, DWORD PTR $LN5@RenderBuff
	call	@_RTC_CheckStackVars@8
	pop	eax
	pop	edx
	pop	edi
	pop	esi
	pop	ebx
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	add	esp, 308				; 00000134H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	4
	npad	1
$LN5@RenderBuff:
	DD	1
	DD	$LN4@RenderBuff
$LN4@RenderBuff:
	DD	-112					; ffffff90H
	DD	80					; 00000050H
	DD	$LN3@RenderBuff
$LN3@RenderBuff:
	DB	99					; 00000063H
	DB	111					; 0000006fH
	DB	117					; 00000075H
	DB	110					; 0000006eH
	DB	116					; 00000074H
	DB	95					; 0000005fH
	DB	116					; 00000074H
	DB	101					; 00000065H
	DB	120					; 00000078H
	DB	116					; 00000074H
	DB	0
?RenderBuffer@WinEngine@@QAEXPAPAUHDC__@@@Z ENDP	; WinEngine::RenderBuffer
_TEXT	ENDS
PUBLIC	__$ArrayPad$
PUBLIC	?DebugRender@WinEngine@@QAEXXZ			; WinEngine::DebugRender
EXTRN	__imp__EndPaint@8:PROC
EXTRN	__imp__BeginPaint@8:PROC
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?DebugRender@WinEngine@@QAEXXZ
_TEXT	SEGMENT
_count_text$ = -184					; size = 80
_hdc$ = -96						; size = 4
_paint_struct$ = -84					; size = 64
_this$ = -12						; size = 4
__$ArrayPad$ = -4					; size = 4
?DebugRender@WinEngine@@QAEXXZ PROC			; WinEngine::DebugRender, COMDAT
; _this$ = ecx
; Line 225
	push	ebp
	mov	ebp, esp
	sub	esp, 380				; 0000017cH
	push	ebx
	push	esi
	push	edi
	push	ecx
	lea	edi, DWORD PTR [ebp-380]
	mov	ecx, 95					; 0000005fH
	mov	eax, -858993460				; ccccccccH
	rep stosd
	pop	ecx
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	mov	DWORD PTR __$ArrayPad$[ebp], eax
	mov	DWORD PTR _this$[ebp], ecx
; Line 227
	mov	esi, esp
	lea	eax, DWORD PTR _paint_struct$[ebp]
	push	eax
	mov	ecx, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR [ecx+100]
	push	edx
	call	DWORD PTR __imp__BeginPaint@8
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _hdc$[ebp], eax
; Line 229
	mov	esi, esp
	mov	eax, DWORD PTR ?frame_counter@@3JA	; frame_counter
	push	eax
	push	OFFSET ??_C@_1BC@NIJKCIBL@?$AAC?$AAO?$AAU?$AAN?$AAT?$AA?$CF?$AAl?$AAd?$AA?$AA@
	push	40					; 00000028H
	lea	ecx, DWORD PTR _count_text$[ebp]
	push	ecx
	call	DWORD PTR __imp__swprintf_s
	add	esp, 16					; 00000010H
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 230
	mov	esi, esp
	lea	eax, DWORD PTR _count_text$[ebp]
	push	eax
	call	DWORD PTR __imp__lstrlenW@4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	esi, esp
	push	eax
	lea	ecx, DWORD PTR _count_text$[ebp]
	push	ecx
	push	100					; 00000064H
	push	100					; 00000064H
	mov	edx, DWORD PTR _hdc$[ebp]
	push	edx
	call	DWORD PTR __imp__TextOutW@20
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 231
	mov	esi, esp
	lea	eax, DWORD PTR _paint_struct$[ebp]
	push	eax
	mov	ecx, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR [ecx+100]
	push	edx
	call	DWORD PTR __imp__EndPaint@8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 232
	push	edx
	mov	ecx, ebp
	push	eax
	lea	edx, DWORD PTR $LN6@DebugRende
	call	@_RTC_CheckStackVars@8
	pop	eax
	pop	edx
	pop	edi
	pop	esi
	pop	ebx
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	add	esp, 380				; 0000017cH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
	npad	2
$LN6@DebugRende:
	DD	2
	DD	$LN5@DebugRende
$LN5@DebugRende:
	DD	-84					; ffffffacH
	DD	64					; 00000040H
	DD	$LN3@DebugRende
	DD	-184					; ffffff48H
	DD	80					; 00000050H
	DD	$LN4@DebugRende
$LN4@DebugRende:
	DB	99					; 00000063H
	DB	111					; 0000006fH
	DB	117					; 00000075H
	DB	110					; 0000006eH
	DB	116					; 00000074H
	DB	95					; 0000005fH
	DB	116					; 00000074H
	DB	101					; 00000065H
	DB	120					; 00000078H
	DB	116					; 00000074H
	DB	0
$LN3@DebugRende:
	DB	112					; 00000070H
	DB	97					; 00000061H
	DB	105					; 00000069H
	DB	110					; 0000006eH
	DB	116					; 00000074H
	DB	95					; 0000005fH
	DB	115					; 00000073H
	DB	116					; 00000074H
	DB	114					; 00000072H
	DB	117					; 00000075H
	DB	99					; 00000063H
	DB	116					; 00000074H
	DB	0
?DebugRender@WinEngine@@QAEXXZ ENDP			; WinEngine::DebugRender
_TEXT	ENDS
EXTRN	?win_engine@@3PAVWinEngine@@A:DWORD		; win_engine
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?WndProc@@YGJPAUHWND__@@IIJ@Z
_TEXT	SEGMENT
_hwnd$ = 8						; size = 4
_uMsg$ = 12						; size = 4
_wParam$ = 16						; size = 4
_lParam$ = 20						; size = 4
?WndProc@@YGJPAUHWND__@@IIJ@Z PROC			; WndProc, COMDAT
; Line 235
	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-192]
	mov	ecx, 48					; 00000030H
	mov	eax, -858993460				; ccccccccH
	rep stosd
; Line 236
	mov	eax, DWORD PTR _lParam$[ebp]
	push	eax
	mov	ecx, DWORD PTR _wParam$[ebp]
	push	ecx
	mov	edx, DWORD PTR _uMsg$[ebp]
	push	edx
	mov	eax, DWORD PTR _hwnd$[ebp]
	push	eax
	mov	ecx, DWORD PTR ?win_engine@@3PAVWinEngine@@A ; win_engine
	push	ecx
	call	?MsgProc@WinEngine@@QAGJPAUHWND__@@IIJ@Z ; WinEngine::MsgProc
; Line 237
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	16					; 00000010H
?WndProc@@YGJPAUHWND__@@IIJ@Z ENDP			; WndProc
_TEXT	ENDS
END