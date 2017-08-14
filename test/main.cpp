#include <iostream>
#include <memory>

#include <SSKV.hpp>

using namespace SSVK;

int main(void)
{
	std::cout << "Just a simple demo..." << std::endl;
#ifdef _WIN32
	MessageBox(NULL,
		"We will input a series of keystroke to open the Firefox program via the Run dialog.\n"
		"This program will press the keys : WINDOWS KEY + R; F; I; R; E; F; O; X; RETURN;",
		"open firefox",
		MB_OK);

	/*
	 * KeySender is an abstract class that act like an "interface"
	 * KeySenderWindows is a child class of KeySender that implements the pure virutal
	 * methods of KeySender. By polymorphism, a KeySenderWindows pointer can be stored
	 * inside a KeySender pointer. This only allow to access KeySender's public members only,
	 * and that's exactly what we want for an "interface" ;-)
	 */

	auto ks = std::make_unique<KeySenderWindows>();

	//Press Win + R
	ks->sendKeyDown(KC_WIN);
	ks->sendKeyDown(KC_R);

	//Release Win + R
	ks->sendKeyUp(KC_R);
	ks->sendKeyUp(KC_WIN);

#else

	auto ks = std::make_unique<KeySenderLinux>();

	std::cerr << "This program will simultaneously press ALT + F2 to oppen the command prompt of your Desktop Environement, they Type the command \"firefox\" and press RETURN to run it" << std::endl;

	ks->sendKeyDown(KC_ALT);
	ks->sendKeyDown(KC_F2);

	ks->sendKeyUp(KC_F2);
	ks->sendKeyUp(KC_ALT);

#endif
	ks->delay(500);

	ks->sendKeyPress("F");
	ks->sendKeyPress("I");
	ks->sendKeyPress("R");
	ks->sendKeyPress("E");
	ks->sendKeyPress("F");
	ks->sendKeyPress("O");
	ks->sendKeyPress("X");

	ks->delay(500);

	//Press return key
	ks->sendKeyPress(KC_RETURN);

#ifdef _WIN32
	MessageBox(NULL,
		"Now we will open the task manager with the keyboard shortcut : CTRL + ALT + ESC",
		"open taskmgr",
		MB_OK);

	ks->sendKeyDown(KC_CTRL);
	ks->sendKeyDown(KC_SHIFT);
	ks->sendKeyDown(KC_ESC);

	ks->sendKeyUp(KC_ESC);
	ks->sendKeyUp(KC_SHIFT);
	ks->sendKeyUp(KC_CTRL);

#endif

	return 0;
}