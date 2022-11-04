/* プリコンパイル済みヘッダー */
// 全てのヘッダーをここに書き込む。使うときはpch.hをインクルードする
#pragma once

/* 外部参照 */
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <Windows.h>
#include <vector>
#include <mmsystem.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <array>

#pragma comment(lib,"winmm.lib")

/* App */
#include "App.h"

/* Common */
#include "Common.h"

/* System */
#include "Input.h"
#include "Fps.h"
#include "StopWatch.h"

/* Scene */
#include "Scene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "SceneManager.h"

/* Effect */
#include "HitEffect.h"

// Object
#include "Object.h"

// Assets
#include "Sound.h"
#include "AssetManager.h"

// Title
// UI
#include "Logo.h"
#include "TransitionButton.h"
#include "Gradation.h"

// Model
/* title */
#include "TitleTomatoWall.h"
#include "TitleGround.h"
#include "SkyDome.h"
/* play */
#include "PlayGround.h"
#include "BasketController.h"
//result
#include "ResultGround.h"
