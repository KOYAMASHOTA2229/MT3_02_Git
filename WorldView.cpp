#include "WorldView.h"

WorldView::WorldView(Affine affine){

	affine_ = affine;

	worldMatrix_ = {};

	worldViewprojectioinMatrix_ = {};

}

WorldView::~WorldView()
{
}

void WorldView::MakeAffineMatrix()
{
	worldMatrix_ = MyFunction::SRTAffineMatrix(affine_);
}

void WorldView::MakeWorldViewProjectionMatrix(const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix){

	worldViewprojectioinMatrix_ = MyFunction::Multiply(worldMatrix_, MyFunction::Multiply(viewMatrix, projectionMatrix));

}

Matrix4x4 WorldView::GetViewProjectionMatrix()
{
	return worldViewprojectioinMatrix_;
}
