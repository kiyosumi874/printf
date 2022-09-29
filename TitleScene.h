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
	void InitLogo();
	void InitTransitionButton();
	void InitGradation();

	void TermObject(); // オブジェクトの解放
	void UpdateObject(); // オブジェクトの更新
	void DrawObject(); // オブジェクトの描画

	enum ModelName
	{
		Ground,
		TomatoWall1,
		TomatoWall2,
		TomatoWall3
	};

	void InitModel();   // 3Dモデルの初期化
	void UpdateModel(); // 3Dモデルの更新
	void DrawModel();   // 3Dモデルの描画
	vector<int> m_models;
};