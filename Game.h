#pragma once
#include "MyFunction.h"
#include "Camera.h"
#include "WorldView.h"

class Game:public MyFunction{

public:

	Game();

	~Game();

	void CheckIsCollision();

	void Update();

	void DrawDebugText();

	void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	void DrawPlane(const Plane& plane, Matrix4x4 viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	void Draw();

	void Main();

private:

	Affine worldAffine_;

	WorldView* world_;

	Affine cameraAffine_;

	Camera* camera_;

	Sphere sphere_;

	uint32_t sphereColor_;

	Plane plane_;

};

