#include "Game.h"
#include <Novice.h>
#include <imgui.h>

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

	segment_ = {
		{-2.0f,-1.0f,0.0f}, 
		{ 3.0f, 2.0f,2.0f},
	};

	point_ = { -1.5f,0.6f,0.6f };

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

void Game::Main(){

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	uint32_t gridColor_ = 0xAAAAAAFF;

	uint32_t sphereColor[2];
	sphereColor[0] = RED;
	sphereColor[1] = BLACK;

	Vector3 project = { 0.0f };
	Vector3 closestPoint = { 0.0f };

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


		project = MyFunction::Project(MyFunction::Subtract(point_, segment_.origin), segment_.diff);
	
		closestPoint = MyFunction::ClosestPoint(point_, segment_);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//デバッグテキストの描画
		ImGui::Begin("DebugWindow");
		ImGui::DragFloat3("Point", &point_.x, 0.01f);
		ImGui::DragFloat3("Segment Origin", &segment_.origin.x, 0.01f);
		ImGui::DragFloat3("Segment Diff", &segment_.diff.x, 0.01f);
		ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::End();

		Game::DrawGrid(world_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), gridColor_);

		Vector3 start = Transform(Transform(segment_.origin, world_->GetViewProjectionMatrix()), camera_->GetViewportMatrix());
		
		Vector3 end = Transform(Transform(Add(segment_.origin, segment_.diff), world_->GetViewProjectionMatrix()), camera_->GetViewportMatrix());
		
		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);

		Sphere pointSphere = { point_,0.01f };
		Sphere closestPointSphere = { closestPoint,0.01f };
		
		Game::DrawSphere(pointSphere, world_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), sphereColor[0]);
		Game::DrawSphere(closestPointSphere, world_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), sphereColor[1]);

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
