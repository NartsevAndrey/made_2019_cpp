#include <stdexcept>
#include "allocator.h"

LinearAllocator::LinearAllocator(size_t maxSize)
{
    // Попытка аллокации блока нулевого размера
    if (maxSize == 0)
    {
        throw std::runtime_error("Attempt to select a zero-size block");
    }

    buffer_ = static_cast<char*>(malloc(maxSize));
    // Если malloc вернул nullptr - malloc не смог выделить память
    if (buffer_ == nullptr)
    {
        throw std::runtime_error("Failed to allocate memory");
    }

    size_ = maxSize;
    offset_ = 0;
}

LinearAllocator::~LinearAllocator()
{
    std::free(buffer_);
}

// Возвращает указатель на блок запрошенного размера
// или nullptr, если места недостаточно
char* LinearAllocator::alloc(size_t size)
{
    // Если требуется выделить блок нулевого размера
    if (size == 0)
    {
        return nullptr;
    }

    // Вычисляем новое смещение относительно начала зарезервированного блока
    size_t newOffset = offset_ + size;

    // Проверяем, достаточно ли места
    if (newOffset > size_)
    {
        return nullptr;
    }

    // Обновляем смещение
    size_t prevOffset = offset_;
    offset_ = newOffset;

    // Возвращаем указатель на блок запрошенного размера
    return (buffer_ + prevOffset);
}

// Позволяет использовать память аллокатора снова
void LinearAllocator::reset()
{
    // Обнуляем смещение
    offset_ = 0;
}
