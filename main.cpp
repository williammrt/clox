#include "chunk.h"
#include "debug.h"

int main() {
    clox::chunk chunk;

    int constant = chunk.add_constant(1.2); 
    chunk.add_code(clox::OP_CONSTANT, 1);
    chunk.add_code(constant, 1);

    chunk.add_code(clox::OP_RETURN, 1);
    
    clox::disassemble_chunk(chunk, "test_chunk");
    return 0;
}