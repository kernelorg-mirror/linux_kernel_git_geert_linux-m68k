#if defined(CONFIG_MMU) || defined(CONFIG_UAMIGA)
#include "vmlinux.lds_mm.S"
#else
#include "vmlinux.lds_no.S"
#endif
