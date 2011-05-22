#if defined(CONFIG_MMU) || defined(CONFIG_UAMIGA)
#include "entry_mm.S"
#else
#include "entry_no.S"
#endif
