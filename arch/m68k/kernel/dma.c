#if defined(CONFIG_MMU) || defined(CONFIG_UAMIGA)
#include "dma_mm.c"
#else
#include "dma_no.c"
#endif
