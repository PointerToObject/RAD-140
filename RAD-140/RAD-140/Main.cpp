#include "RenderThreadCheat.h"


int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    std::thread renderThread(RenderOverlayThread);
    while (true) {
        if (GetAsyncKeyState(VK_END)) { 
            shouldRenderMenu = false; 
            break; 
        }
        

        std::this_thread::sleep_for(std::chrono::milliseconds(1)); 
    }

    
    renderThread.join();

    return 0;
}