#ifndef MEGA_CALCAPP_PARSER_H
#define MEGA_CALCAPP_PARSER_H

#include "queue"
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

std::vector<Token> tokenizer(const std::string &s);

std::queue<std::pair<Token, int>> parser(const std::string &s);


#endif //MEGA_CALCAPP_PARSER_H
