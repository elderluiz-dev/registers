#include "8bit_reg.h"
#include <stdio.h>

DataRegisters mock_data0; 
DataRegisters *DATA0 = &mock_data0;

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

void INTERNAL_SETSTATUS_FIFO_FULL(void)
{
    DATA0->STATUS &= ~(STATUS_FIFO_NF_MASK);
    DATA0->STATUS |= STATUS_FIFO_ISF_MASK;
}

void INTERNAL_SETSTATUS_FIFO_NFULL(void)
{
    DATA0->STATUS &= ~(STATUS_FIFO_ISF_MASK);
    DATA0->STATUS |= STATUS_FIFO_NF_MASK;
}

void INTERNAL_SETSTATUS_LIFO_FULL(void)
{
    DATA0->STATUS &= ~(STATUS_LIFO_NF_MASK);
    DATA0->STATUS |= STATUS_LIFO_ISF_MASK;
}

void INTERNAL_SETSTATUS_LIFO_NFULL(void)
{
    DATA0->STATUS &= ~(STATUS_LIFO_ISF_MASK);
    DATA0->STATUS |= STATUS_LIFO_NF_MASK;
}
