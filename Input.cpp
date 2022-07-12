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
		initKeyCode[CONTROLLER].push_back(PAD_ID_DOWN);
		initKeyCode[CONTROLLER].push_back(PAD_ID_LEFT);
		initKeyCode[CONTROLLER].push_back(PAD_ID_RIGHT);
		initKeyCode[CONTROLLER].push_back(PAD_ID_UP);
		initKeyCode[CONTROLLER].push_back(PAD_ID_A);
		initKeyCode[CONTROLLER].push_back(PAD_ID_B);
		initKeyCode[CONTROLLER].push_back(PAD_ID_X);
		initKeyCode[CONTROLLER].push_back(PAD_ID_Y);
		initKeyCode[CONTROLLER].push_back(PAD_ID_L);
		initKeyCode[CONTROLLER].push_back(PAD_ID_R);
		initKeyCode[CONTROLLER].push_back(PAD_ID_BACK);
		initKeyCode[CONTROLLER].push_back(PAD_ID_START);
	}
	
	
	for (int i = 0; i < BUTTON_ID_MAX; i++)
	{
		m_keys[i].keyCode[KEYBOARD] = initKeyCode[KEYBOARD][i];
		m_keys[i].pressCount[KEYBOARD] = -1;
		if (m_joyPadNum > 0)
		{
			m_keys[i].keyCode[CONTROLLER] = initKeyCode[CONTROLLER][i];
			m_keys[i].pressCount[CONTROLLER] = -1;
		}
		else
		{
			m_keys[i].keyCode[CONTROLLER] = '\0';
			m_keys[i].pressCount[CONTROLLER] = -1;
		}
	}
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
			if (GetJoypadInputState(DX_INPUT_PAD1) & m_input->m_keys[i].keyCode[CONTROLLER])
			{
				m_input->m_keys[i].pressCount[CONTROLLER] = max(++m_input->m_keys[i].pressCount[CONTROLLER], 1);
			}
			else
			{
				m_input->m_keys[i].pressCount[CONTROLLER] = min(--m_input->m_keys[i].pressCount[CONTROLLER], 0);
			}
		}
		
	}
}
