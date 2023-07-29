#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "chunk.h"
#include "debug.h"
#include "vm.h"
#include "token.h"
#include "scanner.h"

void test_scanner(clox::token t) {
    static int line = -1;
    if (t.line != line) {
        std::cout << std::right << std::setfill('0') << std::setw(4) << t.line  << " ";
        line = t.line;
    } else {
        std::cout << "   | ";
    }
    std::cout << std::setw(2) << t.type << " '" << t.lexeme << "'\n";
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: clox [path]\n";
        std::exit(64);
    }

    // get source code
    std::ifstream in_file(argv[1]);
    if (!in_file) {
        std::cerr << "Could not open file \"" << argv[1] << "\".\n ";
        exit(74);
    }

    std::string source_code = std::string(std::istreambuf_iterator<char>(in_file), std::istreambuf_iterator<char>());
    in_file.close();

    // source code -> (Scanner)
    clox::scanner my_scanner(source_code);
    // (Scanner) -> tokens
    
    while (true) {
        clox::token new_token = my_scanner.scan_token();
        if (new_token.type == clox::TOKEN_EOF) {
            break;
        }
        test_scanner(new_token);
    }
    // tokens -> (Compiler)

    // (Compiler) -> bytecode chunks

    // bytecode chunks -> Virtual Machine

    // handle result

    
    clox::interpret_result result = clox::INTERPRET_OK;

    if (result == clox::INTERPRET_COMPILE_ERROR) { exit(65); }
    if (result == clox::INTERPRET_RUNTIME_ERROR) { exit(70); }

    return 0;
}