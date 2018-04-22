#pragma once

#include <string>
#include <vector>

class Evaluation {
        public:
                int solution(std::string);
                std::vector<std::string> infixToSuffix(const std::string&);
                int rpn(std::vector<std::string> &);

        public:
                int eval(int, int, std::string);
                bool is_operator(const std::string&);
                void print_vector_string(std::vector<std::string> &);

                void handleOperator(std::vector<std::string> &, char, \
                                    std::vector<std::string>&);
                bool inferier(char, char);
                bool superier(char, char);
                int getPriority(char);
                bool isNumber(char);
                bool isOperator(char);
                bool isSpace(char c);
};
