
#pragma once

constexpr int ExceptionBufferSize = 2048;

class Exception
{
public:
	Exception() { };
	Exception(int line, const char* pFunction, const char* pText);

	inline auto GetLine() const { return _line; }
	inline auto GetFunction() const { return _function; }
	inline auto GetText() const { return _text; }

protected:

	int		_line = 0;
	char	_function[ExceptionBufferSize]{};
	char	_text[ExceptionBufferSize]{};
};

class ExceptionVA : public Exception
{
public:
	ExceptionVA(int line, const char* pFunction, const char* pFormat, ...);
};

#define THROW_EXCEPTION(text)			throw Exception(__LINE__, __FUNCTION__, text)
#define THROW_EXCEPTION_VA(text, ...)	throw ExceptionVA(__LINE__, __FUNCTION__, text, __VA_ARGS__)
