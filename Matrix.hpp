#pragma once

// TODO : Logic for det() that can calculate any dimension without recursion, and build cross()
// Maybe dot() is too slow...

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class Matrix{
private:
    const int rows;
    const int cols;
    std::vector<std::vector<T>> value;

    bool isVector() const{ return rows == 1 || cols ==1; }
    
public:
    Matrix(int r, int c, T init_value = T())
    : rows(r), cols(c), value(r, std::vector<T>(c, init_value))
    {
        if (rows <= 0 || cols <= 0) {
            throw std::invalid_argument("Rows or Columns does not exist");
        }
    }

    // Matrix.operator+(Matrix)
    Matrix<T> operator+(const Matrix<T>& temp) const{
        if (this->rows != temp.rows || this->cols != temp.cols){
            throw std::invalid_argument("Columns ! = Rows");
        }

        Matrix<T> result(this->rows, this->cols);

        for (int i = 0; i < this->rows; ++i){
            for (int j = 0; j < this->cols; ++j){
                result.value[i][j] = this->value[i][j] + temp.value[i][j];
            }
        }
        
        return result;
    }

    // Matrix.operator*(Scalar)
    Matrix<T> operator*(T scalar) const{
        Matrix<T> result(this->rows, this->cols);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                result.value[i][j] = this->value[i][j] * scalar;
            }
        }
        return result;
    }

    // Matrix.operator*(Matrix)
    Matrix<T> operator*(const Matrix<T>& temp) const{
        
        if (this->cols != temp.rows){
            throw std::invalid_argument("Columns != Rows");
        }
        
        Matrix<T> result(this->rows, temp.cols, T());
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < temp.cols; ++j) {
                for (int k = 0; k < this->cols; ++k) {
                    result.value[i][j] += this->value[i][k] * temp.value[k][j];
                }
            }
        }
        return result;
    }

    // Transpose
    Matrix<T> transpose() const{
        Matrix<T> result(this->cols, this->rows);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                result.value[j][i] = this->value[i][j];
            }
        }
        return result;
    }

    // Dot product
    T dot(const Matrix<T>& temp) const{
        if (!this->isVector() || !temp.isVector()){
            throw std::logic_error("Dimension is Not in R^1");
        }
        
        Matrix<T> row_vec = (this->rows == 1) ? (*this) : this->transpose();
        Matrix<T> col_vec = (temp.cols == 1) ? temp : temp.transpose();
        // Guarantee (1*N) * (N*1)
        return (row_vec * col_vec).value[0][0];
    }
    
    // Projection
    Matrix<T> proj(const Matrix<T>& temp) const{
        return temp * (this->dot(temp) / temp.dot(temp));
    }

    // Determinent
    T det() const{
        if (rows != cols) throw std::logic_error("Not square");
        if (rows == 1) return value[0][0];
        if (rows == 2) return value[0][0] * value[1][1] - value[0][1] * value[1][0];
        // 3x3 추가할 것. 2x2를 빼서 재귀하면 속도 이슈 
        // iter로 짜자
    }

    // Cross product
    Matrix<T> cross(const Matrix<T>& temp) const{
        if (!this->isVector() || !temp.isVector()){
            throw std::logic_error("Not in R^1");
        }

        // det() 만들고 호출
    }
    
    // Basic Print
    void print() const{
        for (int i = 0; i < rows; ++i){
            for (int j = 0; j < cols; ++j){
                std::cout << value[i][j] << "  ";
            }
            std::cout << "\n";
        }
    }
};