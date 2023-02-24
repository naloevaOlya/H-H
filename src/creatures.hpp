#pragma once
#include <map>
#include <random>
#include <iostream>

enum characteristics {health, protection, attack, damage_start, damage_end};

class Creature {
 private:
        std::map <characteristics, int> attribute;

 public:
        Creature() : attribute{{characteristics::health, 0}, {characteristics::protection, 0},
                        {characteristics::attack, 0}, {characteristics::damage_start, 0},
                        {characteristics::damage_end, 0}} {};

        bool is_data_valid(int new_num, characteristics key) {
            if (!is_key_valid(key)) {
                throw "incorrect key-characteristic for creatures";
            }
            if (key == health) {
                return new_num >= 0;
            } else if (key == protection || key == attack) {
                return new_num >= 0 && new_num <= 20;
            } else {
                return true;  // так как на диапазон урона не стоит никаких условий кроме целочисленности
            }
        }

        bool is_key_valid(characteristics key) {
            return key == health || key == protection || key == attack ||
                    key == damage_start || key == damage_end;
            }

        void set_attribute(int smth, characteristics key) {
            if (!is_data_valid(smth, key)) {
                throw "incorrect data for creatures";
            }
            this->attribute[key] = smth;
        }

        std::map <characteristics, int> &get_attribute() { return this->attribute;}

        bool is_it_alive() { return this->get_attribute()[health] > 0; }

        int attack_modifier(Creature *defensive) {
            return ( this->get_attribute()[attack] - defensive->get_attribute()[protection] + 1);
        }

        void fix_damage() {
            int start = this->get_attribute()[damage_start];
            int end = this->get_attribute()[damage_end];
            if (start > end) {
                this->set_attribute(start, damage_end);
                this->set_attribute(end, damage_start);
            }
        }

        int damage_power() {
            this->fix_damage();
            int start = this->get_attribute()[damage_start];
            int end = this->get_attribute()[damage_end];
            std::random_device random_device;
            std::mt19937 generator(random_device());
            std::uniform_int_distribution<> distribution(start, end);
            return distribution(generator);
        }

        void hit(Creature *defensive, int damage_power) {
            int result = defensive->get_attribute()[health] - damage_power;
            if (result < 0) {
                defensive->set_attribute(0, health);
            } else {
                defensive->set_attribute(result, health);
            }
        }
};

class Gamer : public Creature {
 private:
        int attempts;
        int max_recovery = this->get_attribute()[characteristics::health];

 public:
        Gamer(): attempts(0) {}

        Gamer(int _health, int _protection, int _attack, int _damage_start, int _damage_end) : attempts(0) {
            if (!this->is_data_valid(_health, health) || !this->is_data_valid(_protection, protection)
            || !this->is_data_valid(_attack, attack)) {
                throw  "incorrect attribures";
            }
            this->set_attribute(_health, health);
            this->set_attribute(_protection, protection);
            this->set_attribute(_attack, attack);
            this->set_attribute(_damage_start, damage_start);
            this->set_attribute(_damage_end, damage_end);
            this->set_recovery(_health/2);
        }

        bool num_is_valid(int num) { return num >= 0 && num <= 3;}

        const int &get_recovery() { return this->max_recovery;}

        int &get_num_attemps() { return this->attempts;}

        void set_recovery(int num) {
            if (num > this->get_attribute()[health]/2) {
                throw "processing up to 50% is acceptable";
            }
            this->max_recovery = num;}

        void set_attemps(int num) {
            if (!num_is_valid(num)) {
                throw "incorrect num of attempts";
            }
            this->attempts = num;
        }

        void healing() {
            if (this->get_num_attemps() < 3) {
                this->set_attemps(this->get_num_attemps()+1);
                this->set_attribute(this->get_attribute()[health] + this->max_recovery/2, health);
                std::cout << "Gamer healed to " << this->get_attribute()[health] << std::endl;
            }
        }
};

class Monster : public Creature {
 public:
        Monster(int _health, int _protection, int _attack, int _damage_start, int _damage_end) {
            if (!this->is_data_valid(_health, health) || !this->is_data_valid(_protection, protection)
            || !this->is_data_valid(_attack, attack)) {
                throw  "incorrect attribures";
            }
            this->set_attribute(_health, health);
            this->set_attribute(_protection, protection);
            this->set_attribute(_attack, attack);
            this->set_attribute(_damage_start, damage_start);
            this->set_attribute(_damage_end, damage_end);
        }
};

