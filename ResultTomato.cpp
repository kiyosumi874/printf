#include "pch.h"
#include "ResultTomato.h"
#include "Transform.h"

// コンストラクタ
ResultTomato::ResultTomato()
{
    m_velocity = VGet(0.0f, 0.0f, 0.0f);

    m_gravity = 9.80665f;
    m_deg = 30.0f;
    m_rad = m_deg * (DX_PI_F / 180.0f);
}

// デストラクタ
ResultTomato::~ResultTomato()
{
}


void ResultTomato::Start()
{
}

// 更新処理
void ResultTomato::Update()
{
    m_var.pos.x += 0.1f;
    if (m_var.pos.x > 30.0f)
    {
        m_var.pos.x = 0.0f;
    }
    LEFTQUAD();

    MV1SetPosition(m_var.handle, m_var.pos);
}

// 描画処理
void ResultTomato::Draw()
{
    MV1DrawModel(m_var.handle);
    printbDX("tomatoX:%5.2f", m_var.pos.x);
    printbDX("tomatoY:%5.2f\n", m_var.pos.y);
}

// 初期化処理
void ResultTomato::Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale)
{
    m_var.Init(MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::Tomato)), pos, rotate, scale);

    // 3Dモデルの設定
    MV1SetPosition(m_var.handle, m_var.pos);
    MV1SetRotationXYZ(m_var.handle, m_var.rotate);
    MV1SetScale(m_var.handle, m_var.scale);
}

void ResultTomato::LEFTQUAD()
{
    // 二次関数 y = a(x - p)^2 + q

    auto sub = m_var.pos.x - 3;
    m_var.pos.y = (-2 * (sub * sub)) + 1;
}
