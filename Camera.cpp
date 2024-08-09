#include "Camera.h"

Camera::Camera(Affine affine) {

	affine_ = affine;

	cameraWorldMatrix_ = {};

	viewMatrix_ = {};

	projectionMatrix_ = {};

	viewportMatrix_ = {};

}

Camera::~Camera() {}

void Camera::MakeAffineMatrix(Affine affine) {

	cameraWorldMatrix_ = MyFunction::STRAffineMatrix(affine);

}

void Camera::MakeViewMatrix() {

	viewMatrix_ = MyFunction::Inverse(cameraWorldMatrix_);

}

void Camera::MakeProjectionMatrix() {

	projectionMatrix_ = MyFunction::MakePerspectiveFovMatrix(0.45f, kWindowWidth_ / kWindowHeight_, 0.1f, 100.0f);

}

void Camera::MakeViewportMatrix() {

	viewportMatrix_ = MyFunction::ViewportMatrix(0, 0, kWindowWidth_, kWindowHeight_, 0.0f, 1.0f);

}

Matrix4x4 Camera::GetViewMatrix() { return viewMatrix_; }

Matrix4x4 Camera::GetProjectionMatrix() { return projectionMatrix_; }

Matrix4x4 Camera::GetViewportMatrix() { return viewportMatrix_; }

float Camera::GetKWindowWidth()
{
	return kWindowWidth_;
}

float Camera::GetKWindowHeight()
{
	return kWindowHeight_;
}
