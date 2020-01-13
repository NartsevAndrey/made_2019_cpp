#include <string>
#include <sstream>
#include "serializer.h"

Serializer::Serializer(std::ostream& out)
	: out_(out)
{
}

void Serializer::toStream(bool val)
{
	out_ << (val ? "true" : "false") << Separator;
}

void Serializer::toStream(uint64_t val)
{
	out_ << val << Separator;
}

Error Serializer::argsSerialize()
{
	return Error::NoError;
}

Deserializer::Deserializer(std::istream& in)
	: in_(in)
{
}

Error Deserializer::toValue(bool& value)
{
	std::string text;
	in_ >> text;

	if (text == "true")
		value = true;
	else if (text == "false")
		value = false;
	else
		return Error::CorruptedArchive;

	return Error::NoError;
}

Error Deserializer::toValue(uint64_t& value)
{
	std::string text;
	in_ >> text;

	try
	{
		value = std::stoull(text);
	}
	catch (std::exception&)
	{
		return Error::CorruptedArchive;
	}
	return Error::NoError;
}

Error Deserializer::argsDeserialize()
{
	return Error::NoError;
}
