#include "creatures.hpp"
#include "cubes.hpp"

void playing(Creature *gamer, Creature *monster);
void print_result(Gamer gamer);
void print_info(Gamer gamer, Creature monster);
bool is_need_to_stop(int gamer_h, int monster_h, Creature *gamer, Creature *monster);

int main() {
    try {
        Gamer aboba(25, 6, 17, 1, 6);
        Monster buba(40, 15, 18, 1, 6);

        int gamer_h = aboba.get_attribute()[health];
        int monster_h = buba.get_attribute()[health];

        while (aboba.is_it_alive() && buba.is_it_alive()) {
            print_info(aboba, buba);
            playing(&aboba, &buba);
            playing(&buba, &aboba);
            if (aboba.get_attribute()[health] < 10) {
                aboba.healing();
                }
            if (is_need_to_stop(gamer_h, monster_h, &aboba, &buba)) {  // не доспускает бесконечного цикла
            // при отрицательных значениях диапазона урона
                break;
            }
        }
        print_result(aboba);
    } catch (char const* & ex) {
        std::cout << ex << std::endl;
    }
    return 0;
}

bool is_need_to_stop(int gamer_h, int monster_h, Creature *gamer, Creature *monster) {
    return (gamer_h*10 < gamer->get_attribute()[health] || monster_h*10 < monster->get_attribute()[health]);
}

void playing(Creature *gamer, Creature *monster) {
    Cubes cubes;
    cubes.fill_cubes(gamer->attack_modifier(monster));
    if (cubes.is_attack_successful()) {
        gamer->hit(monster, gamer->damage_power());
        }
}

void print_result(Gamer gamer) {
    gamer.is_it_alive() ? std::cout << "Gamer winner" << std::endl :
                    std::cout << "Monster winner" << std::endl;
}

void print_info(Gamer gamer, Creature monster) {
     std::cout  << "\nGamer:"<< gamer.get_attribute()[health] << " attemps " <<
     gamer.get_num_attemps() << "\nMonster:" << monster.get_attribute()[health] << std::endl;
}



