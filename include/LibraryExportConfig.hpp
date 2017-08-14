#pragma once

#ifdef _WIN32
#ifdef DLLEXPORT
#define SSVK_DLL  __declspec(dllexport)
#define EXPIMP_TEMPLATE
#else
#define SSVK_DLL  __declspec(dllimport)
#define EXPIMP_TEMPLATE extern
#endif
#else
#define SSVK_EXPORT
#endif