@echo off
if NOT exist ..\bin\ (
	mkdir ..\bin\
)
cl.exe /Zi /D_USRDLL /D_WINDLL utils.c main.c kenny_bot.c objects.c user32.lib /link /DLL /OUT:..\bin\kenny_bot.dll
cl.exe utils.c launcher.c User32.lib Shell32.lib Advapi32.lib /link /OUT:..\bin\launcher.exe
