#include <iostream>
#include <string>
#include <vector>
#include "parser.h"

Parser::Parser()
    : callbackBefore_(nullptr), callbackAfter_(nullptr)
    , callbackInt_(nullptr), callbackString_(nullptr)
{
}

Parser::Parser(CallbackBefore before, CallbackAfter after)
    : callbackBefore_(before), callbackAfter_(after)
    , callbackInt_(nullptr), callbackString_(nullptr)
{
}

Parser::Parser(CallbackBefore before, CallbackAfter after,
    Callback callbackInt, Callback callbackString)
    : callbackBefore_(before), callbackAfter_(after)
    , callbackInt_(callbackInt), callbackString_(callbackString)
{
}

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
std::vector<std::string> Parser::parse(const std::string& expr,
    CallbackBefore callbackBefore, CallbackAfter callbackAfter,
    Callback callbackInt, Callback callbackString)
{
    std::string s = (callbackBefore == nullptr ? expr : callbackBefore(expr));

    std::vector<std::string> resultOfParsing;
    for (size_t i = 0; i < s.size(); )
    {
        if (isspace(s[i]))
        {
            i++;
            continue;
        }
        
        std::string str;
        bool isInt = true;
        while (i < s.size() && !isspace(s[i]))
        {
            isInt = isInt && isdigit(s[i]);
            str += s[i++];
        }

        if (isInt)
            call(callbackInt, str);
        else
            call(callbackString, str);

        resultOfParsing.push_back(str);
    }

    if (callbackAfter != nullptr)
        callbackAfter(resultOfParsing);

    return resultOfParsing;
}

std::vector<std::string> Parser::parse(const std::string& expression)
{
    return parse(expression, callbackBefore_, callbackAfter_,
        callbackInt_, callbackString_);
}

std::vector<std::string> Parser::parse(const std::string& expression,
    Callback callbackInt, Callback callbackString)
{
    return parse(expression, callbackBefore_, callbackAfter_,
        callbackInt, callbackString);
}

void Parser::setCallbackBefore(CallbackBefore callback)
{
    callbackBefore_ = callback;
}

void Parser::setCallbackAfter(CallbackAfter callback)
{
    callbackAfter_ = callback;
}

void Parser::setCallbackInt(Callback callback)
{
    callbackInt_ = callback;
}

void Parser::setCallbackString(Callback callback)
{
    callbackString_ = callback;
}

void Parser::call(Callback callback, std::string& s)
{
    if (callback != nullptr)
        callback(s);
}
