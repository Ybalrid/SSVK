# SSVK
Super Simple Virtual Keypress : A Windows/Linux solution to generate system-wide keyboard events.

This library permit to send fake keypresses to the desktop. This litterally simulate if somebody was pressing keys on a virtual keyboard using OS availlable API.

This library provide a single interface to do it in multiple systems.

This is a toy project, and it's probably not implemented in the most efficient manner. (for instance, the "universal keycodes" used by the library are stored as strings, for easy manipulations, and values are put in a bunch of defines).

Please note that when initializing a KeySender object, a table (sotred as an `std::unordered_map`) that serve to translate keycodes to your own code is created. You don't need multiple objects of this type around, it will just be a waste.

Note that you are sending key press without any way to know by code if they are actually working. This is intended to write really simple automation code, but not reliable/sensible code. 

Do not be [Tom Scott](https://youtu.be/lIFE7h3m40U?t=4m11s), do not use janky open source softawre to deploy parachutes. :wink:

## Dependencies:

 - On Windows, the library just issues call to the Win32 API. You don't need to install any special library beside your compiler
 - On Linux, this program is using the XTest extension of the XLib that may not installed by default on your system (linkage with `-lX11 -lXtst`)
 
## Building

 - On Windows, just run CMake and you are done
 - On Linux, you'll just need to install the developement libraries for x11 (xorg-x11) and the xtst
 
## Installing and using 

 - CMake will install the shared library and the headers in your installation prefix
 I don't have a "find_SSVK" script yet, but it's comming!
