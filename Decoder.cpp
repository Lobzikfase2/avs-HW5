//
// Created by Игорь on 24.12.2021.
//

#include "Decoder.h"

Decoder::Decoder(const string &str, int threadNumber)  {
    for (int i = 0; i < str.length()/2; ++i) {
        data.push_back(str.substr(i*2, 2));
    }
    this->threadNumber = threadNumber;
}

string Decoder::decode() {
    next_task = 0;
    thread *workers[threadNumber];
    for (int i=0 ; i<threadNumber ; i++) {
        workers[i] = new thread{[this](){decode_char();}};
    }

    for (int i=0 ; i<threadNumber ; i++) {
        workers[i]->join();
        delete workers[i];
    }

    string encoded_data;
    for (int i = 0; i < data.size(); ++i) {
        encoded_data += data.at(i);
    }
    return encoded_data;
}

void Decoder::decode_char()  {
    int current_task;
    while (true) {
        mtx.lock();
        current_task = next_task;
        next_task++;
        if (current_task >= data.size()) {
            mtx.unlock();
            break;
        }
        mtx.unlock();
        string encoded = data[current_task];
        string decoded = table[stoi(encoded)];
        data[current_task] = decoded;

        stringstream ss;
        ss << this_thread::get_id();
        string log = "Thread ID: " + to_string(stoi(ss.str())-1);
        log += ", Task " + to_string(current_task);
        log += ": " + encoded;
        log +=  + " -> " + decoded;
        cout<<log + "\n";
    }
}