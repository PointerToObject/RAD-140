#include "RenderThreadCheat.h"

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    std::thread renderThread(&MemRead::RenderOverlayThread, &memread);
    renderThread.detach();

    while (true) {
        if (GetAsyncKeyState(VK_END)) {
            shouldRenderMenu = false;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}