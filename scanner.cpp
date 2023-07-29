#include "scanner.h"
#include <cctype>

namespace clox {

scanner::scanner(const std::string& source)
    :start{0}, current {0}, line{1}, source{source} {}

token scanner::scan_token() {
    skip_white_space();
    start = current;
    if (at_end()) {
        return make_token(TOKEN_EOF);
    }

    char c = advance();
    if (isalpha(c) || c == '_') { return make_identifier_token(); }
    if (isdigit(c)) { return make_number_token(); }

    switch (c) {
        case '(': return make_token(TOKEN_LEFT_PAREN);
        case ')': return make_token(TOKEN_RIGHT_PAREN);
        case '{': return make_token(TOKEN_LEFT_BRACE);
        case '}': return make_token(TOKEN_RIGHT_BRACE);
        case ';': return make_token(TOKEN_SEMICOLON);
        case ',': return make_token(TOKEN_COMMA);
        case '.': return make_token(TOKEN_DOT);
        case '-': return make_token(TOKEN_MINUS);
        case '+': return make_token(TOKEN_PLUS);
        case '/': return make_token(TOKEN_SLASH);
        case '*': return make_token(TOKEN_STAR);
        case '!':
            return make_token(
                match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
        case '=':
            return make_token(
                match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
        case '<':
            return make_token(
                match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
        case '>':
            return make_token(
                match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
        case '"':
            return make_string_token();
    }

    return make_error_token("Unexpected character.");
}

void scanner::skip_white_space() {
    while (true) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                line += 1;
                advance();
                break;
            case '/':
                if (peek_next() == '/') {
                    // A comment goes until the end of the line.
                    while (peek() != '\n' && !at_end()) { advance(); }
                } else {
                    return;
                }
                break;
            default:
                return;
        }
    }
}

token scanner::make_token(token_type type) {
    return {type, source.substr(start, current-start), line};
}

token scanner::make_error_token(std::string_view message) {
    return {TOKEN_ERROR, message, line};
}

token scanner::make_string_token() {
    while (!at_end() && peek() != '"') {
        if (peek() == '\n') {
            line += 1;
        }
        advance();
    }

    if (at_end()) {
        return make_error_token("Unterminated string.");
    }

    // consume closing quote
    advance();
    return make_token(TOKEN_STRING);
}

token scanner::make_number_token() {
    while (isdigit(peek())) { advance(); }

    // Look for a fractional part.
    if (peek() == '.' && isdigit(peek_next())) {
        advance();
        while (isdigit(peek())) { advance(); }
    }

    return make_token(TOKEN_NUMBER);
}

token scanner::make_identifier_token() {
    while (isalnum(peek())) { advance(); }
    return make_token(identifier_type());
}

token_type scanner::identifier_type() {
    switch (source[start]) {
    case 'a':
        return check_keyword(1, 2, "nd", TOKEN_AND);
    case 'c':
        return check_keyword(1, 4, "lass", TOKEN_CLASS);
    case 'e':
        return check_keyword(1, 3, "lse", TOKEN_ELSE);
    case 'f':
        if (current - start > 1) {
        switch (source[start + 1]) {
            case 'a':
                return check_keyword(2, 3, "lse", TOKEN_FALSE);
            case 'o':
                return check_keyword(2, 1, "r", TOKEN_FOR);
            case 'u':
                return check_keyword(2, 1, "n", TOKEN_FUN);
            }
        }
        break;
    case 'i':
        return check_keyword(1, 1, "f", TOKEN_IF);
    case 'n':
        return check_keyword(1, 2, "il", TOKEN_NIL);
    case 'o':
        return check_keyword(1, 1, "r", TOKEN_OR);
    case 'p':
        return check_keyword(1, 4, "rint", TOKEN_PRINT);
    case 'r':
        return check_keyword(1, 5, "eturn", TOKEN_RETURN);
    case 's':
        return check_keyword(1, 4, "uper", TOKEN_SUPER);
    case 't':
        if (current - start > 1) {
        switch (source[start + 1]) {
            case 'h':
                return check_keyword(2, 2, "is", TOKEN_THIS);
            case 'r':
                return check_keyword(2, 2, "ue", TOKEN_TRUE);
            }
        }
        break;
    case 'v':
        return check_keyword(1, 2, "ar", TOKEN_VAR);
    case 'w':
        return check_keyword(1, 4, "hile", TOKEN_WHILE);
    }

    return TOKEN_IDENTIFIER;
}

token_type scanner::check_keyword(int matched_len, int to_match_len, std::string_view to_match, token_type type) {
    if ( (current - start == matched_len + to_match_len)
        && source.substr(start+matched_len, current-start - matched_len).compare(to_match) == 0) {
            return type;
        }
    return TOKEN_IDENTIFIER;
}

bool scanner::at_end() {
    return current == static_cast<int>(source.size());
}

char scanner::advance() {
    current += 1;
    return source[current -1];
}

bool scanner::match(char expected) {
    if (at_end()) { return false; }
    if (source[current] != expected) { return false; }
    current += 1;
    return true;
}

char scanner::peek() {
    return source[current];
}

char scanner::peek_next() {
    // string_view cannot access '\0'
    if (current >= static_cast<int>(source.size())-1) {
        return '\0';
    }
    return source[current+1];
}

}