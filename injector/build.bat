@echo off
cl.exe injector.c User32.lib Shell32.lib Advapi32.lib /link /OUT:injector.exe
