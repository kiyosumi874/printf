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

		// ƒƒ“ƒo•Ï”‚Ì‰Šú‰»
		void InitImageVar(int handle, int x, int y, int width, int height, float alpha)
		{
			this->handle = handle;
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
			this->alpha = alpha;
		}
	};

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
	ImageVar m_var;
};