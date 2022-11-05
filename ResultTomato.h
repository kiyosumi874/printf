#pragma once

class ResultTomato : public ModelBase, public Component
{
public:
    ResultTomato();
    ~ResultTomato();

    void Start()  override;     // コンストラクタの後に1回のみ呼ばれる処理
    void Update() override;     // 更新処理
    void Draw()   override;     // 描画処理

    void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale, int index);        // 初期化処理

private:

    enum MoveState
    {
        LEFT_QUAD_VERSION_0,    // 左への二次関数を使った動き1
        RIGHT_QUAD_VERSION_0,   // 右への二次関数を使った動き1
        LEFT_QUAD_VERSION_1,    // 左への二次関数を使った動き2
        RIGHT_QUAD_VERSION_1,   // 右への二次関数を使った動き2
        LEFT_QUAD_VERSION_2,    // 左への二次関数を使った動き3
        RIGHT_QUAD_VERSION_2,   // 右への二次関数を使った動き3
        LEFT_UPPER,             // 左上への動き
        RIGHT_UPPER,            // 右上への動き
        FALL                    // 上から下への動き
    };

    VECTOR m_velocity;  // 速度

    int m_index;        // 番号

    float m_gravity;    // 重力
    float m_deg;        // 角度
    float m_rad;        // ラジアン

    void LEFTQUAD();
};