#if defined(CONFIG_MMU) || defined(CONFIG_UAMIGA)
#include "module_mm.c"
#else
#include "module_no.c"
#endif
