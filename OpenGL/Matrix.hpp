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
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

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
    void addRow(Row<T> row);
    
    bool operator==(const Matrix<T> &matrix) const;
    bool operator!=(const Matrix<T> &matrix) const;
    Matrix operator+(const Matrix<T> &matrix) const;
    Matrix operator-(const Matrix<T> &matrix) const;
    Matrix operator*(const T scalar) const;
    Matrix operator*(const Matrix<T> &matrix) const;
};

/**
 *  Implementation
 */

template<typename T>
Matrix<T>::Matrix(){};

template<typename T>
Matrix<T>::Matrix(std::vector<Row<T>> _rows) : rows(_rows) {
    std::cout << "Construct: Matrix" << std::endl;
}

template<typename T>
Matrix<T>::~Matrix() {
    std::cout << "Destruct: Matrix" << std::endl;
}

template<typename T>
std::vector<Row<T>> Matrix<T>::getRows() const {
    return rows;
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
                    
                    T first = *a;
                    T second = b->items.at(i);
                    
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

#endif /* Matrix_hpp */
