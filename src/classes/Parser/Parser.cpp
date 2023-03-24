#include "Parser.h"
#include "iostream"
#include "stack"
#include "../LongNumber/LongNumber.h"
#include "../LongComplex/LongComplex.h"

static const std::string char_after_num = "+-*/(,)";
static const std::string operators = "+-*/,";
static const std::string low_priority_operators = "+-";
static const std::string high_priority_operators = "*/";

std::vector<Token> tokenizer(const std::string &s) {
    if (s.empty())
        throw std::logic_error("Syntax error");
    long long pos = 0;
    std::vector<Token> tokens;
    if (s[0] == '-') {
        tokens.emplace_back("0", Type::num_real);
    }
    while (pos < s.size()) {
        if (isdigit(s[pos])) {
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
        } else {
            throw std::logic_error("Syntax error");
        }
    }
    return tokens;
}

std::queue<std::pair<Token, int>> parser(const std::string &s) {
    std::string str = s;
    std::erase(str, ' ');
    while (str.find('%') != std::string::npos) {
        str.replace(str.find('%'), 1, "/100");
    }
    auto tokens = tokenizer(str);
    std::queue<std::pair<Token, int>> out_queue;
    std::stack<std::pair<Token, int>> stack;
    for (auto &token: tokens) {
        if (token.type == Type::num_real or token.type == Type::num_complex or token.type == Type::constant) {
            out_queue.emplace(token, 0);
        } else if (token.type == Type::func) {
            stack.emplace(token, 0);
        } else if (token.type == Type::separator) {
            if (stack.empty()) {
                throw std::logic_error("Syntax error");
            }
            while (stack.top().first.type != Type::open_bracket) {
                out_queue.push(stack.top());
                stack.pop();
                if (stack.empty()) {
                    throw std::logic_error("Syntax error");
                }
            }
            if (stack.top().second != 0) {
                ++stack.top().second;
            } else {
                throw std::logic_error("Syntax error");
            }
        } else if (token.type == Type::oper) {
            if (token.token == "+" or token.token == "-") {
                while (!stack.empty() and stack.top().first.type == Type::oper) {
                    out_queue.push(stack.top());
                    stack.pop();
                }
                stack.emplace(token, 0);
            } else {
                while (!stack.empty() and stack.top().first.type == Type::oper and (stack.top().first.token == "*" or stack.top().first.token == "/")) {
                    out_queue.push(stack.top());
                    stack.pop();
                }
                stack.emplace(token, 0);
            }
        } else if (token.type == Type::open_bracket) {
            stack.emplace(token, (!stack.empty() and stack.top().first.type == Type::func) ? 1 : 0);
        } else if (token.type == Type::close_bracket) {
            if (stack.empty()) {
                throw std::logic_error("Syntax error");
            }
            while (stack.top().first.type != Type::open_bracket) {
                out_queue.push(stack.top());
                stack.pop();
                if (stack.empty()) {
                    throw std::logic_error("Syntax error");
                }
            }
            int tmp_counter = stack.top().second;
            stack.pop();
            if (!stack.empty() and stack.top().first.type == Type::func) {
                out_queue.emplace(stack.top().first, tmp_counter);
                stack.pop();
            }
        }
    }
    while (!stack.empty()) {
        if (stack.top().first.type == Type::open_bracket) {
            throw std::logic_error("Syntax error");
        }
        out_queue.push(stack.top());
        stack.pop();
    }
    return out_queue;
}
