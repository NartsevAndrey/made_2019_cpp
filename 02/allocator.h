#pragma once

// Аллокатор со стратегией линейного выделения памяти
class LinearAllocator
{
public:
    LinearAllocator(size_t maxSize);
    ~LinearAllocator();

    char* alloc(size_t size);
    void reset();

private:
    // Выделенный блок памяти
    char* buffer_;
    // Размер выделенного блока памяти
    size_t size_;
    // Смещение относительно начала выделенного блока
    // (указывает на первый свободный байт)
    size_t offset_;
};
