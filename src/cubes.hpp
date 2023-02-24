#pragma once
#include <vector>
#include <random>

class Cubes {
 private :
        std::vector<int> cubes_vector;

 public:
        Cubes() : cubes_vector(1) {}

        explicit Cubes(int modifier) : cubes_vector(modifier) {}

        std::vector<int> &get_vector() { return this->cubes_vector; }

        void set_num(size_t position, int num) {
            if (!this->is_element_valid(num)) {
                 throw "incorrect num on cubes element";
            }
            this->get_vector().at(position) = num;
        }

        bool is_element_valid(size_t position) {
            return this->get_vector().at(position) >= 1 && this->get_vector().at(position) <= 6;
        }

        bool is_element_valid(int element) { return element >= 1 && element <= 6;}

        void fill_cubes(int modifier) {
            for (size_t iter = 0; iter != this->get_vector().size(); iter++) {
                std::random_device random_device;  // Источник энтропии.
                std::mt19937 generator(random_device());  // Генератор случайных чисел.
                std::uniform_int_distribution<> distribution(1, 6);  // Равномерное распределение [1, 6]
                this->set_num(iter, distribution(generator));  // Случайное число.
            }
        }

        bool is_attack_successful() {
            bool result = false;
            for (size_t start = 0; start != this->get_vector().size(); start++) {
                if (this->get_vector().at(start) == 5
                    || this->get_vector().at(start) == 6) {
                    result = true;
                    break;
                }
            }
        return result;
    }
};
