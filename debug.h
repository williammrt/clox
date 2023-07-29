#ifndef clox_debug_h
#define clox_debug_h

#include <string>
#include "chunk.h"

namespace clox {

class disassemble_chunk {
public:

    /**
     * @param chunk module you want to disassemble
     * @param name how to name the module
    */
    explicit disassemble_chunk(const chunk& chunk, std::string name);

private:
    const chunk& my_chunk;

    /**
     * @brief base on opcode, call suitable handler
     * @param offset instruction's offset in array of bytecode
     * @return The offset of the next opcode
    */
    int disassemble_instr(int offset);

    /**
     * @brief handle 1 byte instruction
     * @return The offset of the next opcode
    */
    int simple_instr(std::string name, int offset);

    /**
     * @brief handle OP_CONSTANT
     * @return The offset of the next opcode
    */
    int constant_instr(std::string name, uint8_t offset);
};

}

#endif