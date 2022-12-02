#include "exception.h"

const char* EndOfFileException::what()const noexcept
{
	return "Attempting to read outside of a file!";
}
