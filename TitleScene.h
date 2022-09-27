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
	enum ImageName
	{
		Logo,
		TransitionButton,
		Gradation
	};

	struct ImageVar
	{
		int modelHandle;
		int x;
		int y;
		int width;
		int height;
		float alpha;
	};

	enum ModelName
	{
		Ground,
		TomatoWall1,
		TomatoWall2,
		TomatoWall3
	};

	void InitImage(); // 画像の初期化
	void UpdateImage(); // 画像の更新
	void DrawImage(); // 画像の描画
	vector<int> m_images;

	void InitModel(); // 3Dモデルの初期化
	void UpdateModel(); // 3Dモデルの更新
	void DrawModel(); // 3Dモデルの描画
	vector<int> m_models;
};
