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

		// メンバ変数の初期化
		void Init(int handle, const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale)
		{
			this->handle = handle;
			this->pos = pos;
			this->rotate = rotate;
			this->scale = scale;
		}
	};
protected:
	ModelVar m_var;
};