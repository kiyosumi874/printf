/* プリコンパイル済みヘッダー */
// 全てのヘッダーをここに書き込む。使うときはpch.hをインクルードする
#pragma once

/* 外部参照 */
#include <DxLib.h>
#include <Windows.h>
#include <vector>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

/* App */
#include "App.h"

/* Common */
#include "Common.h"

/* System */
#include "Input.h"
#include "Fps.h"

/* Scene */
#include "Scene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "SceneManager.h"