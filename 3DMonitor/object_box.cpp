// Copyright 2011 MineStudio.
// ObjectBox�N���X�̒�`���s���܂��B

#include "object_box.h"

#include "model_data.h"
#include "dx_engine.h"
#include "appdefs.h"

// �R���X�g���N�^
ObjectBox::ObjectBox(ModelData* model) {
	model_		= model;
	position_	= D3DXVECTOR3(0.0f,0.0f,0.0f);
	direction_	= DirectionYPR(0.0f,0.0f,0.0f);
	scale_		= 1.0f;
}
ObjectBox::ObjectBox(ModelData* model, D3DXVECTOR3 position) {
	model_		= model;
	position_	= position;
	direction_	= DirectionYPR(0.0f,0.0f,0.0f);
	scale_		= 1.0f;
}
ObjectBox::ObjectBox(ModelData* model, D3DXVECTOR3 position, DirectionYPR direction) {
	model_		= model;
	position_	= position;
	direction_	= direction;
	scale_		= 1.0f;
}

// �f�X�g���N�^
ObjectBox::~ObjectBox()
{
}

// �����_�����O
void ObjectBox::Render(DXEngine* dx_engine)
{
	dx_engine->SetObjectMatrix(position_, direction_, scale_*(model_->get_scale_()));
	model_->RenderModel(dx_engine->get_d3d_device());
}

// �e�X�g�X�s��
void ObjectBox::TestSpin()
{
	direction_.Pitch += D3DX_PI/kSetFps/5;
}