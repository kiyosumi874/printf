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