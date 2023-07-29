#ifndef clox_scanner_h
#define clox_scanner_h

#include <string>
#include <string_view>
#include "token.h"


namespace clox {

/**
 * @brief Get source code as big string, return tokens
 * @warning For now, no literal information, only lexeme
*/
class scanner {
public:
    scanner(const std::string& source);
    token scan_token();
private:
    int start, current, line;
    const std::string_view source;

    void skip_white_space();
    token make_token(token_type type);
    token make_error_token(std::string_view message);
    /**
     * @warning the lexeme also contains "", be careful
    */
    token make_string_token();
    token make_number_token();
    token make_identifier_token();
    token_type identifier_type();
    token_type check_keyword(int matched_len, int to_match_len, std::string_view to_match, token_type type);

    bool at_end();
    char advance();
    bool match(char expected);
    char peek();
    char peek_next();
};

}

#endif