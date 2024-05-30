#include "RenderThreadCheat.h"

std::atomic<bool> shouldRenderMenu = true;



void MemRead::RenderESPThread() {
    CDispatcher* mem = CDispatcher::Get();
    if (esp) {
        mem->Attach("cs2.exe");
        uintptr_t base = mem->GetModuleBase("client.dll");
        CBaseEntity centity;
        CBasePlayer cplayer;
        
        for (int i = 0; i < 64; i++) {
            uintptr_t entitylist = centity.GetEntityList(base);
            view_matrix_t vm = mem->ReadMemory<view_matrix_t>(base + dwViewMatrix);
            uintptr_t playerpawn = cplayer.getPCSPlayerPawn(base, i);
            int health = cplayer.getHealth(playerpawn);
            int team = cplayer.GetTeam(playerpawn);
            int localTeam = cplayer.getLocalTeam(base);
            CVector vecOrig = cplayer.GetOrigin(playerpawn);
            CVector localOrig = cplayer.GetLocalOrigin(base);
            if (!health) continue;
            CVector screen;
            ImVec2 screensize = ImGui::GetIO().DisplaySize;
            if (!W2S(screensize, vecOrig, screen, vm));
                continue;
            float huDistance = pythag(vecOrig, localOrig); // Distance in game 
            float distance = (huDistance / 16) / 3.28084; // convert from hammer units to meters
            char textBuffer[64];
            sprintf_s(textBuffer, "PLAYER [%.1fm]", distance);
            if (localTeam != team) {
                ImGui::GetBackgroundDrawList()->AddText(ImVec2(screen.x + 6.0, screen.y + 3.0), IM_COL32(255, 255, 255, 255), textBuffer, 0);
                ImGui::GetBackgroundDrawList()->AddRect(ImVec2(screen.x - 3.0f, screen.y - 3.0f), ImVec2(screen.x + 3.0f, screen.y + 3.0f), IM_COL32(255, 0, 0, 255), 1, 1.0f);
            }

        }
       //std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
   
}

void MemRead::RenderOverlayThread() {
    overlay.CreateOverlay();
    overlay.CreateDevice();
    overlay.CreateImGui();

    printf("[>>] Hit insert to show the menu in this overlay!\n");

    overlay.SetForeground(GetConsoleWindow());

    while (shouldRenderMenu) {
        overlay.StartRender();

        if (overlay.RenderMenu) {
            overlay.Render();
        }
        else {
            ImGui::GetBackgroundDrawList()->AddText({ 0, 0 }, ImColor(0.0f, 1.0f, 0.0f), "RAD-140 PRESS INSERT TO SHOW");
        }
        if (esp) {
            std::thread testThread(&MemRead::RenderESPThread, &memread);
            testThread.join();
        }
        overlay.EndRender();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    overlay.DestroyImGui();
    overlay.DestroyDevice();
    overlay.DestroyOverlay();
}


