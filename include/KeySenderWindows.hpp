#pragma once
#ifdef _WIN32

#include <Windows.h>
#include <unordered_map>
#include "KeySender.hpp"

//EXPIMP_TEMPLATE template class SSVK_DLL std::unordered_map<SSVK::UKeyCode, DWORD>;
#pragma warning(push)
#pragma warning(disable:4251)

namespace SSVK
{
	///KeySender object for MS Windows using the Win32 API
	class SSVK_DLL KeySenderWindows : public KeySender
	{
	public:

		///Define the type of the "keymap". The object that permit to get system keycode form universal keycodes
		using winkeymap = std::unordered_map<UKeyCode, DWORD>;

		///Construct a KeySenderWindows object. This will populate a map to translate "UKeyCode" to DWORD Virtual Keyboard codes windows uses.
		KeySenderWindows();

		///Empty destructor. No dynamic allocation is done by this class
		~KeySenderWindows();

		void sendKeyPress(UKeyCode code) override;

		///Overload of the sendKeyPress event. translate to Win32 VK code an call the Win32 private method of this class
		void sendKeyUp(UKeyCode code) override;

		///Overload of the sendKeyPress event. translate to Win32 VK code an call the Win32 private method of this class
		void sendKeyDown(UKeyCode code) override;

		///Implement millisec delay by calling Win32 "Sleep" function
		void delay(int milliseconds) override;

	private:
		///Check if UKeyCode is known. If so, return a VK code for it. If not, return 0xFF
		DWORD UKeyCodeToWin32VKcode(UKeyCode code);

		///Call sendKeyDownWin32 then sendKeyUpWin32 since Win32 inputs don't have a "pressed" or "typed" evnt out of the box
		void sendKeyPressWin32(DWORD VKcode);

		///Send KeyUp input
		void sendKeyUpWin32(DWORD VKcode);

		///Send KeyDown input
		void sendKeyDownWin32(DWORD VKcode);

		///Create a keyDown input
		INPUT createKeyboardDownInput(DWORD virtualUKeyCode);

		///Creeate a keyUp input
		INPUT createKeyboardUpInput(DWORD virtualUKeyCode);

		///Translation unordered_map of UKeyCodes and VK codes. unordered_map "find" cost is of o(1) complexity. Need C++11.
		winkeymap winmap;
	};
}

#pragma warning(pop)

#endif 