#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main() {
    clox::chunk chunk;

    int constant = chunk.add_constant(1.2); 
    chunk.add_code(clox::OP_CONSTANT, 123);
    chunk.add_code(constant, 123);

    constant = chunk.add_constant(3.4); 
    chunk.add_code(clox::OP_CONSTANT, 123);
    chunk.add_code(constant, 123);

    chunk.add_code(clox::OP_ADD, 123);

    constant = chunk.add_constant(5.6); 
    chunk.add_code(clox::OP_CONSTANT, 123);
    chunk.add_code(constant, 123);

    chunk.add_code(clox::OP_DIVIDE, 123);
    chunk.add_code(clox::OP_NEGATE, 123);

    chunk.add_code(clox::OP_RETURN, 123);


    clox::disassemble_chunk(chunk, "test_chunk");

    clox::virtual_machine vm(chunk);
    vm.interpret();

    return 0;
}