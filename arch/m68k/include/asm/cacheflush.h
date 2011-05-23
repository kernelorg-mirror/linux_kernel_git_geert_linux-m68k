#if defined(__uClinux__) && !defined(CONFIG_UAMIGA)
#include "cacheflush_no.h"
#else
#include "cacheflush_mm.h"
#endif
