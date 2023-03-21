#ifndef MEGA_CALCAPP_PARSER_H
#define MEGA_CALCAPP_PARSER_H

#include "stack"
#include "string"
#include "vector"

enum Type {
    func = 'f',
    oper = 'o',
    num_real = 'r',
    num_complex = 'i',
    constant = 'c',
    open_bracket = '(',
    close_bracket = ')',
    separator = ','
};

struct Token {
    std::string token;
    Type type;

    Token(const std::string &token_, Type type_) {
        type = type_;
        token = token_;
    }

};

class Parser {
private:
    std::stack<Token> stack;

public:
    Parser() = default;

    Parser(const std::string &s);

    Parser(const Parser &s);

    Parser(Parser &&s) noexcept;

    Parser &operator=(const Parser &rhs) = default;

    Parser &operator=(Parser &&rhs) noexcept;

    bool empty();

    Token top();

    void push(const Token &s);

    void pop();

    ~Parser() = default;
};


#endif //MEGA_CALCAPP_PARSER_H
