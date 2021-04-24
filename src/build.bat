@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars32.bat"
cl.exe /Zi /D_USRDLL /D_WINDLL main.c lazybot.c object_manager.c user32.lib /link /DLL /OUT:..\bin\lazybot.dll
cl.exe injector.c User32.lib Shell32.lib Advapi32.lib /link /OUT:..\bin\injector.exe
