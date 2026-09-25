#pragma once

#include <stdint.h>

typedef struct {
    volatile uint8_t CTRL;
    volatile uint8_t STATUS;
} DataRegisters;

extern DataRegisters *DATA0;

#define MASK_ALL (0xFF << 0)

// == CTRL Register masks ==
// LIFO Data Flow Not Blocked
// 0b01100000U
#define CTRL_LIFO_DFNB_MASK (0b11 << 5);

// LIFO Data Flow Blocked
// 0b00001000U
#define CTRL_LIFO_DFB_MASK (0b01 << 3);

// FIFO Data Flow Not Blocked
// 0b10010000U
#define CTRL_FIFO_DFNB_MASK (0b1001 << 4);

// FIFO Data Flow Blocked
// 0b10000000U
#define CTRL_FIFO_DFB_MASK (0b01 << 7);


// == STATUS Register masks ==
// Data FIFO is Full
// 0b11000000U
#define STATUS_FIFO_ISF_MASK (0b11 << 6)

// Data FIFO is Not Full
// 0b10000000U
#define STATUS_FIFO_NF_MASK (0b01 << 7)

// Data LIFO is Full
// 0b00110000U
#define STATUS_LIFO_ISF_MASK (0b11 << 4)

// Data LIFO is Not Full
// 0b00100000U
#define STATUS_LIFO_NF_MASK (0b01 << 5)

void _INIT_REGISTERS(void);