#if defined(CONFIG_MMU) || defined(CONFIG_UAMIGA)
#include "init_mm.c"
#else
#include "init_no.c"
#endif
