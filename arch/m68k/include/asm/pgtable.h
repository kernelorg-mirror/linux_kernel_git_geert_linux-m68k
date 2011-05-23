#if defined(__uClinux__) && !defined(CONFIG_UAMIGA)
#include "pgtable_no.h"
#else
#include "pgtable_mm.h"
#endif
