//

#include "../../include/Math/Matrix.h"


//}

void Pancake::Math::Matrix::translate(Pancake::Math::Matrix& m, Pancake::Math::Vector2 v) {
    m.loadIdentity();
    m.data[3] = v.x;
    m.data[7] = v.y;
}

void Pancake::Math::Matrix::scale(Pancake::Math::Matrix& m, Pancake::Math::Vector2 v) {
    m.loadIdentity();
    m.data[0] = v.x;
    m.data[5] = v.y;
}

void Pancake::Math::Matrix::rotateX(Pancake::Math::Matrix& m, float t) {
    m.loadIdentity();
    m.data[5] = cos(t);
    m.data[6] = -(sin(t));
    m.data[9] = sin(t);
    m.data[10] = cos(t);
}

void Pancake::Math::Matrix::rotateY(Pancake::Math::Matrix& m, float t) {
    m.loadIdentity();
    m.data[0] = cos(t);
    m.data[2] = sin(t);
    m.data[8] = -(sin(t));
    m.data[10] = cos(t);
}

void Pancake::Math::Matrix::rotateZ(Pancake::Math::Matrix& m, float t) {
    m.loadIdentity();
    m.data[0] = cos(t);
    m.data[1] = -(sin(t));
    m.data[5] = sin(t);
    m.data[6] = cos(t);
}

void Pancake::Math::Matrix::ortho(Pancake::Math::Matrix& m,
                                  float left, float right,
                                  float bottom, float top,
                                  float near, float far) {
    m.loadIdentity();
    m.data[0] = 2 / (right - left);
    m.data[3] = -((right + left) / (right - left));
    m.data[5] = 2 / (top - bottom);
    m.data[7] = -((top + bottom) - (top - bottom));
    m.data[9] = (-2) / (far - near);
    m.data[10] = -((far + near) / (far - near));

}


float Pancake::Math::Matrix::combineRowAndColumn(float* row, float* column) {
    return (row[0] * column[0]) +
           (row[1] * column[1]) +
           (row[2] * column[2]) +
           (row[3] * column[3]);
}

//
// Created by Michael Malura on 28/04/17.
//std::ostream& Pancake::Math::Matrix::operator<<(std::ostream& stream, const Pancake::Math::Matrix& m) {
//    short width = 1;
//
//    float min = 0, max = 0;
//
//    for (short i = 0; i < 16; i++) {
//        if (m.data[i] < min) {
//            min = m.data[i];
//        }
//        if (m.data[i] > max) {
//            max = m.data[i];
//        }
//    }
//
//    if (max > 9 || std::abs(min) > 9) {
//        width++;
//    }
//    if (max > 99 || std::abs(min) > 99) {
//        width++;
//    }
//    if (max > 999 || std::abs(min) > 999) {
//        width++;
//    }
//    if (max > 9999 || std::abs(min) > 9999) {
//        width++;
//    }
//    if (max > 99999 || std::abs(min) > 99999) {
//        width++;
//    }
//
//    if (min < 0) {
//        width++;
//    }
//
//    std::cout << "[" << std::setfill(' ') << std::setw(width) << m.data[0];
//    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[1];
//    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[2];
//    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[3];
//    std::cout << ",\n";
//
//    std::cout << std::setfill(' ') << std::setw(width + 1) << m.data[4];
//    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[5];
//    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[6];
//    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[7];
//    std::cout << ",\n";
//
//    std::cout << std::setfill(' ') << std::setw(width + 1) << m.data[8];
//    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[9];
//    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[10];
//    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[11];
//    std::cout << ",\n";
//
//    std::cout << std::setfill(' ') << std::setw(width + 1) << m.data[12];
//    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[13];
//    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[14];
//    std::cout << "," << std::setfill(' ') << std::setw(width) << m.data[15];
//    std::cout << "]\n";
//
//    return stream;
Pancake::Math::Matrix::Matrix(const Pancake::Math::Matrix& o) {
    memcpy(this->data, o.data, 16 * sizeof(float));
}

void Pancake::Math::Matrix::multiply(const Pancake::Math::Matrix& o) {

    Matrix m(*this);

    // first row
    m.data[0] = combineRowAndColumn(this->firstRow[0], o.firstColumn[0]);
    m.data[1] = combineRowAndColumn(this->firstRow[0], o.secondColumn[0]);
    m.data[2] = combineRowAndColumn(this->firstRow[0], o.thirdColumn[0]);
    m.data[3] = combineRowAndColumn(this->firstRow[0], o.fourthColumn[0]);

    // second row
    m.data[4] = combineRowAndColumn(this->secondRow[0], o.firstColumn[0]);
    m.data[5] = combineRowAndColumn(this->secondRow[0], o.secondColumn[0]);
    m.data[6] = combineRowAndColumn(this->secondRow[0], o.thirdColumn[0]);
    m.data[7] = combineRowAndColumn(this->secondRow[0], o.fourthColumn[0]);

    // third row
    m.data[8] = combineRowAndColumn(this->thirdRow[0], o.firstColumn[0]);
    m.data[9] = combineRowAndColumn(this->thirdRow[0], o.secondColumn[0]);
    m.data[10] = combineRowAndColumn(this->thirdRow[0], o.thirdColumn[0]);
    m.data[11] = combineRowAndColumn(this->thirdRow[0], o.fourthColumn[0]);

    // fourth row
    m.data[12] = combineRowAndColumn(this->fourthRow[0], o.firstColumn[0]);
    m.data[13] = combineRowAndColumn(this->fourthRow[0], o.secondColumn[0]);
    m.data[14] = combineRowAndColumn(this->fourthRow[0], o.thirdColumn[0]);
    m.data[15] = combineRowAndColumn(this->fourthRow[0], o.fourthColumn[0]);

    memcpy(this->data, m.data, 16 * sizeof(float));
}

Pancake::Math::Matrix Pancake::Math::Matrix::operator*(const Pancake::Math::Matrix& o) {
    Pancake::Math::Matrix m;

    // first row
    m.data[0] = combineRowAndColumn(this->firstRow[0], o.firstColumn[0]);
    m.data[1] = combineRowAndColumn(this->firstRow[0], o.secondColumn[0]);
    m.data[2] = combineRowAndColumn(this->firstRow[0], o.thirdColumn[0]);
    m.data[3] = combineRowAndColumn(this->firstRow[0], o.fourthColumn[0]);

    // second row
    m.data[4] = combineRowAndColumn(this->secondRow[0], o.firstColumn[0]);
    m.data[5] = combineRowAndColumn(this->secondRow[0], o.secondColumn[0]);
    m.data[6] = combineRowAndColumn(this->secondRow[0], o.thirdColumn[0]);
    m.data[7] = combineRowAndColumn(this->secondRow[0], o.fourthColumn[0]);

    // third row
    m.data[8] = combineRowAndColumn(this->thirdRow[0], o.firstColumn[0]);
    m.data[9] = combineRowAndColumn(this->thirdRow[0], o.secondColumn[0]);
    m.data[10] = combineRowAndColumn(this->thirdRow[0], o.thirdColumn[0]);
    m.data[11] = combineRowAndColumn(this->thirdRow[0], o.fourthColumn[0]);

    // fourth row
    m.data[12] = combineRowAndColumn(this->fourthRow[0], o.firstColumn[0]);
    m.data[13] = combineRowAndColumn(this->fourthRow[0], o.secondColumn[0]);
    m.data[14] = combineRowAndColumn(this->fourthRow[0], o.thirdColumn[0]);
    m.data[15] = combineRowAndColumn(this->fourthRow[0], o.fourthColumn[0]);

    return m;
}

void Pancake::Math::Matrix::loadIdentity() {
    float d[] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
    };
    memcpy(data, d, sizeof(float) * 16);

    firstRow[0] = &data[0];
    firstRow[1] = &data[1];
    firstRow[2] = &data[2];
    firstRow[3] = &data[3];

    secondRow[0] = &data[4];
    secondRow[1] = &data[5];
    secondRow[2] = &data[6];
    secondRow[3] = &data[7];

    thirdRow[0] = &data[8];
    thirdRow[1] = &data[9];
    thirdRow[2] = &data[10];
    thirdRow[3] = &data[11];

    fourthRow[0] = &data[12];
    fourthRow[1] = &data[13];
    fourthRow[2] = &data[14];
    fourthRow[3] = &data[15];

    firstColumn[0] = &data[0];
    firstColumn[1] = &data[4];
    firstColumn[2] = &data[8];
    firstColumn[3] = &data[12];

    secondColumn[0] = &data[1];
    secondColumn[1] = &data[5];
    secondColumn[2] = &data[9];
    secondColumn[3] = &data[13];

    thirdColumn[0] = &data[2];
    thirdColumn[1] = &data[6];
    thirdColumn[2] = &data[10];
    thirdColumn[3] = &data[14];

    fourthColumn[0] = &data[3];
    fourthColumn[1] = &data[7];
    fourthColumn[2] = &data[11];
    fourthColumn[3] = &data[15];
}

Pancake::Math::Matrix::~Matrix() {
//    if (data != nullptr) {
//        delete[] data;
//        data = nullptr;
//    }
}

Pancake::Math::Matrix::Matrix() {
//    data = new float[16];
    loadIdentity();
}
