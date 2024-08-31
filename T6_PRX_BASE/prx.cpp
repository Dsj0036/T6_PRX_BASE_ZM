

#include <cellstatus.h>
#include <sys/prx.h>


#define MODULE_NAME T6_PRX_BASE

SYS_MODULE_INFO(MODULE_NAME, 0, 1, 1);
SYS_MODULE_START(Entry);

extern "C" int Entry(void)
{
    return SYS_PRX_RESIDENT;
}
