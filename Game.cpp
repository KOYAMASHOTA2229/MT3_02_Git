#include "Game.h"
#include <Novice.h>
#include <imgui.h>
#define GRAY 0xAAAAAAFF

Game::Game(){

	worldAffine_ = {
		{1.0f,1.0f,1.0f},
		{0,0,0},
		{0,0,0},
	};

	world_ = new WorldView(worldAffine_);

	cameraAffine_ = {
		{ 1.0f,1.0f,1.0f },
		{ 0.26f,0.0f,0.0f },
		{ 0.0f,1.9f,-6.49f }
	};

	camera_ = new Camera(cameraAffine_);
	
	triangle_.vertices[0] = { -1.0f,0.0f,0.0f };
	triangle_.vertices[1] = { 0.0f,1.0f,0.0f };
	triangle_.vertices[2] = { 1.0f,0.0f,0.0f };

	segment_ = {
		{0.0f,0.5f,-1.0f},
		{0.0f,0.5f, 2.0f},
	};

}

Game::~Game(){
	delete world_, camera_;
}

void Game::Update(){

	world_->MakeAffineMatrix();

	camera_->MakeAffineMatrix();

	camera_->MakeViewMatrix();

	camera_->MakeProjectionMatrix();

	world_->MakeWorldViewProjectionMatrix(camera_->GetViewMatrix(), camera_->GetProjectionMatrix());

	camera_->MakeViewportMatrix();

	Game::CheckIsCollision();



}

void Game::CheckIsCollision() {

	
	if (MyFunction::IsCollision(triangle_, segment_)) {

		
		lineColor_ = RED;
	}
	else {
		
		lineColor_ = WHITE;
	}

}

void Game::DrawDebugText()
{
	ImGui::Begin("DebugWindow");
	ImGui::DragFloat3("triangle.v0", &triangle_.vertices[0].x, 0.01f);
	ImGui::DragFloat3("triangle.v1", &triangle_.vertices[1].x, 0.01f);
	ImGui::DragFloat3("triangle.v2", &triangle_.vertices[2].x, 0.01f);
	ImGui::DragFloat3("segment origin", &segment_.origin.x, 0.01f);
	ImGui::DragFloat3("segment diff", &segment_.diff.x, 0.01f);
	ImGui::End();
}

void Game::DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 screenVertices[3];

	for (int32_t i = 0; i < 3; i++) {
		Vector3 ndcVertex = MyFunction::Transform(triangle.vertices[i], viewProjectionMatrix);
		screenVertices[i] = MyFunction::Transform(ndcVertex, viewportMatrix);
	}

	Novice::DrawTriangle(
		int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y),
		int(screenVertices[2].x), int(screenVertices[2].y), color, kFillModeWireFrame
	);
}


void Game::DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color){

	const float kGirdHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGirdEvery = (kGirdHalfWidth * 2.0f) / float(kSubdivision);

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		float positionX = -kGirdHalfWidth + (xIndex * kGirdEvery);

		Vector3 start = { positionX, 0.0f, -kGirdHalfWidth };
		Vector3 end = { positionX, 0.0f, kGirdHalfWidth };

		Vector3 screenStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, positionX == 0.0f ? BLACK : color);
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		float positionZ = -kGirdHalfWidth + (zIndex * kGirdEvery);

		Vector3 start = { -kGirdHalfWidth, 0.0f, positionZ };
		Vector3 end = { kGirdHalfWidth, 0.0f, positionZ };

		Vector3 screenStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, positionZ == 0.0f ? BLACK : color);
	}

}

void Game::DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color){

	const uint32_t kSubdivision = 10; 
	const float kLonEvery = (2.0f * float(M_PI)) / kSubdivision; 
	const float kLatEvery = float(M_PI) / kSubdivision;

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex;
		float nextLat = lat + kLatEvery;

		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; 
			float nextLon = lon + kLonEvery; 

			Vector3 a = {
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lon)
			};
			Vector3 b = {
				sphere.center.x + sphere.radius * cosf(nextLat) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(nextLat),
				sphere.center.z + sphere.radius * cosf(nextLat) * sinf(lon)
			};
			Vector3 c = {
				sphere.center.x + sphere.radius * cosf(nextLat) * cosf(nextLon),
				sphere.center.y + sphere.radius * sinf(nextLat),
				sphere.center.z + sphere.radius * cosf(nextLat) * sinf(nextLon)
			};

			Vector3 ScreenA = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 ScreenB = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);
			Vector3 ScreenC = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);

			Novice::DrawLine((int)ScreenA.x, (int)ScreenA.y, (int)ScreenB.x, (int)ScreenB.y, color);

			Novice::DrawLine((int)ScreenB.x, (int)ScreenB.y, (int)ScreenC.x, (int)ScreenC.y, color);
		}
	}

}

void Game::DrawPlane(const Plane& plane, Matrix4x4 viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 center = MyFunction::Multiply(plane.distance, plane.normal);

	Vector3 perpendiculars[4];
	perpendiculars[0] = MyFunction::Normalize(MyFunction::Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	perpendiculars[2] = MyFunction::Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; index++) {
		Vector3 extend = MyFunction::Multiply(2.0f, perpendiculars[index]);
		Vector3 point = MyFunction::Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	///pointsをそれぞれ結んで、DrawLineで平面を描画する
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[3].x), int(points[3].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[3].x), int(points[3].y), color);
}

void Game::Draw()
{

	uint32_t gridColor = GRAY;
	uint32_t triangleColor = WHITE;

	Game::DrawDebugText();

	Game::DrawGrid(world_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), gridColor);

	Game::DrawTriangle(triangle_, world_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), triangleColor);

	Vector3 start = Transform(Transform(segment_.origin, world_->GetViewProjectionMatrix()), camera_->GetViewportMatrix());

	Vector3 end = Transform(Transform(Add(segment_.origin, segment_.diff), world_->GetViewProjectionMatrix()), camera_->GetViewportMatrix());

	Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), lineColor_);

}

void Game::Main(){

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Game::Update();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Game::Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

}
