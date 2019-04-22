#ifndef PROGVM_MAIN
#define PROGVM_MAIN
#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>
#include <iostream>
#include <cstring>

enum
{
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_R8,
    R_R9,
    R_R10,
    R_R11,
    R_R12,
    R_R13,
    R_R14,
    R_R15,
    R_R16,
    R_R17,
    R_R18,
    R_R19,
    R_R20,
    R_R21,
    R_R22,
    R_R23,
    R_R24,
    R_R25,
    R_R26,
    R_R27,
    R_R28,
    R_R29,
    R_R30,
    R_R31,
    R_PC,
    R_COND,
    R_COUNT
};

/* Should be 512 kB of memory */
extern uint8_t memory[524288];

/* Registers */
extern uint64_t reg[R_COUNT];

extern void memWrite(uint64_t address, uint8_t* val, int offset, int len);

extern uint64_t memRead(uint64_t address, int offset, int len);

extern uint64_t signExtend(uint64_t x, int bitCount);

extern uint64_t swapEndian(uint64_t x);

extern bool littleEndian;

#endif