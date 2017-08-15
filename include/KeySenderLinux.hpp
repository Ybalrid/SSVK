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
        ///Construct a key sender object for Linux and populate the symbol map
		KeySenderLinux();

        ///Destructor
		~KeySenderLinux();

        ///Send a key press (donw, then up) via Xtst
		void sendKeyPress(UKeyCode code) override;

        ///Send a key up (release) via Xtst
		void sendKeyUp(UKeyCode code) override;

        ///Send a key down (push) via Xtst
		void sendKeyDown(UKeyCode code) override;

        ///Wait for some milliseconds
        ///\param millisec time to wait in milliseconds
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
