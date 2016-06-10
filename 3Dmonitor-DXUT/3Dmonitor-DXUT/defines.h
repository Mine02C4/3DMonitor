// Copyright 2011 MineStudio.
// アプリケーションで使用する定義(define)をしていきます

#ifndef NPCA3DMONITOR__DEFINES_H_
#define NPCA3DMONITOR__DEFINES_H_

// ----
// 定数
// ----

// ウィンドウの名前
#define kWindowTitle		TEXT("npca 3D Monitor Project")
#define kBufferTitle		TEXT("npca 3D Buffer")
// エラーメッセージのタイトル
#define	kErrorMessage		TEXT("npca 3D Monitor Project エラー")

// ウィンドウの形など
#define	kWindowWidth	3840
#define	kWindowHeight	2400
#define	kWindowTop		50
#define	kWindowLeft		50

// 画面サイズ
#define kMonitorWidth	3840
#define kMonitorHeight	2400

// 1三次元ピクセル内の二次元ピクセルの数
#define kNumOfHorizontal2DPixel	6
#define kNumOfVertical2DPixel	6

// 三次元ピクセルの画素数
#define kWidth3DPixel	(kMonitorWidth/kNumOfHorizontal2DPixel)
#define kHeight3DPixel	(kMonitorHeight/kNumOfVertical2DPixel)

// 視差数
#define kNumOfParallax	(kNumOfHorizontal2DPixel*kNumOfVertical2DPixel)

// 一視差の視野角(DEG)
#define kAnglePitch		0.63
// 上記ラジアン値
#define kRadAnglePitch	(D3DXToRadian(kAnglePitch))

// ファイル名の最長
#define	kStringLength	512

// 10/1000msec. Sleepする時間
#define	kSleep			10

#define	kTimerId		1

#define	kSetFps			20
#define	kTimerLap		(1000/kSetFps)

#endif