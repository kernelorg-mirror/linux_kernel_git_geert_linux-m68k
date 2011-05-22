#if defined(CONFIG_MMU) || defined(CONFIG_UAMIGA)
#include "traps_mm.c"
#else
#include "traps_no.c"
#endif
