#include <Novice.h>
#include <Game.h>
#include <Camera.h>

const char kWindowTitle[] = "GC2B_06_コヤマ_ショウタ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, (int)Camera::GetKWindowWidth(), (int)Camera::GetKWindowHeight());

	Game* game = new Game();
	
	game->Main();
	
	// ライブラリの終了
	Novice::Finalize();
	delete game;
	return 0;

}
