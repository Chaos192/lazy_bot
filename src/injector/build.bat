@echo off
cl.exe main.c user32.lib advapi32.lib shell32.lib /link /OUT:injector.exe
