#include "Solver.h"
#include "unordered_map"
#include "functional"
#include "../LongNumber/LongNumber.h"
#include "../LongComplex/LongComplex.h"
#include "stack"

LongComplex max(const LongComplex &a, const LongComplex &b) {
    throw std::logic_error("Complex numbers do not support comparisons");
}

LongComplex min(const LongComplex &a, const LongComplex &b) {
    throw std::logic_error("Complex numbers do not support comparisons");
}

struct Number {
    LongComplex lc;
    LongNumber ll;
    Type type;

    Number(const LongComplex &lc_, Type type_) {
        lc = lc_;
        type = type_;
    }

    Number(const LongNumber &ll_, Type type_) {
        ll = ll_;
        lc = LongComplex(ll);
        type = type_;
    }
};

template<class T>
static const std::unordered_map<std::string, std::pair<std::function<T(const std::vector<T> &args)>, int>> funcs = {
        {"+",         {[](const std::vector<T> &args) { return args[0] + args[1]; },      2}},
        {"-",         {[](const std::vector<T> &args) { return args[0] - args[1]; },      2}},
        {"*",         {[](const std::vector<T> &args) { return args[0] * args[1]; },      2}},
        {"/",         {[](const std::vector<T> &args) { return args[0] / args[1]; },      2}},
        {"pow",       {[](const std::vector<T> &args) { return pow(args[0], args[1]); },  2}},
        {"sqr",       {[](const std::vector<T> &args) { return pow(args[0], T(2)); },     1}},
        {"exp",       {[](const std::vector<T> &args) { return exp(args[0]); },           1}},
        {"sqrt",      {[](const std::vector<T> &args) { return sqrt(args[0]); },          1}},
        {"surd",      {[](const std::vector<T> &args) { return surd(args[0], args[1]); }, 2}},
        {"ln",        {[](const std::vector<T> &args) { return ln(args[0]); },            1}},
        {"lg",        {[](const std::vector<T> &args) { return log(args[0], T(10)); },    1}},
        {"log",       {[](const std::vector<T> &args) { return log(args[0], args[1]); },  2}},
        {"abs",       {[](const std::vector<T> &args) { return T(abs(args[0])); },        1}},
        {"factorial", {[](const std::vector<T> &args) { return factorial(args[0]); },     1}},
        {"max",       {[](const std::vector<T> &args) { return max(args[0], args[1]); },  2}},
        {"min",       {[](const std::vector<T> &args) { return max(args[0], args[1]); },  2}},
        {"floor",     {[](const std::vector<T> &args) { return floor(args[0]); },         1}},
        {"ceil",      {[](const std::vector<T> &args) { return ceil(args[0]); },          1}},
        {"rtg",       {[](const std::vector<T> &args) { return rad_to_grad(args[0]); },   1}},
};
static std::unordered_map<std::string, Number> constants = {
        {"Pi",   {LongNumber::Pi,    Type::num_real}},
        {"inf",  {LongNumber::inf,   Type::num_real}},
        {"infm", {LongNumber::infm,  Type::num_real}},
        {"cinf", {LongComplex::cinf, Type::num_complex}},
        {"e",    {LongNumber::e,     Type::num_real}},
        {"i",    {LongComplex::I,    Type::num_complex}},
        {"Ans",  {LongNumber::zero,  Type::num_real}},
};

std::string solver(parser_queue &a) {
    std::stack<Number> solver_stack;
    while (!a.empty()) {
        if (a.front().first.type == Type::num_real) {
            solver_stack.emplace(LongNumber(a.front().first.token), Type::num_real);
            a.pop();
        } else if (a.front().first.type == Type::num_complex) {
            solver_stack.emplace(LongComplex(a.front().first.token), Type::num_complex);
            a.pop();
        } else if (a.front().first.type == Type::constant) {
            if (!constants.contains(a.front().first.token)) {
                throw std::logic_error("Constant not found: " + a.front().first.token);
            }
            solver_stack.push(constants.at(a.front().first.token));
            a.pop();
        } else if (a.front().first.type == Type::oper) {
            Number n2 = solver_stack.top();
            solver_stack.pop();
            Number n1 = solver_stack.top();
            solver_stack.pop();
            if (n1.type == Type::num_real and n2.type == Type::num_real) {
                solver_stack.emplace(funcs<LongNumber>.at(a.front().first.token).first({n1.ll, n2.ll}), Type::num_real);
            } else {
                solver_stack.emplace(funcs<LongComplex>.at(a.front().first.token).first({n1.lc, n2.lc}), Type::num_complex);
            }
            a.pop();
        } else if (a.front().first.type == Type::func) {
            if (!funcs<LongComplex>.contains(a.front().first.token)) {
                throw std::logic_error("Function not found: " + a.front().first.token);
            }
            if (funcs<LongComplex>.at(a.front().first.token).second == a.front().second) {
                std::vector<Number> tmp_vec;
                bool all_real = true;
                for (int i = 0; i < a.front().second; ++i) {
                    tmp_vec.emplace_back(solver_stack.top());
                    solver_stack.pop();
                    if (tmp_vec[i].type == Type::num_complex) {
                        all_real = false;
                    }
                }
                if (all_real) {
                    std::vector<LongNumber> args;
                    for (long long i = (long long) tmp_vec.size() - 1; i >= 0; --i) {
                        args.emplace_back(tmp_vec[i].ll);
                    }
                    solver_stack.emplace(funcs<LongNumber>.at(a.front().first.token).first(args), Type::num_real);
                } else {
                    std::vector<LongComplex> args;
                    for (long long i = (long long) tmp_vec.size() - 1; i >= 0; --i) {
                        args.emplace_back(tmp_vec[i].lc);
                    }
                    solver_stack.emplace(funcs<LongComplex>.at(a.front().first.token).first(args), Type::num_complex);
                }
                a.pop();
            } else {
                throw std::logic_error("Invalid number of parameters for the function: " + a.front().first.token);
            }
        }
    }
    LongComplex tmp_c;
    LongNumber tmp_r;
    if (solver_stack.top().type == Type::num_real) {
        tmp_r = solver_stack.top().ll;
        constants.insert_or_assign("Ans", Number{tmp_r, Type::num_real});
        return tmp_r.to_string();
    } else {
        tmp_c = solver_stack.top().lc;
        constants.insert_or_assign("Ans", Number{tmp_c, Type::num_complex});
        return tmp_c.to_string();
    }
}