#include "Includes.h"
#include "SDK.h"
#include "Offsets.h"
#include "Memory.h"
#include "Vector.h"
#include "W2S.h"
#include <thread>
#include <atomic>
#include "overlay.h"
#include <mutex>

extern std::atomic<bool> shouldRenderMenu;

//trolling dont make fun of me its temp
class MemRead {
public:
	void RenderESPThread();
	void RenderOverlayThread();

private:
	std::mutex mtx;
	CBaseEntity centity;
	CBasePlayer cplayer;
	uintptr_t entitylist;
	view_matrix_t vm;
	uintptr_t playerpawn;
	int health;
	int team;
	int localTeam;
	CVector vecOrig;
	CVector localOrig;
};
inline MemRead memread;
