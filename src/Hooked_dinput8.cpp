
#define CINTERFACE 1
#include <Windows.h>
#include <dinput.h>

#include "Hooked_dinput8.h"
#include "Hooked_dinput8_InitVoice.h"

#define DINPUT8_DLL "dinput8.dll"
#define OLD_DINPUT8_DLL ".\\dinput8_old.dll"
#define SYS_DINPUT8_DLL "%systemroot%\\System32\\dinput8.dll"

#define STR_DirectInput8Create "DirectInput8Create"

#define MAX_PATH_LEN 1024

const GUID guid_keyboard = { 0x6F1D2B61, 0xD5A0, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 };

static HMODULE dll = 0;
static HINSTANCE hinstDLL;

using Call_Create = decltype(Hooked_DirectInput8Create)*;
static Call_Create ori_DirectInput8Create = nullptr;

long SVCALL Hooked_DirectInput8Create(void * hinst, unsigned dwVersion, void * riidltf, void ** ppvOut, void * punkOuter)
{
	if (!dll) {
		dll = LoadLibraryA(OLD_DINPUT8_DLL);
		if (!dll) {
			char buff[MAX_PATH_LEN + 1];
			ExpandEnvironmentStringsA(SYS_DINPUT8_DLL, buff, sizeof(buff));
			dll = LoadLibraryA(buff);
			ori_DirectInput8Create = (Call_Create)GetProcAddress(dll, STR_DirectInput8Create);
		}
	}

	if (!ip) {
		Init(hinstDLL);
		if (ip) Go();
	}

	if (ori_DirectInput8Create) {
		return ori_DirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
	}
	else {
		return 0x80070057L;
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	::hinstDLL = hinstDLL;
	return TRUE;
}
