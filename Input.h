#pragma once

enum ButtonID
{
    BUTTON_ID_DOWN,     // 十字キー
    BUTTON_ID_LEFT,
    BUTTON_ID_RIGHT,
    BUTTON_ID_UP,
    BUTTON_ID_A,
    BUTTON_ID_B,
    BUTTON_ID_X,
    BUTTON_ID_Y,
    BUTTON_ID_L,
    BUTTON_ID_R,
    BUTTON_ID_BACK,
    BUTTON_ID_START,

    BUTTON_ID_MAX
};

enum PAD_ID
{
    PAD_ID_DOWN = (0x0001),// ↓チェックマスク
    PAD_ID_LEFT = (0x0002),// ←チェックマスク
    PAD_ID_RIGHT = (0x0004),// →チェックマスク
    PAD_ID_UP = (0x0008),// ↑チェックマスク
    PAD_ID_A = (0x0010),// Ａボタンチェックマスク
    PAD_ID_B = (0x0020),// Ｂボタンチェックマスク
    PAD_ID_X = (0x0040),// Ｘボタンチェックマスク
    PAD_ID_Y = (0x0080),// Ｙボタンチェックマスク
    PAD_ID_L = (0x0100),// Ｌボタンチェックマスク
    PAD_ID_R = (0x0200),// Ｒボタンチェックマスク
    PAD_ID_BACK = (0x0400),// BACK
    PAD_ID_START = (0x0800)	 // ＳＴＡＲＴボタンチェックマスク

};
const int KEYBOARD = 0;
const int CONTROLLER_1P = 1;
const int CONTROLLER_2P = 2;

class Input
{
private:
    static Input* m_input;
    struct KeyInformation
    {
        int keyCode[3]; // VK_SHIFTとか'A'のやつh
        int pressCount[3]; // 状態
    };
    KeyInformation m_keys[BUTTON_ID_MAX];
    int m_analogStickX[2];
    int m_analogStickY[2];

    int m_joyPadNum;
    Input();
    ~Input();


public:
    Input(const Input&) = delete; // コピーコンストラクタを delete 指定。
    Input& operator=(const Input&) = delete; // コピー代入演算子も delete 指定。
    Input(Input&&) = delete; // ムーブコンストラクタを delete 指定。
    Input& operator=(Input&&) = delete; // ムーブ代入演算子も delete 指定。

    static void GetInstance()
    {
        if (!m_input)
        {
            m_input = new Input;
        }
    }

    static void Terminate()
    {
        if (m_input)
        {
            delete m_input;
            m_input = nullptr;
        }

    }

    /// <summary>
    /// スティックの無効範囲を設定する
    /// </summary>
    /// <param name="deadZone">0.0～1.0(デフォルトは0.35)</param>
    static void SetStickDeadZone(const double deadZone)
    {
        SetJoypadDeadZone(DX_INPUT_PAD1, deadZone);
        SetJoypadDeadZone(DX_INPUT_PAD2, deadZone);
    }

    /// <summary>
    /// 1Pコントローラーを振動させる
    /// </summary>
    /// <param name="power">振動の強さ(0～1000)</param>
    /// <param name="time">振動する時間(-1でStopVibration1Pが呼ばれるまで振動する)</param>
    /// <param name="effectIndex">振動させるモーター番号(気にせんでもええ)</param>
    static void StartVibration1P(const int power, const int time, int effectIndex = -1)
    {
        StartJoypadVibration(DX_INPUT_PAD1, power, time, effectIndex);
    }

    /// <summary>
    /// 2Pコントローラーを振動させる
    /// </summary>
    /// <param name="power">振動の強さ(0～1000)</param>
    /// <param name="time">振動する時間(-1でStopVibration2Pが呼ばれるまで振動する)</param>
    /// <param name="effectIndex">振動させるモーター番号(気にせんでもええ)</param>
    static void StartVibration2P(const int power, const int time, int effectIndex = -1)
    {
        StartJoypadVibration(DX_INPUT_PAD2, power, time, effectIndex);
    }

    /// <summary>
    /// 1Pコントローラーの振動を止める
    /// </summary>
    /// <param name="effectIndex">振動を止めるモーター番号(StartVibration1Pで指定した値を入れる)</param>
    static void StopVibration1P(int effectIndex = -1)
    {
        StopJoypadVibration(DX_INPUT_PAD1, effectIndex);
    }

    /// <summary>
    /// 2Pコントローラーの振動を止める
    /// </summary>
    /// <param name="effectIndex">振動を止めるモーター番号(StartVibration2Pで指定した値を入れる)</param>
    static void StopVibration2P(int effectIndex = -1)
    {
        StopJoypadVibration(DX_INPUT_PAD2, effectIndex);
    }

    /// <summary>
    /// 1Pコントローラーのスティックの状態を取得
    /// </summary>
    /// <param name="x">引数を参照してxを取得します(1000～-1000)</param>
    /// <param name="y">引数を参照してyを取得します(1000～-1000)</param>
    /// 自分で正規化してけろ(VNorm(VGet(x,y,1))てするとうまくいく気がするぞ)
    static void GetAnalogStick1P(int& x, int& y)
    {
        x = m_input->m_analogStickX[0];
        y = m_input->m_analogStickY[0];
    }

    /// <summary>
    /// 2Pコントローラーのスティックの状態を取得
    /// </summary>
    /// <param name="x">引数を参照してxを取得します(1000～-1000)</param>
    /// <param name="y">引数を参照してyを取得します(1000～-1000)</param>
    /// 自分で正規化してけろ(VNorm(VGet(x,y,1))てするとうまくいく気がするぞ)
    static void GetAnalogStick2P(int& x, int& y)
    {
        x = m_input->m_analogStickX[1];
        y = m_input->m_analogStickY[1];
    }

    static void Update();
    // 1Pが押した瞬間
    static bool IsDown1P(int buttonID) { return ((m_input->m_keys[buttonID].pressCount[KEYBOARD] == 1) || (m_input->m_keys[buttonID].pressCount[CONTROLLER_1P] == 1)); }
    // 1Pが押しているとき
    static bool IsPress1P(int buttonID) { return m_input->m_keys[buttonID].pressCount[KEYBOARD] > 1 || m_input->m_keys[buttonID].pressCount[CONTROLLER_1P] > 1; }
    // 1Pが離した瞬間
    static bool IsUp1P(int buttonID) { return m_input->m_keys[buttonID].pressCount[KEYBOARD] == 0 || m_input->m_keys[buttonID].pressCount[CONTROLLER_1P] == 0; }
    // 1Pが離しているとき
    static bool IsRelease1P(int buttonID) { return m_input->m_keys[buttonID].pressCount[KEYBOARD] < 0 || m_input->m_keys[buttonID].pressCount[CONTROLLER_1P] < 0; }


    // 2Pが押した瞬間
    static bool IsDown2P(int buttonID) { return m_input->m_keys[buttonID].pressCount[CONTROLLER_2P] == 1; }
    // 2Pが押しているとき
    static bool IsPress2P(int buttonID) { return m_input->m_keys[buttonID].pressCount[CONTROLLER_2P] > 1; }
    // 2Pが離した瞬間
    static bool IsUp2P(int buttonID) { return m_input->m_keys[buttonID].pressCount[CONTROLLER_2P] == 0; }
    // 2Pが離しているとき
    static bool IsRelease2P(int buttonID) { return m_input->m_keys[buttonID].pressCount[CONTROLLER_2P] < 0; }
};
