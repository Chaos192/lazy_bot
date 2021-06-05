@echo off

rem This will use VS2015 for compiler
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86

fxc.exe /nologo /T vs_4_0_level_9_0 /E vs /O3 /Zpc /Ges /Fh nuklear_d3d11_vertex_shader.h /Vn nk_d3d11_vertex_shader /Qstrip_reflect /Qstrip_debug /Qstrip_priv ..\lib\nuklear\nuklear_d3d11.hlsl
fxc.exe /nologo /T ps_4_0_level_9_0 /E ps /O3 /Zpc /Ges /Fh nuklear_d3d11_pixel_shader.h /Vn nk_d3d11_pixel_shader /Qstrip_reflect /Qstrip_debug /Qstrip_priv ..\lib\nuklear\nuklear_d3d11.hlsl

cl /LD /Zi /Fe..\bin\kenny_bot.dll -DSOKOL_GLCORE33 main.c gui.c state.c bot.c local_player.c objects.c utils.c hacks.c memory_manager.c game_functions.c sync_thread.c user32.lib dxguid.lib d3d11.lib gdi32.lib /link /incremental:no
