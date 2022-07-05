#pragma once

enum ButtonID
{
    BUTTON_ID_DOWN,     // �\���L�[
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
    PAD_ID_DOWN =  (0x0001) ,// ���`�F�b�N�}�X�N
    PAD_ID_LEFT =  (0x0002)	,// ���`�F�b�N�}�X�N
    PAD_ID_RIGHT = (0x0004)	,// ���`�F�b�N�}�X�N
    PAD_ID_UP =    (0x0008)	,// ���`�F�b�N�}�X�N
    PAD_ID_A =     (0x0010)	,// �`�{�^���`�F�b�N�}�X�N
    PAD_ID_B =     (0x0020)	,// �a�{�^���`�F�b�N�}�X�N
    PAD_ID_X =     (0x0040)	,// �w�{�^���`�F�b�N�}�X�N
    PAD_ID_Y =     (0x0080)	,// �x�{�^���`�F�b�N�}�X�N
    PAD_ID_L =     (0x0100)	,// �k�{�^���`�F�b�N�}�X�N
    PAD_ID_R =     (0x0200)	,// �q�{�^���`�F�b�N�}�X�N
    PAD_ID_BACK =  (0x0400)	,// BACK
    PAD_ID_START = (0x0800)	 // �r�s�`�q�s�{�^���`�F�b�N�}�X�N

};
const int KEYBOARD = 0;
const int CONTROLLER = 1;
class Input
{
private:
    static Input* m_input;
    struct KeyInformation
    {
        int keyCode[2]; // VK_SHIFT�Ƃ�'A'�̂��h
        int pressCount[2]; // ���
    };
    KeyInformation m_keys[BUTTON_ID_MAX];
    int m_joyPadNum;
    Input();
    ~Input();
    

public:
    Input(const Input&) = delete; // �R�s�[�R���X�g���N�^�� delete �w��B
    Input& operator=(const Input&) = delete; // �R�s�[������Z�q�� delete �w��B
    Input(Input&&) = delete; // ���[�u�R���X�g���N�^�� delete �w��B
    Input& operator=(Input&&) = delete; // ���[�u������Z�q�� delete �w��B

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
    // �������u��
    static bool IsDown(int buttonID) { return ((m_input->m_keys[buttonID].pressCount[KEYBOARD] == 1) || (m_input->m_keys[buttonID].pressCount[CONTROLLER] == 1)); }
    // �����Ă���Ƃ�
    static bool IsPress(int buttonID) { return m_input->m_keys[buttonID].pressCount[KEYBOARD] > 1 || m_input->m_keys[buttonID].pressCount[CONTROLLER] > 1; }
    // �������u��
    static bool IsUp(int buttonID) { return m_input->m_keys[buttonID].pressCount[KEYBOARD] == 0 || m_input->m_keys[buttonID].pressCount[CONTROLLER] == 0; }
    // �����Ă���Ƃ�
    static bool IsRelease(int buttonID) { return m_input->m_keys[buttonID].pressCount[KEYBOARD] < 0 || m_input->m_keys[buttonID].pressCount[CONTROLLER] < 0; }


};
