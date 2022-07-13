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
