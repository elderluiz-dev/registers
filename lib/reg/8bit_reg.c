#include "8bit_reg.h"

void _INIT_REGISTERS(void)
{
    // Cleaning registers
    DATA0->CTRL &= ~(MASK_ALL);
    DATA0->STATUS &= ~(MASK_ALL);

    // Setting initial status of FIFO and LIFO in STATUS register
    DATA0->STATUS |= STATUS_FIFO_NF_MASK;
    DATA0->STATUS |= STATUS_LIFO_NF_MASK;

    // Setting initial status of FIFO and LIFO in CTRL register
    DATA0->CTRL |= CTRL_FIFO_DFNB_MASK;
    DATA0->CTRL |= CTRL_LIFO_DFNB_MASK;
}
