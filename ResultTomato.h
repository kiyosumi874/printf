#pragma once

class ResultTomato : public ModelBase, public Component
{
public:
    ResultTomato();
    ~ResultTomato();

    void Start()  override;     // �R���X�g���N�^�̌��1��̂݌Ă΂�鏈��
    void Update() override;     // �X�V����
    void Draw()   override;     // �`�揈��

    void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale, int index);        // ����������

private:

    enum MoveState
    {
        LEFT_QUAD_VERSION_0,    // ���ւ̓񎟊֐����g��������1
        RIGHT_QUAD_VERSION_0,   // �E�ւ̓񎟊֐����g��������1
        LEFT_QUAD_VERSION_1,    // ���ւ̓񎟊֐����g��������2
        RIGHT_QUAD_VERSION_1,   // �E�ւ̓񎟊֐����g��������2
        LEFT_QUAD_VERSION_2,    // ���ւ̓񎟊֐����g��������3
        RIGHT_QUAD_VERSION_2,   // �E�ւ̓񎟊֐����g��������3
        LEFT_UPPER,             // ����ւ̓���
        RIGHT_UPPER,            // �E��ւ̓���
        FALL                    // �ォ�牺�ւ̓���
    };

    VECTOR m_velocity;  // ���x

    int m_index;        // �ԍ�

    float m_gravity;    // �d��
    float m_deg;        // �p�x
    float m_rad;        // ���W�A��

    void LEFTQUAD();
};