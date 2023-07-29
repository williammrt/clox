#include "chunk.h"

namespace clox {

void chunk::add_code(uint8_t byte, int line) {
    code.push_back(byte);
    lines.push_back(line);
}

uint8_t chunk::get_code(int offset) const {
    return code[offset];
}

int chunk::code_size() const {
    return code.size();
}

int chunk::add_constant(value val) {
    constants.push_back(val);
    return constants.size()-1;
}

value chunk::get_constant(int offset) const {
    return constants[offset];
}

int chunk::get_line(int offset) const {
    return lines[offset];
}

}