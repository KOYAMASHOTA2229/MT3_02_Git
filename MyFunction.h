#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include "ObjectInfo.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>

class MyFunction {

public:

	static float cot(float x);

	static Vector3 Perpendicular(const Vector3& vector);


	static Vector3 Add(const Vector3& v1, const Vector3& v2);

	static Vector3 Subtract(const Vector3& v1, const Vector3& v2);

	static Vector3 Multiply(float scalar, const Vector3& v2);

	static float Length(const Vector3& v);

	static float Dot(const Vector3& v1, const Vector3& v2);

	static Vector3 Normalize(const Vector3& v);

	static Vector3 Cross(const Vector3& v1, const Vector3& v2);

	static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	static Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	static Matrix4x4 MakeRotateXMatrix(float radian);

	static Matrix4x4 MakeRotateYMatrix(float radian);

	static Matrix4x4 MakeRotateZMatrix(float radian);

	static Matrix4x4 MakeRotateMatrix(const Vector3& radian);

	static Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	static Matrix4x4 AffineMatrix(const Affine& affine);

	static Matrix4x4 Inverse(const Matrix4x4& m);

	static Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	static Matrix4x4 ViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

	static Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	static bool IsCollision(const AABB& aabb1, const AABB& aabb2);

};

