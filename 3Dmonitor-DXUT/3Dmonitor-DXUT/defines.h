// Copyright 2011 MineStudio.
// �A�v���P�[�V�����Ŏg�p�����`(define)�����Ă����܂�

#ifndef NPCA3DMONITOR__DEFINES_H_
#define NPCA3DMONITOR__DEFINES_H_

// ----
// �萔
// ----

// �E�B���h�E�̖��O
#define kWindowTitle		TEXT("npca 3D Monitor Project")
#define kBufferTitle		TEXT("npca 3D Buffer")
// �G���[���b�Z�[�W�̃^�C�g��
#define	kErrorMessage		TEXT("npca 3D Monitor Project �G���[")

// �E�B���h�E�̌`�Ȃ�
#define	kWindowWidth	3840
#define	kWindowHeight	2400
#define	kWindowTop		50
#define	kWindowLeft		50

// ��ʃT�C�Y
#define kMonitorWidth	3840
#define kMonitorHeight	2400

// 1�O�����s�N�Z�����̓񎟌��s�N�Z���̐�
#define kNumOfHorizontal2DPixel	6
#define kNumOfVertical2DPixel	6

// �O�����s�N�Z���̉�f��
#define kWidth3DPixel	(kMonitorWidth/kNumOfHorizontal2DPixel)
#define kHeight3DPixel	(kMonitorHeight/kNumOfVertical2DPixel)

// ������
#define kNumOfParallax	(kNumOfHorizontal2DPixel*kNumOfVertical2DPixel)

// �ꎋ���̎���p(DEG)
#define kAnglePitch		0.63
// ��L���W�A���l
#define kRadAnglePitch	(D3DXToRadian(kAnglePitch))

// �t�@�C�����̍Œ�
#define	kStringLength	512

// 10/1000msec. Sleep���鎞��
#define	kSleep			10

#define	kTimerId		1

#define	kSetFps			20
#define	kTimerLap		(1000/kSetFps)

#endif