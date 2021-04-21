@echo off
cl.exe /D_USRDLL /D_WINDLL main.c lazybot.c /link /DLL /OUT:lazybot.dll
