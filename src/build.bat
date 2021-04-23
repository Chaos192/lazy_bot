@echo off
cl.exe injector.c User32.lib Shell32.lib Advapi32.lib /link /OUT:..\bin\injector.exe
cl.exe /D_USRDLL /D_WINDLL main.c lazybot.c object_manager.c user32.lib /link /DLL /OUT:..\bin\lazybot.dll
..\bin\injector.exe