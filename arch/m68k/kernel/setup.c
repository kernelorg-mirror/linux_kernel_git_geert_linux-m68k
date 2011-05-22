#if defined(CONFIG_MMU) || defined(CONFIG_UAMIGA)
#include "setup_mm.c"
#else
#include "setup_no.c"
#endif
