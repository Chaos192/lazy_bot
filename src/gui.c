#include <windows.h>
#include <stdbool.h>

#include "object_manager.h"
#include "bot.h"

#define START_BOT       1
#define STOP_BOT        2
#define PUSH_CRY_STATE  3
#define PUSH_YELL_STATE 4
#define POP_STATE       5

HINSTANCE inj_inst;
HWND prnt_hWnd;

//HMENU CreateDLLWindowMenu();

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
    HFONT hfDefault = (HFONT) GetStockObject(DEFAULT_GUI_FONT);
    SendMessage(hWnd, WM_SETFONT, (WPARAM) hfDefault, MAKELPARAM(TRUE, 0));
    return TRUE;
}

LRESULT CALLBACK DLLWindowProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
            CreateWindowW(L"Button", L"Start",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                5, 10, 70, 20, hwnd, (HMENU) START_BOT, NULL, NULL);
            CreateWindowW(L"Button", L"Stop",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                85, 10, 70, 20, hwnd, (HMENU) STOP_BOT, NULL, NULL);
            CreateWindowW(L"Button", L"PushCryState",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                165, 10, 70, 20, hwnd, (HMENU) PUSH_CRY_STATE, NULL, NULL);
            CreateWindowW(L"Button", L"PushYellState",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                245, 10, 70, 20, hwnd, (HMENU) PUSH_YELL_STATE, NULL, NULL);
            CreateWindowW(L"Button", L"PopState",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                325, 10, 70, 20, hwnd, (HMENU) POP_STATE, NULL, NULL);
            EnumChildWindows(hwnd, EnumChildProc, 0);
            break;

		case WM_COMMAND:
               switch(wParam) {
                    case START_BOT:
                        enable_bot();
                        break;
                    case STOP_BOT:
                        disable_bot();
                        break;
                    case PUSH_CRY_STATE:
                        push_state(CRY_STATE);
                        break;
                    case PUSH_YELL_STATE:
                        push_state(YELL_STATE);
                        break;
                    case POP_STATE:
                        pop_state();
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
	HWND hwnd = CreateWindowEx (0, "InjectedDLLWindowClass", lpParam, WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 410, 200, prnt_hWnd, NULL, inj_inst, NULL );
	ShowWindow (hwnd, SW_SHOWNORMAL);
    //font 
    HFONT hFont = CreateFont (13, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, 
      OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
      DEFAULT_PITCH | FF_DONTCARE, TEXT("Consolas"));
    SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
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
    wc.hbrBackground = (HBRUSH) 0x0;
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

