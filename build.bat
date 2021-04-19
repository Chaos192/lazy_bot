@echo off
cl.exe /D_USRDLL /D_WINDLL main.c lazybot.c game_functions.c User32.lib /link /DLL /OUT:lazybot.dll
