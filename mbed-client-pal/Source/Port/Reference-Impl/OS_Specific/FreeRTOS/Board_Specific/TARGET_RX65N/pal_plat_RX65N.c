// terminator

#include "pal_plat_rtos.h"
#include "r_bsp_cpu.h"

void pal_plat_osReboot(void)
{
    /// \todo
}

int32_t pal_plat_osAtomicIncrement(int32_t* valuePtr, int32_t increment)
{
    int32_t res;

    R_BSP_InterruptsDisable();

    res = *valuePtr + increment;
    *valuePtr = res;

    R_BSP_InterruptsEnable();
    return (res);
}

palStatus_t pal_plat_getRandomBufferFromHW(uint8_t *randomBuf, size_t bufSizeBytes, size_t* actualRandomSizeBytes)
{
    /// \todo
}