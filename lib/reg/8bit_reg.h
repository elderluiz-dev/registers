#pragma once

#include <stdint.h>

typedef struct {
    volatile uint8_t CTRL;
    volatile uint8_t STATUS;
} DataRegisters;

extern DataRegisters *DATA0;

#define CLEAR_MASK_ALL (0xFFU << 0)

// == CTRL Register masks ==
// FIFO Data Flow Not Blocked
// 0b00000010U
#define CTRL_FIFO_DFNB_MASK (uint8_t)(0b1 << 1)

// FIFO Data Flow Blocked
// 0b10000000U
#define CTRL_FIFO_DFB_MASK  (uint8_t)(0b1 << 7)

// LIFO Data Flow Not Blocked
// 0b00000001U
#define CTRL_LIFO_DFNB_MASK (uint8_t)(0b1 << 0)

// LIFO Data Flow Blocked
// 0b01000000U
#define CTRL_LIFO_DFB_MASK  (uint8_t)(0b1 << 6)

// == STATUS Register masks ==
// Data FIFO is Full
// 0b10000000U
#define STATUS_FIFO_ISF_MASK (uint8_t)(0b1 << 7)

// Data LIFO is Full
// 0b01000000U
#define STATUS_LIFO_ISF_MASK (uint8_t)(0b1 << 6)

void _INIT_REGISTERS(void);

void _FIFO_BLOCK_DATAFLOW(void);
void _LIFO_BLOCK_DATAFLOW(void);

void _FIFO_UNLOCK_DATAFLOW(void);
void _LIFO_UNLOCK_DATAFLOW(void);

void _INTERNAL_SETSTATUS_FIFO_FULL(void);
void _INTERNAL_SETSTATUS_FIFO_NFULL(void);

void _INTERNAL_SETSTATUS_LIFO_FULL(void);
void _INTERNAL_SETSTATUS_LIFO_NFULL(void);