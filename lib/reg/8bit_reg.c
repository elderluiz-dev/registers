#include "8bit_reg.h"
#include <stdio.h>

DataRegisters mock_data0; 
DataRegisters *DATA0 = &mock_data0;

void _INIT_REGISTERS(void)
{
    // Cleaning registers
    DATA0->CTRL &= ~(CLEAR_MASK_ALL);
    DATA0->STATUS &= ~(CLEAR_MASK_ALL);

    // Setting initial status of FIFO and LIFO in CTRL register
    DATA0->CTRL |= CTRL_FIFO_DFNB_MASK;
    DATA0->CTRL |= CTRL_LIFO_DFNB_MASK;
}

void _FIFO_BLOCK_DATAFLOW(void)
{
    // Cleaning and setting FIFO bit
    DATA0->CTRL &= ~(CTRL_FIFO_DFNB_MASK);
    DATA0->CTRL |= CTRL_FIFO_DFB_MASK;
}

void _LIFO_BLOCK_DATAFLOW(void)
{
    // Cleaning and setting LIFO bit
    DATA0->CTRL &= ~(CTRL_LIFO_DFNB_MASK);
    DATA0->CTRL |= CTRL_LIFO_DFB_MASK;
}

void _FIFO_UNLOCK_DATAFLOW(void)
{
    // Cleaning and setting FIFO bit
    DATA0->CTRL &= ~(CTRL_FIFO_DFB_MASK);
    DATA0->CTRL |= CTRL_FIFO_DFNB_MASK;
}

void _LIFO_UNLOCK_DATAFLOW(void)
{
    // Cleaning and setting LIFO bit
    DATA0->CTRL &= ~(CTRL_LIFO_DFB_MASK);
    DATA0->CTRL |= CTRL_LIFO_DFNB_MASK;
}

// INTERNAL status register

void _INTERNAL_SETSTATUS_FIFO_FULL(void)
{
    DATA0->STATUS |= STATUS_FIFO_ISF_MASK;
}

void _INTERNAL_SETSTATUS_FIFO_NFULL(void)
{
    DATA0->STATUS &= ~(STATUS_FIFO_ISF_MASK);
}

void _INTERNAL_SETSTATUS_LIFO_FULL(void)
{
    DATA0->STATUS |= STATUS_LIFO_ISF_MASK;
}

void _INTERNAL_SETSTATUS_LIFO_NFULL(void)
{
    DATA0->STATUS &= ~(STATUS_LIFO_ISF_MASK);
}

int main()
{
    printf("Valor de DATA0->STATUS: %d\n\n", DATA0->STATUS);

    _INTERNAL_SETSTATUS_FIFO_FULL();
    _INTERNAL_SETSTATUS_LIFO_FULL();

    printf("Valor de DATA0->STATUS: %d\n\n", DATA0->STATUS);

    return 0;
}