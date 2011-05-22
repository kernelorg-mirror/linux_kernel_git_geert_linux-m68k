#if defined(CONFIG_MMU) || defined(CONFIG_UAMIGA)
#include "time_mm.c"
#else
#include "time_no.c"
#endif
