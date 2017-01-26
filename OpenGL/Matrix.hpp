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
    Matrix(std::vector<Row<T>> _rows);
    
    ~Matrix();
    
    std::vector<Row<T>> getRows();
    
    bool operator==(const Matrix<T> &matrix) const;
    bool operator!=(const Matrix<T> &matrix) const;
    Matrix operator+(const Matrix<T> &matrix) const;
    Matrix operator-(const Matrix<T> &matrix) const;
    Matrix operator*(const Matrix<T> &matrix) const;
};

/**
 *  Implementation
 */
template<typename T>
Matrix<T>::Matrix(std::vector<Row<T>> _rows) : rows(_rows) {
    std::cout << "Construct: Matrix" << std::endl;
}

template<typename T>
Matrix<T>::~Matrix() {
    std::cout << "Destruct: Matrix" << std::endl;
}

template<typename T>
std::vector<Row<T>> Matrix<T>::getRows() {
    return rows;
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
    assert(rows.size() == matrix.rows.size());
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &matrix) const {
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix) const {
    return *this;
}

#endif /* Matrix_hpp */
