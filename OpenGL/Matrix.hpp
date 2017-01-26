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
    
    
    
}

#endif /* Matrix_hpp */
