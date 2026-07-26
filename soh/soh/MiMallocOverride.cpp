// Experiment branch, Windows only. Including this header in exactly one translation unit defines
// the global operator new/delete overloads, which routes every C++ allocation in the binary --
// including torch's, since it is linked statically -- through mimalloc.
#ifdef SOH_USE_MIMALLOC
#include <mimalloc-new-delete.h>
#endif
