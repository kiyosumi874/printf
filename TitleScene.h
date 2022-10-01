#pragma once
#include <vector>

using namespace std;

class TitleScene : public Scene
{
public:
	TitleScene() = delete; // デフォルトコンストラクタは使わない
	TitleScene(const MODE& mode); // コンストラクタ
	~TitleScene() override; // デストラクタ

	TAG_SCENE Update() override; // 更新
	void Draw() override; // 描画

private:
	// オブジェクトの初期化
	void InitObject();
	void InitSkyDomeModel();
	void InitGroundModel();
	void InitTomatoWallModel();
	void InitLogoUI();
	void InitTransitionButtonUI();
	void InitGradationUI();

	void TermObject(); // オブジェクトの解放
	void UpdateObject(); // オブジェクトの更新
	void DrawObject(); // オブジェクトの描画
};