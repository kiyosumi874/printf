#pragma once
#include "pch.h"
const float MIN_FRAME_TIME = 1.0f / 60.0f;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;
const int COLOR_BIT_DEPTH = 16;

struct Pos
{
	float x;
	float y;

	void operator+=(const Pos& rhs)
	{
		x = x + rhs.x;
		y = y + rhs.y;
	}

	void operator*=(const Pos& rhs)
	{
		x = x * rhs.x;
		y = y * rhs.y;
	}

	void operator*=(const float rhs)
	{
		x = x * rhs;
		y = y * rhs;
	}
};

struct Size
{
	int w;
	int h;
};

static void printbDX(const char* str, unsigned int v)
{
	unsigned int mask = (int)1 << (sizeof(v) * 8 - 1);
	printfDx(str);
	do printfDx(mask & v ? "1" : "0");
	while (mask >>= 1);
	printfDx("\n");
}