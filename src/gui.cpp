#include <stdio.h>
#include <windows.h>
#include <stdint.h>

#include "imgui\imgui.h"
#include "utils.h"
#include "objects.h"
#include "local_player.h"

#define WINDOW_NAME "Kronos Bot"

void frame() {
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("#tabs", tab_bar_flags)) {
        if (ImGui::BeginTabItem("Main")) {
            if (ImGui::Button("Start")) {
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Debug")) {
            if (ImGui::Button("Show Console")) {
                create_console();
            }
            ImGui::SameLine();
            if (ImGui::Button("Test")) {
                update_view();
                go_to(get_object_position(get_closest_enemy()));
            }
            ImGui::EndTabItem();
        }
    }
    ImGui::EndTabBar();

    // Reformat the imgui's window frame to match Windows's window frame.
    RECT rect;
    ::GetClientRect(FindWindow(NULL, WINDOW_NAME), &rect);
    ImGui::SetWindowSize(ImVec2((float)(rect.right - rect.left), 
                                (float)(rect.bottom - rect.top)+20));
    ImGui::SetWindowPos(ImVec2(0, -20));

    Sleep(20);
}

void gui() {
    uint32_t config_flags = 0;
    imgui_app(frame, WINDOW_NAME, 500, 300, config_flags);
}
