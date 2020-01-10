#include <vector>
#include <stdexcept>
#include "matrix.h"

void indexValidation(size_t index, size_t max)
{
    if (index < 0 || index >= max)
        throw std::out_of_range("");
}

Row::Row() : rowLength_(0), row_(std::vector<int>())
{
}

Row::Row(size_t len) : rowLength_(len), row_(std::vector<int>(len))
{
}

int& Row::operator[](size_t index)
{
    indexValidation(index, rowLength_);
    return row_[index];
}

const int& Row::operator[](size_t index) const
{
    indexValidation(index, rowLength_);
    return row_[index];
}

Matrix::Matrix() : rowCount_(0), colCount_(0), rows_(std::vector<Row>())
{
}

Matrix::Matrix(size_t rowC, size_t colC)
    : rowCount_(rowC), colCount_(colC), rows_(std::vector<Row>(rowCount_))
{
    for (int i = 0; i < rowCount_; i++)
        rows_[i] = Row(colCount_);
}

size_t Matrix::getRows() const
{
    return rowCount_;
}

size_t Matrix::getColumns() const
{
    return colCount_;
}

Row& Matrix::operator[](size_t index)
{
    indexValidation(index, rowCount_);
    return rows_[index];
}

const Row& Matrix::operator[](size_t index) const
{
    indexValidation(index, rowCount_);
    return rows_[index];
}

Matrix& operator*=(Matrix& left, int right)
{
    for (int i = 0; i < left.rowCount_; i++)
        for (int j = 0; j < left.colCount_; j++)
            left.rows_[i][j] *= right;
    return left;
}

bool Matrix::operator==(const Matrix& other) const
{
    if (this == &other)
        return true;

    if (rowCount_ != other.rowCount_ || colCount_ != other.colCount_)
        return false;

    for (int i = 0; i < rowCount_; i++)
        for (int j = 0; j < colCount_; j++)
            if (rows_[i][j] != other.rows_[i][j])
                return false;
    return true;
}

bool Matrix::operator!=(const Matrix& other) const
{
    return !(*this == other);
}
