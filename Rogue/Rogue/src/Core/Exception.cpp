
#include "Exception.h"

#include <stdio.h>	// For '_vsnprintf_s'
#include <stdarg.h>	// For 'va_start', 'va_end'
#include <cstring>  // For 'strncpy'

Exception::Exception(int line, const char* pFunction, const char* pText)
	: _line(line)
{
	strncpy_s(_function, pFunction, ExceptionBufferSize);
	strncpy_s(_text, pText, ExceptionBufferSize);
}

ExceptionVA::ExceptionVA(int line, const char* pFunction, const char* pFormat, ...)
{
	va_list args;
	va_start(args, pFormat);

	const size_t length = _vsnprintf_s(_text, sizeof(_text) - 1, pFormat, args);

	va_end(args);

	// Ensure null-termination of the string
	if (length > 0 && length < sizeof(_text))
		_text[length] = '\0';
	else
		_text[sizeof(_text) - 1] = '\0'; // Make sure the string is null-terminated in case of truncation or error

	_line = line;

	strncpy_s(_function, ExceptionBufferSize, pFunction, _TRUNCATE);
}
