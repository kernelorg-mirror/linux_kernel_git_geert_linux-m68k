#if defined(__uClinux__) && !defined(CONFIG_UAMIGA)
#include "hardirq_no.h"
#else
#include "hardirq_mm.h"
#endif
