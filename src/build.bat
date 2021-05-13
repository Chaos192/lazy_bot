@echo off
if NOT exist ..\bin\ (
    mkdir ..\bin\
)
cl.exe /LD main.c gui.c utils.c user32.lib gdi32.lib /Zi /link /OUT:..\bin\lazy_bot.dll
cl.exe injector.c user32.lib advapi32.lib /Zi /link /OUT:..\bin\injector.exe
