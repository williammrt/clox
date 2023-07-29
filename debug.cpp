#include <iomanip>
#include <iostream>
#include "debug.h"

namespace clox {

disassemble_chunk::disassemble_chunk(const chunk& outer_chunk, std::string name)
    :my_chunk {outer_chunk} {

    std::cout << "== " << name << " ==\n";
    for (int offset = 0; offset < my_chunk.code_size();) {
        offset = disassemble_instr(offset);
    }
}

int disassemble_chunk::disassemble_instr(int offset) {
    std::cout << std::right << std::setfill('0') << std::setw(4) << offset << " ";
    // about setting precision:
    // https://stackoverflow.com/questions/530614/print-leading-zeros-with-c-output-operator

    if (offset > 0 && (my_chunk.get_line(offset) == my_chunk.get_line(offset - 1))) {
        std::cout << "   | ";
    } else {
        std::cout << std::right << std::setfill(' ') << std::setw(4)
                << my_chunk.get_line(offset) << " ";
    }

    uint8_t instruction = my_chunk.get_code(offset);
    switch (instruction) {
        case OP_CONSTANT:
            return constant_instr("OP_CONSTANT", offset);
        case OP_ADD:
            return simple_instr("OP_ADD", offset);
        case OP_SUBTRACT:
            return simple_instr("OP_SUBTRACT", offset);
        case OP_MULTIPLY:
            return simple_instr("OP_MULTIPLY", offset);
        case OP_DIVIDE:
            return simple_instr("OP_DIVIDE", offset);
        case OP_NEGATE:
            return simple_instr("OP_NEGATE", offset);
        case OP_RETURN:
            return simple_instr("OP_RETURN", offset);
        default:
            std::cout << "Unknown opcode " << instruction
                    << "\n"; // in book it print out opcode in byte
            return offset + 1;
    }
}

int disassemble_chunk::simple_instr(std::string name, int offset) {
    std::cout << name << "\n";
    return offset + 1;
}

int disassemble_chunk::constant_instr(std::string name, uint8_t offset) {
    uint8_t constant_pos = my_chunk.get_code(offset + 1);
    std::cout << std::left << std::setfill(' ') << std::setw(16) << name << " "
                << std::right << std::setw(4) << static_cast<int>(constant_pos)
                << " '";
    // static cast here because cout << uint8_t will print char instead of int
    print_value(my_chunk.get_constant(constant_pos));
    std::cout << "'\n";
    return offset + 2;
}

};