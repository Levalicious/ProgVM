#include "main.h"
#include "baseISA.h"

/* Should be 512 kB of memory */
uint8_t memory[524288];

/* Registers */
uint64_t reg[R_COUNT];

bool littleEndian;

uint64_t signExtend(uint64_t x, int bitCount) {
    if ((x >> (bitCount - 1)) & 1) {
        x |= (UINT16_MAX << bitCount);
    }

    return x;
}

uint64_t swapEndian(uint64_t x) {
    uint8_t* arr = (uint8_t*) &x;

    uint64_t out;
    uint8_t* arr2 = (uint8_t*) &out;

    for (int i = 0; i < 8; i++) {
        arr2[7 - i] = arr[i];
    }

    return out;
}

void readImgFile(FILE* file) {
    uint64_t maxRead = (524288);
    uint64_t* p = ((uint64_t*)memory);
    size_t read = fread(p, sizeof(uint8_t), maxRead, file);

    /* If computer is little endian, load program, then swap endianness */
    if (littleEndian) {
        while (read-- > 0) {
            *p = swapEndian(*p);
            ++p;
        }
    }
}

int readImg(const char* imgPath) {
    FILE* file = fopen(imgPath, "rb");
    if (!file) {return 0; };
    readImgFile(file);
    fclose(file);
    return 1;
}

/* Memcpy arguments: origin pointer, target pointer, length */

void memWrite(uint64_t address, uint8_t* val, int offset, int len) {
    std::memcpy(&memory[address], &val[offset], len);
}

uint64_t memRead(uint64_t address, int offset, int len) {
    uint64_t result;
    uint8_t* arr = (uint8_t*) &result;

    std::memcpy(&arr[offset], &memory[address], len);

    return result;
}

bool isLE() {
    uint16_t val = 1;
    uint8_t* arr = (uint8_t*) &val;
    
    return (arr[0] == 1);
}

struct termios originalTio;

void disableInputBuffering() {
    tcgetattr(STDIN_FILENO, &originalTio);
    struct termios newTio = originalTio;
    newTio.c_lflag &= ~ICANON & ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newTio);
}

void restoreInputBuffering() {
    tcsetattr(STDIN_FILENO, TCSANOW, &originalTio);
}

void handleInterrupt(int signal) {
    restoreInputBuffering();
    printf("\n");
    exit(-2);
}

int running = 1;

void (*instructions[34])(uint64_t) = { add, sub, xorr, orr, sll, srl, sra, slt, sltu, addi, subi, xori, ori, slli, srli, srai, slti, sltiu, lw, lh, lhu, lq, lqu, lb, lbu, sw, sh, sq, sb, beq, bne, j, jr, lui };

int main(int argc, const char* argv[]) {
    littleEndian = isLE();

    if (argc < 2) {
        std::cout << "Program Usage: \n" << "ProgVM64 [Program File]\n";
        exit(2);
    }

    for (int j = 1; j < argc; ++j) {
        if (!readImg(argv[j])) {
            std::cout << "Failed to load image " << argv[j] << "\n";
            exit(1);
        }
    }

    signal(SIGINT, handleInterrupt);
    disableInputBuffering();

    enum { PC_START = 0x0000 };
    reg[R_PC] = PC_START;

    while (running) {
        uint64_t word = memRead(reg[R_PC], 0, 8);

        uint64_t tempc = reg[R_PC];

        uint8_t op = (word >> 56);

        if (op < 34) {
            (**instructions[op])(word);
        } else {
            std::cout << "HALT";
            running = 0;
        }

    }

    std::cout << "Execution successfully completed.\n";
    std::cout << "Value of Register 31: " << reg[R_R31] << "\n";

    restoreInputBuffering();
}