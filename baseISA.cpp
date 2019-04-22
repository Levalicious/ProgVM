#include "baseISA.h"
#include "main.h"

#define incrPC() reg[R_PC] += 8;

void add(uint64_t instr) {
    uint8_t rs1 = (instr >> 48);

    uint8_t rs2 = (instr >> 40);

    uint8_t rd = (instr >> 32);

    reg[rd] = reg[rs1] + reg[rs2];

    incrPC();
}

void sub(uint64_t instr) {
    uint8_t rs1 = (instr >> 48);

    uint8_t rs2 = (instr >> 40);

    uint8_t rd = (instr >> 32);

    reg[rd] = reg[rs1] - reg[rs2];

    incrPC();
}

void xorr(uint64_t instr) {
    uint8_t rs1 = (instr >> 48);

    uint8_t rs2 = (instr >> 40);

    uint8_t rd = (instr >> 32);

    reg[rd] = reg[rs1] ^ reg[rs2];

    incrPC();
}

void orr(uint64_t instr) {
    uint8_t rs1 = (instr >> 48);

    uint8_t rs2 = (instr >> 40);

    uint8_t rd = (instr >> 32);

    reg[rd] = reg[rs1] | reg[rs2];

    incrPC();
}

void sll(uint64_t instr) {
    uint8_t rs1 = (instr >> 48);

    uint8_t rs2 = (instr >> 40);

    uint8_t rd = (instr >> 32);

    reg[rd] = reg[rs1] << reg[rs2];

    incrPC();
}

void srl(uint64_t instr) {
    uint8_t rs1 = (instr >> 48);

    uint8_t rs2 = (instr >> 40);

    uint8_t rd = (instr >> 32);

    reg[rd] = reg[rs1] >> reg[rs2];

    incrPC();
}

void sra(uint64_t instr) {
    uint8_t rs1 = (instr >> 48);

    uint8_t rs2 = (instr >> 40);

    uint8_t rd = (instr >> 32);

    reg[rd] = (uint64_t) (((int64_t) reg[rs1]) >> ((int64_t) reg[rs2]));

    incrPC();
}

void slt(uint64_t instr) {
    uint8_t rs1 = (instr >> 48);

    uint8_t rs2 = (instr >> 40);

    uint8_t rd = (instr >> 32);

    if (((int64_t) reg[rs1]) < ((int64_t) reg[rs2])) {
        reg[rd] = 1;
    } else {
        reg[rd] = 0;
    }

    incrPC();
}

void sltu(uint64_t instr) {
    uint8_t rs1 = (instr >> 48);

    uint8_t rs2 = (instr >> 40);

    uint8_t rd = (instr >> 32);

    if (reg[rs1] < reg[rs2]) {
        reg[rd] = 1;
    } else {
        reg[rd] = 0;
    }

    incrPC();
}

void addi(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    uint32_t imm  = instr;

    reg[rd] = reg[rs] + imm;
    
    incrPC();
}

void subi(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    uint32_t imm  = instr;

    reg[rd] = reg[rs] - imm;

    incrPC();
}

void xori(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    uint32_t imm  = instr;

    reg[rd] = reg[rs] ^ ((uint64_t) imm);

    incrPC();
}

void ori(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    uint32_t imm  = instr;

    reg[rd] = reg[rs] | ((uint64_t) imm);

    incrPC();
}

void slli(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    uint32_t imm  = instr;

    reg[rd] = reg[rs] << imm;

    incrPC();
}

void srli(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    uint32_t imm  = instr;

    reg[rd] = reg[rs] >> imm;

    incrPC();
}

void srai(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    uint32_t imm  = instr;

    reg[rd] = (uint64_t)(((int64_t) reg[rs]) >> ((int32_t) imm));

    incrPC();
}

void slti(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    uint32_t imm  = instr;

    if (((int64_t) reg[rs]) < ((int64_t) signExtend(imm, 32))) {
        reg[rd] = 1;
    } else {
        reg[rd] = 0;
    }

    incrPC();
}

void sltiu(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    uint32_t imm  = instr;

    if (reg[rs] < imm) {
        reg[rd] = 1;
    } else {
        reg[rd] = 0;
    }

    incrPC();
}

void j(uint64_t instr) {
    /* Identify destination address */
    uint8_t rd = (instr >> 48);

    int64_t imm = signExtend((instr & 0xFFFFFFFFFFFF), 16);

    reg[rd] = reg[R_PC] + 8;

    reg[R_PC] += imm;
}

void jr(uint64_t instr) {
    uint8_t rs = (instr >> 48);
    
    uint8_t rd = (instr >> 32);

    int32_t imm = instr;

    reg[rd] = reg[R_PC] + 8;

    reg[R_PC] = reg[rs] + imm;
}

void beq(uint64_t instr) {
    uint8_t rs1 = (instr >> 48);

    uint8_t rs2 = (instr >> 40);

    uint8_t rd = (instr >> 32);

    int32_t imm  = instr;

    if (reg[rs1] == reg[rs2]) {
        reg[rd] = reg[R_PC] + 8;
        reg[R_PC] += imm;
    }
}

void bne(uint64_t instr) {
    uint8_t rs1 = (instr >> 48);

    uint8_t rs2 = (instr >> 40);

    uint8_t rd = (instr >> 32);

    int32_t imm  = instr;

    if (reg[rs1] != reg[rs2]) {
        reg[rd] = reg[R_PC] + 8;
        reg[R_PC] += imm;
    }
}

/* rs1 = address rd = value destination imm = offset */
void lw(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    int32_t imm = instr;

    uint64_t temp = memRead(reg[rs] + imm, 0, 8);

    if (littleEndian) {
        temp = swapEndian(temp);
    }

    reg[rd] = temp;

    incrPC();
}

void lh(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    int32_t imm = instr;

    uint64_t temp = memRead(reg[rs] + imm, 4, 4);

    if (littleEndian) {
        temp = swapEndian(temp);
    }

    reg[rd] = signExtend(temp, 32);

    incrPC();
}

void lhu(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    int32_t imm = instr;

    uint64_t temp = memRead(reg[rs] + imm, 4, 4);

    if (littleEndian) {
        temp = swapEndian(temp);
    }

    reg[rd] = temp;

    incrPC();
}

void lq(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    int32_t imm = instr;

    uint64_t temp = memRead(reg[rs] + imm, 6, 2);

    if (littleEndian) {
        temp = swapEndian(temp);
    }

    reg[rd] = signExtend(temp, 48);

    incrPC();
}

void lqu(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    int32_t imm = instr;

    uint64_t temp = memRead(reg[rs] + imm, 6, 2);

    if (littleEndian) {
        temp = swapEndian(temp);
    }

    reg[rd] = temp;

    incrPC();
}

void lb(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    int32_t imm = instr;

    uint64_t temp = memRead(reg[rs] + imm, 7, 1);

    if (littleEndian) {
        temp = swapEndian(temp);
    }

    reg[rd] = signExtend(temp, 56);

    incrPC();
}

void lbu(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rd = (instr >> 32);

    int32_t imm = instr;

    uint64_t temp = memRead(reg[rs] + imm, 7, 1);

    if (littleEndian) {
        temp = swapEndian(temp);
    }

    reg[rd] = temp;

    incrPC();
}

void sw(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rs2 = (instr >> 32);

    int32_t imm = instr;

    uint64_t temp = reg[rs2];

    if (littleEndian) {
        temp = swapEndian(temp);
    }

    memWrite(reg[rs] + imm, (uint8_t*) &temp, 0, 8);

    incrPC();
}

void sh(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rs2 = (instr >> 32);

    int32_t imm = instr;

    uint64_t temp = reg[rs2];

    if (littleEndian) {
        temp = swapEndian(temp);
    }

    memWrite(reg[rs] + imm, (uint8_t*) &temp, 4, 4);

    incrPC();
}

void sq(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rs2 = (instr >> 32);

    int32_t imm = instr;

    uint64_t temp = reg[rs2];

    if (littleEndian) {
        temp = swapEndian(temp);
    }

    memWrite(reg[rs] + imm, (uint8_t*) &temp, 6, 2);

    incrPC();
}

void sb(uint64_t instr) {
    uint8_t rs = (instr >> 48);

    uint8_t rs2 = (instr >> 32);

    int32_t imm = instr;

    uint64_t temp = reg[rs2];

    if (littleEndian) {
        temp = swapEndian(temp);
    }

    memWrite(reg[rs] + imm, (uint8_t*) &temp, 7, 1);

    incrPC();
}

void lui(uint64_t instr) {
    uint8_t rd = (instr >> 48);

    uint32_t imm = instr;

    reg[rd] = imm;
    reg[rd] = reg[rd] << 32;

    incrPC();
}