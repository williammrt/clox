#include "chunk.h"

void clox::chunk::add_code(uint8_t byte, int line) {
    code.push_back(byte);
    lines.push_back(line);
}

uint8_t clox::chunk::get_code(int offset) const {
    return code[offset];
}

int clox::chunk::code_size() const {
    return code.size();
}

int clox::chunk::add_constant(value val) {
    constants.push_back(val);
    return constants.size()-1;
}

clox::value clox::chunk::get_constant(int offset) const {
    return constants[offset];
}

int clox::chunk::get_line(int offset) const {
    return lines[offset];
}