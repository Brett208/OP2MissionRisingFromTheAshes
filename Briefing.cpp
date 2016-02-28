#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

//#include <afxwin.h>
#include <richedit.h>
#include "resource.h"
#include "odasl\odasl.h"
#include <string>

// These deal with the briefing screen
HINSTANCE hInst;
LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

std::string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}

DWORD CALLBACK EditStreamCallback(DWORD_PTR dwCookie, LPBYTE lpBuff,
	LONG cb, PLONG pcb)
{
	HANDLE hFile = (HANDLE)dwCookie;
	return !ReadFile(hFile, lpBuff, cb, (DWORD *)pcb, NULL);
}

BOOL FillRichEditFromFile(HWND hwnd, LPCTSTR pszFile)
{
	BOOL fSuccess = FALSE;

	HANDLE hFile = CreateFile(pszFile, GENERIC_READ, FILE_SHARE_READ,
		0, OPEN_EXISTING,
		FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		EDITSTREAM es = { (DWORD_PTR)hFile, 0, EditStreamCallback };
		if (SendMessage(hwnd, EM_STREAMIN, SF_RTF, (LPARAM)&es) &&
			es.dwError == 0)
		{
			fSuccess = TRUE;
		}

		CloseHandle(hFile);
	}
	return fSuccess;
}

void ShowBriefing()
{
    // OP2 turns off the skinning before the game loads.
    // We have to re-enable it (otherwise the briefing box will look ugly).
    wplEnable();
    // Show the dialog box, using the shell window as the parent
	HWND shellWnd = FindWindow("Outpost2Shell", NULL);
	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_MISSIONINFO), shellWnd, (DLGPROC)DialogProc, NULL);  //Creates a modal dialog box from a dialog box template resource.
    // Turn off the skinning again (probably not needed but a good idea to do it anyway)
    wplDisable();
}

LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HRSRC txtRes = NULL; //Handle to a resource
    HWND richEdit = NULL; //Handle to a window.
	switch(msg)
	{
		case WM_INITDIALOG:
            // Make the background black in the rich edit box
            richEdit = GetDlgItem(hWnd, IDC_TEXTAREA); //Retrieves a handle to a control in the specified dialog box. 
            SendMessage(richEdit, EM_SETBKGNDCOLOR, 0, 0);

            // Find the text resource
            txtRes = FindResource(hInst, MAKEINTRESOURCE(IDS_STRING101), "TEXT");
            if (txtRes)
            {
                // Load it
                HGLOBAL resHdl = LoadResource(hInst, txtRes);
                if (resHdl)
                {
                    // Lock it and set the text
                    char *briefing = (char*)LockResource(resHdl);
                    if (briefing)
                    {
                        SetDlgItemText(hWnd, IDC_TEXTAREA, briefing);
                        return TRUE;
                    }
                }
            }
            SetDlgItemText(hWnd, IDC_TEXTAREA, "Error: Mission text could not be loaded.");
            return TRUE;
        case WM_COMMAND:
            if (wParam == IDOK) //IDOK mean ID OK.
            {
                EndDialog(hWnd, IDOK);
                return TRUE;
            }
            return FALSE;
	}
	return FALSE;
}

