#ifndef MEGA_CALCAPP_SOLVER_H
#define MEGA_CALCAPP_SOLVER_H

#include "../Parser/Parser.h"

using parser_queue = decltype(parser(""));

std::string solver(parser_queue &a);

std::string derivative_solver(parser_queue &a);

#endif //MEGA_CALCAPP_SOLVER_H
