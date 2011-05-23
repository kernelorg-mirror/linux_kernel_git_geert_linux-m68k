#if defined(__uClinux__) && !defined(CONFIG_UAMIGA)
#include "io_no.h"
#else
#include "io_mm.h"
#endif
