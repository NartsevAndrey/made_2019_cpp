#pragma once

enum class Error
{
	NoError,
	CorruptedArchive,
	CorruptedOutputStream
};

class Serializer
{
public:
	explicit Serializer(std::ostream& out);

	template <class T>
	Error save(T& object);

	template <class... ArgsT>
	Error operator()(ArgsT... args);

private:
	static constexpr char Separator = ' ';
	std::ostream& out_;

	template <class... ArgsT>
	Error process(ArgsT... args);

	template <class T, class... ArgsT>
	Error argsSerialize(T head, ArgsT... args);

	Error argsSerialize();

	void toStream(bool val);
	void toStream(uint64_t val);
};

template <class T>
Error Serializer::save(T& object)
{
	return object.serialize(*this);
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT... args)
{
	return process(args...);
}

template <class... ArgsT>
Error Serializer::process(ArgsT... args)
{
	// В начале записываем количество полей структуры, подлежащих сериализации,
	// в поток (нужно, для проверки возможности десериализации в дальнейшем)
	int argsCount = sizeof...(args);
	out_ << argsCount << Separator;
	return argsSerialize(args...);
}

template <class T, class... ArgsT>
Error Serializer::argsSerialize(T head, ArgsT... args)
{
	toStream(head);
	return argsSerialize(args...);
}


class Deserializer
{
public:
	explicit Deserializer(std::istream& in);

	template <class T>
	Error load(T& object);

	template <class... ArgsT>
	Error operator()(ArgsT&... args);

private:
	std::istream& in_;

	template <class... ArgsT>
	Error process(ArgsT&... args);

	template <class T, class... ArgsT>
	Error argsDeserialize(T& head, ArgsT&... args);
	Error argsDeserialize();

	Error toValue(bool& value);
	Error toValue(uint64_t& value);
};

template <class T>
Error Deserializer::load(T& object)
{
	return object.serialize(*this);
}

template <class... ArgsT>
Error Deserializer::operator()(ArgsT&... args)
{
	return process(args...);
}

template <class... ArgsT>
Error Deserializer::process(ArgsT&... args)
{
	// Сначала считываем количество полей в сериализованной структуре
	// Если оно совпадает с числом полей в данной структуре, пытаемся выполнить
	// сериализации, иначе выполнение сериализации невозможно
	size_t argsCount;
	in_ >> argsCount;

	if (argsCount != sizeof...(args))
		return Error::CorruptedArchive;
	return argsDeserialize(args...);
}

template <class T, class... ArgsT>
Error Deserializer::argsDeserialize(T& head, ArgsT&... args)
{
	Error err = toValue(head);
	return err != Error::NoError ? err : argsDeserialize(args...);
}
