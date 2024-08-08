#pragma once
#include "MyFunction.h"

class Camera:public MyFunction{

public:

	Camera(Affine affine);

	~Camera();

	void MakeAffineMatrix();

	void MakeViewMatrix();

	void MakeProjectionMatrix();

	void MakeViewportMatrix();

public:

	Matrix4x4 GetViewMatrix();
	
	Matrix4x4 GetProjectionMatrix();

	Matrix4x4 GetViewportMatrix();

	static float GetKWindowWidth();

	static float GetKWindowHeight();

private:

	Affine affine_;

	Matrix4x4 cameraWorldMatrix_;

	Matrix4x4 viewMatrix_;

	Matrix4x4 projectionMatrix_;

	Matrix4x4 viewportMatrix_;

	static inline const float kWindowWidth_ = 1280.0f;

	static inline const float kWindowHeight_ = 720.0f;

};

