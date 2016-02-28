#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include "HFL\Source\HFL.h"
#include <Windows.h>
//#include <afxwin.h>

/**
* DLL Entry point function.
*/
BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	//AfxInitRichEdit2();

	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		HFLCleanup();
	}

	return TRUE;
}