@echo off
cl.exe /D_USRDLL /D_WINDLL main.c User32.lib /link /DLL /OUT:lazybot.dll
