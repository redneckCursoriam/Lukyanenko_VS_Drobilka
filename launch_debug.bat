@echo off
chcp 65001
setlocal EnableDelayedExpansion
set app=bin\Lukyanenko_VS_Drobilka_x64d.exe
$(ADDITIONAL_PATH)
start ""  "%app%" -video_app auto -video_refresh 0 -video_debug 0 -main_window_size 1920 1080 -main_window_resizable 1 -main_window_fullscreen 0 -render_vsync 0 -video_offscreen 0 -sound_app auto -data_path ../data/ -extern_plugin FbxImporter,GLTFImporter,FbxExporter -console_command "config_autosave 0 && world_load \"Lukyanenko_VS_Drobilka\""
