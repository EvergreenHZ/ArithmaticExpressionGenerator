#include <vector>
#include <string>

class ArithmaticExpression {
        public:
                /* I want good numbers */
                int MODULE;
                int gen_random();
                std::vector<int> sequence;

                explicit ArithmaticExpression(int module);
                //~ArithmaticExpression();

                /* a op b */
                //std::vector<std::string> gen_a_op_b();
                bool gen_a_op_b(std::vector<std::string> &);

                /* a op b op c */
                std::vector<std::string> gen_a_op_b_op_c();

                /* a op b op c */
                //std::vector<std::string> gen_a_op_b_op_c();
        public:
                /* helper functions */
                void int_to_string(int, std::string&);
                void get_factors(int, std::vector<int> &);
                int get_priority(char);
                bool good_enough(const int);
                bool cast_coin();
                int get_random(int);
                char gen_operator();

                bool collect_a_op_b_op_c(int, int, int, \
                                char, char, std::vector<std::string> &);

                /* make sure this four must be legal */
                bool a_plus_b(std::vector<std::string> &);
                bool a_minus_b(std::vector<std::string> &);
                bool a_times_b(std::vector<std::string> &);
                bool a_over_b(std::vector<std::string> &);

                /* split number to construct expression */
                bool split_a_plus_b(const int c, int& a, int& b);
                bool split_a_minus_b(const int c, int& a, int& b);
                bool split_a_times_b(const int c, int& a, int& b);
                bool split_a_over_b(const int c, int& a, int& b);


                /* helper */
                bool find_good_y_for_x_times_y(const int, int&);
                bool find_good_y_for_x_over_y(const int , int&);
                bool find_good_y_for_x_plus_y(const int, int&);
                bool find_good_y_for_x_minus_y(const int, int&);
};
