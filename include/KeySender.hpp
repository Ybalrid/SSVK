#ifndef KEY_SENDER
#define KEY_SENDER

#include "LibraryExportConfig.hpp"
#include "KeyCode.hpp"

namespace SSVK
{
	enum OS_type
	{
		NOT_SET,
		MS_WINDOWS_WIN32,
		GNU_LINUX_X11,
	};

	///Abstract class to send keyborad event to the system. Need to overload sendKey{Press,Up,Down}
	class SSVK_DLL KeySender
	{
	public:
		//Construct a KeySender object
		KeySender();

		//Destructor
		virtual ~KeySender();

		///Pure virtual function for "pressing" a key
		virtual void sendKeyPress(UKeyCode code) = 0;

		///Pure virtual function for "key down"
		virtual void sendKeyUp(UKeyCode code) = 0;

		///Pure virtual function for "key up"
		virtual void sendKeyDown(UKeyCode code) = 0;

		///Pure virtual function for "wait X milliseconds"
		virtual void delay(int millisec) = 0;

		///Return the OS used here
		OS_type getOsType() const;

	protected:
		///Stored OS type
		OS_type os;
	};
}
#endif //KEY_SENDER