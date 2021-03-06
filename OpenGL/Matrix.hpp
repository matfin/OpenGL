//
//  Matrix.hpp
//  OpenGL
//
//  Created by Matt Finucane on 25/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <GLFW/glfw3.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include "VecMat.hpp"

/**
 *  Interface
 */
template<typename T>
struct Row {
    std::vector<T> items;
    
    Row() {};
    
    Row(std::vector<T> _items) {
        items = _items;
    }
    
    bool operator==(const Row &row) const {
        return items == row.items;
    }
};

template<class T>
class Matrix {
    
private:
    std::vector<Row<T>> rows;
    
public:
    Matrix();
    Matrix(std::vector<Row<T>> _rows);
    
    ~Matrix();
    
    std::vector<Row<T>> getRows() const;
    std::vector<T> unwind() const;
    void addRow(Row<T> row);
    void adjust(const int _row, const int _column, T value);
    T getValueAtIndex(int index);
    T getDeterminant(void);
    Matrix<T> inverse(void);
    std::string repr(void);
    
    bool operator==(const Matrix<T> &matrix) const;
    bool operator!=(const Matrix<T> &matrix) const;
    Matrix operator+(const Matrix<T> &matrix) const;
    Matrix operator+=(const Matrix<T> &matrix);
    Matrix operator-(const Matrix<T> &matrix) const;
    Matrix operator-=(const Matrix<T> &matrix);
    Matrix operator*(const T scalar) const;
    Matrix operator*=(const T scalar);
    Matrix operator*(const Matrix<T> &matrix) const;
    Matrix operator*=(const Matrix<T> &matrix);
};

/**
 *  Implementation
 */

template<typename T>
Matrix<T>::Matrix(){};

template<typename T>
Matrix<T>::Matrix(std::vector<Row<T>> _rows) : rows(_rows) {
//    std::cout << "Construct: Matrix" << std::endl;
}

template<typename T>
Matrix<T>::~Matrix() {
//    std::cout << "Destruct: Matrix" << std::endl;
}

template<typename T>
std::vector<Row<T>> Matrix<T>::getRows() const {
    return rows;
}

template<typename T>
std::vector<T> Matrix<T>::unwind() const {
    std::vector<T> result;
    for(const auto &row: rows) {
        for(const auto &item: row.items) {
            result.push_back(item);
        }
    }
    return result;
}

template<typename T>
void Matrix<T>::adjust(const int _row, const int _column, T value) {
    try {
        rows.at(_row).items.at(_column) = value;
    }
    catch(std::exception &e) {
        std::cout << "Adjustment failed for row: " << _row << ", column: " << _column << std::endl;
    }
}

template<typename T>
T Matrix<T>::getValueAtIndex(int index) {
    std::vector<T>unwound = unwind();
    return unwound.at(index);
}

template<typename T>
T Matrix<T>::getDeterminant(void) {
    return
        getValueAtIndex(12) * getValueAtIndex(9) * getValueAtIndex(6) * getValueAtIndex(3) -
        getValueAtIndex(8) * getValueAtIndex(13) * getValueAtIndex(6) * getValueAtIndex(3) -
        getValueAtIndex(12) * getValueAtIndex(5) * getValueAtIndex(10) * getValueAtIndex(3) +
        getValueAtIndex(4) * getValueAtIndex(13) * getValueAtIndex(10) * getValueAtIndex(3) +
    
        getValueAtIndex(8) * getValueAtIndex(5) * getValueAtIndex(14) * getValueAtIndex(3) -
        getValueAtIndex(4) * getValueAtIndex(9) * getValueAtIndex(14) * getValueAtIndex(3) -
        getValueAtIndex(12) * getValueAtIndex(9) * getValueAtIndex(2) * getValueAtIndex(7) +
        getValueAtIndex(8) * getValueAtIndex(13) * getValueAtIndex(2) * getValueAtIndex(7) +
    
        getValueAtIndex(12) * getValueAtIndex(1) * getValueAtIndex(10) * getValueAtIndex(7) -
        getValueAtIndex(0) * getValueAtIndex(13) * getValueAtIndex(10) * getValueAtIndex(7) -
        getValueAtIndex(8) * getValueAtIndex(1) * getValueAtIndex(14) * getValueAtIndex(7) +
        getValueAtIndex(0) * getValueAtIndex(9) * getValueAtIndex(14) * getValueAtIndex(7) +
    
        getValueAtIndex(12) * getValueAtIndex(5) * getValueAtIndex(2) * getValueAtIndex(11) -
        getValueAtIndex(4) * getValueAtIndex(13) * getValueAtIndex(2) * getValueAtIndex(11) -
        getValueAtIndex(12) * getValueAtIndex(1) * getValueAtIndex(6) * getValueAtIndex(11) +
        getValueAtIndex(0) * getValueAtIndex(13) * getValueAtIndex(6) * getValueAtIndex(11) +
    
        getValueAtIndex(4) * getValueAtIndex(1) * getValueAtIndex(14) * getValueAtIndex(11) -
        getValueAtIndex(0) * getValueAtIndex(5) * getValueAtIndex(14) * getValueAtIndex(11) -
        getValueAtIndex(8) * getValueAtIndex(5) * getValueAtIndex(2) * getValueAtIndex(15) +
        getValueAtIndex(4) * getValueAtIndex(9) * getValueAtIndex(2) * getValueAtIndex(15) +
    
        getValueAtIndex(8) * getValueAtIndex(1) * getValueAtIndex(6) * getValueAtIndex(15) -
        getValueAtIndex(0) * getValueAtIndex(9) * getValueAtIndex(6) * getValueAtIndex(15) -
        getValueAtIndex(4) * getValueAtIndex(1) * getValueAtIndex(10) * getValueAtIndex(15) +
        getValueAtIndex(0) * getValueAtIndex(5) * getValueAtIndex(10) * getValueAtIndex(15);
}

template<typename T>
Matrix<T> Matrix<T>::inverse(void) {
    /**
     *  Doing some checks to make sure the matrix is suitable.
     *  It needs to be a 4x4 matrix.
     */
    assert(rows.size() == 4);
    for(auto &row: rows) {
        assert(row.items.size() == 4);
    }
    
    Matrix<T> result;
    float det = getDeterminant();
    
    if(0.0f == det) {
        std::cout << "Warning: This matrix has no determinant so we cannot invert." << std::endl;
        return *this;
    }
    
    float inv_det = 1.0f / det;
    
    Row<T> row_1({
        inv_det * (
            getValueAtIndex(9) * getValueAtIndex(14) * getValueAtIndex(7) - getValueAtIndex(13) * getValueAtIndex(10) * getValueAtIndex(7) +
            getValueAtIndex(13) * getValueAtIndex(6) * getValueAtIndex(11) - getValueAtIndex(5) * getValueAtIndex(14) * getValueAtIndex(11) -
            getValueAtIndex(9) * getValueAtIndex(6) * getValueAtIndex(15) + getValueAtIndex(5) * getValueAtIndex(10) * getValueAtIndex(15)
        ),
        inv_det * (
            getValueAtIndex(13) * getValueAtIndex(10) * getValueAtIndex(3) - getValueAtIndex(9) * getValueAtIndex(14) * getValueAtIndex(3) -
            getValueAtIndex(13) * getValueAtIndex(2) * getValueAtIndex(11) + getValueAtIndex(1) * getValueAtIndex(14) * getValueAtIndex(11) +
            getValueAtIndex(9) * getValueAtIndex(2) * getValueAtIndex(15) - getValueAtIndex(1) * getValueAtIndex(10) * getValueAtIndex(15)
        ),
        inv_det * (
            getValueAtIndex(5) * getValueAtIndex(14) * getValueAtIndex(3) - getValueAtIndex(13) * getValueAtIndex(6) * getValueAtIndex(3) +
            getValueAtIndex(13) * getValueAtIndex(2) * getValueAtIndex(7) - getValueAtIndex(1) * getValueAtIndex(14) * getValueAtIndex(7) -
            getValueAtIndex(5) * getValueAtIndex(2) * getValueAtIndex(15) + getValueAtIndex(1) * getValueAtIndex(6) * getValueAtIndex(15)
        ),
        inv_det * (
            getValueAtIndex(9) * getValueAtIndex(6) * getValueAtIndex(3) - getValueAtIndex(5) * getValueAtIndex(10) * getValueAtIndex(3) -
            getValueAtIndex(9) * getValueAtIndex(2) * getValueAtIndex(7) + getValueAtIndex(1) * getValueAtIndex(10) * getValueAtIndex(7) +
            getValueAtIndex(5) * getValueAtIndex(2) * getValueAtIndex(11) - getValueAtIndex(1) * getValueAtIndex(6) * getValueAtIndex(11)
        )
    });
    
    Row<T> row_2({
        inv_det * (
            getValueAtIndex(12) * getValueAtIndex(10) * getValueAtIndex(7) - getValueAtIndex(8) * getValueAtIndex(14) * getValueAtIndex(7) -
            getValueAtIndex(12) * getValueAtIndex(6) * getValueAtIndex(11) + getValueAtIndex(4) * getValueAtIndex(14) * getValueAtIndex(11) +
            getValueAtIndex(8) * getValueAtIndex(6) * getValueAtIndex(15) - getValueAtIndex(4) * getValueAtIndex(10) * getValueAtIndex(15)
        ),
        inv_det * (
            getValueAtIndex(8) * getValueAtIndex(14) * getValueAtIndex(3) - getValueAtIndex(12) * getValueAtIndex(10) * getValueAtIndex(3) +
            getValueAtIndex(12) * getValueAtIndex(2) * getValueAtIndex(11) - getValueAtIndex(0) * getValueAtIndex(14) * getValueAtIndex(11) -
            getValueAtIndex(8) * getValueAtIndex(2) * getValueAtIndex(15) + getValueAtIndex(0) * getValueAtIndex(10) * getValueAtIndex(15)
        ),
        inv_det * (
            getValueAtIndex(12) * getValueAtIndex(6) * getValueAtIndex(3) - getValueAtIndex(4) * getValueAtIndex(14) * getValueAtIndex(3) -
            getValueAtIndex(12) * getValueAtIndex(2) * getValueAtIndex(7) + getValueAtIndex(0) * getValueAtIndex(14) * getValueAtIndex(7) +
            getValueAtIndex(4) * getValueAtIndex(2) * getValueAtIndex(15) - getValueAtIndex(0) * getValueAtIndex(6) * getValueAtIndex(15)
        ),
        inv_det * (
            getValueAtIndex(4) * getValueAtIndex(10) * getValueAtIndex(3) - getValueAtIndex(8) * getValueAtIndex(6) * getValueAtIndex(3) +
            getValueAtIndex(8) * getValueAtIndex(2) * getValueAtIndex(7) - getValueAtIndex(0) * getValueAtIndex(10) * getValueAtIndex(7) -
            getValueAtIndex(4) * getValueAtIndex(2) * getValueAtIndex(11) + getValueAtIndex(0) * getValueAtIndex(6) * getValueAtIndex(11)
        )
    });
    
    Row<T> row_3({
        inv_det * (
            getValueAtIndex(8) * getValueAtIndex(13) * getValueAtIndex(7) - getValueAtIndex(12) * getValueAtIndex(9) * getValueAtIndex(7) +
            getValueAtIndex(12) * getValueAtIndex(5) * getValueAtIndex(11) - getValueAtIndex(4) * getValueAtIndex(13) * getValueAtIndex(11) -
            getValueAtIndex(8) * getValueAtIndex(5) * getValueAtIndex(15) + getValueAtIndex(4) * getValueAtIndex(9) * getValueAtIndex(15)
        ),
        inv_det * (
            getValueAtIndex(12) * getValueAtIndex(9) * getValueAtIndex(3) - getValueAtIndex(8) * getValueAtIndex(13) * getValueAtIndex(3) -
            getValueAtIndex(12) * getValueAtIndex(1) * getValueAtIndex(11) + getValueAtIndex(0) * getValueAtIndex(13) * getValueAtIndex(11) +
            getValueAtIndex(8) * getValueAtIndex(1) * getValueAtIndex(15) - getValueAtIndex(0) * getValueAtIndex(9) * getValueAtIndex(15)
        ),
        inv_det * (
            getValueAtIndex(4) * getValueAtIndex(13) * getValueAtIndex(3) - getValueAtIndex(12) * getValueAtIndex(5) * getValueAtIndex(3) +
            getValueAtIndex(12) * getValueAtIndex(1) * getValueAtIndex(7) - getValueAtIndex(0) * getValueAtIndex(13) * getValueAtIndex(7) -
            getValueAtIndex(4) * getValueAtIndex(1) * getValueAtIndex(15) + getValueAtIndex(0) * getValueAtIndex(5) * getValueAtIndex(15)
        ),
        inv_det * (
            getValueAtIndex(8) * getValueAtIndex(5) * getValueAtIndex(3) - getValueAtIndex(4) * getValueAtIndex(9) * getValueAtIndex(3) -
            getValueAtIndex(8) * getValueAtIndex(1) * getValueAtIndex(7) + getValueAtIndex(0) * getValueAtIndex(9) * getValueAtIndex(7) +
            getValueAtIndex(4) * getValueAtIndex(1) * getValueAtIndex(11) - getValueAtIndex(0) * getValueAtIndex(5) * getValueAtIndex(11)
        )
    });
    
    Row<T> row_4({
        inv_det * (
            getValueAtIndex(12) * getValueAtIndex(9) * getValueAtIndex(6) - getValueAtIndex(8) * getValueAtIndex(13) * getValueAtIndex(6) -
            getValueAtIndex(12) * getValueAtIndex(5) * getValueAtIndex(10) + getValueAtIndex(4) * getValueAtIndex(13) * getValueAtIndex(10) +
            getValueAtIndex(8) * getValueAtIndex(5) * getValueAtIndex(14) - getValueAtIndex(4) * getValueAtIndex(9) * getValueAtIndex(14)
        ),
        inv_det * (
            getValueAtIndex(8) * getValueAtIndex(13) * getValueAtIndex(2) - getValueAtIndex(12) * getValueAtIndex(9) * getValueAtIndex(2) +
            getValueAtIndex(12) * getValueAtIndex(1) * getValueAtIndex(10) - getValueAtIndex(0) * getValueAtIndex(13) * getValueAtIndex(10) -
            getValueAtIndex(8) * getValueAtIndex(1) * getValueAtIndex(14) + getValueAtIndex(0) * getValueAtIndex(9) * getValueAtIndex(14)
        ),
        inv_det * (
            getValueAtIndex(12) * getValueAtIndex(5) * getValueAtIndex(2) - getValueAtIndex(4) * getValueAtIndex(13) * getValueAtIndex(2) -
            getValueAtIndex(12) * getValueAtIndex(1) * getValueAtIndex(6) + getValueAtIndex(0) * getValueAtIndex(13) * getValueAtIndex(6) +
            getValueAtIndex(4) * getValueAtIndex(1) * getValueAtIndex(14) - getValueAtIndex(0) * getValueAtIndex(5) * getValueAtIndex(14)
        ),
        inv_det * (
            getValueAtIndex(4) * getValueAtIndex(9) * getValueAtIndex(2) - getValueAtIndex(8) * getValueAtIndex(5) * getValueAtIndex(2) +
            getValueAtIndex(8) * getValueAtIndex(1) * getValueAtIndex(6) - getValueAtIndex(0) * getValueAtIndex(9) * getValueAtIndex(6) -
            getValueAtIndex(4) * getValueAtIndex(1) * getValueAtIndex(10) + getValueAtIndex(0) * getValueAtIndex(5) * getValueAtIndex(10)
        )
    });
    
    result.addRow(row_1);
    result.addRow(row_2);
    result.addRow(row_3);
    result.addRow(row_4);
    
    return result;
}

template<typename T>
std::string Matrix<T>::repr(void) {
    std::stringstream oss;
    for(auto &row : rows) {
        for(auto &item : row.items) {
            oss << item << ",";
        }
    }
    return oss.str();
}

template<typename T>
void Matrix<T>::addRow(Row<T> row) {
    rows.push_back(row);
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> &matrix) const {
    return rows == matrix.rows;
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix<T> &matrix) const {
    return rows != matrix.rows;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &matrix) const {
    /**
     *  For addition/subtraction, the number of 
     *  rows must be the same.
     */
    assert(rows.size() == matrix.rows.size());
    
    /**
     *  Teeing up the new Matrix we will return.
     */
    Matrix<T> m;
    
    /**
     *  The numner of columns should also be the same
     *  and the assertion should fail if they are not.
     */
    auto a = begin(rows);
    auto b = begin(matrix.rows);
    for(; a != end(rows) && b != end(matrix.rows); ++a, ++b) {
        assert(a->items.size() == b->items.size());
        
        auto c = begin(a->items);
        auto d = begin(b->items);
        Row<T> row;
        
        for(; c != end(a->items) && d != end(b->items); ++c, ++d) {
            row.items.push_back(*c + *d);
        }
        
        m.addRow(row);
    }

    return m;
}

template<typename T>
Matrix<T> Matrix<T>::operator+=(const Matrix<T> &matrix) {
    /**
     *  For addition/subtraction, the number of
     *  rows must be the same.
     */
    assert(rows.size() == matrix.rows.size());
    
    /**
     *  The numner of columns should also be the same
     *  and the assertion should fail if they are not.
     */
    auto a = begin(rows);
    auto b = begin(matrix.rows);
    for(; a != end(rows) && b != end(matrix.rows); ++a, ++b) {
        assert(a->items.size() == b->items.size());
        
        auto c = begin(a->items);
        auto d = begin(b->items);
        
        for(; c != end(a->items) && d != end(b->items); ++c, ++d) {
            *c += *d;
        }
    }
    
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &matrix) const {
    
    assert(rows.size() == matrix.rows.size());
    Matrix<T> m;
    
    auto a = begin(rows);
    auto b = begin(matrix.rows);
    for(; a != end(rows) && b != end(matrix.rows); ++a, ++b) {
        assert(a->items.size() == b->items.size());
        
        auto c = begin(a->items);
        auto d = begin(b->items);
        Row<T> row;
        
        for(; c != end(a->items) && d != end(b->items); ++c, ++d) {
            row.items.push_back(*c - *d);
        }
        
        m.addRow(row);
    }
    
    return m;
}

template<typename T>
Matrix<T> Matrix<T>::operator-=(const Matrix<T> &matrix) {
    
    assert(rows.size() == matrix.rows.size());
    
    auto a = begin(rows);
    auto b = begin(matrix.rows);
    for(; a != end(rows) && b != end(matrix.rows); ++a, ++b) {
        assert(a->items.size() == b->items.size());
        
        auto c = begin(a->items);
        auto d = begin(b->items);
        
        for(; c != end(a->items) && d != end(b->items); ++c, ++d) {
            *c -= *d;
        }
    }
    
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T scalar) const {
    
    Matrix<T> m;
    
    for(auto &row: rows) {
        Row<T> m_row;
        for(auto &value: row.items) {
            m_row.items.push_back(value * scalar);
        }
        m.addRow(m_row);
    }
    
    return m;
}

template<typename T>
Matrix<T> Matrix<T>::operator*=(const T scalar) {
    
    for(auto &row: rows) {
        for(auto &value: row.items) {
            value *= scalar;
        }
    }
    
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix) const {
    
    /**
     *  When multiplying matrices, the number of rows in
     *  the second matrix must be equal to the number of 
     *  columns in the first matrix. Here, we get the number
     *  of rows in the second matrix.
     */
    int matrix_row_size = matrix.rows.size();
    
    /**
     *  We then run through each row of the first matrix to ensure 
     *  that the size of the items in each row is eqaul to the size 
     *  of the rows in the second matrix.
     *
     *  If one of the sizes doesn't match, then we don't have a valid
     *  matrix we can multiply.
     */
    bool row_column_match = std::all_of(begin(rows), end(rows), [matrix_row_size](Row<T> row) {
        return row.items.size() == matrix_row_size;
    });
    
    /**
     *  This assert will fail if the matrix is not valid.
     */
    assert(row_column_match);
    
    Matrix<T> m;
    
    for(const auto &row: rows) {
        
        try {
            
            Row<T> m_row;
            for(int i = 0; i < matrix.rows.at(0).items.size(); i++) {
                
                auto a = begin(row.items);
                auto a_end = end(row.items);
                std::vector<Row<T>> matrix_rows = matrix.getRows();
                auto b = begin(matrix_rows);
                auto b_end = end(matrix_rows);
                
                T product = 0;
                for(; a != a_end && b != b_end; ++a, ++b) {
                    product += *(a) * b->items.at(i);
                }
                m_row.items.push_back(product);
            }
            
            m.addRow(m_row);
        }
        catch(std::exception &e) {
            std::cout << "Error in vector multiplication: " <<  e.what() << std::endl;
            return *this;
        }
    }

    return m;
}

template<typename T>
Matrix<T> Matrix<T>::operator*=(const Matrix<T> &matrix) {
    
    int matrix_row_size = matrix.rows.size();
    
    bool row_column_match = std::all_of(begin(rows), end(rows), [matrix_row_size](Row<T> row) {
        return row.items.size() == matrix_row_size;
    });
    
    assert(row_column_match);
    
    for(auto &row: rows) {
        try {
            
            Row<T> m_row;
            
            for(int i = 0; i < matrix.rows.at(0).items.size(); i++) {
                std::vector<Row<T>> matrix_rows = matrix.getRows();
                T product = 0;
                auto b = begin(matrix_rows);
                
                for(auto a = begin(row.items); a != end(row.items); a++) {
                    T first = *a;
                    T second = b->items.at(i);
                    product += first * second;
                    b++;
                }
                m_row.items.push_back(product);
            }
            
            row = m_row;
        }
        catch(std::exception &e) {
            std::cout << "Error in vector multiplication: " <<  e.what() << std::endl;
            return *this;
        }
    }
    
    return *this;
}

#endif /* Matrix_hpp */
