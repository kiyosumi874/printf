#include "pch.h"
#include "DebugDraw.h"

// ���[���h���_�𒆐S�ɁA�c��groundSize�̑傫��
// divideNum�������ꂽ�O���b�h����`�悷��
void DrawGrid(float groundSize, int divideNum)
{
	VECTOR L_start, L_end;						// �����̎n�܂�ƏI���̍��W
	int L_lineColor = GetColor(0, 128, 0);		// ���ΐF
	L_start = L_end = VGet(0.0f, 0.0f, 0.0f);	// ������

	float L_halfWidth = groundSize * 0.5f;				// �O���b�h�������������̕�
	float L_addWidth = groundSize / (float)divideNum;	// �O���b�h����������

	// �c��������
	L_start.z = -L_halfWidth;
	L_end.z = L_halfWidth;
	for (auto ix = 0; ix < divideNum + 1; ix++)
	{
		L_start.x = L_end.x = -L_halfWidth + ix * L_addWidth;
		DrawLine3D(L_start, L_end, L_lineColor);
	}

	// ����������
	L_start.x = -L_halfWidth;
	L_end.x = L_halfWidth;
	for (auto iz = 0; iz < divideNum + 1; iz++)
	{
		L_start.z = L_end.z = -L_halfWidth + iz * L_addWidth;
		DrawLine3D(L_start, L_end, L_lineColor);
	}
}
