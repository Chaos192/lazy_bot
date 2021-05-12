#include <windows.h>
#include <stdio.h>

#include "object_manager.h"

#define MYMENU_EXIT         (WM_APP + 101)
#define MYMENU_MESSAGEBOX   (WM_APP + 102)
#define TEST_OBJ_MNG 1
#define ID_QUIT 2

HINSTANCE inj_inst;
HWND prnt_hWnd;

void bot();
//HMENU CreateDLLWindowMenu();

LRESULT CALLBACK DLLWindowProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
            CreateWindowW(L"Button", L"Walk",
                WS_VISIBLE | WS_CHILD ,
                20, 50, 80, 25, hwnd, (HMENU) TEST_OBJ_MNG, NULL, NULL);

            CreateWindowW(L"Button", L"Quit",
                WS_VISIBLE | WS_CHILD ,
                120, 50, 80, 25, hwnd, (HMENU) MYMENU_EXIT, NULL, NULL);
            break;

		case WM_COMMAND:
               switch(wParam)
               {
                    case MYMENU_EXIT:
                        exit(0);
                        break;
                    case MYMENU_MESSAGEBOX:
						MessageBox(hwnd, "Test", "MessageBox",MB_OK);
                        break;
                    case TEST_OBJ_MNG:
                        enumerate_visible_objects();
                        break;
               }
               break;
		case WM_DESTROY:
			PostQuitMessage (0);
			break;
		default:
			return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}

DWORD WINAPI ThreadProc( LPVOID lpParam ) {
	MSG messages;
	RegisterDLLWindowClass("InjectedDLLWindowClass");
    //HMENU hMenu = CreateDLLWindowMenu();
	prnt_hWnd = FindWindow("Window Injected Into ClassName", "Window Injected Into Caption");
	HWND hwnd = CreateWindowEx (0, "InjectedDLLWindowClass", lpParam, WS_EX_PALETTEWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, prnt_hWnd, NULL, inj_inst, NULL );
	ShowWindow (hwnd, SW_SHOWNORMAL);
	while (GetMessage (&messages, NULL, 0, 0))
	{
		TranslateMessage(&messages);
        DispatchMessage(&messages);
	}
	return 1;
}

BOOL RegisterDLLWindowClass(char szClassName[]) {
    WNDCLASSEX wc;
    wc.hInstance =  inj_inst;
    wc.lpszClassName = (LPCSTR)szClassName;
    wc.lpfnWndProc = DLLWindowProc;
    wc.style = CS_DBLCLKS;
    wc.cbSize = sizeof (WNDCLASSEX);
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.lpszMenuName = NULL;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
    if (!RegisterClassEx (&wc))
		return 0;
    return 1;
}

//HMENU CreateDLLWindowMenu() {
//	HMENU hMenu;
//	hMenu = CreateMenu();
//	HMENU hMenuPopup;
//    if(hMenu==NULL)
//        return FALSE;
//    hMenuPopup = CreatePopupMenu();
//	AppendMenu (hMenuPopup, MF_STRING, MYMENU_EXIT, TEXT("Exit"));
//    AppendMenu (hMenu, MF_POPUP, (UINT_PTR) hMenuPopup, TEXT("File")); 
//
//	hMenuPopup = CreatePopupMenu();
//    AppendMenu (hMenuPopup, MF_STRING,MYMENU_MESSAGEBOX, TEXT("MessageBox")); 
//    AppendMenu (hMenu, MF_POPUP, (UINT_PTR) hMenuPopup, TEXT("Test")); 
//	return hMenu;
//}

BOOL WINAPI DllMain(HINSTANCE inst, DWORD Reason, LPVOID Reserved) {
    if (Reason == DLL_PROCESS_ATTACH) {
        inj_inst = inst;
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot, NULL, 0, NULL);
    }
    return TRUE;
}

void bot() {
    AllocConsole();
    FILE *file_dummy;
    freopen_s(&file_dummy, "CONOUT$", "w", stdout);
    printf("Injected.\n");

    CreateThread(NULL, 0, ThreadProc, (LPVOID)"Kenny Bot", 0, NULL);

    while (TRUE) {
        Sleep(100);
    }
}
