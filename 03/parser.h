#pragma once

// Класс парсера
// Парсинг выглядит следующим образом:
// на вход подается строка s,
// к ней применяется колбек, вызываемый перед началом парсинга;
// строка (возможно измененная) разбивается на токены,
// для каждого токена определяется его тип и вызывается соответствующий колбек;
// к полученному списку токенов применяется колбек,
// вызываемый после окончания парсинга.
// Все регистрируемые колбеки (кроме CallbackBefore) могут изменять объект,
// который получают. CallbackBefore не изменяет исходную строку, а возвращает
// ее (возможно измененную) копию.
class Parser
{
public:
    // Синонимы для колбек-функций, вызываемых при выделении токенов
    // (получает токен, работает с ним с возможностью изменения)
    using Callback = void(*)(std::string& s);

    // Синоним для колбек-функции, вызываемой до начала парсинга строки
    // (получает исходую строку, выполняет некоторую предобработку (возможно),
    // возвращает строку (возможно измененную))
    using CallbackBefore = std::string(*)(const std::string& s);

    // Синоним для колбек-функции, вызываемой после окончания процесса парсинга
    // (получает список выделенных токенов и выполняет с ним некоторые действия)
    using CallbackAfter = void(*)(std::vector<std::string>& a);

    // Конструкторы
    Parser();
    Parser(CallbackBefore before, CallbackAfter after);
    Parser(CallbackBefore before, CallbackAfter after,
        Callback callbackInt, Callback callbackString);

    // Сеттеры для колбек-функций
    void setCallbackBefore(CallbackBefore callback);
    void setCallbackAfter(CallbackAfter callback);
    void setCallbackInt(Callback callback);
    void setCallbackString(Callback callback);

    // Парсинг токенов с колбек-функциями, указанными для класса (если они есть)
    std::vector<std::string> parse(const std::string& expression);

    // Парсинг токенов
    // (указываем колбеки при распознавании токенов для конкретного парсинга)
    std::vector<std::string> parse(const std::string& expression,
        Callback callbackInt, Callback callbackString);

    // Парсинг токенов
    // (все колбеки указаны для конкретного парсинга)
    std::vector<std::string> parse(const std::string& expression,
        CallbackBefore before, CallbackAfter after,
        Callback callbackInt, Callback callbackString);

private:
    // Указатели на колбеки (по умолчанию)
    CallbackBefore callbackBefore_;
    CallbackAfter callbackAfter_;
    Callback callbackInt_;
    Callback callbackString_;

    // Вспомогательный метод для применений колбека к строке (если он указан)
    void call(Callback callback, std::string& s);
};
