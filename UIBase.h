#pragma once

class UIBase
{
public:
	struct ImageVar
	{
		int handle;
		int x;
		int y;
		int width;
		int height;
		float alpha;

		// メンバ変数の初期化
		void Init(int handle, int x, int y, int width, int height, float alpha)
		{
			this->handle = handle;
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
			this->alpha = alpha;
		}
	};

protected:
	ImageVar m_var;
};