#include <string>
#include <sstream>
#include "serializer.h"

Serializer::Serializer(std::ostream& out)
    : out_(out)
{
}

Error Serializer::toStream(bool val) {
	try {
		out_ << (val ? "true" : "false") << Separator;
	}
	catch (std::exception&) {
		return Error::CorruptedOutputStream;
	}
	return Error::NoError;
}

Error Serializer::toStream(uint64_t val) {
	try {
		out_ << std::to_string(val) << Separator;
	}
	catch (std::exception&) {
		return Error::CorruptedOutputStream;
	}
	return Error::NoError;
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

int Deserializer::argsCount(const std::string& s)
{
	std::string sub = s.substr(0, s.length() - 1);
	return stoi(sub);
}

Error Deserializer::argsDeserialize()
{
	return Error::NoError;
}
