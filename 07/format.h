#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <string>

template <typename T>
std::string toString(const T& arg)
{
	std::stringstream ss;
	ss << arg;
	return ss.str();
}

// Вспомогательная функция для получения списка аргументов команды format
void argsToArray(std::vector<std::string>& arr, int idx);

template <typename T, typename... Args>
void argsToArray(std::vector<std::string>& arr, int idx, const T& head, const Args&... args)
{
	arr[idx] = toString(head);
	argsToArray(arr, idx + 1, args...);
}

template <typename ... Args>
std::string format(const std::string& format, const Args&... args)
{
	// Определяем количество аргументов
	size_t argsCount = sizeof...(args);
	// Получаем аргументы в виде массива строк
	std::vector<std::string> strs(argsCount);
	argsToArray(strs, 0, args...);

	// Результат подстановки
	std::string result;
	for (size_t i = 0; i < format.size(); i++)
	{
		if (format[i] == '{')
		{
			// Пытаемся выделить индекс аргумента
			size_t j = i + 1;
			std::string index;
			// Была ли пропущена закрывающая скобка
			bool missCloseBracket = false;
			// Корректен ли индекс
			bool badIndex = false;
			while (j < format.size() && format[j] != '}')
			{
				if (format[j] == '{')
				{
					// Если встретили открывающую скобку раньше закрывающей
					// (закрывающая скобка пропущена)
					missCloseBracket = true;
					break;
				}
				if (!isdigit(format[j]))
				{
					// Если символ не является цифрой - ошибка (индекс некорректен)
					badIndex = true;
					break;
				}
				else
					index += format[j];
				j++;
			}
			// Проверяем, что закрывающая скобка на месте
			if (missCloseBracket || j == format.size())
				throw std::runtime_error("Invalid format string: missing close bracket");

			// Проверяем, что индекс корректен (состоит из цифр и непустой)
			if (badIndex || j == i + 1)
				throw std::runtime_error("Invalid format string: incorrect index");

			// Проверяем, что индекс в нужном диапазоне
			int num = std::stoi(index);
			if (num >= argsCount)
				throw std::runtime_error("Extra arguments provided to format");

			result += strs[num];
			i = j;
		}
		else if (format[i] == '}')
			// Если встретили закрывающую скобку без парной открывающей
			throw std::runtime_error("Invalid format string: missing open bracket");
		else
			// Символы вне подстановок просто добавляем к результату без изменений
			result += format[i];
	}
	return result;
}
