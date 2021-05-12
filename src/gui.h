HINSTANCE inj_inst;
LRESULT CALLBACK DLLWindowProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
DWORD WINAPI ThreadProc( LPVOID lpParam );
BOOL RegisterDLLWindowClass(char szClassName[]);
