#pragma once

// Калькулятор, реализованный с помощью метода рекурсивного спуска.
// Поддерживаемые операции:
// умножение, деление, сложение, вычитание, унарный минус.
// Метод рекурсивного спуска пострен для следующей грамматики:
// множество нетерминальных символов = {exprAS, exprMD, prime, integer}, где
// exprAS - выражение, которое возможно содержит все допускаемые операции,
// exprMD - выражение, которое возможно содержит операции *, / и - (унарный),
// prime - выражение, которое возможно содержит унарный минус,
// integer - целое число;
// множество терминальных символов = {+, -, *, /, - (унарный), целые числа};
// стартовый символ грамматики = exprAS;
// правила грамматики:
// 1. exprAS -> exprMD + exprAS
// 2. exprAS -> exprMD - exprAS
// 3. exprAS -> exprMD
// 4. exprMD -> prime * exprMD
// 5. exprMD -> prime / exprMD
// 6. exprMD -> prime
// 7. prime -> -prime
// 8. prime -> integer
// Данная грамматика является грамматикой без левой рекурсии.
class Calculator
{
public:
    Calculator() = default;

    // Вычисление значения выражения
    int calculate(const std::string& expr);

private:
    // Непосредственная реализация метода рекурсивного спуска.
    // Каждый метод реализует соответствующее правило грамматики.
    // expr - исходное выражения для вычисления,
    // pos - номер позиции pos, с которой нужно рассматривать выражение
    // (считаем, что префикс[0, pos) уже рассмотрен).
    // Для корректного вычисления выражений, содержащих несколько
    // последовательных применений операций вычитания и деления
    // (например, exprMD - exprMD - exprAS или prime / prime / exprMD),
    // будем поддерживать:
    // prevLength - накопленная длина уже распознанного токена,
    // prevValue - предыдущее значение вычисления токена
    // prevOp - предыдущий оператор.
    // Возвращает пару <длина токена; вычисленное значение>.
    // Если токен не был обнаружен, вернет пару <0, 0>.
    std::pair<size_t, int> exprAS(const std::string& expr, size_t pos,
        size_t prevLength, int prevValue, char prevOp);
    std::pair<size_t, int> exprMD(const std::string& expr, size_t pos,
        size_t prevLength, int prevValue, char prevOp);
    std::pair<size_t, int> prime(const std::string& expr, size_t pos);
    std::pair<size_t, int> integer(const std::string& expr, size_t pos);

    // Применение бинарного оператора к операндам
    int evalOperator(int x, int y, char op);

    // Вспомогательный метод для удаления пробелов из строки
    std::string eraseSpaces(const std::string& str);
};
