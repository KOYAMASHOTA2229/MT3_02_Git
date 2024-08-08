#pragma once
#include "MyFunction.h"

class WorldView:public MyFunction{

public:

	WorldView(Affine affine);

	~WorldView();

	void MakeAffineMatrix();

	void MakeWorldViewProjectionMatrix(const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix);

public:

	Matrix4x4 GetViewProjectionMatrix();

private:

	Affine affine_;
	
	Matrix4x4 worldMatrix_;

	Matrix4x4 worldViewprojectioinMatrix_;

};

