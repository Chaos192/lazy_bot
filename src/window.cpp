// Exchange the application's window proc, so that we can run code in the main thread any time,
// and so we can intercept messages sent to the window passing them to ImGui

HWND window = NULL;
WNDPROC originalWindowProc = NULL;

b32 CALLBACK enumWindowsCallback(HWND handle, LPARAM lParam) {
	DWORD windowProcID;
	GetWindowThreadProcessId(handle, &windowProcID);

	if (GetCurrentProcessId() != windowProcID) return true;

	window = handle;
	return false;
}

HWND getProcessWindow() {
	window = NULL;
	EnumWindows(enumWindowsCallback, NULL);
	return window;
}

LRESULT ourWindowProc(HWND window, u32 msg, WPARAM wParam, LPARAM lParam);

void takeoverWindowProc(HWND hwnd) {
    window = hwnd,
    originalWindowProc = (WNDPROC) SetWindowLong(hwnd, GWL_WNDPROC, (u32)ourWindowProc);
}

void givebackWindowProc() {
    SetWindowLong(window, GWL_WNDPROC, (u32)originalWindowProc);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef void(* _RunCodeOnMainThreadCallback)();

LRESULT ourWindowProc(HWND window, u32 msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_USER) {
        auto callback = (_RunCodeOnMainThreadCallback) wParam;
        callback();
        return 0;
    }

	if (ImGui_ImplWin32_WndProcHandler(window, msg, wParam, lParam)) return true;

    auto io = ImGui::GetIO();
    if ((io.WantCaptureMouse || io.WantCaptureKeyboard) && msg != WM_KEYUP) return true;

    return CallWindowProc(originalWindowProc, window, msg, wParam, lParam);
}

void runCodeOnMainThread(_RunCodeOnMainThreadCallback callback) {
    SendMessage(window, WM_USER, (WPARAM)callback, 0);
}
