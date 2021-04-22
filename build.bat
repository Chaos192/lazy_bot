@echo off
cl.exe /D_USRDLL /D_WINDLL main.c lazybot.c object_manager.c user32.lib /link /DLL /OUT:lazybot.dll
