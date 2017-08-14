#ifndef KEY_SENDER_LINUX
#define KEY_SENDER_LINUX
#ifdef __linux__

#include "KeySender.hpp"
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
//Xtest extension make it easier to send key events
#include <X11/extensions/XTest.h>

#include <iostream>
#include <unordered_map>

namespace SSVK
{
	class SSVK_DLL KeySenderLinux : public KeySender
	{
	public:
		KeySenderLinux();
		~KeySenderLinux();

		void sendKeyPress(UKeyCode code) override;
		void sendKeyUp(UKeyCode code) override;
		void sendKeyDown(UKeyCode code) override;
		void delay(int millisec) override;

	private:

		void sendKeyUpX11(KeySym keysym);
		void sendKeyDownX11(KeySym keysym);

		KeySym getKeySymFromUKeyCode(UKeyCode code);

		Display* display;
		std::unordered_map<UKeyCode, KeySym> linmap;
	};
}
#endif //GNU/LINUX
#endif //KEY_SENDER_LINUx