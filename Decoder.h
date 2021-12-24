#ifndef AVS_HW5_DECODER_H
#define AVS_HW5_DECODER_H

#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <vector>
#include <mutex>

using namespace std;



class Decoder {
public:
    Decoder(const string &str, int threadNumber = 1);

    string decode();

private:
    int threadNumber;
    int next_task;
    mutex mtx;
    vector<string> data;
    const string table[53] =
            { " ",
              "b", "l", "i", "s", "n", "o", "v", "f", "u", "e", "j", "w", "x",
              "k", "d", "q", "p", "c", "y", "g", "z", "m", "h", "t", "a", "r",
              "V", "R", "M", "D", "W", "Y", "Q", "A", "L", "J", "U", "X", "F",
              "C", "P", "H", "T", "K", "O", "B", "N", "I", "S", "G", "E", "Z"
            };

    void decode_char();
};


#endif //AVS_HW5_DECODER_H
