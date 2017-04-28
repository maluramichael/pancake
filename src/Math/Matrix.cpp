//
// Created by Michael Malura on 28/04/17.
//

#include "../../include/Math/Matrix.h"


std::ostream& Pancake::Math::operator<<(std::ostream& stream, const Pancake::Math::Matrix& m) {
    short width = 1;

    float min = 0, max = 0;

    for (short i = 0; i < 16; i++) {
        if (m.data[i]<min){
            min = m.data[i];
        }
        if (m.data[i]>max){
            max = m.data[i];
        }
    }

    if (max > 9 || abs(min) > 9) {
        width++;
    }
    if (max > 99 || abs(min) > 99) {
        width++;
    }
    if (max > 999 || abs(min) > 999) {
        width++;
    }
    if (max > 9999 || abs(min) > 9999) {
        width++;
    }
    if (max > 99999 || abs(min) > 99999) {
        width++;
    }

    if (min < 0) {
        width++;
    }

    std::cout << "[" << std::setfill(' ') << std::setw(width) << m.data[0];
    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[1];
    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[2];
    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[3];
    std::cout << ",\n";

    std::cout << std::setfill(' ') << std::setw(width + 1) << m.data[4];
    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[5];
    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[6];
    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[7];
    std::cout << ",\n";

    std::cout << std::setfill(' ') << std::setw(width + 1) << m.data[8];
    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[9];
    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[10];
    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[11];
    std::cout << ",\n";

    std::cout << std::setfill(' ') << std::setw(width + 1) << m.data[12];
    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[13];
    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[14];
    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[15];
    std::cout << "]\n";

    return stream;
}