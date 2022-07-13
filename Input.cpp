#include "pch.h"

Input* Input::m_input = nullptr;

Input::Input()
{
	m_joyPadNum = GetJoypadNum();
	std::vector<int> initKeyCode[2];
	initKeyCode[KEYBOARD].push_back(VK_DOWN);
	initKeyCode[KEYBOARD].push_back(VK_LEFT);
	initKeyCode[KEYBOARD].push_back(VK_RIGHT);
	initKeyCode[KEYBOARD].push_back(VK_UP);
	initKeyCode[KEYBOARD].push_back(static_cast<int>('X'));
	initKeyCode[KEYBOARD].push_back(static_cast<int>('V'));
	initKeyCode[KEYBOARD].push_back(static_cast<int>('Z'));
	initKeyCode[KEYBOARD].push_back(static_cast<int>('C'));
	initKeyCode[KEYBOARD].push_back(static_cast<int>('B'));
	initKeyCode[KEYBOARD].push_back(static_cast<int>('N'));
	initKeyCode[KEYBOARD].push_back(VK_ESCAPE);
	initKeyCode[KEYBOARD].push_back(VK_RETURN);

	if (m_joyPadNum > 0)
	{
		initKeyCode[CONTROLLER_1P].push_back(PAD_ID_DOWN);
		initKeyCode[CONTROLLER_1P].push_back(PAD_ID_LEFT);
		initKeyCode[CONTROLLER_1P].push_back(PAD_ID_RIGHT);
		initKeyCode[CONTROLLER_1P].push_back(PAD_ID_UP);
		initKeyCode[CONTROLLER_1P].push_back(PAD_ID_A);
		initKeyCode[CONTROLLER_1P].push_back(PAD_ID_B);
		initKeyCode[CONTROLLER_1P].push_back(PAD_ID_X);
		initKeyCode[CONTROLLER_1P].push_back(PAD_ID_Y);
		initKeyCode[CONTROLLER_1P].push_back(PAD_ID_L);
		initKeyCode[CONTROLLER_1P].push_back(PAD_ID_R);
		initKeyCode[CONTROLLER_1P].push_back(PAD_ID_BACK);
		initKeyCode[CONTROLLER_1P].push_back(PAD_ID_START);
	}

	if (m_joyPadNum > 0)
	{
		for (int i = 0; i < BUTTON_ID_MAX; i++)
		{
			m_keys[i].keyCode[KEYBOARD] = initKeyCode[KEYBOARD][i];
			m_keys[i].pressCount[KEYBOARD] = -1;
			m_keys[i].keyCode[CONTROLLER_1P] = initKeyCode[CONTROLLER_1P][i];
			m_keys[i].pressCount[CONTROLLER_1P] = -1;
			m_keys[i].keyCode[CONTROLLER_2P] = initKeyCode[CONTROLLER_1P][i];
			m_keys[i].pressCount[CONTROLLER_2P] = -1;
		}
	}
	else
	{
		for (int i = 0; i < BUTTON_ID_MAX; i++)
		{
			m_keys[i].keyCode[KEYBOARD] = initKeyCode[KEYBOARD][i];
			m_keys[i].pressCount[KEYBOARD] = -1;
			m_keys[i].keyCode[CONTROLLER_1P] = '\0';
			m_keys[i].pressCount[CONTROLLER_1P] = -1;
			m_keys[i].keyCode[CONTROLLER_2P] = '\0';
			m_keys[i].pressCount[CONTROLLER_2P] = -1;
		}
	}
	_RPTF1(_CRT_WARN, "connectGamePad:%d\n", m_joyPadNum);
}

Input::~Input()
{
}

void Input::Update()
{

	for (int i = 0; i < BUTTON_ID_MAX; i++)
	{
		// GetAsyncKeyStateは押しているとき最上位ビットが立つ
		if (GetAsyncKeyState(m_input->m_keys[i].keyCode[KEYBOARD]) & 0x8000) // 0x8000はshortの最上位ビットが立っていることを表す
		{
			m_input->m_keys[i].pressCount[KEYBOARD] = max(++m_input->m_keys[i].pressCount[KEYBOARD], 1);
		}
		else
		{
			m_input->m_keys[i].pressCount[KEYBOARD] = min(--m_input->m_keys[i].pressCount[KEYBOARD], 0);
		}

		if (m_input->m_joyPadNum > 0)
		{
			if (GetJoypadInputState(DX_INPUT_PAD1) & m_input->m_keys[i].keyCode[CONTROLLER_1P])
			{
				m_input->m_keys[i].pressCount[CONTROLLER_1P] = max(++m_input->m_keys[i].pressCount[CONTROLLER_1P], 1);
			}
			else
			{
				m_input->m_keys[i].pressCount[CONTROLLER_1P] = min(--m_input->m_keys[i].pressCount[CONTROLLER_1P], 0);
			}

			if (GetJoypadInputState(DX_INPUT_PAD2) & m_input->m_keys[i].keyCode[CONTROLLER_2P])
			{
				m_input->m_keys[i].pressCount[CONTROLLER_2P] = max(++m_input->m_keys[i].pressCount[CONTROLLER_2P], 1);
			}
			else
			{
				m_input->m_keys[i].pressCount[CONTROLLER_2P] = min(--m_input->m_keys[i].pressCount[CONTROLLER_2P], 0);
			}
		}

	}
}
