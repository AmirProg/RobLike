#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include <ostream>
#include <cassert>

/***********************************************************************************************
*
* ~ Matrix<> class ~
*
* Manage a Matrix object, useful to linearize 2D array and vector
*
* For instance Matrix matrix<int>(x,y) creates an integer matrix with x lines and y rows
*
* -> In order to get an element located in (x,y), you can use matrix(x,y).
* You can also modify this memory case : matrix(x,y) = newValue
*
* Useful for linearization of 2D array/vector
*
************************************************************************************************/

template<typename T>
class Matrix {

public:
    Matrix(std::size_t lines, std::size_t rows) :
        lines_(lines),
        rows_(rows),
        data_(new T[lines_ * rows_])
    {}

    Matrix() : Matrix(0, 0)
    {}

    Matrix(const Matrix& matrix) : Matrix(matrix.lines_, matrix.rows_)
    {
        data_ = matrix.data_;
    }

    Matrix(Matrix&& matrix) noexcept = default;

    Matrix& operator=(const Matrix& matrix) {

        lines_ = matrix.lines_;
        rows_ = matrix.rows_;

        for(std::size_t i = 0; i < lines_ * rows_; ++i)
          data_[i] = matrix.data_[i];

        return *this;
    }

    Matrix& operator=(Matrix&& matrix) noexcept = default;

    ~Matrix() {

        delete[] data_; // Delete the pointer array
    }

    void resize(std::size_t lines, std::size_t rows) {

        lines_ = lines;
        rows_ = rows;
        data_ = new T[lines_ * rows_];
    }

    T const& operator()(std::size_t line, std::size_t row) const {

        assert((line < lines_ || row < rows_) && "Matrix out of bound");
        return data_[line * rows_ + row];
    }

    T& operator()(std::size_t line, std::size_t row) {

        assert((line < lines_ || row < rows_) && "Matrix out of bound");
        return data_[line * rows_ + row];
    }

    std::size_t getLines() const{
      return lines_;
    }

    std::size_t getRows() const{
      return rows_;
    }

    template<typename K>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<K>& m) noexcept { // Stream overloading -> std::cout << m;

        for (size_t i{}; i < m.lines_; i++) {
            for (size_t j{}; j < m.rows_; j++)
                os << m(i, j) << ' ';
            os << '\n';
        }

        return os;
    }

private:
    std::size_t lines_, rows_;
    T* data_;
};

#endif // MATRIX_HPP_INCLUDED
