#ifndef clox_vm_h
#define clox_vm_h

#include <array>
#include "chunk.h"

namespace clox {

enum interpret_result {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
};

/**
 * @brief Virtual Machine class that execute bytecode
 * @todo DEBUG_TRACE_EXECUTION
*/
class virtual_machine {
public:
    static constexpr int STACK_MAX = 256;

    explicit virtual_machine(const chunk& new_chunk);

    /**
     * @brief Interpret the chunk of code
    */
    interpret_result interpret();

private:
    const chunk& my_chunk;

    /**
     * @brief instruction pointer
    */
    int ip;

    std::array<value, STACK_MAX> stack;
    int stack_top;

    interpret_result run();
    /**
     * @brief return a new bytecode and move ip forward
    */
    uint8_t read_byte();

    /**
     * @brief return the value point to in bytecode, no need handle ip
    */
    value read_constant();

    /**
     * @brief push val to stack
    */
    void push(value val);

    /**
     * @brief pop value from stack
     * @return value just popped
    */
    value pop();

    template <typename func>
    void binary_op(func op);
};

};

#endif