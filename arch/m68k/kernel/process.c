#if defined(CONFIG_MMU) || defined(CONFIG_UAMIGA)
#include "process_mm.c"
#else
#include "process_no.c"
#endif
