
#include "Parser.h"
#include "iostream"
#include "../LongNumber/LongNumber.h"
#include "../LongComplex/LongComplex.h"

static const std::string char_after_num = "+-*/(,)";
static const std::string operators = "+-*/,";

Parser::Parser(const Parser &s) {
    stack = s.stack;
}

Parser::Parser(Parser &&s) noexcept {
    stack = std::move(s.stack);
}

Parser &Parser::operator=(Parser &&rhs) noexcept {
    if (this == &rhs)
        return *this;
    stack = std::move(rhs.stack);
    return *this;
}

std::vector<Token> tokenizer(const std::string &s) {//обработать %
    if (s.empty())
        throw std::logic_error("Syntax error");
    long long pos = 0;
    std::vector<Token> tokens;
    if (s[0] == '-') {
        tokens.emplace_back("0", Type::num_real);
    }
    while (pos < s.size()) {
        if (s[pos] == '.') {
            throw std::logic_error("Syntax error");
        } else if (isdigit(s[pos])) {
            std::string buf;
            while (pos < s.size() and (isdigit(s[pos]) or s[pos] == '.')) {
                buf += s[pos++];
            }
            if (!correct_long_num(buf))
                throw std::logic_error("Syntax error");
            if (pos < s.size() and s[pos] == 'i') {
                ++pos;
                tokens.emplace_back(buf + 'i', Type::num_complex);
            } else {
                tokens.emplace_back(buf, Type::num_real);
            }
            if (pos < s.size() and char_after_num.find(s[pos]) == std::string::npos) {
                if (isalpha(s[pos]) or isdigit(s[pos])) {
                    tokens.emplace_back("*", Type::oper);
                } else {
                    throw std::logic_error("Syntax error");
                }
            }
            if (pos < s.size() and s[pos] == '(') {
                tokens.emplace_back("*", Type::oper);
            }
        } else if (operators.find(s[pos]) != std::string::npos) {
            if (pos < s.size() - 1) {
                if (isdigit(s[pos + 1]) or isalpha(s[pos + 1]) or s[pos + 1] == '(') {
                    tokens.emplace_back(std::string(1, s[pos]), s[pos] == ',' ? Type::separator : Type::oper);
                } else if (s[pos] == ',' and s[pos + 1] == '-') {
                    tokens.emplace_back(std::string(1, s[pos]), Type::separator);
                    tokens.emplace_back("0", Type::num_real);
                } else {
                    throw std::logic_error("Syntax error");
                }
                ++pos;
            } else {
                throw std::logic_error("Syntax error");
            }
        } else if (isalpha(s[pos])) {
            std::string buf;
            while (pos < s.size() and isalpha(s[pos])) {
                buf += s[pos++];
            }
            if (pos < s.size()) {
                if (s[pos] == '(') {
                    tokens.emplace_back(buf, Type::func);
                } else if (operators.find(s[pos]) != std::string::npos or s[pos] == ')') {
                    tokens.emplace_back(buf, Type::constant);
                } else {
                    throw std::logic_error("Syntax error");
                }
            } else {
                tokens.emplace_back(buf, Type::constant);
            }
        } else if (s[pos] == '(') {
            ++pos;
            if (pos < s.size()) {
                if (isdigit(s[pos]) or isalpha(s[pos]) or s[pos] == '(') {
                    tokens.emplace_back("(", Type::open_bracket);
                } else if (s[pos] == '-') {
                    tokens.emplace_back("(", Type::open_bracket);
                    tokens.emplace_back("0", Type::num_real);
                } else {
                    throw std::logic_error("Syntax error");
                }
            } else {
                throw std::logic_error("Syntax error");
            }
        } else if (s[pos] == ')') {
            ++pos;
            tokens.emplace_back(")", Type::close_bracket);
            if (pos < s.size() and (s[pos] == '(' or isdigit(s[pos]) or isalpha(s[pos]))) {
                tokens.emplace_back("*", Type::oper);
            }
        }
    }
    return tokens;
}

Parser::Parser(const std::string &s) {
    auto tokens = tokenizer(s);
    for (auto &token: tokens) {
        std::cout << token.token << ' ' << (char) token.type << '\n';
    }
}

bool Parser::empty() {
    return stack.empty();
}

Token Parser::top() {
    return stack.top();
}

void Parser::push(const Token &s) {
    stack.push(s);
}

void Parser::pop() {
    return stack.pop();
}


