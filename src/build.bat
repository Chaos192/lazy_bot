@echo off
if NOT exist ..\bin\ (
    mkdir ..\bin\
)
cl.exe /LD main.c game_functions.c object_manager.c memory_manager.c user32.lib /Zi /link /OUT:..\bin\kenny_bot.dll
cl.exe injector.c user32.lib advapi32.lib shell32.lib /Zi /link /OUT:..\bin\injector.exe
