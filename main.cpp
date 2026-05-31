#include "Matrix.hpp"

int main() {
    Matrix<double> m1(3, 3, 1.1);
    Matrix<double> m2(3, 3, 5);
    Matrix<double> m3 = m1 + m2;
    
    std::cout << "Matrix + Matrix: \n";
    m3.print();

    std::cout << "Matrix * Scalar: \n";
    Matrix<double> m4 = m2 * 3;
    m4.print();

    std::cout << "Matrix * Matrix: \n";
    Matrix<double> m5 = m1 * m2;
    m5.print();

    std::cout << "Dot product: \n";
    Matrix<double> v1(1, 3, 1.5);
    Matrix<double> m6(3, 1, 4);
    std::cout << m6.dot(v1) << "\n";
    return 0;
}