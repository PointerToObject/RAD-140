#include "Includes.h"
#include "SDK.h"
#include "Offsets.h"
#include "Memory.h"
#include "Vector.h"
#include "W2S.h"
#include <thread>
#include <atomic>
#include "overlay.h"

extern std::atomic<bool> shouldRenderMenu;




extern void RenderESPThread();
extern void RenderOverlayThread();
