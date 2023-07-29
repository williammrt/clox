#ifndef clox_chunk_h
#define clox_chunk_h

#include <vector>
#include "common.h"
#include "value.h"

namespace clox {

enum Opcode {
    OP_CONSTANT,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_RETURN
};

/**
 * Data structure for holding bytecode
*/
class chunk {
public:
    /**
     * @brief add byte to code, record line information
    */
    void add_code(uint8_t byte, int line);

    /**
     * @return byte-code at offset
    */
    uint8_t get_code(int offset) const;

    int code_size() const;

    /**
     * @brief add val to constant pool
     * @return newly add val's pos in constant pool
    */
    int add_constant(value val);

    /**
     * @return value in constant pool at offset
    */
    value get_constant(int offset) const;

    int get_line(int offset) const;

private:
    /**
     * @brief array of bytecode
    */
    std::vector<uint8_t> code;

    /**
     * @brief constant pool
    */
    std::vector<value> constants;

    /**
     * @brief lines for debug, lines.size() == num of OP in code
    */
    std::vector<int> lines;

};

}

#endif