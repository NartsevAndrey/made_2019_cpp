#pragma once
#include<vector> 

// Вспомогательный прокси-класс для реализации [][]
class Row
{
public:
    friend class Matrix;
    Row();
    Row(size_t len);

    int& operator[](size_t index);
    const int& operator[] (size_t index) const;

private:
    size_t rowLength_;
    std::vector<int> row_;
};

class Matrix
{
public:
    Matrix();
    Matrix(size_t rowC, size_t colC);

    size_t getRows() const;
    size_t getColumns() const;

    Row& operator[](size_t index);
    const Row& operator[](size_t index) const;

    friend Matrix& operator*=(Matrix& left, int right);

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

private:
    size_t rowCount_;
    size_t colCount_;
    std::vector<Row> rows_;
};
