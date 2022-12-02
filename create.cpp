#include <string>
#include <cstdlib>
#include "create.h"
#include "fileArray.h"

const size_t SIZE = 1000000000;

void create(const std::string& filename)
{
	FileArray array(filename, OUT);

	for (size_t i = 0; i < SIZE; ++i)
	{
		array.push((2 * (rand() % 2) - 1) * rand());
	}
}
