@echo off
cl.exe /LD main.c game_functions.c user32.lib /link /OUT:kenny_bot.dll
cl.exe injector.c user32.lib advapi32.lib shell32.lib /link /OUT:injector.exe