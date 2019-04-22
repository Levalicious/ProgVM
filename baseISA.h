#ifndef PROGVM_BASE_ISA
#define PROGVM_BASE_ISA
#include <stdint.h>

/* R-Types */
/* Op, Rs1, Rs2, Rd, 0-imm */
void add(uint64_t instr);
void sub(uint64_t instr);
void xorr(uint64_t instr);
void orr(uint64_t instr);
void sll(uint64_t instr);
void srl(uint64_t instr);
void sra(uint64_t instr);
void slt(uint64_t instr);
void sltu(uint64_t instr);

/* I-Types */
/* Op, Rs1, 0-rs2, Rd, Imm */
void addi(uint64_t instr);
void subi(uint64_t instr);
void xori(uint64_t instr);
void ori(uint64_t instr);
void slli(uint64_t instr);
void srli(uint64_t instr);
void srai(uint64_t instr);
void slti(uint64_t instr);
void sltiu(uint64_t instr);
void lw(uint64_t instr);
void lh(uint64_t instr);
void lhu(uint64_t instr);
void lq(uint64_t instr);
void lqu(uint64_t instr);
void lb(uint64_t instr);
void lbu(uint64_t instr);
void sw(uint64_t instr);
void sh(uint64_t instr);
void sq(uint64_t instr);
void sb(uint64_t instr);

/* B-Types */
/* Op, Rs1, Rs2, Rd, Imm */
void beq(uint64_t instr);
void bne(uint64_t instr);

/* J-Types */
/* Op, Rs1, Imm */
void j(uint64_t instr);

/* JR-Types */
/* Op, Rs1, 0-rs2, Rd, Imm */
void jr(uint64_t instr);

/* ?-Types */
/* Op, Rs1, 0-rs2, 0-rd, Imm */
void lui(uint64_t instr);

#endif