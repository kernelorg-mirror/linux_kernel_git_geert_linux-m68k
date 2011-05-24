#if defined(CONFIG_MMU)
#include "dma_mm.c"
#else
#include "dma_no.c"
#endif
