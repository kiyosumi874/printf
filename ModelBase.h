#pragma once
#include "DxLib.h"

class ModelBase
{
public:
	struct ModelVar
	{
		int handle;
		VECTOR pos;
		VECTOR rotate;
		VECTOR scale;

		// ƒƒ“ƒo•Ï”‚Ì‰Šú‰»
		void Init(int handle, const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale)
		{
			this->handle = handle;
			this->pos = pos;
			this->rotate = rotate;
			this->scale = scale;
		}
	};

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
	ModelVar m_var;
};