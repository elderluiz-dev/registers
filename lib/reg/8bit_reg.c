#include <stdio.h>

#include "8bit_reg.h"

#define FIFO_BLOCK_BIT ((DATA0->CTRL >> 7) & 1)
#define FIFO_FULL_BIT  ((DATA0->STATUS >> 7) & 1)

#define LIFO_BLOCK_BIT ((DATA0->CTRL >> 6) & 1)
#define LIFO_FULL_BIT  ((DATA0->STATUS >> 6) & 1)

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

uint8_t _FIFO_UNLOCK_DATAFLOW(void)
{
    // Cleaning and setting FIFO bit
    DATA0->CTRL &= ~(CTRL_FIFO_DFB_MASK);
    DATA0->CTRL |= CTRL_FIFO_DFNB_MASK;

    return 0;
}

uint8_t _LIFO_UNLOCK_DATAFLOW(void)
{
    // Cleaning and setting LIFO bit
    DATA0->CTRL &= ~(CTRL_LIFO_DFB_MASK);
    DATA0->CTRL |= CTRL_LIFO_DFNB_MASK;

    return 0;
}

// === INTERNAL status register functions ===

// == FIFO ==

void _INTERNAL_SETSTATUS_FIFO_FULL(void)
{
    DATA0->STATUS |= STATUS_FIFO_ISF_MASK;
}

void _INTERNAL_SETSTATUS_FIFO_NFULL(void)
{
    DATA0->STATUS &= ~(STATUS_FIFO_ISF_MASK);
}

// == LIFO ==

void _INTERNAL_SETSTATUS_LIFO_FULL(void)
{
    DATA0->STATUS |= STATUS_LIFO_ISF_MASK;
}

void _INTERNAL_SETSTATUS_LIFO_NFULL(void)
{
    DATA0->STATUS &= ~(STATUS_LIFO_ISF_MASK);
}

// === Check Functions ===

// == FIFO ==

uint8_t _CHECK_FIFO_DATAFLOW(void)
{
    if(FIFO_BLOCK_BIT == 1)
    {
        return 1;
    }

    return 0;
}

// == LIFO ==

uint8_t _CHECK_LIFO_DATAFLOW(void)
{
    if(LIFO_BLOCK_BIT == 1)
    {
        return 1;
    }

    return 0;
}