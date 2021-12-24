#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include <fstream>
#include "Decoder.h"
#include "Random.h"

using namespace std;
int main(int argc, char* argv[]) {
    string encoded;
    int count;
    if (argc == 5 && strcmp(argv[1], "-i") == 0) {
        count = stoi(argv[3]);
        if ((count < 1) || (count > 100)) {
            cout << "Incorrect number of threads = " << count << "! Choose from [1, 100].\n";
            return 2;
        }
        ifstream input_stream(argv[2]);
        getline(input_stream, encoded);
    }
    else if (argc == 4 && strcmp(argv[1], "-f") == 0) {
        count = stoi(argv[2]);
        if ((count < 1) || (count > 100)) {
            cout << "Incorrect number of threads = " << count << "! Choose from [1, 100].\n";
            return 2;
        }
        encoded = gen_encrypted();
    }
    else {
        cout << "Incorrect command line!\n"
                "  Waited:\n"
                "     command -i input_file number_of_threads output_file\n"
                "  Or:\n"
                "     command -f number_of_threads output_file\n";
        return 1;
    }

    clock_t start_time = clock();
    cout << "Start..." << endl;
    cout << "Encrypted string: " << encoded << endl;
    Decoder decoder(encoded, count);
    ofstream output_stream(argv[4]);
    string decoded;
    try {
        decoded = decoder.decode();
    }
    catch (exception){
        cout << "Problems with decoding! Check your input data" << endl;
        return 2;
    }
    cout << "Decrypted string: " << decoded << endl;
    output_stream << "Decrypted string: " << decoded << endl;
    clock_t end_time = clock();
    double seconds = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Time has passed: " << seconds << "s." << endl;
    cout << "End." << endl;
    return 0;
}
