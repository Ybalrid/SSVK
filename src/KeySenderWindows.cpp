#include "KeySenderWindows.hpp"
#ifdef _WIN32

using namespace SSVK;

KeySenderWindows::KeySenderWindows() : KeySender()
{
	os = MS_WINDOWS_WIN32;

	//Fill the winmap map :
	winmap[KC_A] = 'A';
	winmap[KC_B] = 'B';
	winmap[KC_C] = 'C';
	winmap[KC_D] = 'D';
	winmap[KC_E] = 'E';
	winmap[KC_F] = 'F';
	winmap[KC_G] = 'G';
	winmap[KC_H] = 'H';
	winmap[KC_I] = 'I';
	winmap[KC_J] = 'J';
	winmap[KC_K] = 'K';
	winmap[KC_L] = 'L';
	winmap[KC_M] = 'M';
	winmap[KC_N] = 'N';
	winmap[KC_O] = 'O';
	winmap[KC_P] = 'P';
	winmap[KC_Q] = 'Q';
	winmap[KC_R] = 'R';
	winmap[KC_S] = 'S';
	winmap[KC_T] = 'T';
	winmap[KC_U] = 'U';
	winmap[KC_V] = 'V';
	winmap[KC_W] = 'W';
	winmap[KC_X] = 'X';
	winmap[KC_Y] = 'Y';
	winmap[KC_Z] = 'Z';

	winmap[KC_CTRL] = VK_CONTROL;
	winmap[KC_ALT] = VK_MENU;
	winmap[KC_WIN] = VK_LWIN;
	winmap[KC_RETURN] = VK_RETURN;
	winmap[KC_DEL] = VK_DELETE;
	winmap[KC_SHIFT] = VK_LSHIFT;

	winmap[KC_0] = '0';
	winmap[KC_1] = '1';
	winmap[KC_2] = '2';
	winmap[KC_3] = '3';
	winmap[KC_4] = '4';
	winmap[KC_5] = '5';
	winmap[KC_6] = '6';
	winmap[KC_7] = '7';
	winmap[KC_8] = '8';
	winmap[KC_9] = '9';

	winmap[KC_UP] = VK_UP;
	winmap[KC_DOWN] = VK_DOWN;
	winmap[KC_LEFT] = VK_LEFT;
	winmap[KC_RIGHT] = VK_RIGHT;

	winmap[KC_TAB] = VK_TAB;
	winmap[KC_ESC] = VK_ESCAPE;

	winmap[KC_F1] = VK_F1;
	winmap[KC_F2] = VK_F2;
	winmap[KC_F3] = VK_F3;
	winmap[KC_F4] = VK_F4;
	winmap[KC_F5] = VK_F5;
	winmap[KC_F6] = VK_F6;
	winmap[KC_F7] = VK_F7;
	winmap[KC_F8] = VK_F8;
	winmap[KC_F9] = VK_F9;
	winmap[KC_F10] = VK_F10;
	winmap[KC_F11] = VK_F11;
	winmap[KC_F12] = VK_F12;
}

KeySenderWindows::~KeySenderWindows()
{
	//No dynamic allocations done in this class
}

DWORD KeySenderWindows::UKeyCodeToWin32VKcode(UKeyCode code)
{
	auto query = winmap.find(code);
	if (query != winmap.end())
		return query->second;
	return 0xFF;
}

void KeySenderWindows::sendKeyPress(UKeyCode code)
{
	DWORD vkcode = UKeyCodeToWin32VKcode(code);
	if (vkcode == 0xFF) return;
	sendKeyPressWin32(vkcode);
}
void KeySenderWindows::sendKeyUp(UKeyCode code)
{
	DWORD vkcode = UKeyCodeToWin32VKcode(code);
	if (vkcode == 0xFF) return;
	sendKeyUpWin32(vkcode);
}
void KeySenderWindows::sendKeyDown(UKeyCode code)
{
	DWORD vkcode = UKeyCodeToWin32VKcode(code);
	if (vkcode == 0xFF) return;
	sendKeyDownWin32(vkcode);
}

void KeySenderWindows::sendKeyPressWin32(DWORD virtualUKeyCode)
{
	sendKeyDownWin32(virtualUKeyCode);
	delay(1);
	sendKeyUpWin32(virtualUKeyCode);
	delay(1);
}
void KeySenderWindows::sendKeyUpWin32(DWORD virtualUKeyCode)
{
	INPUT input = createKeyboardUpInput(virtualUKeyCode);
	SendInput(1, &input, sizeof(input));
	delay(1);
}
void KeySenderWindows::sendKeyDownWin32(DWORD virtualUKeyCode)
{
	INPUT input = createKeyboardDownInput(virtualUKeyCode);
	SendInput(1, &input, sizeof(input));
	delay(1);
}

///Create a keyDown input
INPUT KeySenderWindows::createKeyboardDownInput(DWORD virtualUKeyCode)
{
	INPUT input; //Represent an input event for keyboard, mouse or hardware
	input.type = INPUT_KEYBOARD; //We want it to be a keyboard envent

	//Inside the INPUT struct, there's a number of struct for each type. Windows will only look to the type of event we defined

	KEYBDINPUT keyInput;
	keyInput.wVk = WORD(virtualUKeyCode); 	//The wanted code
	keyInput.wScan = 0;				//Usefull only for unicode
	keyInput.dwFlags = 0; 				//If set to nothing, this will be a keydown event
	keyInput.time = 0; 				//Timestamp in milliseconds. If set to 0, Windows will choose for you
	keyInput.dwExtraInfo = 0;			//Just ignore that.

	input.ki = keyInput; //Set the keyborad input to the INPUT struct

	return input;
}

///Creeate a keyUp input
INPUT KeySenderWindows::createKeyboardUpInput(DWORD virtualUKeyCode)
{
	//Same thing as a keyDown event, but we neet to set the KEYBDINPUT.dwFlags to KEYEVENT_KEYUP
	INPUT input = createKeyboardDownInput(virtualUKeyCode);
	input.ki.dwFlags = KEYEVENTF_KEYUP; //Change the flag

	return input;
}

void KeySenderWindows::delay(int ms)
{
	Sleep(ms);
}

#endif//win32