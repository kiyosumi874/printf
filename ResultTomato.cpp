#include "pch.h"
#include "ResultTomato.h"
#include "Transform.h"

// コンストラクタ
ResultTomato::ResultTomato()
{
    m_velocity = VGet(0.0f, 0.0f, 0.0f);

    m_gravity = 9.80665f;
    m_deg = 30.0f;
    m_index = 0;
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
    m_var.pos.x += m_deg;
    if (m_var.pos.x > 50.0f)
    {
        m_var.pos.x = -49.9f;
        m_var.pos.z = -20.0f;
    }
    if (m_var.pos.x < -50.0f)
    {
        m_var.pos.x = 49.9f;
        m_var.pos.z = -20.0f;
    }
    m_var.pos.z -= 0.07f;
    LEFTQUAD();

    MV1SetPosition(m_var.handle, m_var.pos);
}

// 描画処理
void ResultTomato::Draw()
{
    MV1DrawModel(m_var.handle);
#ifndef _DEBUG

#endif // !_DEBUG
    printfDx("tomato index:%d", m_index);
    printfDx("posX:%f", m_var.pos.x);
    printfDx("posY:%f\n", m_var.pos.y);
}

// 初期化処理
void ResultTomato::Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale, int index)
{
    m_var.Init(MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::Tomato)), pos, rotate, scale);

    // 3Dモデルの設定
    MV1SetPosition(m_var.handle, m_var.pos);
    MV1SetRotationXYZ(m_var.handle, m_var.rotate);
    MV1SetScale(m_var.handle, m_var.scale);

    m_index = index;
    switch (m_index)
    {
    case 0:
        m_deg = 0.1f;
        m_var.pos.x = -50.0f;
        break;
    case 1:
        m_deg = 0.2f;
        m_var.pos.x = -30.0f;
        break;
    case 2:
        m_deg = 0.3f;
        m_var.pos.x = -10.0f;
        break;
    case 3:
        m_deg = -0.1f;
        m_var.pos.x = 30.0f;
        break;
    case 4:
        m_deg = -0.2f;
        m_var.pos.x = 10.0f;
        break;
    case 5:
        m_deg = -0.3f;
        m_var.pos.x = 50.0f;
        break;
    default:
        break;
    }
}

void ResultTomato::LEFTQUAD()
{
    // 二次関数 y = a(x - p)^2 + q
    if (m_index > 2)
    {
        auto sub = (m_var.pos.x - 20) / 5;
        m_var.pos.y = (1 * (sub * sub)) + 2;
    }
    else
    {
        auto sub = (m_var.pos.x + 20) / 5;
        m_var.pos.y = (1 * (sub * sub)) + 2;
    }
}
