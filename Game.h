#pragma once
#include "MyFunction.h"
#include "Camera.h"
#include "WorldView.h"

class Game:public MyFunction{

public:

	Game();

	~Game();

	void CheckIsCollision();

	void MoveScale();

	void MoveRotation();

	void CameraController();

	void Update();

	void DrawDebugText();

	void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

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

	Segment segment_;

	AABB aabb_;

	uint32_t aabbColor_;

	int prevMouseX_;
	int prevMouseY_;

	int mouseX_;
	int mouseY_;

};

