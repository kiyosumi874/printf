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
    PAD_ID_DOWN = (0x0001),// ���`�F�b�N�}�X�N
    PAD_ID_LEFT = (0x0002),// ���`�F�b�N�}�X�N
    PAD_ID_RIGHT = (0x0004),// ���`�F�b�N�}�X�N
    PAD_ID_UP = (0x0008),// ���`�F�b�N�}�X�N
    PAD_ID_A = (0x0010),// �`�{�^���`�F�b�N�}�X�N
    PAD_ID_B = (0x0020),// �a�{�^���`�F�b�N�}�X�N
    PAD_ID_X = (0x0040),// �w�{�^���`�F�b�N�}�X�N
    PAD_ID_Y = (0x0080),// �x�{�^���`�F�b�N�}�X�N
    PAD_ID_L = (0x0100),// �k�{�^���`�F�b�N�}�X�N
    PAD_ID_R = (0x0200),// �q�{�^���`�F�b�N�}�X�N
    PAD_ID_BACK = (0x0400),// BACK
    PAD_ID_START = (0x0800)	 // �r�s�`�q�s�{�^���`�F�b�N�}�X�N

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
        int keyCode[3]; // VK_SHIFT�Ƃ�'A'�̂��h
        int pressCount[3]; // ���
    };
    KeyInformation m_keys[BUTTON_ID_MAX];
    int m_analogStickX[2];
    int m_analogStickY[2];

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

    /// <summary>
    /// �X�e�B�b�N�̖����͈͂�ݒ肷��
    /// </summary>
    /// <param name="deadZone">0.0�`1.0(�f�t�H���g��0.35)</param>
    static void SetStickDeadZone(const double deadZone)
    {
        SetJoypadDeadZone(DX_INPUT_PAD1, deadZone);
        SetJoypadDeadZone(DX_INPUT_PAD2, deadZone);
    }

    /// <summary>
    /// 1P�R���g���[���[��U��������
    /// </summary>
    /// <param name="power">�U���̋���(0�`1000)</param>
    /// <param name="time">�U�����鎞��(-1��StopVibration1P���Ă΂��܂ŐU������)</param>
    /// <param name="effectIndex">�U�������郂�[�^�[�ԍ�(�C�ɂ���ł�����)</param>
    static void StartVibration1P(const int power, const int time, int effectIndex = -1)
    {
        StartJoypadVibration(DX_INPUT_PAD1, power, time, effectIndex);
    }

    /// <summary>
    /// 2P�R���g���[���[��U��������
    /// </summary>
    /// <param name="power">�U���̋���(0�`1000)</param>
    /// <param name="time">�U�����鎞��(-1��StopVibration2P���Ă΂��܂ŐU������)</param>
    /// <param name="effectIndex">�U�������郂�[�^�[�ԍ�(�C�ɂ���ł�����)</param>
    static void StartVibration2P(const int power, const int time, int effectIndex = -1)
    {
        StartJoypadVibration(DX_INPUT_PAD2, power, time, effectIndex);
    }

    /// <summary>
    /// 1P�R���g���[���[�̐U�����~�߂�
    /// </summary>
    /// <param name="effectIndex">�U�����~�߂郂�[�^�[�ԍ�(StartVibration1P�Ŏw�肵���l������)</param>
    static void StopVibration1P(int effectIndex = -1)
    {
        StopJoypadVibration(DX_INPUT_PAD1, effectIndex);
    }

    /// <summary>
    /// 2P�R���g���[���[�̐U�����~�߂�
    /// </summary>
    /// <param name="effectIndex">�U�����~�߂郂�[�^�[�ԍ�(StartVibration2P�Ŏw�肵���l������)</param>
    static void StopVibration2P(int effectIndex = -1)
    {
        StopJoypadVibration(DX_INPUT_PAD2, effectIndex);
    }

    /// <summary>
    /// 1P�R���g���[���[�̃X�e�B�b�N�̏�Ԃ��擾
    /// </summary>
    /// <param name="x">�������Q�Ƃ���x���擾���܂�(1000�`-1000)</param>
    /// <param name="y">�������Q�Ƃ���y���擾���܂�(1000�`-1000)</param>
    /// �����Ő��K�����Ă���(VNorm(VGet(x,y,1))�Ă���Ƃ��܂������C�����邼)
    static void GetAnalogStick1P(int& x, int& y)
    {
        x = m_input->m_analogStickX[0];
        y = m_input->m_analogStickY[0];
    }

    /// <summary>
    /// 2P�R���g���[���[�̃X�e�B�b�N�̏�Ԃ��擾
    /// </summary>
    /// <param name="x">�������Q�Ƃ���x���擾���܂�(1000�`-1000)</param>
    /// <param name="y">�������Q�Ƃ���y���擾���܂�(1000�`-1000)</param>
    /// �����Ő��K�����Ă���(VNorm(VGet(x,y,1))�Ă���Ƃ��܂������C�����邼)
    static void GetAnalogStick2P(int& x, int& y)
    {
        x = m_input->m_analogStickX[1];
        y = m_input->m_analogStickY[1];
    }

    static void Update();
    // 1P���������u��
    static bool IsDown1P(int buttonID) { return ((m_input->m_keys[buttonID].pressCount[KEYBOARD] == 1) || (m_input->m_keys[buttonID].pressCount[CONTROLLER_1P] == 1)); }
    // 1P�������Ă���Ƃ�
    static bool IsPress1P(int buttonID) { return m_input->m_keys[buttonID].pressCount[KEYBOARD] > 1 || m_input->m_keys[buttonID].pressCount[CONTROLLER_1P] > 1; }
    // 1P���������u��
    static bool IsUp1P(int buttonID) { return m_input->m_keys[buttonID].pressCount[KEYBOARD] == 0 || m_input->m_keys[buttonID].pressCount[CONTROLLER_1P] == 0; }
    // 1P�������Ă���Ƃ�
    static bool IsRelease1P(int buttonID) { return m_input->m_keys[buttonID].pressCount[KEYBOARD] < 0 || m_input->m_keys[buttonID].pressCount[CONTROLLER_1P] < 0; }


    // 2P���������u��
    static bool IsDown2P(int buttonID) { return m_input->m_keys[buttonID].pressCount[CONTROLLER_2P] == 1; }
    // 2P�������Ă���Ƃ�
    static bool IsPress2P(int buttonID) { return m_input->m_keys[buttonID].pressCount[CONTROLLER_2P] > 1; }
    // 2P���������u��
    static bool IsUp2P(int buttonID) { return m_input->m_keys[buttonID].pressCount[CONTROLLER_2P] == 0; }
    // 2P�������Ă���Ƃ�
    static bool IsRelease2P(int buttonID) { return m_input->m_keys[buttonID].pressCount[CONTROLLER_2P] < 0; }
};
