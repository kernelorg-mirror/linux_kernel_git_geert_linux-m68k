#if defined(CONFIG_MMU) || defined(CONFIG_UAMIGA)
#include "sys_m68k_mm.c"
#else
#include "sys_m68k_no.c"
#endif
