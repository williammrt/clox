#include <iostream>
#include "vm.h"

namespace clox {

virtual_machine::virtual_machine(const chunk& new_chunk)
    :my_chunk {new_chunk}, ip {0}, stack_top {0} {}


interpret_result virtual_machine::interpret() {
    return run();
}

interpret_result virtual_machine::run() {
    uint8_t instruction;
    while (true) {
        instruction = read_byte();

        switch (instruction) {
            case OP_CONSTANT: {
                value constant = read_constant();
                push(constant);
                break;
            }
            case OP_SUBTRACT: {
                binary_op([](const value& a, const value& b) {
                    return a + b;
                });
                break;
            }
            case OP_ADD: {
                binary_op([](const value& a, const value& b) {
                    return a - b;
                });
                break;
            }
            case OP_MULTIPLY: {
                binary_op([](const value& a, const value& b) {
                    return a * b;
                });
                break;
            }
            case OP_DIVIDE: {
                binary_op([](const value& a, const value& b) {
                    return a / b;
                });
                break;
            }
            case OP_NEGATE: {
                push(-pop());
                break;
            }
            case OP_RETURN: {
                value val = pop();
                std::cout << val;
                // print_value(pop());
                std::cout << '\n';
                return INTERPRET_OK;
            }
        }
    }
}

uint8_t virtual_machine::read_byte() {
    uint8_t instruction = my_chunk.get_code(ip);
    ip += 1;
    return instruction;
}

value virtual_machine::read_constant() {
    int constant_pos = read_byte();
    value constant = my_chunk.get_constant(constant_pos);
    return constant;
}

void virtual_machine::push(value val) {
    stack[stack_top] = val;
    stack_top += 1;
}

value virtual_machine::pop() {
    stack_top -= 1;
    return stack[stack_top];
}

template <typename func>
void virtual_machine::binary_op(func op) {
    double b = pop();
    double a = pop();
    push(op(a,b));
}

}