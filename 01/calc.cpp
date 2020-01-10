#include <iostream>
#include <string>
#include <stdexcept>
#include "calc.h"

// Вычисление значения выражения
int Calculator::calculate(const std::string& expr)
{
    // Очищаем строку от пробелов
    std::string exprWithoutSpaces = eraseSpaces(expr);

    // Начинаем вычисления выражения (т.к. изначально выражение может содержать
    // все допустимые операции, начинаем парсить как exprAS)
    auto parseExprAS = exprAS(exprWithoutSpaces, 0, 0, 0, '+');

    // Если выражение было полностью вычислено, возвращаем результат
    if (parseExprAS.first == exprWithoutSpaces.size())
    {
        return parseExprAS.second;
    }
    // Иначе выражение некорректно
    throw std::runtime_error("Invalid input");
}

// exprAS - выражение, которое возможно содержит все допускаемые операции
// (Реализация правил 1, 2, 3)
std::pair<size_t, int> Calculator::exprAS(const std::string& expr, size_t pos,
    size_t prevLength, int prevValue, char prevOp)
{
    auto parseExprMD = exprMD(expr, pos, 0, 1, '*');
    if (!parseExprMD.first)
    {
        return std::make_pair(prevLength, prevValue);
    }

    size_t newPos = pos + parseExprMD.first;
    for (char op : {'+', '-'})
    {
        if (newPos < expr.size() && expr[newPos] == op)
        {
            return exprAS(expr, newPos + 1, prevLength + parseExprMD.first + 1,
                evalOperator(prevValue, parseExprMD.second, prevOp), op);
        }
    }

    return std::make_pair(prevLength + parseExprMD.first,
        evalOperator(prevValue, parseExprMD.second, prevOp));
}

// exprMD - выражение, которое возможно содержит операции *, / и - (унарный)
// (Реализация правил 4, 5, 6)
std::pair<size_t, int> Calculator::exprMD(const std::string& expr, size_t pos,
    size_t prevLength, int prevValue, char prevOp)
{
    auto parsePrime = prime(expr, pos);
    if (!parsePrime.first)
    {
        return std::make_pair(prevLength, prevValue);
    }

    size_t newPos = pos + parsePrime.first;
    for (char op : {'*', '/'})
    {
        if (newPos < expr.size() && expr[newPos] == op)
        {
            return exprMD(expr, newPos + 1, prevLength + parsePrime.first + 1,
                evalOperator(prevValue, parsePrime.second, prevOp), op);
        }
    }

    return std::make_pair(prevLength + parsePrime.first,
        evalOperator(prevValue, parsePrime.second, prevOp));
}

// prime - выражение, которое возможно содержит унарный минус
// (Реализация правил 8, 9)
std::pair<size_t, int> Calculator::prime(const std::string& expr, size_t pos)
{
    // Все минусы, стоящие впереди числа, рассматриваем как унарные
    if (pos < expr.size() && expr[pos] == '-')
    {
        auto parsePrime = prime(expr, pos + 1);
        if (!parsePrime.first)
        {
            return std::make_pair(0, 0);
        }
        return std::make_pair(parsePrime.first + 1, -parsePrime.second);
    }
    // Если минуса нет, то дальше должно стоять целое число
    return integer(expr, pos);
}

// Считывание числа из выражения expr, начиная с позиции pos
std::pair<size_t, int> Calculator::integer(const std::string& expr, size_t pos)
{
    int value = 0;
    size_t newPos = pos;
    while (newPos < expr.size() && isdigit(expr[newPos]))
    {
        value = 10 * value + int(expr[newPos] - '0');
        newPos++;
    }
    // Если симовол, стоящий на позиции pos, не является цифрой,
    // то выражение некорректно
    if (pos == newPos)
    {
        throw std::runtime_error("Invalid input");
    }
    return std::make_pair(newPos - pos, value);
}

// Примерного бинарного оператора к операндам
int Calculator::evalOperator(int x, int y, char op)
{
    switch (op)
    {
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '*':
        return x * y;
    case '/':
        if (y == 0)
        {
            throw std::runtime_error("Division by zero");
        }
        return x / y;
    default:
        throw std::runtime_error("Unknown operator");
    }
}

// Вспомогательный метод для удаления пробелов из строки
std::string Calculator::eraseSpaces(const std::string& str)
{
    std::string res;
    for (char c : str)
    {
        if (!isspace(c))
        {
            res += c;
        }
    }
    return res;
}
