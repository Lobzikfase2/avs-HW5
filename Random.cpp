//
// Created by Игорь on 24.12.2021.
//

#include "Random.h"

std::string gen_encrypted(){
    srand(time(nullptr));
    std::string str;

    for (int i = 0; i < rand() % 21 + 3; ++i) {
        int chr = rand() % 53;
        if (chr < 10) {
            str += "0" + std::to_string(chr);
        }
        else {
            str += std::to_string(chr);
        }
    }
    return str;
}
