#if defined(CONFIG_MMU) || defined(CONFIG_UAMIGA)
#include "signal_mm.c"
#else
#include "signal_no.c"
#endif
