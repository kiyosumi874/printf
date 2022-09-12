#include "pch.h"
#include "SkyDome.h"

int g_skyDomeHandle = -1;

void InitSkyDome()
{
	g_skyDomeHandle = MV1LoadModel("data/Skydome_T2/Dome_T201.pmx");
	MV1SetScale(g_skyDomeHandle, VGet(1.0f, 1.0f, 1.0f));
	MV1SetPosition(g_skyDomeHandle, VGet(0.0f, 0.0f, 0.0f));
}

void DrawSkyDome()
{
	MV1DrawModel(g_skyDomeHandle);
}
