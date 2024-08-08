#pragma once
#include "MyFunction.h"
#include "Camera.h"
#include "WorldView.h"

class Game:public MyFunction{

public:

	Game();

	~Game();

	void Update();

	void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	void Main();

private:

	Affine worldAffine_;

	WorldView* world_;

	Affine cameraAffine_;

	Camera* camera_;

	Segment segment_;

	Vector3 point_;

};

