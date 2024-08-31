

#include <cellstatus.h>
#include <sys/prx.h>
#include "ps3\debug.h"
#include "ps3\rmain.h"

#define MODULE_NAME T6_PRX_BASE

SYS_MODULE_INFO(MODULE_NAME, 0, 1, 1);
SYS_MODULE_START(Entry);

extern "C" int Entry(void)
{
    IM_HERE;
    Debug::initialize();
    Debug::coutl("Test init stage debug output");
    Prog::Write();
    // end process and keep sprx resident.
    return SYS_PRX_RESIDENT;
}
