#include "KeySenderLinux.hpp"
#ifdef __linux__

using namespace std;
using namespace SSVK;

KeySenderLinux::KeySenderLinux() : KeySender()
{
	os = GNU_LINUX_X11;
	cout << "Linux system detected" << endl;
	cout << "Opening X11 display" << endl;

	display = XOpenDisplay(NULL);
	if (!display)
	{
		cerr << "Cannot open X11 display" << endl;
		exit(-1);
	}

	//Populate the linux keymap translation - lookup table for X11 KeySim
	linmap[KC_A] = XK_A;
	linmap[KC_B] = XK_B;
	linmap[KC_C] = XK_C;
	linmap[KC_D] = XK_D;
	linmap[KC_E] = XK_E;
	linmap[KC_F] = XK_F;
	linmap[KC_G] = XK_G;
	linmap[KC_H] = XK_H;
	linmap[KC_I] = XK_I;
	linmap[KC_J] = XK_J;
	linmap[KC_K] = XK_K;
	linmap[KC_L] = XK_L;
	linmap[KC_M] = XK_M;
	linmap[KC_N] = XK_N;
	linmap[KC_O] = XK_O;
	linmap[KC_P] = XK_P;
	linmap[KC_Q] = XK_Q;
	linmap[KC_R] = XK_R;
	linmap[KC_S] = XK_S;
	linmap[KC_T] = XK_T;
	linmap[KC_U] = XK_U;
	linmap[KC_V] = XK_V;
	linmap[KC_W] = XK_W;
	linmap[KC_X] = XK_X;
	linmap[KC_Y] = XK_Y;
	linmap[KC_Z] = XK_Z;

	//cout << "Done." << endl;
	//cout << "special keys... ";

	linmap[KC_CTRL] = XK_Control_R;
	linmap[KC_ALT] = XK_Alt_L;
	linmap[KC_WIN] = XK_Meta_L;
	linmap[KC_RETURN] = XK_Return;
	linmap[KC_DEL] = XK_Delete;
	linmap[KC_SHIFT] = XK_Shift_L;

	//cout << "Done." << endl;
	//cout << "Number row... ";

	linmap[KC_0] = XK_0;
	linmap[KC_1] = XK_1;
	linmap[KC_2] = XK_2;
	linmap[KC_3] = XK_3;
	linmap[KC_4] = XK_4;
	linmap[KC_5] = XK_5;
	linmap[KC_6] = XK_6;
	linmap[KC_7] = XK_7;
	linmap[KC_8] = XK_8;
	linmap[KC_9] = XK_9;

	//cout << "Done." << endl;
	//cout << "Arrows keys... ";

	linmap[KC_UP] = XK_Up;
	linmap[KC_DOWN] = XK_Down;
	linmap[KC_LEFT] = XK_Left;
	linmap[KC_RIGHT] = XK_Right;

	//cout << "Done." << endl;
	//cout << "Function keys... ";

	linmap[KC_F1] = XK_F1;
	linmap[KC_F2] = XK_F2;
	linmap[KC_F3] = XK_F3;
	linmap[KC_F4] = XK_F4;
	linmap[KC_F5] = XK_F5;
	linmap[KC_F6] = XK_F6;
	linmap[KC_F7] = XK_F7;
	linmap[KC_F8] = XK_F8;
	linmap[KC_F9] = XK_F9;
	linmap[KC_F10] = XK_F10;
	linmap[KC_F11] = XK_F11;
	linmap[KC_F12] = XK_F12;

	//cout << "Done." << endl;
}

KeySenderLinux::~KeySenderLinux()
{
	XCloseDisplay(display);
}

void KeySenderLinux::sendKeyPress(UKeyCode code)
{
	sendKeyDown(code);
	delay(1);
	sendKeyUp(code);
	delay(1);
}

void KeySenderLinux::sendKeyUp(UKeyCode code)
{
	KeySym sym = getKeySymFromUKeyCode(code);
	if (sym != (unsigned int)-1)
		sendKeyUpX11(sym);
}

void KeySenderLinux::sendKeyDown(UKeyCode code)
{
	KeySym sym = getKeySymFromUKeyCode(code);
	if (sym != (unsigned int)-1)
		sendKeyDownX11(sym);
}

void KeySenderLinux::delay(int millisec)
{
	usleep(1000 * millisec);
}

void KeySenderLinux::sendKeyUpX11(KeySym keysym)
{
	KeyCode code = XKeysymToKeycode(display, keysym);

	//  //cout << "KeySym : " << keysym << " X11 KeyCode : " << code << endl;

	if (!XTestFakeKeyEvent(display, code, False, 0))
		cerr << "Error when sending keyboard event" << endl;

	delay(1);
	XFlush(display);
}

void KeySenderLinux::sendKeyDownX11(KeySym keysym)
{
	KeyCode code = XKeysymToKeycode(display, keysym);

	//    //cout << "KeySym : " << keysym << " X11 KeyCode : " << code << endl;

	if (!XTestFakeKeyEvent(display, code, True, 0))
		cerr << "Error when sending keyboard event" << endl;
	delay(1);
	XFlush(display);
}

KeySym KeySenderLinux::getKeySymFromUKeyCode(UKeyCode code)
{
	//cout << "Translating UKeyCode to KeySym" << endl;
	//cout << "Code : " << code;
	auto query = linmap.find(code);
	if (query != linmap.end())
	{
		//cout << " found! : " << query->second << endl;
		return query->second;
	}
	//cout << " not found : -1" << endl;
	return -1;
}

#endif //GNU_LINUX